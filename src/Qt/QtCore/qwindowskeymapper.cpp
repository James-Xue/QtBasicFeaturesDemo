// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include "qwindowskeymapper.h"
#include "qwindowscontext.h"
#include "qwindowsintegration.h"
#include "qwindowswindow.h"
#include "qwindowsinputcontext.h"

#include <QtGui/qguiapplication.h>
#include <QtGui/qwindow.h>
#include <qpa/qwindowsysteminterface.h>
#include <private/qguiapplication_p.h>
#include <private/qhighdpiscaling_p.h>
#include <QtGui/qevent.h>
#include <QtGui/private/qwindowsguieventdispatcher_p.h>
#include <QtCore/private/qdebug_p.h>
#include <QtCore/private/qtools_p.h>

#if defined(WM_APPCOMMAND)
#  ifndef FAPPCOMMAND_MOUSE
#    define FAPPCOMMAND_MOUSE 0x8000
#  endif
#  ifndef FAPPCOMMAND_KEY
#    define FAPPCOMMAND_KEY   0
#  endif
#  ifndef FAPPCOMMAND_OEM
#    define FAPPCOMMAND_OEM   0x1000
#  endif
#  ifndef FAPPCOMMAND_MASK
#    define FAPPCOMMAND_MASK  0xF000
#  endif
#  ifndef GET_APPCOMMAND_LPARAM
#    define GET_APPCOMMAND_LPARAM(lParam) ((short)(HIWORD(lParam) & ~FAPPCOMMAND_MASK))
#  endif
#  ifndef GET_DEVICE_LPARAM
#    define GET_DEVICE_LPARAM(lParam)     ((WORD)(HIWORD(lParam) & FAPPCOMMAND_MASK))
#  endif
#  ifndef GET_MOUSEORKEY_LPARAM
#    define GET_MOUSEORKEY_LPARAM         GET_DEVICE_LPARAM
#  endif
#  ifndef GET_FLAGS_LPARAM
#    define GET_FLAGS_LPARAM(lParam)      (LOWORD(lParam))
#  endif
#  ifndef GET_KEYSTATE_LPARAM
#    define GET_KEYSTATE_LPARAM(lParam)   GET_FLAGS_LPARAM(lParam)
#  endif
#endif

QT_BEGIN_NAMESPACE

/*!
    \class QWindowsKeyMapper
    \brief Translates Windows keys to QWindowSystemInterface events.
    \internal

    In addition, handles some special keys to display system menus, etc.
    The code originates from \c qkeymapper_win.cpp.
*/

static void clearKeyRecorderOnApplicationInActive(Qt::ApplicationState state);

QWindowsKeyMapper::QWindowsKeyMapper()
    : m_useRTLExtensions(false), m_keyGrabber(nullptr)
{
    memset(keyLayout, 0, sizeof(keyLayout));
    auto *app = static_cast<QGuiApplication *>(QGuiApplication::instance());
    QObject::connect(app, &QGuiApplication::applicationStateChanged,
                     app, clearKeyRecorderOnApplicationInActive);
    changeKeyboard();
}

QWindowsKeyMapper::~QWindowsKeyMapper()= default;

#ifndef LANG_PASHTO
#define LANG_PASHTO 0x63
#endif
#ifndef LANG_SYRIAC
#define LANG_SYRIAC 0x5a
#endif
#ifndef LANG_DIVEHI
#define LANG_DIVEHI 0x65
#endif
#ifndef VK_OEM_PLUS
#define VK_OEM_PLUS 0xBB
#endif
#ifndef VK_OEM_3
#define VK_OEM_3 0xC0
#endif

// Get scancode from the given message
static constexpr quint32 getScancode(const MSG &msg)
{
    const auto keyFlags = HIWORD(msg.lParam);
    quint32 scancode = LOBYTE(keyFlags);
    // if extended-key flag is on, the scan code consists of a sequence of two bytes,
    // where the first byte has a value of 0xe0.
    if ((keyFlags & KF_EXTENDED) != 0)
        scancode |= 0xE000;
    return scancode;
}

// Key recorder ------------------------------------------------------------------------[ start ] --
struct KeyRecord {
    KeyRecord(int c, int a, int s, const QString &t) : code(c), ascii(a), state(s), text(t) {}
    KeyRecord() {}

    int code;
    int ascii;
    int state;
    QString text;
};

// We need to record the pressed keys in order to decide, whether the key event is an autorepeat
// event. As soon as its state changes, the chain of autorepeat events will be broken.
static const int QT_MAX_KEY_RECORDINGS = 64; // User has LOTS of fingers...
struct KeyRecorder
{
    inline KeyRecord *findKey(int code, bool remove);
    inline void storeKey(int code, int ascii, int state, const QString& text);
    inline void clearKeys();

    int nrecs = 0;
    KeyRecord deleted_record; // A copy of last entry removed from records[]
    KeyRecord records[QT_MAX_KEY_RECORDINGS];
};
static KeyRecorder key_recorder;

static void clearKeyRecorderOnApplicationInActive(Qt::ApplicationState state)
{
    if (state == Qt::ApplicationInactive)
        key_recorder.clearKeys();
}

KeyRecord *KeyRecorder::findKey(int code, bool remove)
{
    KeyRecord *result = nullptr;
    for (int i = 0; i < nrecs; ++i) {
        if (records[i].code == code) {
            if (remove) {
                deleted_record = records[i];
                // Move rest down, and decrease count
                while (i + 1 < nrecs) {
                    records[i] = records[i + 1];
                    ++i;
                }
                --nrecs;
                result = &deleted_record;
            } else {
                result = &records[i];
            }
            break;
        }
    }
    return result;
}

void KeyRecorder::storeKey(int code, int ascii, int state, const QString& text)
{
    Q_ASSERT_X(nrecs != QT_MAX_KEY_RECORDINGS,
               "Internal KeyRecorder",
               "Keyboard recorder buffer overflow, consider increasing QT_MAX_KEY_RECORDINGS");

    if (nrecs == QT_MAX_KEY_RECORDINGS) {
        qWarning("Qt: Internal keyboard buffer overflow");
        return;
    }
    records[nrecs++] = KeyRecord(code,ascii,state,text);
}

void KeyRecorder::clearKeys()
{
    nrecs = 0;
}
// Key recorder --------------------------------------------------------------------------[ end ] --


