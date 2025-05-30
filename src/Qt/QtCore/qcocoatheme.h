// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QPLATFORMTHEME_COCOA_H
#define QPLATFORMTHEME_COCOA_H

#include <QtCore/QHash>
#include <qpa/qplatformtheme.h>

#include <QtCore/private/qcore_mac_p.h>

QT_BEGIN_NAMESPACE

class QPalette;
class QCocoaTheme : public QPlatformTheme
{
public:
    QCocoaTheme();
    ~QCocoaTheme();

    void reset();

    QPlatformMenuItem* createPlatformMenuItem() const override;
    QPlatformMenu* createPlatformMenu() const override;
    QPlatformMenuBar* createPlatformMenuBar() const override;

#ifndef QT_NO_SYSTEMTRAYICON
    QPlatformSystemTrayIcon *createPlatformSystemTrayIcon() const override;
#endif

    bool usePlatformNativeDialog(DialogType dialogType) const override;
    QPlatformDialogHelper *createPlatformDialogHelper(DialogType dialogType) const override;

    const QPalette *palette(Palette type = SystemPalette) const override;
    const QFont *font(Font type = SystemFont) const override;
    QPixmap standardPixmap(StandardPixmap sp, const QSizeF &size) const override;
    QIcon fileIcon(const QFileInfo &fileInfo, QPlatformTheme::IconOptions options = {}) const override;
    QIconEngine *createIconEngine(const QString &iconName) const override;

    QVariant themeHint(ThemeHint hint) const override;
    Qt::ColorScheme colorScheme() const override;
    QString standardButtonText(int button) const override;
    QKeySequence standardButtonShortcut(int button) const override;

    static const char *name;

    void requestColorScheme(Qt::ColorScheme scheme) override;
    void handleSystemThemeChange();

#ifndef QT_NO_SHORTCUT
    QList<QKeySequence> keyBindings(QKeySequence::StandardKey key) const override;
#endif

private:
    mutable QPalette *m_systemPalette;
    QMacNotificationObserver m_systemColorObserver;
    mutable QHash<QPlatformTheme::Palette, QPalette*> m_palettes;
    QMacKeyValueObserver m_appearanceObserver;

    Qt::ColorScheme m_colorScheme = Qt::ColorScheme::Unknown;
    void updateColorScheme();
};

QT_END_NAMESPACE

#endif
