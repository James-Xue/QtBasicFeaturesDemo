// Copyright (C) 2022 The Qt Company Ltd.


#ifndef QGTK3STORAGE_P_H
#define QGTK3STORAGE_P_H

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

#include "qgtk3interface_p.h"
#if QT_CONFIG(dbus)
#include "qgtk3portalinterface_p.h"
#endif

#include <QtCore/QJsonDocument>
#include <QtCore/QCache>
#include <QtCore/QString>
#include <QtGui/QGuiApplication>
#include <QtGui/QPalette>

#include <qpa/qplatformtheme.h>
#include <private/qflatmap_p.h>

QT_BEGIN_NAMESPACE
class QGtk3Storage
{
    Q_GADGET
public:
    QGtk3Storage();

    // Enum documented in cpp file. Please keep it in line with updates made here.
    enum class SourceType {
        Gtk,
        Fixed,
        Modified,
        Mixed,
        Invalid
    };
    Q_ENUM(SourceType)

    // Standard GTK source: Populate a brush from GTK
    struct Gtk3Source  {
        QGtk3Interface::QGtkWidget gtkWidgetType;
        QGtk3Interface::QGtkColorSource source;
        GtkStateFlags state;
        int width = -1;
        int height = -1;
        QDebug operator<<(QDebug dbg)
        {
            return dbg << "QGtkStorage::Gtk3Source(gtkwidgetType=" << gtkWidgetType << ", source="
                       << source << ", state=" << state << ", width=" << width << ", height="
                       << height << ")";
        }
    };

    // Recursive source: Populate a brush by altering another source
    struct RecursiveSource  {
        QPalette::ColorGroup colorGroup;
        QPalette::ColorRole colorRole;
        Qt::ColorScheme colorScheme;
        int lighter = 100;
        int deltaRed = 0;
        int deltaGreen = 0;
        int deltaBlue = 0;
        int width = -1;
        int height = -1;
        QDebug operator<<(QDebug dbg)
        {
            return dbg << "QGtkStorage::RecursiceSource(colorGroup=" << colorGroup << ", colorRole="
                       << colorRole << ", colorScheme=" << colorScheme << ", lighter=" << lighter
                       << ", deltaRed="<< deltaRed << "deltaBlue =" << deltaBlue << "deltaGreen="
                       << deltaGreen << ", width=" << width << ", height=" << height << ")";
        }
    };

    // Mixed source: Populate a brush by mixing two brushes.
    // Useful for creating disabled color by mixing,
    // for example the background and foreground colors.
    struct MixSources {
        QPalette::ColorGroup sourceGroup; // source group of the mixing color roles
        QPalette::ColorRole colorRole1;
        QPalette::ColorRole colorRole2;
        QDebug operator<<(QDebug dbg)
        {
            return dbg << "QGtkStorage::MixSources(sourceGroup=" << sourceGroup
                       << ", colorRole1=" << colorRole1
                       << ", colorRole2=" << colorRole2 << ")";
        }
        static inline QColor mixColors(const QColor &color1, const QColor &color2)
        {
            return QColor{ (color1.red() + color2.red()) / 2,
                           (color1.green() + color2.green()) / 2,
                           (color1.blue() + color2.blue()) / 2 };
        }
    };

    // Fixed source: Populate a brush with fixed values rather than reading GTK
    struct FixedSource  {
        QBrush fixedBrush;
        QDebug operator<<(QDebug dbg)
        {
            return dbg << "QGtkStorage::FixedSource(" << fixedBrush << ")";
        }
    };

    // Data source for brushes
    struct Source {
        SourceType sourceType = SourceType::Invalid;
        Gtk3Source gtk3;
        RecursiveSource rec;
        FixedSource fix;
        MixSources mix;

        // GTK constructor
        Source(QGtk3Interface::QGtkWidget wtype, QGtk3Interface::QGtkColorSource csource,
               GtkStateFlags cstate, int bwidth = -1, int bheight = -1) : sourceType(SourceType::Gtk)
        {
             gtk3.gtkWidgetType = wtype;
             gtk3.source = csource;
             gtk3.state = cstate;
             gtk3.width = bwidth;
             gtk3.height = bheight;
        }

        // Recursive constructor for darker/lighter colors
        Source(QPalette::ColorGroup group, QPalette::ColorRole role,
               Qt::ColorScheme scheme, int p_lighter = 100)
               : sourceType(SourceType::Modified)
        {
            rec.colorGroup = group;
            rec.colorRole = role;
            rec.colorScheme = scheme;
            rec.lighter = p_lighter;
        }

        // Recursive constructor for color modification
        Source(QPalette::ColorGroup group, QPalette::ColorRole role,
               Qt::ColorScheme scheme, int p_red, int p_green, int p_blue)
               : sourceType(SourceType::Modified)
        {
            rec.colorGroup = group;
            rec.colorRole = role;
            rec.colorScheme = scheme;
            rec.deltaRed = p_red;
            rec.deltaGreen = p_green;
            rec.deltaBlue = p_blue;
        }

        // Recursive constructor for all: color modification and darker/lighter
        Source(QPalette::ColorGroup group, QPalette::ColorRole role,
               Qt::ColorScheme scheme, int p_lighter,
               int p_red, int p_green, int p_blue) : sourceType(SourceType::Modified)
        {
            rec.colorGroup = group;
            rec.colorRole = role;
            rec.colorScheme = scheme;
            rec.lighter = p_lighter;
            rec.deltaRed = p_red;
            rec.deltaGreen = p_green;
            rec.deltaBlue = p_blue;
        }

        // Mixed constructor for color modification
        Source(QPalette::ColorGroup sourceGroup,
               QPalette::ColorRole role1, QPalette::ColorRole role2)
            : sourceType(SourceType::Mixed)
        {
            mix.sourceGroup = sourceGroup;
            mix.colorRole1 = role1;
            mix.colorRole2 = role2;
        }

        // Fixed Source constructor
        Source(const QBrush &brush) : sourceType(SourceType::Fixed)
        {
            fix.fixedBrush = brush;
        }

        // Invalid constructor and getter
        Source() : sourceType(SourceType::Invalid) {}
        bool isValid() const { return sourceType != SourceType::Invalid; }

        // Debug
        QDebug operator<<(QDebug dbg)
        {
            return dbg << "QGtk3Storage::Source(sourceType=" << sourceType << ")";
        }
    };

    // Struct with key attributes to identify a brush: color group, color role and color scheme
    struct TargetBrush {
        QPalette::ColorGroup colorGroup;
        QPalette::ColorRole colorRole;
        Qt::ColorScheme colorScheme;

        // Generic constructor
        TargetBrush(QPalette::ColorGroup group, QPalette::ColorRole role,
                    Qt::ColorScheme scheme = Qt::ColorScheme::Unknown) :
                    colorGroup(group), colorRole(role), colorScheme(scheme) {}

        // Copy constructor with color scheme modifier for dark/light aware search
        TargetBrush(const TargetBrush &other, Qt::ColorScheme scheme) :
            colorGroup(other.colorGroup), colorRole(other.colorRole), colorScheme(scheme) {}

        // struct becomes key of a map, so operator< is needed
        bool operator<(const TargetBrush& other) const {
           return std::tie(colorGroup, colorRole, colorScheme) <
                  std::tie(other.colorGroup, other.colorRole, other.colorScheme);
        }
    };

    // Mapping a palette's brushes to their GTK sources
    typedef QFlatMap<TargetBrush, Source> BrushMap;

    // Storage of palettes and their GTK sources
    typedef QFlatMap<QPlatformTheme::Palette, BrushMap> PaletteMap;

    // Public getters
    const QPalette *palette(QPlatformTheme::Palette = QPlatformTheme::SystemPalette) const;
    QPixmap standardPixmap(QPlatformTheme::StandardPixmap standardPixmap, const QSizeF &size) const;
    Qt::ColorScheme colorScheme() const { return m_colorScheme; }
    static QPalette standardPalette();
    const QString themeName() const { return m_interface ? m_interface->themeName() : QString(); }
    const QFont *font(QPlatformTheme::Font type) const;
    QIcon fileIcon(const QFileInfo &fileInfo) const;

    // Initialization
    void populateMap();
    void handleThemeChange();

private:
    // Storage for palettes and their brushes
    PaletteMap m_palettes;

    std::unique_ptr<QGtk3Interface> m_interface;
#if QT_CONFIG(dbus)
    std::unique_ptr<QGtk3PortalInterface> m_portalInterface;
#endif

    Qt::ColorScheme m_colorScheme = Qt::ColorScheme::Unknown;

    // Caches for Pixmaps, fonts and palettes
    mutable QCache<QPlatformTheme::StandardPixmap, QImage> m_pixmapCache;
    mutable std::array<std::optional<QPalette>, QPlatformTheme::Palette::NPalettes> m_paletteCache;
    mutable std::array<std::optional<QFont>, QPlatformTheme::NFonts> m_fontCache;

    // Search brush with a given GTK3 source
    QBrush brush(const Source &source, const BrushMap &map) const;

    // Get GTK3 source for a target brush
    Source brush (const TargetBrush &brush, const BrushMap &map) const;

    // clear cache, palettes and color scheme
    void clear();

    // Data creation, import & export
    void createMapping ();
    const PaletteMap savePalettes() const;
    bool save(const QString &filename, const QJsonDocument::JsonFormat f = QJsonDocument::Indented) const;
    QJsonDocument save() const;
    bool load(const QString &filename);
};

QT_END_NAMESPACE
#endif // QGTK3STORAGE_H