// Key translation ---------------------------------------------------------------------[ start ] --
// Meaning of values:
//             0 = Character output key, needs keyboard driver mapping
//   Key_unknown = Unknown Virtual Key, no translation possible, ignore
static const uint KeyTbl[] = { // Keyboard mapping table
                        // Dec |  Hex | Windows Virtual key
    Qt::Key_unknown,    //   0   0x00
    Qt::Key_unknown,    //   1   0x01   VK_LBUTTON          | Left mouse button
    Qt::Key_unknown,    //   2   0x02   VK_RBUTTON          | Right mouse button
    Qt::Key_Cancel,     //   3   0x03   VK_CANCEL           | Control-Break processing
    Qt::Key_unknown,    //   4   0x04   VK_MBUTTON          | Middle mouse button
    Qt::Key_unknown,    //   5   0x05   VK_XBUTTON1         | X1 mouse button
    Qt::Key_unknown,    //   6   0x06   VK_XBUTTON2         | X2 mouse button
    Qt::Key_unknown,    //   7   0x07   -- unassigned --
    Qt::Key_Backspace,  //   8   0x08   VK_BACK             | BackSpace key
    Qt::Key_Tab,        //   9   0x09   VK_TAB              | Tab key
    Qt::Key_unknown,    //  10   0x0A   -- reserved --
    Qt::Key_unknown,    //  11   0x0B   -- reserved --
    Qt::Key_Clear,      //  12   0x0C   VK_CLEAR            | Clear key
    Qt::Key_Return,     //  13   0x0D   VK_RETURN           | Enter key
    Qt::Key_unknown,    //  14   0x0E   -- unassigned --
    Qt::Key_unknown,    //  15   0x0F   -- unassigned --
    Qt::Key_Shift,      //  16   0x10   VK_SHIFT            | Shift key
    Qt::Key_Control,    //  17   0x11   VK_CONTROL          | Ctrl key
    Qt::Key_Alt,        //  18   0x12   VK_MENU             | Alt key
    Qt::Key_Pause,      //  19   0x13   VK_PAUSE            | Pause key
    Qt::Key_CapsLock,   //  20   0x14   VK_CAPITAL          | Caps-Lock
    Qt::Key_unknown,    //  21   0x15   VK_KANA / VK_HANGUL | IME Kana or Hangul mode
    Qt::Key_unknown,    //  22   0x16   -- unassigned --
    Qt::Key_unknown,    //  23   0x17   VK_JUNJA            | IME Junja mode
    Qt::Key_unknown,    //  24   0x18   VK_FINAL            | IME final mode
    Qt::Key_unknown,    //  25   0x19   VK_HANJA / VK_KANJI | IME Hanja or Kanji mode
    Qt::Key_unknown,    //  26   0x1A   -- unassigned --
    Qt::Key_Escape,     //  27   0x1B   VK_ESCAPE           | Esc key
    Qt::Key_unknown,    //  28   0x1C   VK_CONVERT          | IME convert
    Qt::Key_unknown,    //  29   0x1D   VK_NONCONVERT       | IME non-convert
    Qt::Key_unknown,    //  30   0x1E   VK_ACCEPT           | IME accept
    Qt::Key_Mode_switch,//  31   0x1F   VK_MODECHANGE       | IME mode change request
    Qt::Key_Space,      //  32   0x20   VK_SPACE            | Spacebar
    Qt::Key_PageUp,     //  33   0x21   VK_PRIOR            | Page Up key
    Qt::Key_PageDown,   //  34   0x22   VK_NEXT             | Page Down key
    Qt::Key_End,        //  35   0x23   VK_END              | End key
    Qt::Key_Home,       //  36   0x24   VK_HOME             | Home key
    Qt::Key_Left,       //  37   0x25   VK_LEFT             | Left arrow key
    Qt::Key_Up,         //  38   0x26   VK_UP               | Up arrow key
    Qt::Key_Right,      //  39   0x27   VK_RIGHT            | Right arrow key
    Qt::Key_Down,       //  40   0x28   VK_DOWN             | Down arrow key
    Qt::Key_Select,     //  41   0x29   VK_SELECT           | Select key
    Qt::Key_Printer,    //  42   0x2A   VK_PRINT            | Print key
    Qt::Key_Execute,    //  43   0x2B   VK_EXECUTE          | Execute key
    Qt::Key_Print,      //  44   0x2C   VK_SNAPSHOT         | Print Screen key
    Qt::Key_Insert,     //  45   0x2D   VK_INSERT           | Ins key
    Qt::Key_Delete,     //  46   0x2E   VK_DELETE           | Del key
    Qt::Key_Help,       //  47   0x2F   VK_HELP             | Help key
    0,                  //  48   0x30   (VK_0)              | 0 key
    0,                  //  49   0x31   (VK_1)              | 1 key
    0,                  //  50   0x32   (VK_2)              | 2 key
    0,                  //  51   0x33   (VK_3)              | 3 key
    0,                  //  52   0x34   (VK_4)              | 4 key
    0,                  //  53   0x35   (VK_5)              | 5 key
    0,                  //  54   0x36   (VK_6)              | 6 key
    0,                  //  55   0x37   (VK_7)              | 7 key
    0,                  //  56   0x38   (VK_8)              | 8 key
    0,                  //  57   0x39   (VK_9)              | 9 key
    Qt::Key_unknown,    //  58   0x3A   -- unassigned --
    Qt::Key_unknown,    //  59   0x3B   -- unassigned --
    Qt::Key_unknown,    //  60   0x3C   -- unassigned --
    Qt::Key_unknown,    //  61   0x3D   -- unassigned --
    Qt::Key_unknown,    //  62   0x3E   -- unassigned --
    Qt::Key_unknown,    //  63   0x3F   -- unassigned --
    Qt::Key_unknown,    //  64   0x40   -- unassigned --
    0,                  //  65   0x41   (VK_A)              | A key
    0,                  //  66   0x42   (VK_B)              | B key
    0,                  //  67   0x43   (VK_C)              | C key
    0,                  //  68   0x44   (VK_D)              | D key
    0,                  //  69   0x45   (VK_E)              | E key
    0,                  //  70   0x46   (VK_F)              | F key
    0,                  //  71   0x47   (VK_G)              | G key
    0,                  //  72   0x48   (VK_H)              | H key
    0,                  //  73   0x49   (VK_I)              | I key
    0,                  //  74   0x4A   (VK_J)              | J key
    0,                  //  75   0x4B   (VK_K)              | K key
    0,                  //  76   0x4C   (VK_L)              | L key
    0,                  //  77   0x4D   (VK_M)              | M key
    0,                  //  78   0x4E   (VK_N)              | N key
    0,                  //  79   0x4F   (VK_O)              | O key
    0,                  //  80   0x50   (VK_P)              | P key
    0,                  //  81   0x51   (VK_Q)              | Q key
    0,                  //  82   0x52   (VK_R)              | R key
    0,                  //  83   0x53   (VK_S)              | S key
    0,                  //  84   0x54   (VK_T)              | T key
    0,                  //  85   0x55   (VK_U)              | U key
    0,                  //  86   0x56   (VK_V)              | V key
    0,                  //  87   0x57   (VK_W)              | W key
    0,                  //  88   0x58   (VK_X)              | X key
    0,                  //  89   0x59   (VK_Y)              | Y key
    0,                  //  90   0x5A   (VK_Z)              | Z key
    Qt::Key_Meta,       //  91   0x5B   VK_LWIN             | Left Windows  - MS Natural kbd
    Qt::Key_Meta,       //  92   0x5C   VK_RWIN             | Right Windows - MS Natural kbd
    Qt::Key_Menu,       //  93   0x5D   VK_APPS             | Application key-MS Natural kbd
    Qt::Key_unknown,    //  94   0x5E   -- reserved --
    Qt::Key_Sleep,      //  95   0x5F   VK_SLEEP
    Qt::Key_0,          //  96   0x60   VK_NUMPAD0          | Numeric keypad 0 key
    Qt::Key_1,          //  97   0x61   VK_NUMPAD1          | Numeric keypad 1 key
    Qt::Key_2,          //  98   0x62   VK_NUMPAD2          | Numeric keypad 2 key
    Qt::Key_3,          //  99   0x63   VK_NUMPAD3          | Numeric keypad 3 key
    Qt::Key_4,          // 100   0x64   VK_NUMPAD4          | Numeric keypad 4 key
    Qt::Key_5,          // 101   0x65   VK_NUMPAD5          | Numeric keypad 5 key
    Qt::Key_6,          // 102   0x66   VK_NUMPAD6          | Numeric keypad 6 key
    Qt::Key_7,          // 103   0x67   VK_NUMPAD7          | Numeric keypad 7 key
    Qt::Key_8,          // 104   0x68   VK_NUMPAD8          | Numeric keypad 8 key
    Qt::Key_9,          // 105   0x69   VK_NUMPAD9          | Numeric keypad 9 key
    Qt::Key_Asterisk,   // 106   0x6A   VK_MULTIPLY         | Multiply key
    Qt::Key_Plus,       // 107   0x6B   VK_ADD              | Add key
    Qt::Key_unknown,    // 108   0x6C   VK_SEPARATOR        | Separator key (locale-dependent)
    Qt::Key_Minus,      // 109   0x6D   VK_SUBTRACT         | Subtract key
    Qt::Key_unknown,    // 110   0x6E   VK_DECIMAL          | Decimal key (locale-dependent)
    Qt::Key_Slash,      // 111   0x6F   VK_DIVIDE           | Divide key
    Qt::Key_F1,         // 112   0x70   VK_F1               | F1 key
    Qt::Key_F2,         // 113   0x71   VK_F2               | F2 key
    Qt::Key_F3,         // 114   0x72   VK_F3               | F3 key
    Qt::Key_F4,         // 115   0x73   VK_F4               | F4 key
    Qt::Key_F5,         // 116   0x74   VK_F5               | F5 key
    Qt::Key_F6,         // 117   0x75   VK_F6               | F6 key
    Qt::Key_F7,         // 118   0x76   VK_F7               | F7 key
    Qt::Key_F8,         // 119   0x77   VK_F8               | F8 key
    Qt::Key_F9,         // 120   0x78   VK_F9               | F9 key
    Qt::Key_F10,        // 121   0x79   VK_F10              | F10 key
    Qt::Key_F11,        // 122   0x7A   VK_F11              | F11 key
    Qt::Key_F12,        // 123   0x7B   VK_F12              | F12 key
    Qt::Key_F13,        // 124   0x7C   VK_F13              | F13 key
    Qt::Key_F14,        // 125   0x7D   VK_F14              | F14 key
    Qt::Key_F15,        // 126   0x7E   VK_F15              | F15 key
    Qt::Key_F16,        // 127   0x7F   VK_F16              | F16 key
    Qt::Key_F17,        // 128   0x80   VK_F17              | F17 key
    Qt::Key_F18,        // 129   0x81   VK_F18              | F18 key
    Qt::Key_F19,        // 130   0x82   VK_F19              | F19 key
    Qt::Key_F20,        // 131   0x83   VK_F20              | F20 key
    Qt::Key_F21,        // 132   0x84   VK_F21              | F21 key
    Qt::Key_F22,        // 133   0x85   VK_F22              | F22 key
    Qt::Key_F23,        // 134   0x86   VK_F23              | F23 key
    Qt::Key_F24,        // 135   0x87   VK_F24              | F24 key
    Qt::Key_unknown,    // 136   0x88   -- unassigned --
    Qt::Key_unknown,    // 137   0x89   -- unassigned --
    Qt::Key_unknown,    // 138   0x8A   -- unassigned --
    Qt::Key_unknown,    // 139   0x8B   -- unassigned --
    Qt::Key_unknown,    // 140   0x8C   -- unassigned --
    Qt::Key_unknown,    // 141   0x8D   -- unassigned --
    Qt::Key_unknown,    // 142   0x8E   -- unassigned --
    Qt::Key_unknown,    // 143   0x8F   -- unassigned --
    Qt::Key_NumLock,    // 144   0x90   VK_NUMLOCK          | Num Lock key
    Qt::Key_ScrollLock, // 145   0x91   VK_SCROLL           | Scroll Lock key
                        // Fujitsu/OASYS kbd --------------------
    0, //Qt::Key_Jisho, // 146   0x92   VK_OEM_FJ_JISHO     | 'Dictionary' key /
                        //              VK_OEM_NEC_EQUAL  = key on numpad on NEC PC-9800 kbd
    Qt::Key_Massyo,     // 147   0x93   VK_OEM_FJ_MASSHOU   | 'Unregister word' key
    Qt::Key_Touroku,    // 148   0x94   VK_OEM_FJ_TOUROKU   | 'Register word' key
    0, //Qt::Key_Oyayubi_Left,//149   0x95  VK_OEM_FJ_LOYA  | 'Left OYAYUBI' key
    0, //Qt::Key_Oyayubi_Right,//150  0x96  VK_OEM_FJ_ROYA  | 'Right OYAYUBI' key
    Qt::Key_unknown,    // 151   0x97   -- unassigned --
    Qt::Key_unknown,    // 152   0x98   -- unassigned --
    Qt::Key_unknown,    // 153   0x99   -- unassigned --
    Qt::Key_unknown,    // 154   0x9A   -- unassigned --
    Qt::Key_unknown,    // 155   0x9B   -- unassigned --
    Qt::Key_unknown,    // 156   0x9C   -- unassigned --
    Qt::Key_unknown,    // 157   0x9D   -- unassigned --
    Qt::Key_unknown,    // 158   0x9E   -- unassigned --
    Qt::Key_unknown,    // 159   0x9F   -- unassigned --
    Qt::Key_Shift,      // 160   0xA0   VK_LSHIFT           | Left Shift key
    Qt::Key_Shift,      // 161   0xA1   VK_RSHIFT           | Right Shift key
    Qt::Key_Control,    // 162   0xA2   VK_LCONTROL         | Left Ctrl key
    Qt::Key_Control,    // 163   0xA3   VK_RCONTROL         | Right Ctrl key
    Qt::Key_Alt,        // 164   0xA4   VK_LMENU            | Left Menu key
    Qt::Key_Alt,        // 165   0xA5   VK_RMENU            | Right Menu key
    Qt::Key_Back,       // 166   0xA6   VK_BROWSER_BACK     | Browser Back key
    Qt::Key_Forward,    // 167   0xA7   VK_BROWSER_FORWARD  | Browser Forward key
    Qt::Key_Refresh,    // 168   0xA8   VK_BROWSER_REFRESH  | Browser Refresh key
    Qt::Key_Stop,       // 169   0xA9   VK_BROWSER_STOP     | Browser Stop key
    Qt::Key_Search,     // 170   0xAA   VK_BROWSER_SEARCH   | Browser Search key
    Qt::Key_Favorites,  // 171   0xAB   VK_BROWSER_FAVORITES| Browser Favorites key
    Qt::Key_HomePage,   // 172   0xAC   VK_BROWSER_HOME     | Browser Start and Home key
    Qt::Key_VolumeMute, // 173   0xAD   VK_VOLUME_MUTE      | Volume Mute key
    Qt::Key_VolumeDown, // 174   0xAE   VK_VOLUME_DOWN      | Volume Down key
    Qt::Key_VolumeUp,   // 175   0xAF   VK_VOLUME_UP        | Volume Up key
    Qt::Key_MediaNext,  // 176   0xB0   VK_MEDIA_NEXT_TRACK | Next Track key
    Qt::Key_MediaPrevious, //177 0xB1   VK_MEDIA_PREV_TRACK | Previous Track key
    Qt::Key_MediaStop,  // 178   0xB2   VK_MEDIA_STOP       | Stop Media key
    Qt::Key_MediaTogglePlayPause,
                        // 179   0xB3   VK_MEDIA_PLAY_PAUSE | Play/Pause Media key
    Qt::Key_LaunchMail, // 180   0xB4   VK_LAUNCH_MAIL      | Start Mail key
    Qt::Key_LaunchMedia,// 181   0xB5   VK_LAUNCH_MEDIA_SELECT Select Media key
    Qt::Key_Launch0,    // 182   0xB6   VK_LAUNCH_APP1      | Start Application 1 key
    Qt::Key_Launch1,    // 183   0xB7   VK_LAUNCH_APP2      | Start Application 2 key
    Qt::Key_unknown,    // 184   0xB8   -- reserved --
    Qt::Key_unknown,    // 185   0xB9   -- reserved --
    0,                  // 186   0xBA   VK_OEM_1            | ';:' for US
    0,                  // 187   0xBB   VK_OEM_PLUS         | '+' any country
    0,                  // 188   0xBC   VK_OEM_COMMA        | ',' any country
    0,                  // 189   0xBD   VK_OEM_MINUS        | '-' any country
    0,                  // 190   0xBE   VK_OEM_PERIOD       | '.' any country
    0,                  // 191   0xBF   VK_OEM_2            | '/?' for US
    0,                  // 192   0xC0   VK_OEM_3            | '`~' for US
    Qt::Key_unknown,    // 193   0xC1   -- reserved --
    Qt::Key_unknown,    // 194   0xC2   -- reserved --
    Qt::Key_unknown,    // 195   0xC3   -- reserved --
    Qt::Key_unknown,    // 196   0xC4   -- reserved --
    Qt::Key_unknown,    // 197   0xC5   -- reserved --
    Qt::Key_unknown,    // 198   0xC6   -- reserved --
    Qt::Key_unknown,    // 199   0xC7   -- reserved --
    Qt::Key_unknown,    // 200   0xC8   -- reserved --
    Qt::Key_unknown,    // 201   0xC9   -- reserved --
    Qt::Key_unknown,    // 202   0xCA   -- reserved --
    Qt::Key_unknown,    // 203   0xCB   -- reserved --
    Qt::Key_unknown,    // 204   0xCC   -- reserved --
    Qt::Key_unknown,    // 205   0xCD   -- reserved --
    Qt::Key_unknown,    // 206   0xCE   -- reserved --
    Qt::Key_unknown,    // 207   0xCF   -- reserved --
    Qt::Key_unknown,    // 208   0xD0   -- reserved --
    Qt::Key_unknown,    // 209   0xD1   -- reserved --
    Qt::Key_unknown,    // 210   0xD2   -- reserved --
    Qt::Key_unknown,    // 211   0xD3   -- reserved --
    Qt::Key_unknown,    // 212   0xD4   -- reserved --
    Qt::Key_unknown,    // 213   0xD5   -- reserved --
    Qt::Key_unknown,    // 214   0xD6   -- reserved --
    Qt::Key_unknown,    // 215   0xD7   -- reserved --
    Qt::Key_unknown,    // 216   0xD8   -- unassigned --
    Qt::Key_unknown,    // 217   0xD9   -- unassigned --
    Qt::Key_unknown,    // 218   0xDA   -- unassigned --
    0,                  // 219   0xDB   VK_OEM_4            | '[{' for US
    0,                  // 220   0xDC   VK_OEM_5            | '\|' for US
    0,                  // 221   0xDD   VK_OEM_6            | ']}' for US
    0,                  // 222   0xDE   VK_OEM_7            | ''"' for US
    0,                  // 223   0xDF   VK_OEM_8
    Qt::Key_unknown,    // 224   0xE0   -- reserved --
    Qt::Key_unknown,    // 225   0xE1   VK_OEM_AX           | 'AX' key on Japanese AX kbd
    Qt::Key_unknown,    // 226   0xE2   VK_OEM_102          | "<>" or "\|" on RT 102-key kbd
    Qt::Key_unknown,    // 227   0xE3   VK_ICO_HELP         | Help key on ICO
    Qt::Key_unknown,    // 228   0xE4   VK_ICO_00           | 00 key on ICO
    Qt::Key_unknown,    // 229   0xE5   VK_PROCESSKEY       | IME Process key
    Qt::Key_unknown,    // 230   0xE6   VK_ICO_CLEAR        |
    Qt::Key_unknown,    // 231   0xE7   VK_PACKET           | Unicode char as keystrokes
    Qt::Key_unknown,    // 232   0xE8   -- unassigned --
                        // Nokia/Ericsson definitions ---------------
    Qt::Key_unknown,    // 233   0xE9   VK_OEM_RESET
    Qt::Key_unknown,    // 234   0xEA   VK_OEM_JUMP
    Qt::Key_unknown,    // 235   0xEB   VK_OEM_PA1
    Qt::Key_unknown,    // 236   0xEC   VK_OEM_PA2
    Qt::Key_unknown,    // 237   0xED   VK_OEM_PA3
    Qt::Key_unknown,    // 238   0xEE   VK_OEM_WSCTRL
    Qt::Key_unknown,    // 239   0xEF   VK_OEM_CUSEL
    Qt::Key_unknown,    // 240   0xF0   VK_OEM_ATTN
    Qt::Key_unknown,    // 241   0xF1   VK_OEM_FINISH
    Qt::Key_unknown,    // 242   0xF2   VK_OEM_COPY
    Qt::Key_unknown,    // 243   0xF3   VK_OEM_AUTO
    Qt::Key_unknown,    // 244   0xF4   VK_OEM_ENLW
    Qt::Key_unknown,    // 245   0xF5   VK_OEM_BACKTAB
    Qt::Key_unknown,    // 246   0xF6   VK_ATTN             | Attn key
    Qt::Key_unknown,    // 247   0xF7   VK_CRSEL            | CrSel key
    Qt::Key_unknown,    // 248   0xF8   VK_EXSEL            | ExSel key
    Qt::Key_unknown,    // 249   0xF9   VK_EREOF            | Erase EOF key
    Qt::Key_Play,       // 250   0xFA   VK_PLAY             | Play key
    Qt::Key_Zoom,       // 251   0xFB   VK_ZOOM             | Zoom key
    Qt::Key_unknown,    // 252   0xFC   VK_NONAME           | Reserved
    Qt::Key_unknown,    // 253   0xFD   VK_PA1              | PA1 key
    Qt::Key_Clear,      // 254   0xFE   VK_OEM_CLEAR        | Clear key
    0
};

