/********************************************************************************
** Form generated from reading UI file 'attachmentsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATTACHMENTSDIALOG_H
#define UI_ATTACHMENTSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include "attachmentslist.h"

QT_BEGIN_NAMESPACE

class Ui_AttachmentsDialog
{
public:
    QVBoxLayout *verticalLayout;
    AttachmentsList *widget;
    QLabel *label;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AttachmentsDialog)
    {
        if (AttachmentsDialog->objectName().isEmpty())
            AttachmentsDialog->setObjectName(QString::fromUtf8("AttachmentsDialog"));
        AttachmentsDialog->resize(600, 300);
        AttachmentsDialog->setSizeGripEnabled(true);
        verticalLayout = new QVBoxLayout(AttachmentsDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new AttachmentsList(AttachmentsDialog);
        widget->setObjectName(QString::fromUtf8("widget"));

        verticalLayout->addWidget(widget);

        label = new QLabel(AttachmentsDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(16777215, 30));
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        buttonBox = new QDialogButtonBox(AttachmentsDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(AttachmentsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AttachmentsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AttachmentsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AttachmentsDialog);
    } // setupUi

    void retranslateUi(QDialog *AttachmentsDialog)
    {
        AttachmentsDialog->setWindowTitle(QApplication::translate("AttachmentsDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("AttachmentsDialog", "There is list of attachments in document. Use context menu or drag-and-drop to manage it.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AttachmentsDialog: public Ui_AttachmentsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATTACHMENTSDIALOG_H
