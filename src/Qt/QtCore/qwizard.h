// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QWIZARD_H
#define QWIZARD_H

#include <QtWidgets/qtwidgetsglobal.h>
#include <QtWidgets/qdialog.h>

QT_REQUIRE_CONFIG(wizard);

QT_BEGIN_NAMESPACE

class QAbstractButton;
class QWizardPage;
class QWizardPrivate;

class Q_WIDGETS_EXPORT QWizard : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(WizardStyle wizardStyle READ wizardStyle WRITE setWizardStyle)
    Q_PROPERTY(WizardOptions options READ options WRITE setOptions)
    Q_PROPERTY(Qt::TextFormat titleFormat READ titleFormat WRITE setTitleFormat)
    Q_PROPERTY(Qt::TextFormat subTitleFormat READ subTitleFormat WRITE setSubTitleFormat)
    Q_PROPERTY(int startId READ startId WRITE setStartId)
    Q_PROPERTY(int currentId READ currentId WRITE setCurrentId NOTIFY currentIdChanged)

public:
    enum WizardButton {
        BackButton,
        NextButton,
        CommitButton,
        FinishButton,
        CancelButton,
        HelpButton,
        CustomButton1,
        CustomButton2,
        CustomButton3,
        Stretch,

        NoButton = -1,
        NStandardButtons = 6,
        NButtons = 9
    };

    enum WizardPixmap {
        WatermarkPixmap,
        LogoPixmap,
        BannerPixmap,
        BackgroundPixmap,
        NPixmaps
    };

    enum WizardStyle {
        ClassicStyle,
        ModernStyle,
        MacStyle,
        AeroStyle,
        NStyles
    };
    Q_ENUM(WizardStyle)

    enum WizardOption {
        IndependentPages                = 0x00000001,
        IgnoreSubTitles                 = 0x00000002,
        ExtendedWatermarkPixmap         = 0x00000004,
        NoDefaultButton                 = 0x00000008,
        NoBackButtonOnStartPage         = 0x00000010,
        NoBackButtonOnLastPage          = 0x00000020,
        DisabledBackButtonOnLastPage    = 0x00000040,
        HaveNextButtonOnLastPage        = 0x00000080,
        HaveFinishButtonOnEarlyPages    = 0x00000100,
        NoCancelButton                  = 0x00000200,
        CancelButtonOnLeft              = 0x00000400,
        HaveHelpButton                  = 0x00000800,
        HelpButtonOnRight               = 0x00001000,
        HaveCustomButton1               = 0x00002000,
        HaveCustomButton2               = 0x00004000,
        HaveCustomButton3               = 0x00008000,
        NoCancelButtonOnLastPage        = 0x00010000
    };
    Q_ENUM(WizardOption)

    Q_DECLARE_FLAGS(WizardOptions, WizardOption)
    Q_FLAG(WizardOptions)

    explicit QWizard(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    ~QWizard();

    int addPage(QWizardPage *page);
    void setPage(int id, QWizardPage *page);
    void removePage(int id);
    QWizardPage *page(int id) const;
    bool hasVisitedPage(int id) const;
    QList<int> visitedIds() const;
    QList<int> pageIds() const;
    void setStartId(int id);
    int startId() const;
    QWizardPage *currentPage() const;
    int currentId() const;

    virtual bool validateCurrentPage();
    virtual int nextId() const;

    void setField(const QString &name, const QVariant &value);
    QVariant field(const QString &name) const;

    void setWizardStyle(WizardStyle style);
    WizardStyle wizardStyle() const;

    void setOption(WizardOption option, bool on = true);
    bool testOption(WizardOption option) const;
    void setOptions(WizardOptions options);
    WizardOptions options() const;

    void setButtonText(WizardButton which, const QString &text);
    QString buttonText(WizardButton which) const;
    void setButtonLayout(const QList<WizardButton> &layout);
    void setButton(WizardButton which, QAbstractButton *button);
    QAbstractButton *button(WizardButton which) const;

    void setTitleFormat(Qt::TextFormat format);
    Qt::TextFormat titleFormat() const;
    void setSubTitleFormat(Qt::TextFormat format);
    Qt::TextFormat subTitleFormat() const;
    void setPixmap(WizardPixmap which, const QPixmap &pixmap);
    QPixmap pixmap(WizardPixmap which) const;

    void setSideWidget(QWidget *widget);
    QWidget *sideWidget() const;

    void setDefaultProperty(const char *className, const char *property,
                            const char *changedSignal);

    void setVisible(bool visible) override;
    QSize sizeHint() const override;

Q_SIGNALS:
    void currentIdChanged(int id);
    void helpRequested();
    void customButtonClicked(int which);
    void pageAdded(int id);
    void pageRemoved(int id);

public Q_SLOTS:
    void back();
    void next();
    void setCurrentId(int id);
    void restart();

protected:
    bool event(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
#if defined(Q_OS_WIN) || defined(Q_QDOC)
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override;
#endif
    void done(int result) override;
    virtual void initializePage(int id);
    virtual void cleanupPage(int id);

private:
    Q_DISABLE_COPY(QWizard)
    Q_DECLARE_PRIVATE(QWizard)
    Q_PRIVATE_SLOT(d_func(), void _q_emitCustomButtonClicked())
    Q_PRIVATE_SLOT(d_func(), void _q_updateButtonStates())
    Q_PRIVATE_SLOT(d_func(), void _q_handleFieldObjectDestroyed(QObject *))

    friend class QWizardPage;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QWizard::WizardOptions)

class QWizardPagePrivate;

class Q_WIDGETS_EXPORT QWizardPage : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(QString subTitle READ subTitle WRITE setSubTitle)

public:
    explicit QWizardPage(QWidget *parent = nullptr);
    ~QWizardPage();

    void setTitle(const QString &title);
    QString title() const;
    void setSubTitle(const QString &subTitle);
    QString subTitle() const;
    void setPixmap(QWizard::WizardPixmap which, const QPixmap &pixmap);
    QPixmap pixmap(QWizard::WizardPixmap which) const;
    void setFinalPage(bool finalPage);
    bool isFinalPage() const;
    void setCommitPage(bool commitPage);
    bool isCommitPage() const;
    void setButtonText(QWizard::WizardButton which, const QString &text);
    QString buttonText(QWizard::WizardButton which) const;

    virtual void initializePage();
    virtual void cleanupPage();
    virtual bool validatePage();
    virtual bool isComplete() const;
    virtual int nextId() const;

Q_SIGNALS:
    void completeChanged();

protected:
    void setField(const QString &name, const QVariant &value);
    QVariant field(const QString &name) const;
    void registerField(const QString &name, QWidget *widget, const char *property = nullptr,
                       const char *changedSignal = nullptr);
    QWizard *wizard() const;

private:
    Q_DISABLE_COPY(QWizardPage)
    Q_DECLARE_PRIVATE(QWizardPage)
    Q_PRIVATE_SLOT(d_func(), void _q_maybeEmitCompleteChanged())
    Q_PRIVATE_SLOT(d_func(), void _q_updateCachedCompleteState())

    friend class QWizard;
    friend class QWizardPrivate;
};

QT_END_NAMESPACE

#endif // QWIZARD_H