static const uint CmdTbl[] = { // Multimedia keys mapping table
                            // Dec |  Hex | AppCommand
    Qt::Key_unknown,        //   0   0x00
    Qt::Key_Back,           //   1   0x01   APPCOMMAND_BROWSER_BACKWARD
    Qt::Key_Forward,        //   2   0x02   APPCOMMAND_BROWSER_FORWARD
    Qt::Key_Refresh,        //   3   0x03   APPCOMMAND_BROWSER_REFRESH
    Qt::Key_Stop,           //   4   0x04   APPCOMMAND_BROWSER_STOP
    Qt::Key_Search,         //   5   0x05   APPCOMMAND_BROWSER_SEARCH
    Qt::Key_Favorites,      //   6   0x06   APPCOMMAND_BROWSER_FAVORITES
    Qt::Key_Home,           //   7   0x07   APPCOMMAND_BROWSER_HOME
    Qt::Key_VolumeMute,     //   8   0x08   APPCOMMAND_VOLUME_MUTE
    Qt::Key_VolumeDown,     //   9   0x09   APPCOMMAND_VOLUME_DOWN
    Qt::Key_VolumeUp,       //  10   0x0a   APPCOMMAND_VOLUME_UP
    Qt::Key_MediaNext,      //  11   0x0b   APPCOMMAND_MEDIA_NEXTTRACK
    Qt::Key_MediaPrevious,  //  12   0x0c   APPCOMMAND_MEDIA_PREVIOUSTRACK
    Qt::Key_MediaStop,      //  13   0x0d   APPCOMMAND_MEDIA_STOP
    Qt::Key_MediaTogglePlayPause,   //  14   0x0e   APPCOMMAND_MEDIA_PLAYPAUSE
    Qt::Key_LaunchMail,     //  15   0x0f   APPCOMMAND_LAUNCH_MAIL
    Qt::Key_LaunchMedia,    //  16   0x10   APPCOMMAND_LAUNCH_MEDIA_SELECT
    Qt::Key_Launch0,        //  17   0x11   APPCOMMAND_LAUNCH_APP1
    Qt::Key_Launch1,        //  18   0x12   APPCOMMAND_LAUNCH_APP2
    Qt::Key_BassDown,       //  19   0x13   APPCOMMAND_BASS_DOWN
    Qt::Key_BassBoost,      //  20   0x14   APPCOMMAND_BASS_BOOST
    Qt::Key_BassUp,         //  21   0x15   APPCOMMAND_BASS_UP
    Qt::Key_TrebleDown,     //  22   0x16   APPCOMMAND_TREBLE_DOWN
    Qt::Key_TrebleUp,       //  23   0x17   APPCOMMAND_TREBLE_UP
    Qt::Key_MicMute,        //  24   0x18   APPCOMMAND_MICROPHONE_VOLUME_MUTE
    Qt::Key_MicVolumeDown,  //  25   0x19   APPCOMMAND_MICROPHONE_VOLUME_DOWN
    Qt::Key_MicVolumeUp,    //  26   0x1a   APPCOMMAND_MICROPHONE_VOLUME_UP
    Qt::Key_Help,           //  27   0x1b   APPCOMMAND_HELP
    Qt::Key_Find,           //  28   0x1c   APPCOMMAND_FIND
    Qt::Key_New,            //  29   0x1d   APPCOMMAND_NEW
    Qt::Key_Open,           //  30   0x1e   APPCOMMAND_OPEN
    Qt::Key_Close,          //  31   0x1f   APPCOMMAND_CLOSE
    Qt::Key_Save,           //  32   0x20   APPCOMMAND_SAVE
    Qt::Key_Printer,        //  33   0x21   APPCOMMAND_PRINT
    Qt::Key_Undo,           //  34   0x22   APPCOMMAND_UNDO
    Qt::Key_Redo,           //  35   0x23   APPCOMMAND_REDO
    Qt::Key_Copy,           //  36   0x24   APPCOMMAND_COPY
    Qt::Key_Cut,            //  37   0x25   APPCOMMAND_CUT
    Qt::Key_Paste,          //  38   0x26   APPCOMMAND_PASTE
    Qt::Key_Reply,          //  39   0x27   APPCOMMAND_REPLY_TO_MAIL
    Qt::Key_MailForward,    //  40   0x28   APPCOMMAND_FORWARD_MAIL
    Qt::Key_Send,           //  41   0x29   APPCOMMAND_SEND_MAIL
    Qt::Key_Spell,          //  42   0x2a   APPCOMMAND_SPELL_CHECK
    Qt::Key_unknown,        //  43   0x2b   APPCOMMAND_DICTATE_OR_COMMAND_CONTROL_TOGGLE
    Qt::Key_unknown,        //  44   0x2c   APPCOMMAND_MIC_ON_OFF_TOGGLE
    Qt::Key_unknown,        //  45   0x2d   APPCOMMAND_CORRECTION_LIST
    Qt::Key_MediaPlay,      //  46   0x2e   APPCOMMAND_MEDIA_PLAY
    Qt::Key_MediaPause,     //  47   0x2f   APPCOMMAND_MEDIA_PAUSE
    Qt::Key_MediaRecord,    //  48   0x30   APPCOMMAND_MEDIA_RECORD
    Qt::Key_AudioForward,   //  49   0x31   APPCOMMAND_MEDIA_FAST_FORWARD
    Qt::Key_AudioRewind,    //  50   0x32   APPCOMMAND_MEDIA_REWIND
    Qt::Key_ChannelDown,    //  51   0x33   APPCOMMAND_MEDIA_CHANNEL_DOWN
    Qt::Key_ChannelUp       //  52   0x34   APPCOMMAND_MEDIA_CHANNEL_UP
};

