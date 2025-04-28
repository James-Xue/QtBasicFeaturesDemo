/*

* Copyright (C) 2016 The Qt Company Ltd.
* SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

*/

/********************************************************************************
** Form generated from reading UI file 'qfiledialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QFILEDIALOG_H
#define UI_QFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "private/qfiledialog_p.h"
#include "private/qsidebar_p.h"

QT_BEGIN_NAMESPACE

class Ui_QFileDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *lookInLabel;
    QHBoxLayout *hboxLayout;
    QFileDialogComboBox *lookInCombo;
    QToolButton *backButton;
    QToolButton *forwardButton;
    QToolButton *toParentButton;
    QToolButton *newFolderButton;
    QToolButton *listModeButton;
    QToolButton *detailModeButton;
    QSplitter *splitter;
    QSidebar *sidebar;
    QFrame *frame;
    QVBoxLayout *vboxLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *vboxLayout1;
    QFileDialogListView *listView;
    QWidget *page_2;
    QVBoxLayout *vboxLayout2;
    QFileDialogTreeView *treeView;
    QLabel *fileNameLabel;
    QFileDialogLineEdit *fileNameEdit;
    QDialogButtonBox *buttonBox;
    QLabel *fileTypeLabel;
    QComboBox *fileTypeCombo;

    void setupUi(QDialog *QFileDialog)
    {
        if (QFileDialog->objectName().isEmpty())
            QFileDialog->setObjectName("QFileDialog");
        QFileDialog->resize(521, 316);
        QFileDialog->setSizeGripEnabled(true);
        gridLayout = new QGridLayout(QFileDialog);
        gridLayout->setObjectName("gridLayout");
        lookInLabel = new QLabel(QFileDialog);
        lookInLabel->setObjectName("lookInLabel");

        gridLayout->addWidget(lookInLabel, 0, 0, 1, 1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        lookInCombo = new QFileDialogComboBox(QFileDialog);
        lookInCombo->setObjectName("lookInCombo");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lookInCombo->sizePolicy().hasHeightForWidth());
        lookInCombo->setSizePolicy(sizePolicy);
        lookInCombo->setMinimumSize(QSize(50, 0));

        hboxLayout->addWidget(lookInCombo);

        backButton = new QToolButton(QFileDialog);
        backButton->setObjectName("backButton");

        hboxLayout->addWidget(backButton);

        forwardButton = new QToolButton(QFileDialog);
        forwardButton->setObjectName("forwardButton");

        hboxLayout->addWidget(forwardButton);

        toParentButton = new QToolButton(QFileDialog);
        toParentButton->setObjectName("toParentButton");

        hboxLayout->addWidget(toParentButton);

        newFolderButton = new QToolButton(QFileDialog);
        newFolderButton->setObjectName("newFolderButton");

        hboxLayout->addWidget(newFolderButton);

        listModeButton = new QToolButton(QFileDialog);
        listModeButton->setObjectName("listModeButton");

        hboxLayout->addWidget(listModeButton);

        detailModeButton = new QToolButton(QFileDialog);
        detailModeButton->setObjectName("detailModeButton");

        hboxLayout->addWidget(detailModeButton);


        gridLayout->addLayout(hboxLayout, 0, 1, 1, 2);

        splitter = new QSplitter(QFileDialog);
        splitter->setObjectName("splitter");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy1);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setChildrenCollapsible(false);
        sidebar = new QSidebar(splitter);
        sidebar->setObjectName("sidebar");
        splitter->addWidget(sidebar);
        frame = new QFrame(splitter);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        vboxLayout = new QVBoxLayout(frame);
        vboxLayout->setSpacing(0);
        vboxLayout->setObjectName("vboxLayout");
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(frame);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        vboxLayout1 = new QVBoxLayout(page);
        vboxLayout1->setSpacing(0);
        vboxLayout1->setObjectName("vboxLayout1");
        vboxLayout1->setContentsMargins(0, 0, 0, 0);
        listView = new QFileDialogListView(page);
        listView->setObjectName("listView");

        vboxLayout1->addWidget(listView);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        vboxLayout2 = new QVBoxLayout(page_2);
        vboxLayout2->setSpacing(0);
        vboxLayout2->setObjectName("vboxLayout2");
        vboxLayout2->setContentsMargins(0, 0, 0, 0);
        treeView = new QFileDialogTreeView(page_2);
        treeView->setObjectName("treeView");

        vboxLayout2->addWidget(treeView);

        stackedWidget->addWidget(page_2);

        vboxLayout->addWidget(stackedWidget);

        splitter->addWidget(frame);

        gridLayout->addWidget(splitter, 1, 0, 1, 3);

        fileNameLabel = new QLabel(QFileDialog);
        fileNameLabel->setObjectName("fileNameLabel");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(fileNameLabel->sizePolicy().hasHeightForWidth());
        fileNameLabel->setSizePolicy(sizePolicy2);
        fileNameLabel->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(fileNameLabel, 2, 0, 1, 1);

        fileNameEdit = new QFileDialogLineEdit(QFileDialog);
        fileNameEdit->setObjectName("fileNameEdit");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(fileNameEdit->sizePolicy().hasHeightForWidth());
        fileNameEdit->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(fileNameEdit, 2, 1, 1, 1);

        buttonBox = new QDialogButtonBox(QFileDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 2, 2, 1);

        fileTypeLabel = new QLabel(QFileDialog);
        fileTypeLabel->setObjectName("fileTypeLabel");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(fileTypeLabel->sizePolicy().hasHeightForWidth());
        fileTypeLabel->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(fileTypeLabel, 3, 0, 1, 1);

        fileTypeCombo = new QComboBox(QFileDialog);
        fileTypeCombo->setObjectName("fileTypeCombo");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(fileTypeCombo->sizePolicy().hasHeightForWidth());
        fileTypeCombo->setSizePolicy(sizePolicy5);

        gridLayout->addWidget(fileTypeCombo, 3, 1, 1, 1);

        QWidget::setTabOrder(lookInCombo, backButton);
        QWidget::setTabOrder(backButton, forwardButton);
        QWidget::setTabOrder(forwardButton, toParentButton);
        QWidget::setTabOrder(toParentButton, newFolderButton);
        QWidget::setTabOrder(newFolderButton, listModeButton);
        QWidget::setTabOrder(listModeButton, detailModeButton);
        QWidget::setTabOrder(detailModeButton, sidebar);
        QWidget::setTabOrder(sidebar, treeView);
        QWidget::setTabOrder(treeView, listView);
        QWidget::setTabOrder(listView, fileNameEdit);
        QWidget::setTabOrder(fileNameEdit, buttonBox);
        QWidget::setTabOrder(buttonBox, fileTypeCombo);

        retranslateUi(QFileDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QFileDialog);
    } // setupUi

    void retranslateUi(QDialog *QFileDialog)
    {
        lookInLabel->setText(QCoreApplication::translate("QFileDialog", "Look in:", nullptr));
#if QT_CONFIG(tooltip)
        backButton->setToolTip(QCoreApplication::translate("QFileDialog", "Back", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(accessibility)
        backButton->setAccessibleName(QCoreApplication::translate("QFileDialog", "Back", nullptr));
#endif // QT_CONFIG(accessibility)
#if QT_CONFIG(accessibility)
        backButton->setAccessibleDescription(QCoreApplication::translate("QFileDialog", "Go back", nullptr));
#endif // QT_CONFIG(accessibility)
#if QT_CONFIG(shortcut)
        backButton->setShortcut(QCoreApplication::translate("QFileDialog", "Alt+Left", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        forwardButton->setToolTip(QCoreApplication::translate("QFileDialog", "Forward", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(accessibility)
        forwardButton->setAccessibleName(QCoreApplication::translate("QFileDialog", "Forward", nullptr));
#endif // QT_CONFIG(accessibility)
#if QT_CONFIG(accessibility)
        forwardButton->setAccessibleDescription(QCoreApplication::translate("QFileDialog", "Go forward", nullptr));
#endif // QT_CONFIG(accessibility)
#if QT_CONFIG(shortcut)
        forwardButton->setShortcut(QCoreApplication::translate("QFileDialog", "Alt+Right", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        toParentButton->setToolTip(QCoreApplication::translate("QFileDialog", "Parent Directory", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(accessibility)
        toParentButton->setAccessibleName(QCoreApplication::translate("QFileDialog", "Parent Directory", nullptr));
#endif // QT_CONFIG(accessibility)
#if QT_CONFIG(accessibility)
        toParentButton->setAccessibleDescription(QCoreApplication::translate("QFileDialog", "Go to the parent directory", nullptr));
#endif // QT_CONFIG(accessibility)
#if QT_CONFIG(shortcut)
        toParentButton->setShortcut(QCoreApplication::translate("QFileDialog", "Alt+Up", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        newFolderButton->setToolTip(QCoreApplication::translate("QFileDialog", "Create New Folder", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(accessibility)
        newFolderButton->setAccessibleName(QCoreApplication::translate("QFileDialog", "Create New Folder", nullptr));
#endif // QT_CONFIG(accessibility)
#if QT_CONFIG(accessibility)
        newFolderButton->setAccessibleDescription(QCoreApplication::translate("QFileDialog", "Create a New Folder", nullptr));
#endif // QT_CONFIG(accessibility)
#if QT_CONFIG(tooltip)
        listModeButton->setToolTip(QCoreApplication::translate("QFileDialog", "List View", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(accessibility)
        listModeButton->setAccessibleName(QCoreApplication::translate("QFileDialog", "List View", nullptr));
#endif // QT_CONFIG(accessibility)
#if QT_CONFIG(accessibility)
        listModeButton->setAccessibleDescription(QCoreApplication::translate("QFileDialog", "Change to list view mode", nullptr));
#endif // QT_CONFIG(accessibility)
#if QT_CONFIG(tooltip)
        detailModeButton->setToolTip(QCoreApplication::translate("QFileDialog", "Detail View", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(accessibility)
        detailModeButton->setAccessibleName(QCoreApplication::translate("QFileDialog", "Detail View", nullptr));
#endif // QT_CONFIG(accessibility)
#if QT_CONFIG(accessibility)
        detailModeButton->setAccessibleDescription(QCoreApplication::translate("QFileDialog", "Change to detail view mode", nullptr));
#endif // QT_CONFIG(accessibility)
#if QT_CONFIG(accessibility)
        sidebar->setAccessibleName(QCoreApplication::translate("QFileDialog", "Sidebar", nullptr));
#endif // QT_CONFIG(accessibility)
#if QT_CONFIG(accessibility)
        sidebar->setAccessibleDescription(QCoreApplication::translate("QFileDialog", "List of places and bookmarks", nullptr));
#endif // QT_CONFIG(accessibility)
#if QT_CONFIG(accessibility)
        listView->setAccessibleName(QCoreApplication::translate("QFileDialog", "Files", nullptr));
#endif // QT_CONFIG(accessibility)
#if QT_CONFIG(accessibility)
        treeView->setAccessibleName(QCoreApplication::translate("QFileDialog", "Files", nullptr));
#endif // QT_CONFIG(accessibility)
        fileTypeLabel->setText(QCoreApplication::translate("QFileDialog", "Files of type:", nullptr));
        (void)QFileDialog;
    } // retranslateUi

};

namespace Ui {
    class QFileDialog: public Ui_QFileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QFILEDIALOG_H
