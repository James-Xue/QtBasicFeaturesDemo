// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QTEXTDOCUMENTFRAGMENT_P_H
#define QTEXTDOCUMENTFRAGMENT_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtGui/private/qtguiglobal_p.h>
#include "QtGui/qtextdocument.h"
#include "private/qtexthtmlparser_p.h"
#include "private/qtextdocument_p.h"
#include "QtGui/qtexttable.h"
#include "QtCore/qatomic.h"
#include "QtCore/qlist.h"
#include "QtCore/qmap.h"
#include "QtCore/qpointer.h"
#include "QtCore/qvarlengtharray.h"
#include "QtCore/qdatastream.h"

QT_BEGIN_NAMESPACE

class QTextDocumentFragmentPrivate;

class QTextCopyHelper
{
public:
    QTextCopyHelper(const QTextCursor &_source, const QTextCursor &_destination, bool forceCharFormat = false, const QTextCharFormat &fmt = QTextCharFormat());

    void copy();

private:
    void appendFragments(int pos, int endPos);
    int appendFragment(int pos, int endPos, int objectIndex = -1);
    int convertFormatIndex(const QTextFormat &oldFormat, int objectIndexToSet = -1);
    inline int convertFormatIndex(int oldFormatIndex, int objectIndexToSet = -1)
    { return convertFormatIndex(src->formatCollection()->format(oldFormatIndex), objectIndexToSet); }
    inline QTextFormat convertFormat(const QTextFormat &fmt)
    { return dst->formatCollection()->format(convertFormatIndex(fmt)); }

    int insertPos;

    bool forceCharFormat;
    int primaryCharFormatIndex;

    QTextCursor cursor;
    QTextDocumentPrivate *dst;
    QTextDocumentPrivate *src;
    QTextFormatCollection &formatCollection;
    const QString originalText;
    QMap<int, int> objectIndexMap;
};

class QTextDocumentFragmentPrivate
{
public:
    QTextDocumentFragmentPrivate(const QTextCursor &cursor = QTextCursor());
    inline ~QTextDocumentFragmentPrivate() { delete doc; }

    void insert(QTextCursor &cursor) const;

    QAtomicInt ref;
    QTextDocument *doc;

    uint importedFromPlainText : 1;
private:
    Q_DISABLE_COPY_MOVE(QTextDocumentFragmentPrivate)
};

#ifndef QT_NO_TEXTHTMLPARSER

class QTextHtmlImporter : public QTextHtmlParser
{
    struct Table;
public:
    enum ImportMode {
        ImportToFragment,
        ImportToDocument
    };

    QTextHtmlImporter(QTextDocument *_doc, const QString &html,
                      ImportMode mode,
                      const QTextDocument *resourceProvider = nullptr);

    void import();

private:
    bool closeTag();

    Table scanTable(int tableNodeIdx);

    enum ProcessNodeResult { ContinueWithNextNode, ContinueWithCurrentNode, ContinueWithNextSibling };

    void appendBlock(const QTextBlockFormat &format, QTextCharFormat charFmt = QTextCharFormat());
    bool appendNodeText();

    ProcessNodeResult processBlockNode();
    ProcessNodeResult processSpecialNodes();

    struct List
    {
        inline List() : listNode(0) {}
        QTextListFormat format;
        int listNode;
        QPointer<QTextList> list;
    };
    friend class QTypeInfo<List>;
    QList<List> lists;
    int indent;
    int headingLevel;

    // insert a named anchor the next time we emit a char format,
    // either in a block or in regular text
    QStringList namedAnchors;

#ifdef Q_CC_SUN
    friend struct QTextHtmlImporter::Table;
#endif
    struct TableCellIterator
    {
        inline TableCellIterator(QTextTable *t = nullptr) : table(t), row(0), column(0) {}

        inline TableCellIterator &operator++() {
            if (atEnd())
                return *this;
            do {
                const QTextTableCell cell = table->cellAt(row, column);
                if (!cell.isValid())
                    break;
                column += cell.columnSpan();
                if (column >= table->columns()) {
                    column = 0;
                    ++row;
                }
            } while (row < table->rows() && table->cellAt(row, column).row() != row);

            return *this;
        }

        inline bool atEnd() const { return table == nullptr || row >= table->rows(); }

        QTextTableCell cell() const { return table->cellAt(row, column); }

        QTextTable *table;
        int row;
        int column;
    };
    friend class QTypeInfo<TableCellIterator>;

    friend struct Table;
    struct Table
    {
        Table() : isTextFrame(false), rows(0), columns(0), currentRow(0), lastIndent(0) {}
        QPointer<QTextFrame> frame;
        bool isTextFrame;
        int rows;
        int columns;
        int currentRow; // ... for buggy html (see html_skipCell testcase)
        TableCellIterator currentCell;
        int lastIndent;
    };
    friend class QTypeInfo<Table>;
    QList<Table> tables;

    struct RowColSpanInfo
    {
        int row, col;
        int rowSpan, colSpan;
    };
    friend class QTypeInfo<RowColSpanInfo>;

    enum WhiteSpace
    {
        RemoveWhiteSpace,
        CollapseWhiteSpace,
        PreserveWhiteSpace
    };

    WhiteSpace compressNextWhitespace;

    QTextDocument *doc;
    QTextCursor cursor;
    QTextHtmlParserNode::WhiteSpaceMode wsm;
    ImportMode importMode;
    bool hasBlock;
    bool forceBlockMerging;
    bool blockTagClosed;
    int currentNodeIdx;
    const QTextHtmlParserNode *currentNode;
};
Q_DECLARE_TYPEINFO(QTextHtmlImporter::List, Q_RELOCATABLE_TYPE);
Q_DECLARE_TYPEINFO(QTextHtmlImporter::TableCellIterator, Q_PRIMITIVE_TYPE);
Q_DECLARE_TYPEINFO(QTextHtmlImporter::Table, Q_RELOCATABLE_TYPE);
Q_DECLARE_TYPEINFO(QTextHtmlImporter::RowColSpanInfo, Q_PRIMITIVE_TYPE);

QT_END_NAMESPACE
#endif // QT_NO_TEXTHTMLPARSER

#endif // QTEXTDOCUMENTFRAGMENT_P_H