// Possible modifier states.
// NOTE: The order of these states match the order in QWindowsKeyMapper::updatePossibleKeyCodes()!
static const Qt::KeyboardModifiers ModsTbl[] = {
    Qt::NoModifier,                                             // 0
    Qt::ShiftModifier,                                          // 1
    Qt::ControlModifier,                                        // 2
    Qt::ControlModifier | Qt::ShiftModifier,                    // 3
    Qt::AltModifier,                                            // 4
    Qt::AltModifier | Qt::ShiftModifier,                        // 5
    Qt::AltModifier | Qt::ControlModifier,                      // 6
    Qt::AltModifier | Qt::ShiftModifier | Qt::ControlModifier,  // 7
    Qt::NoModifier,                                             // Fall-back to raw Key_*
};
static const size_t NumMods = sizeof ModsTbl / sizeof *ModsTbl;
static_assert((NumMods == KeyboardLayoutItem::NumQtKeys));

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug d, const KeyboardLayoutItem &k)
{
    QDebugStateSaver saver(d);
    d.nospace();
    d << "KeyboardLayoutItem(";
    if (k.exists) {
        for (size_t i = 0; i < NumMods; ++i) {
            if (const quint32 qtKey = k.qtKey[i]) {
                d << '[' << i << ' ';
                QtDebugUtils::formatQFlags(d, ModsTbl[i]);
                d << ' ' << Qt::hex << Qt::showbase << qtKey << Qt::dec << Qt::noshowbase << ' ';
                QtDebugUtils::formatQEnum(d, Qt::Key(qtKey));
                if (qtKey >= 32 && qtKey < 128)
                    d << " '" << char(qtKey)  << '\'';
                if (k.deadkeys & (1<<i))
                    d << "  deadkey";
                d << "] ";
            }
        }
    }
    d << ')';
    return d;
}
#endif // QT_NO_DEBUG_STREAM

/**
  Remap return or action key to select key for windows mobile.
*/
inline quint32 winceKeyBend(quint32 keyCode)
{
    return KeyTbl[keyCode];
}

// Translate a VK into a Qt key code, or unicode character
static inline quint32 toKeyOrUnicode(quint32 vk, quint32 scancode, unsigned char *kbdBuffer, bool *isDeadkey = nullptr)
{
    Q_ASSERT(vk > 0 && vk < 256);
    quint32 code = 0;
    QChar unicodeBuffer[5];
    int res = ToUnicode(vk, scancode, kbdBuffer, reinterpret_cast<LPWSTR>(unicodeBuffer), 5, 0);
    // When Ctrl modifier is used ToUnicode does not return correct values. In order to assign the
    // right key the control modifier is removed for just that function if the previous call failed.
    if (res == 0 && kbdBuffer[VK_CONTROL]) {
        const unsigned char controlState = kbdBuffer[VK_CONTROL];
        kbdBuffer[VK_CONTROL] = 0;
        res = ToUnicode(vk, scancode, kbdBuffer, reinterpret_cast<LPWSTR>(unicodeBuffer), 5, 0);
        kbdBuffer[VK_CONTROL] = controlState;
    }
    if (res)
        code = unicodeBuffer[0].toUpper().unicode();

    // Qt::Key_*'s are not encoded below 0x20, so try again, and DEL keys (0x7f) is encoded with a
    // proper Qt::Key_ code
    if (code < 0x20 || code == 0x7f) // Handles res==0 too
        code = winceKeyBend(vk);

    if (isDeadkey)
        *isDeadkey = (res == -1);

    return code == Qt::Key_unknown ? 0 : code;
}

static inline int asciiToKeycode(char a, int state)
{
    a = QtMiscUtils::toAsciiUpper(a);
    if ((state & Qt::ControlModifier) != 0) {
        if (a >= 0 && a <= 31)              // Ctrl+@..Ctrl+A..CTRL+Z..Ctrl+_
            a += '@';                       // to @..A..Z.._
    }
    return a & 0xff;
}

// Key translation -----------------------------------------------------------------------[ end ]---


// Keyboard map private ----------------------------------------------------------------[ start ]---

void QWindowsKeyMapper::deleteLayouts()
{
    for (KeyboardLayoutItem &k : keyLayout)
        k.exists = false;
}

