// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QSTYLESHEETSTYLE_P_H
#define QSTYLESHEETSTYLE_P_H

#include <QtWidgets/private/qtwidgetsglobal_p.h>
#include "private/qwindowsstyle_p.h"

#ifndef QT_NO_STYLE_STYLESHEET

#include "QtWidgets/qapplication.h"
#include "QtWidgets/qstyleoption.h"
#include "QtCore/qhash.h"
#include "QtCore/qlist.h"
#include "QtCore/qset.h"
#include "QtGui/qbrush.h"
#include "QtGui/qevent.h"
#include "private/qcssparser_p.h"

QT_BEGIN_NAMESPACE

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

class QRenderRule;
class QAbstractScrollArea;
class QStyleSheetStylePrivate;
class QStyleOptionTitleBar;

class Q_AUTOTEST_EXPORT QStyleSheetStyle : public QWindowsStyle
{
    typedef QWindowsStyle ParentStyle;

    Q_OBJECT
public:
    QStyleSheetStyle(QStyle *baseStyle);
    ~QStyleSheetStyle();

    void drawComplexControl(ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p,
                            const QWidget *w = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption *opt, QPainter *p,
                     const QWidget *w = nullptr) const override;
    void drawItemPixmap(QPainter *painter, const QRect &rect, int alignment, const QPixmap &pixmap) const override;
    void drawItemText(QPainter *painter, const QRect& rect, int alignment, const QPalette &pal,
              bool enabled, const QString& text, QPalette::ColorRole textRole  = QPalette::NoRole) const override;
    void drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p,
                       const QWidget *w = nullptr) const override;
    QPixmap generatedIconPixmap(QIcon::Mode iconMode, const QPixmap &pixmap,
                                const QStyleOption *option) const override;
    SubControl hitTestComplexControl(ComplexControl cc, const QStyleOptionComplex *opt,
                                     const QPoint &pt, const QWidget *w = nullptr) const override;
    QRect itemPixmapRect(const QRect &rect, int alignment, const QPixmap &pixmap) const override;
    QRect itemTextRect(const QFontMetrics &metrics, const QRect &rect, int alignment, bool enabled,
                       const QString &text) const override;
    int pixelMetric(PixelMetric metric, const QStyleOption *option = nullptr, const QWidget *widget = nullptr) const override;
    void polish(QWidget *widget) override;
    void polish(QApplication *app) override;
    void polish(QPalette &pal) override;
    QSize sizeFromContents(ContentsType ct, const QStyleOption *opt,
                           const QSize &contentsSize, const QWidget *widget = nullptr) const override;
    QPalette standardPalette() const override;
    QIcon standardIcon(StandardPixmap standardIcon, const QStyleOption *opt = nullptr,
                       const QWidget *widget = nullptr) const override;
    QPixmap standardPixmap(StandardPixmap standardPixmap, const QStyleOption *option = nullptr,
                           const QWidget *w = nullptr ) const override;
    int layoutSpacing(QSizePolicy::ControlType control1, QSizePolicy::ControlType control2,
                          Qt::Orientation orientation, const QStyleOption *option = nullptr,
                          const QWidget *widget = nullptr) const override;
    int styleHint(StyleHint sh, const QStyleOption *opt = nullptr, const QWidget *w = nullptr,
                  QStyleHintReturn *shret = nullptr) const override;
    QRect subElementRect(SubElement r, const QStyleOption *opt, const QWidget *widget = nullptr) const override;
    QRect subControlRect(ComplexControl cc, const QStyleOptionComplex *opt, SubControl sc,
                         const QWidget *w = nullptr) const override;

    // These functions are called from QApplication/QWidget. Be careful.
    QStyle *baseStyle() const;
    void repolish(QWidget *widget);
    void repolish(QApplication *app);

    void unpolish(QWidget *widget) override;
    void unpolish(QApplication *app) override;

    QStyle *base;
    void ref() { ++refcount; }
    void deref() { Q_ASSERT(refcount > 0); if (!--refcount) delete this; }

    void updateStyleSheetFont(QWidget* w) const;
    void saveWidgetFont(QWidget* w, const QFont& font) const;
    void clearWidgetFont(QWidget* w) const;

    bool styleSheetPalette(const QWidget* w, const QStyleOption* opt, QPalette* pal);

