/********************************************************************************
** Form generated from reading UI file 'newpassworddlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPASSWORDDLG_H
#define UI_NEWPASSWORDDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
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
            NewPasswordDlg->setObjectName(QStringLiteral("NewPasswordDlg"));
        NewPasswordDlg->resize(416, 200);
        NewPasswordDlg->setMinimumSize(QSize(400, 188));
        verticalLayout = new QVBoxLayout(NewPasswordDlg);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        mNewPasswordLabel1 = new QLabel(NewPasswordDlg);
        mNewPasswordLabel1->setObjectName(QStringLiteral("mNewPasswordLabel1"));

        formLayout->setWidget(0, QFormLayout::LabelRole, mNewPasswordLabel1);

        mNewPasswordEdit1 = new QLineEdit(NewPasswordDlg);
        mNewPasswordEdit1->setObjectName(QStringLiteral("mNewPasswordEdit1"));
        mNewPasswordEdit1->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        mNewPasswordEdit1->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(0, QFormLayout::FieldRole, mNewPasswordEdit1);

        mNewPasswordLabel2 = new QLabel(NewPasswordDlg);
        mNewPasswordLabel2->setObjectName(QStringLiteral("mNewPasswordLabel2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, mNewPasswordLabel2);

        mNewPasswordEdit2 = new QLineEdit(NewPasswordDlg);
        mNewPasswordEdit2->setObjectName(QStringLiteral("mNewPasswordEdit2"));
        mNewPasswordEdit2->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, mNewPasswordEdit2);


        verticalLayout->addLayout(formLayout);

        mPasswordHintLabel = new QLabel(NewPasswordDlg);
        mPasswordHintLabel->setObjectName(QStringLiteral("mPasswordHintLabel"));
        mPasswordHintLabel->setWordWrap(true);

        verticalLayout->addWidget(mPasswordHintLabel);

        mDialogButtonBox = new QDialogButtonBox(NewPasswordDlg);
        mDialogButtonBox->setObjectName(QStringLiteral("mDialogButtonBox"));
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
        NewPasswordDlg->setWindowTitle(QApplication::translate("NewPasswordDlg", "Password for new database", 0));
        mNewPasswordLabel1->setText(QApplication::translate("NewPasswordDlg", "Password:", 0));
        mNewPasswordLabel2->setText(QApplication::translate("NewPasswordDlg", "Repeat password:", 0));
        mPasswordHintLabel->setText(QApplication::translate("NewPasswordDlg", "<html><head/><body><p>Please enter new password twice to complete database creation.</p> <p>Please be aware - there is no way to recover lost password.</p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class NewPasswordDlg: public Ui_NewPasswordDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPASSWORDDLG_H