void QWindowsKeyMapper::changeKeyboard()
{
    deleteLayouts();

    /* MAKELCID()'s first argument is a WORD, and GetKeyboardLayout()
     * returns a DWORD. */

    LCID newLCID = MAKELCID(quintptr(GetKeyboardLayout(0)), SORT_DEFAULT);
//    keyboardInputLocale = qt_localeFromLCID(newLCID);

    bool bidi = false;
    wchar_t LCIDFontSig[16];
    if (GetLocaleInfo(newLCID, LOCALE_FONTSIGNATURE, LCIDFontSig, sizeof(LCIDFontSig) / sizeof(wchar_t))
        && (LCIDFontSig[7] & wchar_t(0x0800)))
        bidi = true;

    keyboardInputDirection = bidi ? Qt::RightToLeft : Qt::LeftToRight;
    m_seenAltGr = false;
}

// Helper function that is used when obtaining the list of characters that can be produced by one key and
// every possible combination of modifiers
inline void setKbdState(unsigned char *kbd, bool shift, bool ctrl, bool alt)
{
    kbd[VK_LSHIFT  ] = (shift ? 0x80 : 0);
    kbd[VK_SHIFT   ] = (shift ? 0x80 : 0);
    kbd[VK_LCONTROL] = (ctrl ? 0x80 : 0);
    kbd[VK_CONTROL ] = (ctrl ? 0x80 : 0);
    kbd[VK_RMENU   ] = (alt ? 0x80 : 0);
    kbd[VK_MENU    ] = (alt ? 0x80 : 0);
}

// Adds the msg's key to keyLayout if it is not yet present there
void QWindowsKeyMapper::updateKeyMap(const MSG &msg)
{
    unsigned char kbdBuffer[256]; // Will hold the complete keyboard state
    GetKeyboardState(kbdBuffer);
    const quint32 scancode = getScancode(msg);
    updatePossibleKeyCodes(kbdBuffer, scancode, quint32(msg.wParam));
}

// Fills keyLayout for that vk_key. Values are all characters one can type using that key
// (in connection with every combination of modifiers) and whether these "characters" are
// dead keys.
void QWindowsKeyMapper::updatePossibleKeyCodes(unsigned char *kbdBuffer, quint32 scancode,
                                               quint32 vk_key)
{
    if (!vk_key || (keyLayout[vk_key].exists && !keyLayout[vk_key].dirty))
        return;

    // Copy keyboard state, so we can modify and query output for each possible permutation
    unsigned char buffer[256];
    memcpy(buffer, kbdBuffer, sizeof(buffer));
    // Always 0, as Windows doesn't treat these as modifiers;
    buffer[VK_LWIN    ] = 0;
    buffer[VK_RWIN    ] = 0;
    buffer[VK_CAPITAL ] = 0;
    buffer[VK_NUMLOCK ] = 0;
    buffer[VK_SCROLL  ] = 0;
    // Always 0, since we'll only change the other versions
    buffer[VK_RSHIFT  ] = 0;
    buffer[VK_RCONTROL] = 0;
    buffer[VK_LMENU   ] = 0; // Use right Alt, since left Ctrl + right Alt is considered AltGraph

    // keyLayout contains the actual characters which can be written using the vk_key together with the
    // different modifiers. '2' together with shift will for example cause the character
    // to be @ for a US key layout (thus keyLayout[vk_key].qtKey[1] will be @). In addition to that
    // it stores whether the resulting key is a dead key as these keys have to be handled later.
    bool isDeadKey = false;
    keyLayout[vk_key].deadkeys = 0;
    keyLayout[vk_key].dirty = false;
    keyLayout[vk_key].exists = true;
    setKbdState(buffer, false, false, false);
    keyLayout[vk_key].qtKey[0] = toKeyOrUnicode(vk_key, scancode, buffer, &isDeadKey);
    keyLayout[vk_key].deadkeys |= isDeadKey ? 0x01 : 0;
    setKbdState(buffer, true, false, false);
    keyLayout[vk_key].qtKey[1] = toKeyOrUnicode(vk_key, scancode, buffer, &isDeadKey);
    keyLayout[vk_key].deadkeys |= isDeadKey ? 0x02 : 0;
    setKbdState(buffer, false, true, false);
    keyLayout[vk_key].qtKey[2] = toKeyOrUnicode(vk_key, scancode, buffer, &isDeadKey);
    keyLayout[vk_key].deadkeys |= isDeadKey ? 0x04 : 0;
    setKbdState(buffer, true, true, false);
    keyLayout[vk_key].qtKey[3] = toKeyOrUnicode(vk_key, scancode, buffer, &isDeadKey);
    keyLayout[vk_key].deadkeys |= isDeadKey ? 0x08 : 0;
    setKbdState(buffer, false, false, true);
    keyLayout[vk_key].qtKey[4] = toKeyOrUnicode(vk_key, scancode, buffer, &isDeadKey);
    keyLayout[vk_key].deadkeys |= isDeadKey ? 0x10 : 0;
    setKbdState(buffer, true, false, true);
    keyLayout[vk_key].qtKey[5] = toKeyOrUnicode(vk_key, scancode, buffer, &isDeadKey);
    keyLayout[vk_key].deadkeys |= isDeadKey ? 0x20 : 0;
    setKbdState(buffer, false, true, true);
    keyLayout[vk_key].qtKey[6] = toKeyOrUnicode(vk_key, scancode, buffer, &isDeadKey);
    keyLayout[vk_key].deadkeys |= isDeadKey ? 0x40 : 0;
    setKbdState(buffer, true, true, true);
    keyLayout[vk_key].qtKey[7] = toKeyOrUnicode(vk_key, scancode, buffer, &isDeadKey);
    keyLayout[vk_key].deadkeys |= isDeadKey ? 0x80 : 0;
    // Add a fall back key for layouts which don't do composition and show non-latin1 characters
    quint32 fallbackKey = winceKeyBend(vk_key);
    if (!fallbackKey || fallbackKey == Qt::Key_unknown) {
        fallbackKey = 0;
        if (vk_key != keyLayout[vk_key].qtKey[0] && vk_key != keyLayout[vk_key].qtKey[1]
            && vk_key < 0x5B && vk_key > 0x2F)
            fallbackKey = vk_key;
    }
    keyLayout[vk_key].qtKey[8] = fallbackKey;

    // If one of the values inserted into the keyLayout above, can be considered a dead key, we have
    // to run the workaround below.
    if (keyLayout[vk_key].deadkeys) {
        // Push a Space, then the original key through the low-level ToAscii functions.
        // We do this because these functions (ToAscii / ToUnicode) will alter the internal state of
        // the keyboard driver By doing the following, we set the keyboard driver state back to what
        // it was before we wrecked it with the code above.
        // We need to push the space with an empty keystate map, since the driver checks the map for
        // transitions in modifiers, so this helps us capture all possible deadkeys.
        unsigned char emptyBuffer[256];
        memset(emptyBuffer, 0, sizeof(emptyBuffer));
        ::ToAscii(VK_SPACE, 0, emptyBuffer, reinterpret_cast<LPWORD>(&buffer), 0);
        ::ToAscii(vk_key, scancode, kbdBuffer, reinterpret_cast<LPWORD>(&buffer), 0);
    }
    qCDebug(lcQpaEvents) << __FUNCTION__ << "for virtual key="
        << Qt::hex << Qt::showbase << vk_key << Qt::dec << Qt::noshowbase << keyLayout[vk_key];
}

static inline QString messageKeyText(const MSG &msg)
{
    const QChar ch = QChar(ushort(msg.wParam));
    return ch.isNull() ? QString() : QString(ch);
}

[[nodiscard]] static inline int getTitleBarHeight(const HWND hwnd)
{
    const UINT dpi = GetDpiForWindow(hwnd);
    const int captionHeight = GetSystemMetricsForDpi(SM_CYCAPTION, dpi);
    if (IsZoomed(hwnd))
        return captionHeight;
    // The frame height should also be taken into account if the window
    // is not maximized.
    const int frameHeight = GetSystemMetricsForDpi(SM_CYSIZEFRAME, dpi)
                            + GetSystemMetricsForDpi(SM_CXPADDEDBORDER, dpi);
    return captionHeight + frameHeight;
}

[[nodiscard]] static inline bool isSystemMenuOffsetNeeded(const Qt::WindowFlags flags)
{
    static constexpr const Qt::WindowFlags titleBarHints =
        Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::WindowContextHelpButtonHint;
    return (flags & Qt::WindowSystemMenuHint) && (flags & Qt::WindowTitleHint) && !(flags & titleBarHints)
           && (flags & (Qt::FramelessWindowHint | Qt::CustomizeWindowHint));
}

