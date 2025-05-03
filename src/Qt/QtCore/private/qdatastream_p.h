// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QDATASTREAM_P_H
#define QDATASTREAM_P_H

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

#include <QtCore/private/qglobal_p.h>
#include <qdatastream.h>

QT_BEGIN_NAMESPACE

#if !defined(QT_NO_DATASTREAM) || defined(QT_BOOTSTRAPPED)
class QDataStreamPrivate
{
public:
};
#endif

QT_END_NAMESPACE

#endif // QDATASTREAM_P_H
