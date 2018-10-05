/********************************************************************************
** Form generated from reading UI file 'attachmentslist.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATTACHMENTSLIST_H
#define UI_ATTACHMENTSLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AttachmentsList
{
public:
    QAction *mRenameAction;
    QAction *mDeleteAction;
    QAction *mExportAction;
    QAction *mImportAction;
    QHBoxLayout *horizontalLayout;
    QListView *mListView;

    void setupUi(QWidget *AttachmentsList)
    {
        if (AttachmentsList->objectName().isEmpty())
            AttachmentsList->setObjectName(QStringLiteral("AttachmentsList"));
        AttachmentsList->resize(425, 300);
        mRenameAction = new QAction(AttachmentsList);
        mRenameAction->setObjectName(QStringLiteral("mRenameAction"));
        mDeleteAction = new QAction(AttachmentsList);
        mDeleteAction->setObjectName(QStringLiteral("mDeleteAction"));
        mExportAction = new QAction(AttachmentsList);
        mExportAction->setObjectName(QStringLiteral("mExportAction"));
        mImportAction = new QAction(AttachmentsList);
        mImportAction->setObjectName(QStringLiteral("mImportAction"));
        horizontalLayout = new QHBoxLayout(AttachmentsList);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(4, 4, 4, 4);
        mListView = new QListView(AttachmentsList);
        mListView->setObjectName(QStringLiteral("mListView"));
        mListView->setContextMenuPolicy(Qt::CustomContextMenu);
        mListView->setViewMode(QListView::IconMode);

        horizontalLayout->addWidget(mListView);


        retranslateUi(AttachmentsList);
        QObject::connect(mListView, SIGNAL(customContextMenuRequested(QPoint)), AttachmentsList, SLOT(contextualMenu(QPoint)));
        QObject::connect(mImportAction, SIGNAL(triggered()), AttachmentsList, SLOT(importFile()));
        QObject::connect(mExportAction, SIGNAL(triggered()), AttachmentsList, SLOT(exportFile()));
        QObject::connect(mDeleteAction, SIGNAL(triggered()), AttachmentsList, SLOT(deleteFile()));
        QObject::connect(mRenameAction, SIGNAL(triggered()), AttachmentsList, SLOT(renameFile()));

        QMetaObject::connectSlotsByName(AttachmentsList);
    } // setupUi

    void retranslateUi(QWidget *AttachmentsList)
    {
        AttachmentsList->setWindowTitle(QApplication::translate("AttachmentsList", "Form", Q_NULLPTR));
        mRenameAction->setText(QApplication::translate("AttachmentsList", "Rename", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        mRenameAction->setToolTip(QApplication::translate("AttachmentsList", "Rename", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        mDeleteAction->setText(QApplication::translate("AttachmentsList", "Delete", Q_NULLPTR));
        mExportAction->setText(QApplication::translate("AttachmentsList", "Export...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        mExportAction->setToolTip(QApplication::translate("AttachmentsList", "Export", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        mImportAction->setText(QApplication::translate("AttachmentsList", "Import new...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        mImportAction->setToolTip(QApplication::translate("AttachmentsList", "Import", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class AttachmentsList: public Ui_AttachmentsList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATTACHMENTSLIST_H
