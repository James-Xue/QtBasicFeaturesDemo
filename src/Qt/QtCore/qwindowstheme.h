// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QWINDOWSTHEME_H
#define QWINDOWSTHEME_H

#include <qpa/qplatformtheme.h>

#include <QtCore/qsharedpointer.h>
#include <QtCore/qvariant.h>
#include <QtCore/qlist.h>
#include <QtCore/qsize.h>

QT_BEGIN_NAMESPACE

class QWindow;

class QWindowsTheme : public QPlatformTheme
{
    Q_DISABLE_COPY_MOVE(QWindowsTheme)
public:
    QWindowsTheme();
    ~QWindowsTheme() override;

    static QWindowsTheme *instance() { return m_instance; }

    bool usePlatformNativeDialog(DialogType type) const override;
    QPlatformDialogHelper *createPlatformDialogHelper(DialogType type) const override;
#if QT_CONFIG(systemtrayicon)
    QPlatformSystemTrayIcon *createPlatformSystemTrayIcon() const override;
#endif
    QVariant themeHint(ThemeHint) const override;

    Qt::ColorScheme colorScheme() const override;
    void requestColorScheme(Qt::ColorScheme scheme) override;

    static void handleSettingsChanged();

    const QPalette *palette(Palette type = SystemPalette) const override
        { return m_palettes[type]; }
    const QFont *font(Font type = SystemFont) const override
        { return m_fonts[type]; }

    QPixmap standardPixmap(StandardPixmap sp, const QSizeF &size) const override;

    QIcon fileIcon(const QFileInfo &fileInfo, QPlatformTheme::IconOptions iconOptions = {}) const override;
    QIconEngine *createIconEngine(const QString &iconName) const override;

    void windowsThemeChanged(QWindow *window);
    void displayChanged() { refreshIconPixmapSizes(); }

    QList<QSize> availableFileIconSizes() const { return m_fileIconSizes; }

    QPlatformMenuItem *createPlatformMenuItem() const override;
    QPlatformMenu *createPlatformMenu() const override;
    QPlatformMenuBar *createPlatformMenuBar() const override;
    void showPlatformMenuBar() override;

    static bool useNativeMenus();

    void refreshFonts();
    void refresh();

    static const char *name;

    static QPalette systemPalette(Qt::ColorScheme);

private:
    void clearPalettes();
    void refreshPalettes();
    void clearFonts();
    void refreshIconPixmapSizes();

    static void populateLightSystemBasePalette(QPalette &result);
    static void populateDarkSystemBasePalette(QPalette &result);

    static Qt::ColorScheme queryColorScheme();
    static Qt::ColorScheme effectiveColorScheme();
    static bool queryHighContrast();

    static QWindowsTheme *m_instance;
    static inline Qt::ColorScheme s_colorScheme = Qt::ColorScheme::Unknown;
    static inline Qt::ColorScheme s_colorSchemeOverride = Qt::ColorScheme::Unknown;

    QPalette *m_palettes[NPalettes];
    QFont *m_fonts[NFonts];
    QList<QSize> m_fileIconSizes;
};

QT_END_NAMESPACE

#endif // QWINDOWSTHEME_H
