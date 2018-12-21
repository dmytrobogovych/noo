/********************************************************************************
** Form generated from reading UI file 'newpassworddlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPASSWORDDLG_H
#define UI_NEWPASSWORDDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewPasswordDlg
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *mNewPasswordLabel1;
    QLineEdit *mNewPasswordEdit1;
    QLabel *mNewPasswordLabel2;
    QLineEdit *mNewPasswordEdit2;
    QLabel *mPasswordHintLabel;
    QDialogButtonBox *mDialogButtonBox;

    void setupUi(QDialog *NewPasswordDlg)
    {
        if (NewPasswordDlg->objectName().isEmpty())
            NewPasswordDlg->setObjectName(QString::fromUtf8("NewPasswordDlg"));
        NewPasswordDlg->resize(416, 200);
        NewPasswordDlg->setMinimumSize(QSize(400, 188));
        verticalLayout = new QVBoxLayout(NewPasswordDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        mNewPasswordLabel1 = new QLabel(NewPasswordDlg);
        mNewPasswordLabel1->setObjectName(QString::fromUtf8("mNewPasswordLabel1"));

        formLayout->setWidget(0, QFormLayout::LabelRole, mNewPasswordLabel1);

        mNewPasswordEdit1 = new QLineEdit(NewPasswordDlg);
        mNewPasswordEdit1->setObjectName(QString::fromUtf8("mNewPasswordEdit1"));
        mNewPasswordEdit1->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        mNewPasswordEdit1->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(0, QFormLayout::FieldRole, mNewPasswordEdit1);

        mNewPasswordLabel2 = new QLabel(NewPasswordDlg);
        mNewPasswordLabel2->setObjectName(QString::fromUtf8("mNewPasswordLabel2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, mNewPasswordLabel2);

        mNewPasswordEdit2 = new QLineEdit(NewPasswordDlg);
        mNewPasswordEdit2->setObjectName(QString::fromUtf8("mNewPasswordEdit2"));
        mNewPasswordEdit2->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, mNewPasswordEdit2);


        verticalLayout->addLayout(formLayout);

        mPasswordHintLabel = new QLabel(NewPasswordDlg);
        mPasswordHintLabel->setObjectName(QString::fromUtf8("mPasswordHintLabel"));
        mPasswordHintLabel->setWordWrap(true);

        verticalLayout->addWidget(mPasswordHintLabel);

        mDialogButtonBox = new QDialogButtonBox(NewPasswordDlg);
        mDialogButtonBox->setObjectName(QString::fromUtf8("mDialogButtonBox"));
        mDialogButtonBox->setOrientation(Qt::Horizontal);
        mDialogButtonBox->setStandardButtons(QDialogButtonBox::Ok);
        mDialogButtonBox->setCenterButtons(true);

        verticalLayout->addWidget(mDialogButtonBox);


        retranslateUi(NewPasswordDlg);
        QObject::connect(mDialogButtonBox, SIGNAL(accepted()), NewPasswordDlg, SLOT(tryAccept()));

        QMetaObject::connectSlotsByName(NewPasswordDlg);
    } // setupUi

    void retranslateUi(QDialog *NewPasswordDlg)
    {
        NewPasswordDlg->setWindowTitle(QApplication::translate("NewPasswordDlg", "Password for new database", nullptr));
        mNewPasswordLabel1->setText(QApplication::translate("NewPasswordDlg", "Password:", nullptr));
        mNewPasswordLabel2->setText(QApplication::translate("NewPasswordDlg", "Repeat password:", nullptr));
        mPasswordHintLabel->setText(QApplication::translate("NewPasswordDlg", "<html><head/><body><p>Please enter new password twice to complete database creation.</p> <p>Please be aware - there is no way to recover lost password.</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewPasswordDlg: public Ui_NewPasswordDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPASSWORDDLG_H
