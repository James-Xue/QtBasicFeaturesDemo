// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QCOCOAFONTDIALOGHELPER_H
#define QCOCOAFONTDIALOGHELPER_H

#include <QObject>
#include <qpa/qplatformdialoghelper.h>

QT_BEGIN_NAMESPACE

class QCocoaFontDialogHelper : public QPlatformFontDialogHelper
{
public:
    QCocoaFontDialogHelper();
    ~QCocoaFontDialogHelper();

    void exec() override;

    bool show(Qt::WindowFlags windowFlags, Qt::WindowModality windowModality, QWindow *parent) override;
    void hide() override;

    void setCurrentFont(const QFont &) override;
    QFont currentFont() const override;
};

QT_END_NAMESPACE

#endif // QCOCOAFONTDIALOGHELPER_H
