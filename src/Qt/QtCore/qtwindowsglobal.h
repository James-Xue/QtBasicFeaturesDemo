// Copyright (C) 2013 Samuel Gaist <samuel.gaist@edeltech.ch>
// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QTWINDOWSGLOBAL_H
#define QTWINDOWSGLOBAL_H

#include <QtCore/qt_windows.h>
#include <QtCore/qnamespace.h>

#ifndef WM_DWMCOMPOSITIONCHANGED
#  define WM_DWMCOMPOSITIONCHANGED 0x31E
#endif

#ifndef WM_DWMCOLORIZATIONCOLORCHANGED
#  define WM_DWMCOLORIZATIONCOLORCHANGED 0x0320
#endif

#ifndef WM_SYSCOLORCHANGE
#  define WM_SYSCOLORCHANGE 0x0015
#endif

#ifndef WM_TOUCH
#  define WM_TOUCH 0x0240
#endif

#ifndef WM_GESTURE
#  define WM_GESTURE 0x0119
#endif

#ifndef WM_DPICHANGED
#  define WM_DPICHANGED 0x02E0
#endif

#ifndef WM_GETDPISCALEDSIZE
#  define WM_GETDPISCALEDSIZE 0x02E4
#endif

// WM_POINTER support from Windows 8 onwards (WINVER >= 0x0602)
#ifndef WM_POINTERUPDATE
#  define WM_NCPOINTERUPDATE 0x0241
#  define WM_NCPOINTERDOWN   0x0242
#  define WM_NCPOINTERUP     0x0243
#  define WM_POINTERUPDATE   0x0245
#  define WM_POINTERDOWN     0x0246
#  define WM_POINTERUP       0x0247
#  define WM_POINTERENTER    0x0249
#  define WM_POINTERLEAVE    0x024A
#  define WM_POINTERACTIVATE 0x024B
#  define WM_POINTERCAPTURECHANGED 0x024C
#  define WM_POINTERWHEEL    0x024E
#  define WM_POINTERHWHEEL   0x024F
#endif // WM_POINTERUPDATE

#if !defined(_DPI_AWARENESS_CONTEXTS_)
#  define DPI_AWARENESS_CONTEXT_UNAWARE              ((HANDLE)-1)
#  define DPI_AWARENESS_CONTEXT_SYSTEM_AWARE         ((HANDLE)-2)
#  define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE    ((HANDLE)-3)
#  define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 ((HANDLE)-4)
#  define DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED    ((HANDLE)-5)
#endif

QT_BEGIN_NAMESPACE

