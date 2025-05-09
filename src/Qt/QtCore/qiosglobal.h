// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QIOSGLOBAL_H
#define QIOSGLOBAL_H

#import <UIKit/UIKit.h>
#include <QtCore/QtCore>

@class QIOSViewController;

QT_BEGIN_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(lcQpaApplication);
Q_DECLARE_LOGGING_CATEGORY(lcQpaInputMethods);
Q_DECLARE_LOGGING_CATEGORY(lcQpaWindow);
Q_DECLARE_LOGGING_CATEGORY(lcQpaWindowScene);

#if !defined(QT_NO_DEBUG)
#define qImDebug \
    for (bool qt_category_enabled = lcQpaInputMethods().isDebugEnabled(); qt_category_enabled; qt_category_enabled = false) \
        QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC, lcQpaInputMethods().categoryName()).debug
#else
#define qImDebug QT_NO_QDEBUG_MACRO
#endif

class QPlatformScreen;

bool isQtApplication();
bool isRunningOnVisionOS();

#ifndef Q_OS_TVOS
Qt::ScreenOrientation toQtScreenOrientation(UIDeviceOrientation uiDeviceOrientation);
UIDeviceOrientation fromQtScreenOrientation(Qt::ScreenOrientation qtOrientation);
#endif

int infoPlistValue(NSString* key, int defaultValue);

class QWindow;
class QScreen;
UIWindow *presentationWindow(QWindow *);
UIView *rootViewForScreen(const QPlatformScreen *);

QT_END_NAMESPACE

@interface UIResponder (QtFirstResponder)
+ (id)qt_currentFirstResponder;
@end

QT_BEGIN_NAMESPACE

class FirstResponderCandidate : public QScopedValueRollback<UIResponder *>
{
public:
     FirstResponderCandidate(UIResponder *);
     static UIResponder *currentCandidate() { return s_firstResponderCandidate; }

private:
    static UIResponder *s_firstResponderCandidate;
};

QT_END_NAMESPACE

#endif // QIOSGLOBAL_H
