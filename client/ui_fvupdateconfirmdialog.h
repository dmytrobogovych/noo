/********************************************************************************
** Form generated from reading UI file 'fvupdateconfirmdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FVUPDATECONFIRMDIALOG_H
#define UI_FVUPDATECONFIRMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FvUpdateConfirmDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *updateFileIsLocatedLabel;
    QLabel *updateFileLinkLabel;
    QLabel *downloadThisUpdateLabel;
    QLabel *whenYouClickOkLabel;
    QDialogButtonBox *confirmButtonBox;

    void setupUi(QDialog *FvUpdateConfirmDialog)
    {
        if (FvUpdateConfirmDialog->objectName().isEmpty())
            FvUpdateConfirmDialog->setObjectName(QString::fromUtf8("FvUpdateConfirmDialog"));
        FvUpdateConfirmDialog->resize(480, 160);
        verticalLayout = new QVBoxLayout(FvUpdateConfirmDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        updateFileIsLocatedLabel = new QLabel(FvUpdateConfirmDialog);
        updateFileIsLocatedLabel->setObjectName(QString::fromUtf8("updateFileIsLocatedLabel"));

        verticalLayout->addWidget(updateFileIsLocatedLabel);

        updateFileLinkLabel = new QLabel(FvUpdateConfirmDialog);
        updateFileLinkLabel->setObjectName(QString::fromUtf8("updateFileLinkLabel"));
        updateFileLinkLabel->setOpenExternalLinks(true);
        updateFileLinkLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);

        verticalLayout->addWidget(updateFileLinkLabel);

        downloadThisUpdateLabel = new QLabel(FvUpdateConfirmDialog);
        downloadThisUpdateLabel->setObjectName(QString::fromUtf8("downloadThisUpdateLabel"));

        verticalLayout->addWidget(downloadThisUpdateLabel);

        whenYouClickOkLabel = new QLabel(FvUpdateConfirmDialog);
        whenYouClickOkLabel->setObjectName(QString::fromUtf8("whenYouClickOkLabel"));

        verticalLayout->addWidget(whenYouClickOkLabel);

        confirmButtonBox = new QDialogButtonBox(FvUpdateConfirmDialog);
        confirmButtonBox->setObjectName(QString::fromUtf8("confirmButtonBox"));
        confirmButtonBox->setOrientation(Qt::Horizontal);
        confirmButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(confirmButtonBox);


        retranslateUi(FvUpdateConfirmDialog);

        QMetaObject::connectSlotsByName(FvUpdateConfirmDialog);
    } // setupUi

    void retranslateUi(QDialog *FvUpdateConfirmDialog)
    {
        FvUpdateConfirmDialog->setWindowTitle(QApplication::translate("FvUpdateConfirmDialog", "Software Update", nullptr));
        updateFileIsLocatedLabel->setText(QApplication::translate("FvUpdateConfirmDialog", "The update file is located at:", nullptr));
        updateFileLinkLabel->setText(QApplication::translate("FvUpdateConfirmDialog", "<a href=\"%1\">%1</a>", nullptr));
        downloadThisUpdateLabel->setText(QApplication::translate("FvUpdateConfirmDialog", "Download this update, close \"%1\", install it, and then reopen \"%1\".", nullptr));
        whenYouClickOkLabel->setText(QApplication::translate("FvUpdateConfirmDialog", "When you click \"OK\", this link will be opened in your browser.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FvUpdateConfirmDialog: public Ui_FvUpdateConfirmDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FVUPDATECONFIRMDIALOG_H
