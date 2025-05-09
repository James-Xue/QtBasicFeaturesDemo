// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QFONTDIALOG_H
#define QFONTDIALOG_H

#include <QtWidgets/qtwidgetsglobal.h>
#include <QtGui/qwindowdefs.h>
#include <QtGui/qfont.h>

#include <QtWidgets/qdialog.h>

QT_REQUIRE_CONFIG(fontdialog);

QT_BEGIN_NAMESPACE

class QFontDialogPrivate;

class Q_WIDGETS_EXPORT QFontDialog : public QDialog
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QFontDialog)
    Q_PROPERTY(QFont currentFont READ currentFont WRITE setCurrentFont NOTIFY currentFontChanged)
    Q_PROPERTY(FontDialogOptions options READ options WRITE setOptions)

public:
    enum FontDialogOption {
        NoButtons           = 0x00000001,
        DontUseNativeDialog = 0x00000002,
        ScalableFonts       = 0x00000004,
        NonScalableFonts    = 0x00000008,
        MonospacedFonts     = 0x00000010,
        ProportionalFonts   = 0x00000020
    };
    Q_ENUM(FontDialogOption)

    Q_DECLARE_FLAGS(FontDialogOptions, FontDialogOption)

    explicit QFontDialog(QWidget *parent = nullptr);
    explicit QFontDialog(const QFont &initial, QWidget *parent = nullptr);
    ~QFontDialog();

    void setCurrentFont(const QFont &font);
    QFont currentFont() const;

    QFont selectedFont() const;

    void setOption(FontDialogOption option, bool on = true);
    bool testOption(FontDialogOption option) const;
    void setOptions(FontDialogOptions options);
    FontDialogOptions options() const;

    using QDialog::open;
    void open(QObject *receiver, const char *member);

    void setVisible(bool visible) override;

    static QFont getFont(bool *ok, QWidget *parent = nullptr);
    static QFont getFont(bool *ok, const QFont &initial, QWidget *parent = nullptr, const QString &title = QString(),
                         FontDialogOptions options = FontDialogOptions());

Q_SIGNALS:
    void currentFontChanged(const QFont &font);
    void fontSelected(const QFont &font);

protected:
    void changeEvent(QEvent *event) override;
    void done(int result) override;
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    Q_DISABLE_COPY(QFontDialog)
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QFontDialog::FontDialogOptions)

QT_END_NAMESPACE

#endif // QFONTDIALOG_H
