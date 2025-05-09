// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QWIDGETACTION_H
#define QWIDGETACTION_H

#include <QtWidgets/qtwidgetsglobal.h>
#include <QtGui/qaction.h>

QT_REQUIRE_CONFIG(action);

QT_BEGIN_NAMESPACE

class QWidgetActionPrivate;

class Q_WIDGETS_EXPORT QWidgetAction : public QAction
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QWidgetAction)

public:
    explicit QWidgetAction(QObject *parent);
    virtual ~QWidgetAction();

    void setDefaultWidget(QWidget *w);
    QWidget *defaultWidget() const;

    QWidget *requestWidget(QWidget *parent);
    void releaseWidget(QWidget *widget);

protected:
    virtual bool event(QEvent *) override;
    virtual bool eventFilter(QObject *, QEvent *) override;
    virtual QWidget *createWidget(QWidget *parent);
    virtual void deleteWidget(QWidget *widget);
    QList<QWidget *> createdWidgets() const;

private:
    Q_DISABLE_COPY(QWidgetAction)
    friend class QToolBar;
};

QT_END_NAMESPACE

#endif // QWIDGETACTION_H
