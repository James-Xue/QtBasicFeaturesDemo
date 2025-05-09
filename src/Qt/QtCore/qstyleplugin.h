// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QSTYLEPLUGIN_H
#define QSTYLEPLUGIN_H

#include <QtWidgets/qtwidgetsglobal.h>
#include <QtCore/qplugin.h>
#include <QtCore/qfactoryinterface.h>

QT_BEGIN_NAMESPACE


class QStyle;

#define QStyleFactoryInterface_iid "org.qt-project.Qt.QStyleFactoryInterface"

class Q_WIDGETS_EXPORT QStylePlugin : public QObject
{
    Q_OBJECT
public:
    explicit QStylePlugin(QObject *parent = nullptr);
    ~QStylePlugin();

    virtual QStyle *create(const QString &key) = 0;
};

QT_END_NAMESPACE

#endif // QSTYLEPLUGIN_H