static void showSystemMenu(QWindow* w)
{
    QWindow *topLevel = QWindowsWindow::topLevelOf(w);
    HWND topLevelHwnd = QWindowsWindow::handleOf(topLevel);
    HMENU menu = GetSystemMenu(topLevelHwnd, FALSE);
    if (!menu)
        return; // no menu for this window

#define enabled (MF_BYCOMMAND | MFS_ENABLED)
#define disabled (MF_BYCOMMAND | MFS_GRAYED)

    EnableMenuItem(menu, SC_MINIMIZE, (topLevel->flags() & Qt::WindowMinimizeButtonHint) ? enabled : disabled);
    const bool maximized = IsZoomed(topLevelHwnd);

    EnableMenuItem(menu, SC_MAXIMIZE, !(topLevel->flags() & Qt::WindowMaximizeButtonHint) || maximized ? disabled : enabled);

    // We should _not_ check with the setFixedSize(x,y) case here, since Windows is not able to check
    // this and our menu here would be out-of-sync with the menu produced by mouse-click on the
    // System Menu, or right-click on the title bar.
    EnableMenuItem(menu, SC_SIZE, (topLevel->flags() & Qt::MSWindowsFixedSizeDialogHint) || maximized ? disabled : enabled);
    EnableMenuItem(menu, SC_MOVE, maximized ? disabled : enabled);
    EnableMenuItem(menu, SC_CLOSE, enabled);
    EnableMenuItem(menu, SC_RESTORE, maximized ? enabled : disabled);

    // Highlight the first entry in the menu, this is what native Win32 applications usually do.
    HiliteMenuItem(topLevelHwnd, menu, SC_RESTORE, MF_BYCOMMAND | MFS_HILITE);

    // Set bold on close menu item
    SetMenuDefaultItem(menu, SC_CLOSE, FALSE);

#undef enabled
#undef disabled

    const QPoint pos = QHighDpi::toNativePixels(topLevel->geometry().topLeft(), topLevel);
    const int titleBarOffset = isSystemMenuOffsetNeeded(topLevel->flags()) ? getTitleBarHeight(topLevelHwnd) : 0;
    const int ret = TrackPopupMenuEx(menu,
                               TPM_LEFTALIGN | TPM_TOPALIGN | TPM_NONOTIFY | TPM_RETURNCMD,
                               pos.x(), pos.y() + titleBarOffset,
                               topLevelHwnd,
                               nullptr);

    // Remove the highlight of the restore menu item, otherwise when the user right-clicks
    // on the title bar, the popuped system menu will also highlight the restore item, which
    // is not appropriate, it should only be highlighted if the menu is brought up by keyboard.
    HiliteMenuItem(topLevelHwnd, menu, SC_RESTORE, MF_BYCOMMAND | MFS_UNHILITE);

    if (ret)
        qWindowsWndProc(topLevelHwnd, WM_SYSCOMMAND, WPARAM(ret), 0);
}

static inline void sendExtendedPressRelease(QWindow *w, unsigned long timestamp, int k,
                                            Qt::KeyboardModifiers mods,
                                            quint32 nativeScanCode,
                                            quint32 nativeVirtualKey,
                                            quint32 nativeModifiers,
                                            const QString & text = QString(),
                                            bool autorep = false,
                                            ushort count = 1)
{
    QWindowSystemInterface::handleExtendedKeyEvent(w, timestamp, QEvent::KeyPress, k, mods, nativeScanCode, nativeVirtualKey, nativeModifiers, text, autorep, count);
    QWindowSystemInterface::handleExtendedKeyEvent(w, timestamp, QEvent::KeyRelease, k, mods, nativeScanCode, nativeVirtualKey, nativeModifiers, text, autorep, count);
}

/*!
    \brief To be called from the window procedure.
*/

bool QWindowsKeyMapper::translateKeyEvent(QWindow *widget, HWND hwnd,
                                          const MSG &msg, LRESULT *result)
{
    *result = 0;

    // Reset layout map when system keyboard layout is changed
    if (msg.message == WM_INPUTLANGCHANGE) {
        changeKeyboard();
        return true;
    }

#if defined(WM_APPCOMMAND)
    if (msg.message == WM_APPCOMMAND)
        return translateMultimediaKeyEventInternal(widget, msg);
#endif

    // WM_(IME_)CHAR messages already contain the character in question so there is
    // no need to fiddle with our key map. In any other case add this key to the
    // keymap if it is not present yet.
    if (msg.message != WM_CHAR && msg.message != WM_IME_CHAR)
        updateKeyMap(msg);

    MSG peekedMsg;
    // consume dead chars?(for example, typing '`','a' resulting in a-accent).
    if (PeekMessage(&peekedMsg, hwnd, 0, 0, PM_NOREMOVE) && peekedMsg.message == WM_DEADCHAR)
        return true;

    return translateKeyEventInternal(widget, msg, false, result);
}

bool QWindowsKeyMapper::translateMultimediaKeyEventInternal(QWindow *window, const MSG &msg)
{
#if defined(WM_APPCOMMAND)
    const int cmd = GET_APPCOMMAND_LPARAM(msg.lParam);
    // QTBUG-57198, do not send mouse-synthesized commands as key events in addition
    bool skipPressRelease = false;
    switch (GET_DEVICE_LPARAM(msg.lParam)) {
    case FAPPCOMMAND_MOUSE:
        return false;
    case FAPPCOMMAND_KEY:
        // QTBUG-62838, use WM_KEYDOWN/WM_KEYUP for commands that are reflected
        // in VK(s) like VK_MEDIA_NEXT_TRACK, to get correct codes and autorepeat.
        // Don't do that for APPCOMMAND_BROWSER_HOME as that one does not trigger two events.
        if (cmd != APPCOMMAND_BROWSER_HOME)
            skipPressRelease = true;
        break;
    }

    const int dwKeys = GET_KEYSTATE_LPARAM(msg.lParam);
    int state = 0;
    state |= (dwKeys & MK_SHIFT ? int(Qt::ShiftModifier) : 0);
    state |= (dwKeys & MK_CONTROL ? int(Qt::ControlModifier) : 0);

    QWindow *receiver = m_keyGrabber ? m_keyGrabber : window;

    if (cmd < 0 || cmd > 52)
        return false;

    const int qtKey = int(CmdTbl[cmd]);
    if (!skipPressRelease)
        sendExtendedPressRelease(receiver, msg.time, qtKey, Qt::KeyboardModifier(state), 0, 0, 0);
    // QTBUG-43343: Make sure to return false if Qt does not handle the key, otherwise,
    // the keys are not passed to the active media player.
# if QT_CONFIG(shortcut)
    const QKeySequence sequence(Qt::Modifier(state) | Qt::Key(qtKey));
    return QGuiApplicationPrivate::instance()->shortcutMap.hasShortcutForKeySequence(sequence);
# else
    return false;
# endif
#else
    Q_UNREACHABLE();
    return false;
#endif
}

// QTBUG-69317: Check for AltGr found on some keyboards
// which is a sequence of left Ctrl (SYSKEY) + right Menu (Alt).
static bool isAltGr(MSG *msg)
{
    enum : LONG_PTR { RightFlag = 0x1000000 };
    if (msg->wParam != VK_CONTROL || (msg->lParam & RightFlag) != 0
        || (msg->message != WM_KEYDOWN && msg->message != WM_SYSKEYUP)) {
        return false;
    }
    const UINT expectedMessage = msg->message == WM_SYSKEYUP
        ? WM_KEYUP : msg->message;
    MSG peekedMsg;
    if (PeekMessage(&peekedMsg, msg->hwnd, 0, 0, PM_NOREMOVE) == FALSE
        || peekedMsg.message != expectedMessage || peekedMsg.wParam != VK_MENU
        || (peekedMsg.lParam & RightFlag) == 0) {
        return false;
    }
    *msg = peekedMsg;
    PeekMessage(&peekedMsg, msg->hwnd, 0, 0, PM_REMOVE);
    return true;
}

