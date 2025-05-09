// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QDRAWUTIL_H
#define QDRAWUTIL_H

#include <QtWidgets/qtwidgetsglobal.h>
#include <QtCore/qnamespace.h>
#include <QtCore/qstring.h> // char*->QString conversion
#include <QtCore/qmargins.h>
#include <QtGui/qpixmap.h>
QT_BEGIN_NAMESPACE


class QPainter;
class QPalette;
class QPoint;
class QColor;
class QBrush;
class QRect;

//
// Standard shade drawing
//

Q_WIDGETS_EXPORT void qDrawShadeLine(QPainter *p, int x1, int y1, int x2, int y2,
                              const QPalette &pal, bool sunken = true,
                              int lineWidth = 1, int midLineWidth = 0);

Q_WIDGETS_EXPORT void qDrawShadeLine(QPainter *p, const QPoint &p1, const QPoint &p2,
                              const QPalette &pal, bool sunken = true,
                              int lineWidth = 1, int midLineWidth = 0);

Q_WIDGETS_EXPORT void qDrawShadeRect(QPainter *p, int x, int y, int w, int h,
                              const QPalette &pal, bool sunken = false,
                              int lineWidth = 1, int midLineWidth = 0,
                              const QBrush *fill = nullptr);

Q_WIDGETS_EXPORT void qDrawShadeRect(QPainter *p, const QRect &r,
                              const QPalette &pal, bool sunken = false,
                              int lineWidth = 1, int midLineWidth = 0,
                              const QBrush *fill = nullptr);

Q_WIDGETS_EXPORT void qDrawShadePanel(QPainter *p, int x, int y, int w, int h,
                               const QPalette &pal, bool sunken = false,
                               int lineWidth = 1, const QBrush *fill = nullptr);

Q_WIDGETS_EXPORT void qDrawShadePanel(QPainter *p, const QRect &r,
                               const QPalette &pal, bool sunken = false,
                               int lineWidth = 1, const QBrush *fill = nullptr);

Q_WIDGETS_EXPORT void qDrawWinButton(QPainter *p, int x, int y, int w, int h,
                              const QPalette &pal, bool sunken = false,
                              const QBrush *fill = nullptr);

Q_WIDGETS_EXPORT void qDrawWinButton(QPainter *p, const QRect &r,
                              const QPalette &pal, bool sunken = false,
                              const QBrush *fill = nullptr);

Q_WIDGETS_EXPORT void qDrawWinPanel(QPainter *p, int x, int y, int w, int h,
                              const QPalette &pal, bool sunken = false,
                             const QBrush *fill = nullptr);

Q_WIDGETS_EXPORT void qDrawWinPanel(QPainter *p, const QRect &r,
                              const QPalette &pal, bool sunken = false,
                             const QBrush *fill = nullptr);

Q_WIDGETS_EXPORT void qDrawPlainRect(QPainter *p, int x, int y, int w, int h, const QColor &,
                              int lineWidth = 1, const QBrush *fill = nullptr);

Q_WIDGETS_EXPORT void qDrawPlainRect(QPainter *p, const QRect &r, const QColor &,
                              int lineWidth = 1, const QBrush *fill = nullptr);

Q_WIDGETS_EXPORT void qDrawPlainRoundedRect(QPainter *p, int x, int y, int w, int h,
                              qreal rx, qreal ry, const QColor &, int lineWidth = 1,
                              const QBrush *fill = nullptr);

inline void qDrawPlainRoundedRect(QPainter *painter, const QRect& rect, qreal rx, qreal ry,
                                  const QColor &lineColor, int lineWidth = 1,
                                  const QBrush *fill = nullptr)
{
    qDrawPlainRoundedRect(painter, rect.x(), rect.y(), rect.width(), rect.height(),
                          rx, ry, lineColor, lineWidth, fill);
}


struct QTileRules
{
    inline QTileRules(Qt::TileRule horizontalRule, Qt::TileRule verticalRule)
            : horizontal(horizontalRule), vertical(verticalRule) {}
    inline QTileRules(Qt::TileRule rule = Qt::StretchTile)
            : horizontal(rule), vertical(rule) {}
    Qt::TileRule horizontal;
    Qt::TileRule vertical;
};

#ifndef Q_QDOC
// For internal use only.
namespace QDrawBorderPixmap
{
    enum DrawingHint
    {
        OpaqueTopLeft = 0x0001,
        OpaqueTop = 0x0002,
        OpaqueTopRight = 0x0004,
        OpaqueLeft = 0x0008,
        OpaqueCenter = 0x0010,
        OpaqueRight = 0x0020,
        OpaqueBottomLeft = 0x0040,
        OpaqueBottom = 0x0080,
        OpaqueBottomRight = 0x0100,
        OpaqueCorners = OpaqueTopLeft | OpaqueTopRight | OpaqueBottomLeft | OpaqueBottomRight,
        OpaqueEdges = OpaqueTop | OpaqueLeft | OpaqueRight | OpaqueBottom,
        OpaqueFrame = OpaqueCorners | OpaqueEdges,
        OpaqueAll = OpaqueCenter | OpaqueFrame
    };

    Q_DECLARE_FLAGS(DrawingHints, DrawingHint)
}
#endif

Q_WIDGETS_EXPORT void qDrawBorderPixmap(QPainter *painter,
                                    const QRect &targetRect,
                                    const QMargins &targetMargins,
                                    const QPixmap &pixmap,
                                    const QRect &sourceRect,
                                    const QMargins &sourceMargins,
                                    const QTileRules &rules = QTileRules()
#ifndef Q_QDOC
                                    , QDrawBorderPixmap::DrawingHints hints = QDrawBorderPixmap::DrawingHints()
#endif
                                    );

inline void qDrawBorderPixmap(QPainter *painter,
                                           const QRect &target,
                                           const QMargins &margins,
                                           const QPixmap &pixmap)
{
    qDrawBorderPixmap(painter, target, margins, pixmap, pixmap.rect(), margins);
}

QT_END_NAMESPACE

#endif // QDRAWUTIL_H
