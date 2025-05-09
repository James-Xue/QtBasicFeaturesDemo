// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QPICTURE_P_H
#define QPICTURE_P_H

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
#include "QtCore/qatomic.h"
#include "QtCore/qbuffer.h"
#include "QtCore/qlist.h"
#include "QtCore/qobjectdefs.h"
#include "QtCore/qrect.h"
#include "QtGui/qpicture.h"
#include "QtGui/qpixmap.h"
#include "QtGui/qpen.h"
#include "QtGui/qbrush.h"
#include "private/qobject_p.h"

QT_BEGIN_NAMESPACE

class QPaintEngine;

extern const char  *qt_mfhdr_tag;

class QPicturePrivate
{
    friend class QPicturePaintEngine;
    friend Q_GUI_EXPORT QDataStream &operator<<(QDataStream &s, const QPicture &r);
    friend Q_GUI_EXPORT QDataStream &operator>>(QDataStream &s, QPicture &r);

public:
    enum PaintCommand {
        PdcNOP = 0, //  <void>
        PdcDrawPoint = 1, // point
        PdcDrawFirst = PdcDrawPoint,
        PdcMoveTo = 2, // point
        PdcLineTo = 3, // point
        PdcDrawLine = 4, // point,point
        PdcDrawRect = 5, // rect
        PdcDrawRoundRect = 6, // rect,ival,ival
        PdcDrawEllipse = 7, // rect
        PdcDrawArc = 8, // rect,ival,ival
        PdcDrawPie = 9, // rect,ival,ival
        PdcDrawChord = 10, // rect,ival,ival
        PdcDrawLineSegments = 11, // ptarr
        PdcDrawPolyline = 12, // ptarr
        PdcDrawPolygon = 13, // ptarr,ival
        PdcDrawCubicBezier = 14, // ptarr
        PdcDrawText = 15, // point,str
        PdcDrawTextFormatted = 16, // rect,ival,str
        PdcDrawPixmap = 17, // rect,pixmap
        PdcDrawImage = 18, // rect,image
        PdcDrawText2 = 19, // point,str
        PdcDrawText2Formatted = 20, // rect,ival,str
        PdcDrawTextItem = 21, // pos,text,font,flags
        PdcDrawLast = PdcDrawTextItem,
        PdcDrawPoints = 22, // ptarr,ival,ival
        PdcDrawWinFocusRect = 23, // rect,color
        PdcDrawTiledPixmap = 24, // rect,pixmap,point
        PdcDrawPath = 25, // path

        // no painting commands below PdcDrawLast.

        PdcBegin = 30, //  <void>
        PdcEnd = 31, //  <void>
        PdcSave = 32, //  <void>
        PdcRestore = 33, //  <void>
        PdcSetdev = 34, // device - PRIVATE
        PdcSetBkColor = 40, // color
        PdcSetBkMode = 41, // ival
        PdcSetROP = 42, // ival
        PdcSetBrushOrigin = 43, // point
        PdcSetFont = 45, // font
        PdcSetPen = 46, // pen
        PdcSetBrush = 47, // brush
        PdcSetTabStops = 48, // ival
        PdcSetTabArray = 49, // ival,ivec
        PdcSetUnit = 50, // ival
        PdcSetVXform = 51, // ival
        PdcSetWindow = 52, // rect
        PdcSetViewport = 53, // rect
        PdcSetWXform = 54, // ival
        PdcSetWMatrix = 55, // matrix,ival
        PdcSaveWMatrix = 56,
        PdcRestoreWMatrix = 57,
        PdcSetClip = 60, // ival
        PdcSetClipRegion = 61, // rgn
        PdcSetClipPath = 62, // path
        PdcSetRenderHint = 63, // ival
        PdcSetCompositionMode = 64, // ival
        PdcSetClipEnabled = 65, // bool
        PdcSetOpacity = 66, // qreal

        PdcReservedStart = 0, // codes 0-199 are reserved
        PdcReservedStop = 199 //   for Qt
    };

    QPicturePrivate();
    QPicturePrivate(const QPicturePrivate &other);
    QAtomicInt ref;

    bool checkFormat();
    void resetFormat();

    QBuffer pictb;
    int trecs;
    bool formatOk;
    int formatMajor;
    int formatMinor;
    QRect brect;
    QRect override_rect;
    QScopedPointer<QPaintEngine> paintEngine;
    bool in_memory_only;
    QList<QImage> image_list;
    QList<QPixmap> pixmap_list;
    QList<QBrush> brush_list;
    QList<QPen> pen_list;
};

QT_END_NAMESPACE

#endif // QPICTURE_P_H