protected:
    bool event(QEvent *e) override;

private:
    int refcount;

    friend class QRenderRule;
    int nativeFrameWidth(const QWidget *);
    QRenderRule renderRule(const QObject *, int, quint64 = 0) const;
    QRenderRule renderRule(const QObject *, const QStyleOption *, int = 0) const;
    QSize defaultSize(const QWidget *, QSize, const QRect&, int) const;
    QRect positionRect(const QWidget *, const QRenderRule&, const QRenderRule&, int,
                       const QRect&, Qt::LayoutDirection) const;
    QRect positionRect(const QWidget *w, const QRenderRule &rule2, int pe,
                       const QRect &originRect, Qt::LayoutDirection dir) const;

    mutable QCss::Parser parser;

    void setPalette(QWidget *);
    void unsetPalette(QWidget *);
    void setProperties(QWidget *);
    void setGeometry(QWidget *);
    void unsetStyleSheetFont(QWidget *) const;
    QList<QCss::StyleRule> styleRules(const QObject *obj) const;
    bool hasStyleRule(const QObject *obj, int part) const;

    QHash<QStyle::SubControl, QRect> titleBarLayout(const QWidget *w, const QStyleOptionTitleBar *tb) const;

    QCss::StyleSheet getDefaultStyleSheet() const;

    static Qt::Alignment resolveAlignment(Qt::LayoutDirection, Qt::Alignment);
    static bool isNaturalChild(const QObject *obj);
    static QPixmap loadPixmap(const QString &fileName, const QObject *context);
    bool initObject(const QObject *obj) const;
    void renderMenuItemIcon(const QStyleOptionMenuItem *mi, QPainter *p, const QWidget *w,
                            const QRect &rect, QRenderRule &subRule) const;
public:
    static int numinstances;

private:
    Q_DISABLE_COPY_MOVE(QStyleSheetStyle)
    Q_DECLARE_PRIVATE(QStyleSheetStyle)
};

class QStyleSheetStyleCaches : public QObject
{
    Q_OBJECT
public Q_SLOTS:
    void objectDestroyed(QObject *);
    void styleDestroyed(QObject *);
public:
    QHash<const QObject *, QList<QCss::StyleRule>> styleRulesCache;
    QHash<const QObject *, QHash<int, bool> > hasStyleRuleCache;
    typedef QHash<int, QHash<quint64, QRenderRule> > QRenderRules;
    QHash<const QObject *, QRenderRules> renderRulesCache;
    QHash<const void *, QCss::StyleSheet> styleSheetCache; // parsed style sheets
    QSet<const QWidget *> autoFillDisabledWidgets;
    // widgets with whose palettes and fonts we have tampered:
    template <typename T>
    struct Tampered {
        T oldWidgetValue;
        decltype(std::declval<T>().resolveMask()) resolveMask;

        // only call this function on an rvalue *this (it mangles oldWidgetValue)
        T reverted(T current)
#ifdef Q_COMPILER_REF_QUALIFIERS
        &&
#endif
        {
            oldWidgetValue.setResolveMask(oldWidgetValue.resolveMask() & resolveMask);
            current.setResolveMask(current.resolveMask() & ~resolveMask);
            current.resolve(oldWidgetValue);
            current.setResolveMask(current.resolveMask() | oldWidgetValue.resolveMask());
            return current;
        }
    };
    QHash<const QWidget *, Tampered<QPalette>> customPaletteWidgets;
    QHash<const QWidget *, Tampered<QFont>> customFontWidgets;
};
template <typename T>
class QTypeInfo<QStyleSheetStyleCaches::Tampered<T>>
    : public QTypeInfoMerger<QStyleSheetStyleCaches::Tampered<T>, T> {};


// Returns a QStyleSheet from the given style.
inline QStyleSheetStyle* qt_styleSheet(QStyle *style)
{
    return qobject_cast<QStyleSheetStyle *>(style);
}

QT_END_NAMESPACE
#endif // QT_NO_STYLE_STYLESHEET
#endif // QSTYLESHEETSTYLE_P_H
