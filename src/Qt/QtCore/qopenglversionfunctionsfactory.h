// Copyright (C) 2013 Klaralvdalens Datakonsult AB (KDAB)

/***************************************************************************
** This file was generated by glgen version 0.1
** Command line was: glgen
**
** glgen is Copyright (C) 2012 Klaralvdalens Datakonsult AB (KDAB)
**
** This is an auto-generated file.
** Do not edit! All changes made to it will be lost.
**
****************************************************************************/

#ifndef QOPENGLVERSIONFUNCTIONFACTORY_H
#define QOPENGLVERSIONFUNCTIONFACTORY_H

#include <QtOpenGL/qtopenglglobal.h>
#include <QtOpenGL/qopenglversionprofile.h>

QT_BEGIN_NAMESPACE

class QAbstractOpenGLFunctions;
class QOpenGLContext;

class Q_OPENGL_EXPORT QOpenGLVersionFunctionsFactory
{
public:
    static QAbstractOpenGLFunctions *get(const QOpenGLVersionProfile &versionProfile = QOpenGLVersionProfile(), QOpenGLContext *context = nullptr);
    template<class TYPE>
    static TYPE *get(QOpenGLContext *context = nullptr)
    {
        QOpenGLVersionProfile v = TYPE::versionProfile();
        return static_cast<TYPE*>(get(v, context));
    }
};

QT_END_NAMESPACE

#endif
