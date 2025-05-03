// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QSTYLEFACTORY_H
#define QSTYLEFACTORY_H

#include <QtWidgets/qtwidgetsglobal.h>
#include <QtCore/qstringlist.h>

QT_BEGIN_NAMESPACE


class QStyle;

class Q_WIDGETS_EXPORT QStyleFactory
{
public:
    static QStringList keys();
    static QStyle *create(const QString&);
};

QT_END_NAMESPACE

#endif // QSTYLEFACTORY_H
