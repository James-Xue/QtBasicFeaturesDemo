// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QICONENGINEPLUGIN_H
#define QICONENGINEPLUGIN_H

#include <QtGui/qtguiglobal.h>
#include <QtCore/qplugin.h>
#include <QtCore/qfactoryinterface.h>

QT_BEGIN_NAMESPACE


class QIconEngine;

#define QIconEngineFactoryInterface_iid "org.qt-project.Qt.QIconEngineFactoryInterface"

class Q_GUI_EXPORT QIconEnginePlugin : public QObject
{
    Q_OBJECT
public:
    QIconEnginePlugin(QObject *parent = nullptr);
    ~QIconEnginePlugin();

    virtual QIconEngine *create(const QString &filename = QString()) = 0;
};

QT_END_NAMESPACE

#endif // QICONENGINEPLUGIN_H