bool QWindowsKeyMapper::translateKeyEventInternal(QWindow *window, MSG msg,
                                                  bool /* grab */, LRESULT *lResult)
{
    const bool altGr = m_detectAltGrModifier && isAltGr(&msg);
    if (altGr)
        m_seenAltGr = true;
    const UINT msgType = msg.message;

    const quint32 scancode = getScancode(msg);
    auto vk_key = quint32(msg.wParam);
    quint32 nModifiers = 0;

    QWindow *receiver = m_keyGrabber ? m_keyGrabber : window;

    // Map native modifiers to some bit representation
    nModifiers |= (GetKeyState(VK_LSHIFT  ) & 0x80 ? ShiftLeft : 0);
    nModifiers |= (GetKeyState(VK_RSHIFT  ) & 0x80 ? ShiftRight : 0);
    nModifiers |= (GetKeyState(VK_LCONTROL) & 0x80 ? ControlLeft : 0);
    nModifiers |= (GetKeyState(VK_RCONTROL) & 0x80 ? ControlRight : 0);
    nModifiers |= (GetKeyState(VK_LMENU   ) & 0x80 ? AltLeft : 0);
    nModifiers |= (GetKeyState(VK_RMENU   ) & 0x80 ? AltRight : 0);
    nModifiers |= (GetKeyState(VK_LWIN    ) & 0x80 ? MetaLeft : 0);
    nModifiers |= (GetKeyState(VK_RWIN    ) & 0x80 ? MetaRight : 0);
    // Add Lock keys to the same bits
    nModifiers |= (GetKeyState(VK_CAPITAL ) & 0x01 ? CapsLock : 0);
    nModifiers |= (GetKeyState(VK_NUMLOCK ) & 0x01 ? NumLock : 0);
    nModifiers |= (GetKeyState(VK_SCROLL  ) & 0x01 ? ScrollLock : 0);

    if (msg.lParam & ExtendedKey)
        nModifiers |= msg.lParam & ExtendedKey;

    // Get the modifier states (may be altered later, depending on key code)
    int state = 0;
    state |= (nModifiers & ShiftAny ? int(Qt::ShiftModifier) : 0);
    state |= (nModifiers & AltLeft ? int(Qt::AltModifier) : 0);
    if ((nModifiers & AltRight) != 0)
        state |= m_seenAltGr ? Qt::GroupSwitchModifier : Qt::AltModifier;
    if ((nModifiers & ControlAny) != 0 && (state & Qt::GroupSwitchModifier) == 0)
        state |= Qt::ControlModifier;
    state |= (nModifiers & MetaAny ? int(Qt::MetaModifier) : 0);
    // A multi-character key or a Input method character
    // not found by our look-ahead
    if (msgType == WM_CHAR || msgType == WM_IME_CHAR) {
        sendExtendedPressRelease(receiver, msg.time, 0, Qt::KeyboardModifier(state), scancode, 0, nModifiers, messageKeyText(msg), false);
        return true;
    }

    // Enable Alt accelerators ("&File") on menus
    if (msgType == WM_SYSKEYDOWN && (nModifiers & AltAny) != 0 && GetMenu(msg.hwnd) != nullptr)
        return false;
    if (msgType == WM_SYSKEYUP && nModifiers == 0 && GetMenu(msg.hwnd) != nullptr)
        return false;

    bool result = false;
    // handle Directionality changes (BiDi) with RTL extensions
    if (m_useRTLExtensions) {
        static int dirStatus = 0;
        if (!dirStatus && state == Qt::ControlModifier
                && msg.wParam == VK_CONTROL
                && msgType == WM_KEYDOWN) {
            if (GetKeyState(VK_LCONTROL) < 0)
                dirStatus = VK_LCONTROL;
            else if (GetKeyState(VK_RCONTROL) < 0)
                dirStatus = VK_RCONTROL;
        } else if (dirStatus) {
            if (msgType == WM_KEYDOWN) {
                if (msg.wParam == VK_SHIFT) {
                    if (dirStatus == VK_LCONTROL && GetKeyState(VK_LSHIFT) < 0)
                        dirStatus = VK_LSHIFT;
                    else if (dirStatus == VK_RCONTROL && GetKeyState(VK_RSHIFT) < 0)
                        dirStatus = VK_RSHIFT;
                } else {
                    dirStatus = 0;
                }
            } else if (msgType == WM_KEYUP) {
                if (dirStatus == VK_LSHIFT
                        && ((msg.wParam == VK_SHIFT && GetKeyState(VK_LCONTROL))
                            || (msg.wParam == VK_CONTROL && GetKeyState(VK_LSHIFT)))) {
                    sendExtendedPressRelease(receiver, msg.time, Qt::Key_Direction_L, {},
                                             scancode, vk_key, nModifiers, QString(), false);
                    result = true;
                    dirStatus = 0;
                } else if (dirStatus == VK_RSHIFT
                           && ( (msg.wParam == VK_SHIFT && GetKeyState(VK_RCONTROL))
                                || (msg.wParam == VK_CONTROL && GetKeyState(VK_RSHIFT)))) {
                    sendExtendedPressRelease(receiver, msg.time, Qt::Key_Direction_R, {},
                                             scancode, vk_key, nModifiers, QString(), false);
                    result = true;
                    dirStatus = 0;
                } else {
                    dirStatus = 0;
                }
            } else {
                dirStatus = 0;
            }
        }
    } // RTL

    // IME will process these keys, so simply return
    if (msg.wParam == VK_PROCESSKEY)
        return true;

    // Ignore invalid virtual keycodes (see bugs 127424, QTBUG-3630)
    if (msg.wParam == 0 || msg.wParam == 0xFF)
        return true;

    // Translate VK_* (native) -> Key_* (Qt) keys
    int modifiersIndex = 0;
    modifiersIndex |= (nModifiers & ShiftAny ? 0x1 : 0);
    modifiersIndex |= (nModifiers & ControlAny ? 0x2 : 0);
    modifiersIndex |= (nModifiers & AltAny ? 0x4 : 0);

    // Note: For the resulting key, AltGr is equivalent to Alt + Ctrl (as
    // opposed to Linux); hence no entry in KeyboardLayoutItem is required
    int code = keyLayout[vk_key].qtKey[modifiersIndex];

    // If the bit 24 of lParm is set you received a enter,
    // otherwise a Return. (This is the extended key bit)
    if ((code == Qt::Key_Return) && (msg.lParam & 0x1000000))
        code = Qt::Key_Enter;
    else if (altGr)
        code = Qt::Key_AltGr;

    // Invert state logic:
    // If the key actually pressed is a modifier key, then we remove its modifier key from the
    // state, since a modifier-key can't have itself as a modifier
    if (code == Qt::Key_Control)
        state = state ^ Qt::ControlModifier;
    else if (code == Qt::Key_Shift)
        state = state ^ Qt::ShiftModifier;
    else if (code == Qt::Key_Alt)
        state = state ^ Qt::AltModifier;
    else if (code == Qt::Key_AltGr)
        state = state ^ Qt::GroupSwitchModifier;

    // All cursor keys without extended bit
    if (!(msg.lParam & 0x1000000)) {
        switch (code) {
        case Qt::Key_Left:
        case Qt::Key_Right:
        case Qt::Key_Up:
        case Qt::Key_Down:
        case Qt::Key_PageUp:
        case Qt::Key_PageDown:
        case Qt::Key_Home:
        case Qt::Key_End:
        case Qt::Key_Insert:
        case Qt::Key_Delete:
        case Qt::Key_Asterisk:
        case Qt::Key_Plus:
        case Qt::Key_Minus:
        case Qt::Key_Period:
        case Qt::Key_Comma:
        case Qt::Key_0:
        case Qt::Key_1:
        case Qt::Key_2:
        case Qt::Key_3:
        case Qt::Key_4:
        case Qt::Key_5:
        case Qt::Key_6:
        case Qt::Key_7:
        case Qt::Key_8:
        case Qt::Key_9:
            state |= ((msg.wParam >= '0' && msg.wParam <= '9')
                      || (msg.wParam >= VK_OEM_PLUS && msg.wParam <= VK_OEM_3))
                    ? 0 : int(Qt::KeypadModifier);
            Q_FALLTHROUGH();
        default:
            if (uint(msg.lParam) == 0x004c0001 || uint(msg.lParam) == 0xc04c0001)
                state |= Qt::KeypadModifier;
            break;
        }
    }
    // Other keys with with extended bit
    else {
        switch (code) {
        case Qt::Key_Enter:
        case Qt::Key_Slash:
        case Qt::Key_NumLock:
            state |= Qt::KeypadModifier;
            break;
        default:
            break;
        }
    }

    // KEYDOWN ---------------------------------------------------------------------------------
    if (msgType == WM_KEYDOWN || msgType == WM_IME_KEYDOWN || msgType == WM_SYSKEYDOWN) {
        // Get the last record of this key press, so we can validate the current state
        // The record is not removed from the list
        KeyRecord *rec = key_recorder.findKey(int(msg.wParam), false);

        // If rec's state doesn't match the current state, something has changed behind our back
        // (Consumed by modal widget is one possibility) So, remove the record from the list
        // This will stop the auto-repeat of the key, should a modifier change, for example
        if (rec && rec->state != state) {
            key_recorder.findKey(int(msg.wParam), true);
            rec = nullptr;
        }

        // Find unicode character from Windows Message Queue
        MSG wm_char;
        UINT charType = (msgType == WM_KEYDOWN
                         ? WM_CHAR
                         : msgType == WM_IME_KEYDOWN ? WM_IME_CHAR : WM_SYSCHAR);

        QChar uch;
        if (PeekMessage(&wm_char, nullptr, charType, charType, PM_REMOVE)) {
            if (QWindowsContext::filterNativeEvent(&wm_char, lResult))
                return true;
            if (receiver && QWindowsContext::filterNativeEvent(receiver, &wm_char, lResult))
                return true;
            // Found a ?_CHAR
            uch = QChar(ushort(wm_char.wParam));
            if (uch.isHighSurrogate()) {
                m_lastHighSurrogate = uch;
                return true;
            }
            if (uch.isLowSurrogate() && !m_lastHighSurrogate.isNull()) {
                if (QObject *focusObject = QGuiApplication::focusObject()) {
                    const QChar chars[2] = {m_lastHighSurrogate, uch};
                    QInputMethodEvent event;
                    event.setCommitString(QString(chars, 2));
                    QCoreApplication::sendEvent(focusObject, &event);
                }
                m_lastHighSurrogate = QChar();
                return true;
            } else {
                m_lastHighSurrogate = QChar();
            }
            if (msgType == WM_SYSKEYDOWN && uch.isLetter() && (msg.lParam & KF_ALTDOWN))
                uch = uch.toLower(); // (See doc of WM_SYSCHAR) Alt-letter
            if (!code && !uch.row())
                code = asciiToKeycode(char(uch.cell()), state);
        }

        // Special handling for the WM_IME_KEYDOWN message. Microsoft IME (Korean) will not
        // generate a WM_IME_CHAR message corresponding to this message. We might get wrong
        // results, if we map this virtual key-code directly (for eg '?' US layouts). So try
        // to find the correct key using the current message parameters & keyboard state.
        if (uch.isNull() && msgType == WM_IME_KEYDOWN) {
            const auto *windowsInputContext =
                qobject_cast<const QWindowsInputContext *>(QWindowsIntegration::instance()->inputContext());
            if (!(windowsInputContext && windowsInputContext->isComposing()))
                vk_key = ImmGetVirtualKey(reinterpret_cast<HWND>(window->winId()));
            BYTE keyState[256];
            wchar_t newKey[3] = {0};
            GetKeyboardState(keyState);
            int val = ToUnicode(vk_key, scancode, keyState, newKey, 2,  0);
            if (val == 1) {
                uch = QChar(newKey[0]);
            } else {
                // If we are still not able to find a unicode key, pass the WM_IME_KEYDOWN
                // message to DefWindowProc() for generating a proper WM_KEYDOWN.
                return false;
            }
        }

        // If no ?_CHAR was found in the queue; deduct character from the ?_KEYDOWN parameters
        if (uch.isNull()) {
            if (msg.wParam == VK_DELETE) {
                uch = QChar(QLatin1Char(0x7f)); // Windows doesn't know this one.
            } else {
                if (msgType != WM_SYSKEYDOWN || !code) {
                    UINT map = MapVirtualKey(UINT(msg.wParam), 2);
                    // If the high bit of the return value is set, it's a deadkey
                    if (!(map & 0x80000000))
                        uch = QChar(ushort(map));
                }
            }
            if (!code && !uch.row())
                code = asciiToKeycode(char(uch.cell()), state);
        }

        // Special handling of global Windows hotkeys
        if (state == Qt::AltModifier) {
            switch (code) {
            case Qt::Key_Escape:
            case Qt::Key_Tab:
            case Qt::Key_F4:
                return false; // Send the event on to Windows
            case Qt::Key_Space:
                // do not pass this key to windows, we will process it ourselves
                showSystemMenu(receiver);
                return true;
            default:
                break;
            }
        }

        // Map SHIFT + Tab to SHIFT + BackTab, QShortcutMap knows about this translation
        if (code == Qt::Key_Tab && (state & Qt::ShiftModifier) == Qt::ShiftModifier)
            code = Qt::Key_Backtab;

        // If we have a record, it means that the key is already pressed, the state is the same
        // so, we have an auto-repeating key
        if (rec) {
            if (code < Qt::Key_Shift || code > Qt::Key_ScrollLock) {
                QWindowSystemInterface::handleExtendedKeyEvent(receiver, msg.time, QEvent::KeyRelease, code,
                                                               Qt::KeyboardModifier(state), scancode, quint32(msg.wParam), nModifiers, rec->text, true);
                QWindowSystemInterface::handleExtendedKeyEvent(receiver, msg.time, QEvent::KeyPress, code,
                                                               Qt::KeyboardModifier(state), scancode, quint32(msg.wParam), nModifiers, rec->text, true);
                result = true;
            }
        }
        // No record of the key being previous pressed, so we now send a QEvent::KeyPress event,
        // and store the key data into our records.
        else {
            const QString text = uch.isNull() ? QString() : QString(uch);
            const char a = uch.row() ? char(0) : char(uch.cell());
            const Qt::KeyboardModifiers modifiers(state);
#ifndef QT_NO_SHORTCUT
            // Is Qt interested in the context menu key?
            if (modifiers == Qt::SHIFT && code == Qt::Key_F10
                && !QGuiApplicationPrivate::instance()->shortcutMap.hasShortcutForKeySequence(QKeySequence(Qt::SHIFT | Qt::Key_F10))) {
                return false;
            }
#endif // !QT_NO_SHORTCUT
            key_recorder.storeKey(int(msg.wParam), a, state, text);

            // QTBUG-71210
            // VK_PACKET specifies multiple characters. The system only sends the first
            // character of this sequence for each.
            if (msg.wParam == VK_PACKET)
                code = asciiToKeycode(char(uch.cell()), state);

            QWindowSystemInterface::handleExtendedKeyEvent(receiver, msg.time, QEvent::KeyPress, code,
                                                           modifiers, scancode, quint32(msg.wParam), nModifiers, text, false);
            result =true;
            bool store = true;
            // Alt+<alphanumerical> go to the Win32 menu system if unhandled by Qt
            if (msgType == WM_SYSKEYDOWN && !result && a) {
                HWND parent = GetParent(QWindowsWindow::handleOf(receiver));
                while (parent) {
                    if (GetMenu(parent)) {
                        SendMessage(parent, WM_SYSCOMMAND, SC_KEYMENU, a);
                        store = false;
                        result = true;
                        break;
                    }
                    parent = GetParent(parent);
                }
            }
            if (!store)
                key_recorder.findKey(int(msg.wParam), true);
        }
    }

    // KEYUP -----------------------------------------------------------------------------------
    else {
        // Try to locate the key in our records, and remove it if it exists.
        // The key may not be in our records if, for example, the down event was handled by
        // win32 natively, or our window gets focus while a key is already press, but now gets
        // the key release event.
        const KeyRecord *rec = key_recorder.findKey(int(msg.wParam), true);
        if (!rec && !(code == Qt::Key_Shift
                      || code == Qt::Key_Control
                      || code == Qt::Key_Meta
                      || code == Qt::Key_Alt)) {

            // Workaround for QTBUG-77153:
            // The Surface Pen eraser button generates Meta+F18/19/20 keystrokes,
            // but when it is not touching the screen the Fn Down is eaten and only
            // a Fn Up with the previous state as "not pressed" is generated, which
            // would be ignored. We detect this case and synthesize the expected events.
            if ((msg.lParam & 0x40000000) == 0 &&
                    Qt::KeyboardModifier(state) == Qt::NoModifier &&
                    ((code == Qt::Key_F18) || (code == Qt::Key_F19) || (code == Qt::Key_F20))) {
                QWindowSystemInterface::handleExtendedKeyEvent(receiver, msg.time, QEvent::KeyPress, code,
                                                               Qt::MetaModifier, scancode,
                                                               quint32(msg.wParam), MetaLeft);
                QWindowSystemInterface::handleExtendedKeyEvent(receiver, msg.time, QEvent::KeyRelease, code,
                                                               Qt::NoModifier, scancode,
                                                               quint32(msg.wParam), 0);
                result = true;
            }
        } else {
            if (!code)
                code = asciiToKeycode(rec->ascii ? char(rec->ascii) : char(msg.wParam), state);

            // Map SHIFT + Tab to SHIFT + BackTab, QShortcutMap knows about this translation
            if (code == Qt::Key_Tab && (state & Qt::ShiftModifier) == Qt::ShiftModifier)
                code = Qt::Key_Backtab;
            QWindowSystemInterface::handleExtendedKeyEvent(receiver, msg.time, QEvent::KeyRelease, code,
                                                           Qt::KeyboardModifier(state), scancode, quint32(msg.wParam),
                                                           nModifiers,
                                                           (rec ? rec->text : QString()), false);
            result = true;
            // don't pass Alt to Windows unless we are embedded in a non-Qt window
            if (code == Qt::Key_Alt) {
                const QWindowsContext *context = QWindowsContext::instance();
                HWND parent = GetParent(QWindowsWindow::handleOf(receiver));
                while (parent) {
                    if (!context->findPlatformWindow(parent) && GetMenu(parent)) {
                        result = false;
                        break;
                    }
                    parent = GetParent(parent);
                }
            }
        }
    }
    return result;
}

