/********************************************************************************
** Form generated from reading UI file 'aboutdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDLG_H
#define UI_ABOUTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AboutDlg
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *mTextLabel;
    QLabel *mLicenseLabel;
    QDialogButtonBox *mButtonBox;

    void setupUi(QDialog *AboutDlg)
    {
        if (AboutDlg->objectName().isEmpty())
            AboutDlg->setObjectName(QString::fromUtf8("AboutDlg"));
        AboutDlg->resize(323, 170);
        verticalLayout = new QVBoxLayout(AboutDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        mTextLabel = new QLabel(AboutDlg);
        mTextLabel->setObjectName(QString::fromUtf8("mTextLabel"));
        mTextLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(mTextLabel);

        mLicenseLabel = new QLabel(AboutDlg);
        mLicenseLabel->setObjectName(QString::fromUtf8("mLicenseLabel"));
        mLicenseLabel->setMaximumSize(QSize(16777215, 40));
        mLicenseLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(mLicenseLabel);

        mButtonBox = new QDialogButtonBox(AboutDlg);
        mButtonBox->setObjectName(QString::fromUtf8("mButtonBox"));
        mButtonBox->setOrientation(Qt::Horizontal);
        mButtonBox->setStandardButtons(QDialogButtonBox::Ok);
        mButtonBox->setCenterButtons(true);

        verticalLayout->addWidget(mButtonBox);


        retranslateUi(AboutDlg);
        QObject::connect(mButtonBox, SIGNAL(accepted()), AboutDlg, SLOT(accept()));
        QObject::connect(mButtonBox, SIGNAL(rejected()), AboutDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(AboutDlg);
    } // setupUi

    void retranslateUi(QDialog *AboutDlg)
    {
        AboutDlg->setWindowTitle(QApplication::translate("AboutDlg", "Dialog", nullptr));
        mTextLabel->setText(QApplication::translate("AboutDlg", "werwre\n"
"werwer\n"
"", nullptr));
        mLicenseLabel->setText(QApplication::translate("AboutDlg", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutDlg: public Ui_AboutDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDLG_H
