// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QNSVIEW_H
#define QNSVIEW_H

#include <AppKit/NSView.h>

#include <QtCore/private/qcore_mac_p.h>

QT_BEGIN_NAMESPACE
class QCocoaWindow;
class QCocoaGLContext;
class QPointF;
QT_END_NAMESPACE

QT_DECLARE_NAMESPACED_OBJC_INTERFACE(QNSView, NSView
@property (nonatomic, retain) NSCursor *cursor;
- (instancetype)initWithCocoaWindow:(QCocoaWindow *)platformWindow;
- (void)convertFromScreen:(NSPoint)mouseLocation toWindowPoint:(QPointF *)qtWindowPoint andScreenPoint:(QPointF *)qtScreenPoint;
)

#if defined(__OBJC__)
@interface QNSView (MouseAPI)
- (void)handleMouseEvent:(NSEvent *)theEvent;
- (void)handleFrameStrutMouseEvent:(NSEvent *)theEvent;
- (void)resetMouseButtons;
@end

@interface QNSView (ComplexTextAPI)
- (void)unmarkText;
- (void)cancelComposingText;
@end

Q_FORWARD_DECLARE_OBJC_CLASS(NSColorSpace);

@interface QNSView (DrawingAPI)
@property (nonatomic, readonly) NSColorSpace *colorSpace;
@end

@interface QNSView (QtExtras)
@property (nonatomic, readonly) QCocoaWindow *platformWindow;
@end
#endif // __OBJC__


#endif //QNSVIEW_H