namespace QtWindows
{

enum WindowsEventTypeFlags
{
    WindowEventFlag = 0x10000,
    MouseEventFlag = 0x20000,
    NonClientEventFlag = 0x40000,
    InputMethodEventFlag = 0x80000,
    KeyEventFlag = 0x100000,
    KeyDownEventFlag = 0x200000,
    TouchEventFlag = 0x400000,
    ClipboardEventFlag = 0x800000,
    ApplicationEventFlag = 0x1000000,
    ThemingEventFlag = 0x2000000,
    GenericEventFlag = 0x4000000, // Misc
    PointerEventFlag = 0x8000000,
};

enum WindowsEventType // Simplify event types
{
    ExposeEvent = WindowEventFlag + 1,
    ActivateWindowEvent = WindowEventFlag + 2,
    DeactivateWindowEvent = WindowEventFlag + 3,
    MouseActivateWindowEvent = WindowEventFlag + 4,
    LeaveEvent = WindowEventFlag + 5,
    CloseEvent = WindowEventFlag + 6,
    ShowEvent = WindowEventFlag + 7,
    ShowEventOnParentRestoring = WindowEventFlag + 20,
    HideEvent = WindowEventFlag + 8,
    DestroyEvent = WindowEventFlag + 9,
    GeometryChangingEvent = WindowEventFlag + 10,
    MoveEvent = WindowEventFlag + 11,
    ResizeEvent = WindowEventFlag + 12,
    QuerySizeHints = WindowEventFlag + 15,
    CalculateSize = WindowEventFlag + 16,
    FocusInEvent = WindowEventFlag + 17,
    FocusOutEvent = WindowEventFlag + 18,
    WhatsThisEvent = WindowEventFlag + 19,
    DpiChangedEvent = WindowEventFlag + 21,
    EnterSizeMoveEvent = WindowEventFlag + 22,
    ExitSizeMoveEvent = WindowEventFlag + 23,
    PointerActivateWindowEvent = WindowEventFlag + 24,
    DpiScaledSizeEvent = WindowEventFlag + 25,
    DpiChangedAfterParentEvent = WindowEventFlag + 27,
    TaskbarButtonCreated = WindowEventFlag + 28,
    MouseEvent = MouseEventFlag + 1,
    MouseWheelEvent = MouseEventFlag + 2,
    CursorEvent = MouseEventFlag + 3,
    TouchEvent = TouchEventFlag + 1,
    PointerEvent = PointerEventFlag + 1,
    NonClientMouseEvent = NonClientEventFlag + MouseEventFlag + 1,
    NonClientHitTest = NonClientEventFlag + 2,
    NonClientCreate = NonClientEventFlag + 3,
    NonClientPointerEvent = NonClientEventFlag + PointerEventFlag + 4,
    KeyEvent = KeyEventFlag + 1,
    KeyDownEvent = KeyEventFlag + KeyDownEventFlag + 1,
    InputLanguageChangeEvent = KeyEventFlag + 2,
    InputMethodKeyEvent = InputMethodEventFlag + KeyEventFlag + 1,
    InputMethodKeyDownEvent = InputMethodEventFlag + KeyEventFlag + KeyDownEventFlag + 1,
    ClipboardEvent = ClipboardEventFlag + 1,
    ActivateApplicationEvent = ApplicationEventFlag + 1,
    DeactivateApplicationEvent = ApplicationEventFlag + 2,
    AccessibleObjectFromWindowRequest = ApplicationEventFlag + 3,
    QueryEndSessionApplicationEvent = ApplicationEventFlag + 4,
    EndSessionApplicationEvent = ApplicationEventFlag + 5,
    AppCommandEvent = ApplicationEventFlag + 6,
    DeviceChangeEvent = ApplicationEventFlag + 7,
    MenuAboutToShowEvent = ApplicationEventFlag + 8,
    AcceleratorCommandEvent = ApplicationEventFlag + 9,
    MenuCommandEvent = ApplicationEventFlag + 10,
    InputMethodStartCompositionEvent = InputMethodEventFlag + 1,
    InputMethodCompositionEvent = InputMethodEventFlag + 2,
    InputMethodEndCompositionEvent = InputMethodEventFlag + 3,
    InputMethodOpenCandidateWindowEvent = InputMethodEventFlag + 4,
    InputMethodCloseCandidateWindowEvent = InputMethodEventFlag + 5,
    InputMethodRequest = InputMethodEventFlag + 6,
    ThemeChanged = ThemingEventFlag + 1,
    CompositionSettingsChanged = ThemingEventFlag + 2,
    SettingChangedEvent = 438,
    ScrollEvent = GenericEventFlag + 1,
    ContextMenu = 123,
    GestureEvent = 124,
    UnknownEvent = 542
};
Q_DECLARE_MIXED_ENUM_OPERATORS(bool, WindowsEventTypeFlags, WindowsEventType);
Q_DECLARE_MIXED_ENUM_OPERATORS(bool, WindowsEventType, WindowsEventTypeFlags);

enum class DpiAwareness
{
    Invalid = -1,
    Unaware,
    System,
    PerMonitor,
    PerMonitorVersion2,
    Unaware_GdiScaled
};

} // namespace QtWindows

