/********************************************************************************
** Form generated from reading UI file 'passworddlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSWORDDLG_H
#define UI_PASSWORDDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PasswordDlg
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *mPasswordFormLayout;
    QLabel *mPasswordLabel;
    QLineEdit *mPasswordEdit;
    QDialogButtonBox *mButtonBox;

    void setupUi(QDialog *PasswordDlg)
    {
        if (PasswordDlg->objectName().isEmpty())
            PasswordDlg->setObjectName(QString::fromUtf8("PasswordDlg"));
        PasswordDlg->resize(285, 113);
        PasswordDlg->setMinimumSize(QSize(285, 113));
        verticalLayout = new QVBoxLayout(PasswordDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 24, -1, 12);
        mPasswordFormLayout = new QFormLayout();
        mPasswordFormLayout->setObjectName(QString::fromUtf8("mPasswordFormLayout"));
        mPasswordFormLayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
        mPasswordLabel = new QLabel(PasswordDlg);
        mPasswordLabel->setObjectName(QString::fromUtf8("mPasswordLabel"));

        mPasswordFormLayout->setWidget(0, QFormLayout::LabelRole, mPasswordLabel);

        mPasswordEdit = new QLineEdit(PasswordDlg);
        mPasswordEdit->setObjectName(QString::fromUtf8("mPasswordEdit"));
        mPasswordEdit->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        mPasswordEdit->setEchoMode(QLineEdit::Password);

        mPasswordFormLayout->setWidget(0, QFormLayout::FieldRole, mPasswordEdit);


        verticalLayout->addLayout(mPasswordFormLayout);

        mButtonBox = new QDialogButtonBox(PasswordDlg);
        mButtonBox->setObjectName(QString::fromUtf8("mButtonBox"));
        mButtonBox->setMaximumSize(QSize(16777215, 50));
        mButtonBox->setOrientation(Qt::Horizontal);
        mButtonBox->setStandardButtons(QDialogButtonBox::Ok);
        mButtonBox->setCenterButtons(true);

        verticalLayout->addWidget(mButtonBox);


        retranslateUi(PasswordDlg);
        QObject::connect(mButtonBox, SIGNAL(accepted()), PasswordDlg, SLOT(accept()));

        QMetaObject::connectSlotsByName(PasswordDlg);
    } // setupUi

    void retranslateUi(QDialog *PasswordDlg)
    {
        PasswordDlg->setWindowTitle(QApplication::translate("PasswordDlg", "Password required", nullptr));
        mPasswordLabel->setText(QApplication::translate("PasswordDlg", "Password:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PasswordDlg: public Ui_PasswordDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSWORDDLG_H
