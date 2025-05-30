// Copyright (C) 2013 BogDan Vatra <bogdan@kde.org>
// Copyright (C) 2021 The Qt Company Ltd.


#ifndef QANDROIDPLATFORMDIALOGHELPERS_H
#define QANDROIDPLATFORMDIALOGHELPERS_H

#include <jni.h>

#include <QEventLoop>
#include <QtCore/QJniObject>
#include <qpa/qplatformdialoghelper.h>

QT_BEGIN_NAMESPACE

class QJniEnvironment;

namespace QtAndroidDialogHelpers {

class QAndroidPlatformMessageDialogHelper: public QPlatformMessageDialogHelper
{
    Q_OBJECT
public:
    QAndroidPlatformMessageDialogHelper();
    ~QAndroidPlatformMessageDialogHelper();

    void exec() override;
    bool show(Qt::WindowFlags windowFlags, Qt::WindowModality windowModality,
              QWindow *parent) override;
    void hide() override;

public slots:
    void dialogResult(int buttonID);

private:
    void addButtons(QSharedPointer<QMessageDialogOptions> opt, ButtonRole role);

private:
    bool m_shown = false;
    QEventLoop m_loop;
    QJniObject m_javaMessageDialog;
};


bool registerNatives(QJniEnvironment &env);

}

QT_END_NAMESPACE

#endif // QANDROIDPLATFORMDIALOGHELPERS_H