inline QtWindows::WindowsEventType windowsEventType(UINT message, WPARAM wParamIn, LPARAM lParamIn)
{
    static const UINT WM_TASKBAR_BUTTON_CREATED = []{
        UINT message = RegisterWindowMessage(L"TaskbarButtonCreated");
        // In case the application is run elevated, allow the
        // TaskbarButtonCreated message through.
        ChangeWindowMessageFilter(message, MSGFLT_ADD);
        return message;
    }();

    switch (message) {
    case WM_PAINT:
    case WM_ERASEBKGND:
        return QtWindows::ExposeEvent;
    case WM_CLOSE:
        return QtWindows::CloseEvent;
    case WM_DESTROY:
        return QtWindows::DestroyEvent;
    case WM_ACTIVATEAPP:
        return (int)wParamIn ?
        QtWindows::ActivateApplicationEvent : QtWindows::DeactivateApplicationEvent;
    case WM_MOUSEACTIVATE:
        return QtWindows::MouseActivateWindowEvent;
    case WM_POINTERACTIVATE:
        return QtWindows::PointerActivateWindowEvent;
    case WM_ACTIVATE:
        return  LOWORD(wParamIn) == WA_INACTIVE ?
            QtWindows::DeactivateWindowEvent : QtWindows::ActivateWindowEvent;
    case WM_SETCURSOR:
        return QtWindows::CursorEvent;
    case WM_MOUSELEAVE:
        return QtWindows::MouseEvent;
    case WM_HSCROLL:
        return QtWindows::ScrollEvent;
    case WM_MOUSEWHEEL:
    case WM_MOUSEHWHEEL:
        return QtWindows::MouseWheelEvent;
    case WM_WINDOWPOSCHANGING:
        return QtWindows::GeometryChangingEvent;
    case WM_MOVE:
        return QtWindows::MoveEvent;
    case WM_SHOWWINDOW:
        if (wParamIn)
            return lParamIn == SW_PARENTOPENING ? QtWindows::ShowEventOnParentRestoring : QtWindows::ShowEvent;
        return QtWindows::HideEvent;
    case WM_SIZE:
        return QtWindows::ResizeEvent;
    case WM_NCCREATE:
        return QtWindows::NonClientCreate;
    case WM_NCCALCSIZE:
        return QtWindows::CalculateSize;
    case WM_NCHITTEST:
        return QtWindows::NonClientHitTest;
    case WM_GETMINMAXINFO:
        return QtWindows::QuerySizeHints;
    case WM_KEYDOWN:                        // keyboard event
    case WM_SYSKEYDOWN:
        return QtWindows::KeyDownEvent;
    case WM_KEYUP:
    case WM_SYSKEYUP:
    case WM_CHAR:
        return QtWindows::KeyEvent;
    case WM_IME_CHAR:
        return QtWindows::InputMethodKeyEvent;
    case WM_IME_KEYDOWN:
        return QtWindows::InputMethodKeyDownEvent;
#ifdef WM_INPUTLANGCHANGE
    case WM_INPUTLANGCHANGE:
        return QtWindows::InputLanguageChangeEvent;
#endif // WM_INPUTLANGCHANGE
    case WM_TOUCH:
        return QtWindows::TouchEvent;
    case WM_CHANGECBCHAIN:
    case WM_DRAWCLIPBOARD:
    case WM_RENDERFORMAT:
    case WM_RENDERALLFORMATS:
    case WM_DESTROYCLIPBOARD:
        return QtWindows::ClipboardEvent;
    case WM_IME_STARTCOMPOSITION:
        return QtWindows::InputMethodStartCompositionEvent;
    case WM_IME_ENDCOMPOSITION:
        return QtWindows::InputMethodEndCompositionEvent;
    case WM_IME_COMPOSITION:
        return QtWindows::InputMethodCompositionEvent;
    case WM_IME_REQUEST:
        return QtWindows::InputMethodRequest;
    case WM_IME_NOTIFY:
         switch (int(wParamIn)) {
         case IMN_OPENCANDIDATE:
             return QtWindows::InputMethodOpenCandidateWindowEvent;
         case IMN_CLOSECANDIDATE:
             return QtWindows::InputMethodCloseCandidateWindowEvent;
         default:
             break;
         }
         break;
    case WM_GETOBJECT:
        return QtWindows::AccessibleObjectFromWindowRequest;
    case WM_SETFOCUS:
        return QtWindows::FocusInEvent;
    case WM_KILLFOCUS:
        return QtWindows::FocusOutEvent;
    // Among other things, WM_SETTINGCHANGE happens when the taskbar is moved
    // and therefore the "working area" changes.
    // http://msdn.microsoft.com/en-us/library/ms695534(v=vs.85).aspx
    case WM_SETTINGCHANGE:
        return QtWindows::SettingChangedEvent;
    case WM_THEMECHANGED:
    case WM_SYSCOLORCHANGE: // Handle color change as theme change (QTBUG-34170).
    case WM_DWMCOLORIZATIONCOLORCHANGED:
        return QtWindows::ThemeChanged;
    case WM_DWMCOMPOSITIONCHANGED:
        return QtWindows::CompositionSettingsChanged;
#ifndef QT_NO_CONTEXTMENU
    case WM_CONTEXTMENU:
        return QtWindows::ContextMenu;
#endif
    case WM_SYSCOMMAND:
        if ((wParamIn & 0xfff0) == SC_CONTEXTHELP)
            return QtWindows::WhatsThisEvent;
        break;
    case WM_QUERYENDSESSION:
        return QtWindows::QueryEndSessionApplicationEvent;
    case WM_ENDSESSION:
        return QtWindows::EndSessionApplicationEvent;
#if defined(WM_APPCOMMAND)
    case WM_APPCOMMAND:
        return QtWindows::AppCommandEvent;
#endif
    case WM_GESTURE:
        return QtWindows::GestureEvent;
    case WM_DEVICECHANGE:
        return QtWindows::DeviceChangeEvent;
    case WM_INITMENU:
    case WM_INITMENUPOPUP:
        return QtWindows::MenuAboutToShowEvent;
    case WM_COMMAND:
        return HIWORD(wParamIn) ? QtWindows::AcceleratorCommandEvent : QtWindows::MenuCommandEvent;
    case WM_DPICHANGED:
        return QtWindows::DpiChangedEvent;
    case WM_DPICHANGED_AFTERPARENT:
        return QtWindows::DpiChangedAfterParentEvent;
    case WM_GETDPISCALEDSIZE:
        return QtWindows::DpiScaledSizeEvent;
    case WM_ENTERSIZEMOVE:
        return QtWindows::EnterSizeMoveEvent;
    case WM_EXITSIZEMOVE:
        return QtWindows::ExitSizeMoveEvent;
    default:
        break;
    }
    if (message >= WM_NCMOUSEMOVE && message <= WM_NCMBUTTONDBLCLK)
        return QtWindows::NonClientMouseEvent; //
    if ((message >= WM_MOUSEFIRST && message <= WM_MOUSELAST)
         || (message >= WM_XBUTTONDOWN && message <= WM_XBUTTONDBLCLK))
        return QtWindows::MouseEvent;
    if (message >= WM_NCPOINTERUPDATE && message <= WM_NCPOINTERUP)
        return QtWindows::NonClientPointerEvent;
    if (message >= WM_POINTERUPDATE && message <= WM_POINTERHWHEEL)
        return QtWindows::PointerEvent;
    if (message == WM_TASKBAR_BUTTON_CREATED)
        return QtWindows::TaskbarButtonCreated;
    return QtWindows::UnknownEvent;
}

#ifndef QT_NO_DEBUG_STREAM
extern QDebug operator<<(QDebug, QtWindows::DpiAwareness);
#endif

QT_END_NAMESPACE

#endif // QTWINDOWSGLOBAL_H