Qt::KeyboardModifiers QWindowsKeyMapper::queryKeyboardModifiers() const
{
    Qt::KeyboardModifiers modifiers = Qt::NoModifier;
    if (GetKeyState(VK_SHIFT) < 0)
        modifiers |= Qt::ShiftModifier;
    if (GetKeyState(VK_CONTROL) < 0)
        modifiers |= Qt::ControlModifier;
    if (GetKeyState(VK_MENU) < 0)
        modifiers |= Qt::AltModifier;
    if (GetKeyState(VK_LWIN) < 0 || GetKeyState(VK_RWIN) < 0)
        modifiers |= Qt::MetaModifier;
    return modifiers;
}

QList<QKeyCombination> QWindowsKeyMapper::possibleKeyCombinations(const QKeyEvent *e) const
{
    QList<QKeyCombination> result;


    const quint32 nativeVirtualKey = e->nativeVirtualKey();
    if (nativeVirtualKey > 255)
        return result;

    const KeyboardLayoutItem &kbItem = keyLayout[nativeVirtualKey];
    if (!kbItem.exists)
        return result;

    quint32 baseKey = kbItem.qtKey[0];
    Qt::KeyboardModifiers keyMods = e->modifiers();
    if (baseKey == Qt::Key_Return && (e->nativeModifiers() & ExtendedKey)) {
        result << (Qt::Key_Enter | keyMods);
        return result;
    }

    // If Key_Tab+Shift is pressed we add Key_Backtab without
    // shift modifier as a possible combination too
    if (baseKey == Qt::Key_Tab && (keyMods & Qt::ShiftModifier))
        result << (Qt::Key_Backtab | (keyMods & ~Qt::ShiftModifier));

    // The base key is _always_ valid, of course
    result << QKeyCombination::fromCombined(int(baseKey) + int(keyMods));

    for (size_t i = 1; i < NumMods; ++i) {
        Qt::KeyboardModifiers neededMods = ModsTbl[i];
        quint32 key = kbItem.qtKey[i];
        if (key && key != baseKey && ((keyMods & neededMods) == neededMods)) {
            const Qt::KeyboardModifiers missingMods = keyMods & ~neededMods;
            const auto matchedKey = QKeyCombination::fromCombined(int(key) + int(missingMods));
            const auto it = std::find_if(result.begin(), result.end(),
                [key](auto keyCombination) {
                    return keyCombination.key() == key;
                });
            // QTBUG-67200: Use the match with the least modifiers (prefer
            // Shift+9 over Alt + Shift + 9) resulting in more missing modifiers.
            if (it == result.end())
                result << matchedKey;
            else if (missingMods > it->keyboardModifiers())
                *it = matchedKey;
        }
    }
    qCDebug(lcQpaEvents) << __FUNCTION__  << e << "nativeVirtualKey="
        << Qt::showbase << Qt::hex << e->nativeVirtualKey() << Qt::dec << Qt::noshowbase
        << e->modifiers() << kbItem << "\n  returns" << result;
    return result;
}

QT_END_NAMESPACE
