// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QWINDOWSKEYMAPPER_H
#define QWINDOWSKEYMAPPER_H

#include <QtCore/qt_windows.h>

#include <QtCore/qlocale.h>

#include <qpa/qplatformkeymapper.h>

QT_BEGIN_NAMESPACE

class QKeyEvent;
class QWindow;

/*
    \internal
    A Windows KeyboardLayoutItem has 8 possible states:
        1. Unmodified
        2. Shift
        3. Control
        4. Control + Shift
        5. Alt
        6. Alt + Shift
        7. Alt + Control
        8. Alt + Control + Shift
*/
struct KeyboardLayoutItem {
    uint dirty : 1;
    uint exists : 1; // whether this item has been initialized (by updatePossibleKeyCodes)
    quint8 deadkeys;
    static const size_t NumQtKeys = 9;
    quint32 qtKey[NumQtKeys]; // Can by any Qt::Key_<foo>, or unicode character
};

class QWindowsKeyMapper : public QPlatformKeyMapper
{
    Q_DISABLE_COPY_MOVE(QWindowsKeyMapper)
public:
    explicit QWindowsKeyMapper();
    ~QWindowsKeyMapper();

    void changeKeyboard();

    void setUseRTLExtensions(bool e) { m_useRTLExtensions = e; }
    bool useRTLExtensions() const    { return m_useRTLExtensions; }

    void setDetectAltGrModifier(bool a) { m_detectAltGrModifier = a; }
    bool detectAltGrModifier() const { return m_detectAltGrModifier; }

    bool translateKeyEvent(QWindow *widget, HWND hwnd, const MSG &msg, LRESULT *result);

    QWindow *keyGrabber() const      { return m_keyGrabber; }
    void setKeyGrabber(QWindow *w)   { m_keyGrabber = w; }

    Qt::KeyboardModifiers queryKeyboardModifiers() const override;
    QList<QKeyCombination> possibleKeyCombinations(const QKeyEvent *e) const override;

private:
    bool translateKeyEventInternal(QWindow *receiver, MSG msg, bool grab, LRESULT *lResult);
    bool translateMultimediaKeyEventInternal(QWindow *receiver, const MSG &msg);
    void updateKeyMap(const MSG &msg);

    bool m_useRTLExtensions;

    QLocale keyboardInputLocale;
    Qt::LayoutDirection keyboardInputDirection;

    void updatePossibleKeyCodes(unsigned char *kbdBuffer, quint32 scancode, quint32 vk_key);
    void deleteLayouts();

    QWindow *m_keyGrabber;
    QChar m_lastHighSurrogate;
    static const size_t NumKeyboardLayoutItems = 256;
    KeyboardLayoutItem keyLayout[NumKeyboardLayoutItems];
    bool m_detectAltGrModifier =  false;
    bool m_seenAltGr = false;

};

enum WindowsNativeModifiers {
    ShiftLeft            = 0x00000001,
    ControlLeft          = 0x00000002,
    AltLeft              = 0x00000004,
    MetaLeft             = 0x00000008,
    ShiftRight           = 0x00000010,
    ControlRight         = 0x00000020,
    AltRight             = 0x00000040,
    MetaRight            = 0x00000080,
    CapsLock             = 0x00000100,
    NumLock              = 0x00000200,
    ScrollLock           = 0x00000400,
    ExtendedKey          = 0x01000000,

    // Convenience mappings
    ShiftAny             = 0x00000011,
    ControlAny           = 0x00000022,
    AltAny               = 0x00000044,
    MetaAny              = 0x00000088,
    LockAny              = 0x00000700
};

QT_END_NAMESPACE

#endif // QWINDOWSKEYMAPPER_H
