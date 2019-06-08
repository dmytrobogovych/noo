/********************************************************************************
** Form generated from reading UI file 'fvupdatewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FVUPDATEWINDOW_H
#define UI_FVUPDATEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FvUpdateWindow
{
public:
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout;
    QLabel *newVersionIsAvailableLabel;
    QLabel *wouldYouLikeToDownloadLabel;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_7;
    QTextBrowser *releaseNotes;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *skipThisVersionButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *remindMeLaterButton;
    QPushButton *installUpdateButton;

    void setupUi(QWidget *FvUpdateWindow)
    {
        if (FvUpdateWindow->objectName().isEmpty())
            FvUpdateWindow->setObjectName(QString::fromUtf8("FvUpdateWindow"));
        FvUpdateWindow->resize(640, 480);
        horizontalLayout_6 = new QHBoxLayout(FvUpdateWindow);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        newVersionIsAvailableLabel = new QLabel(FvUpdateWindow);
        newVersionIsAvailableLabel->setObjectName(QString::fromUtf8("newVersionIsAvailableLabel"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        newVersionIsAvailableLabel->setFont(font);

        verticalLayout->addWidget(newVersionIsAvailableLabel);

        wouldYouLikeToDownloadLabel = new QLabel(FvUpdateWindow);
        wouldYouLikeToDownloadLabel->setObjectName(QString::fromUtf8("wouldYouLikeToDownloadLabel"));

        verticalLayout->addWidget(wouldYouLikeToDownloadLabel);

        groupBox = new QGroupBox(FvUpdateWindow);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFont(font);
        horizontalLayout_7 = new QHBoxLayout(groupBox);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        releaseNotes = new QTextBrowser(groupBox);
        releaseNotes->setObjectName(QString::fromUtf8("releaseNotes"));

        horizontalLayout_7->addWidget(releaseNotes);


        verticalLayout->addWidget(groupBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        skipThisVersionButton = new QPushButton(FvUpdateWindow);
        skipThisVersionButton->setObjectName(QString::fromUtf8("skipThisVersionButton"));

        horizontalLayout_3->addWidget(skipThisVersionButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        remindMeLaterButton = new QPushButton(FvUpdateWindow);
        remindMeLaterButton->setObjectName(QString::fromUtf8("remindMeLaterButton"));

        horizontalLayout_3->addWidget(remindMeLaterButton);

        installUpdateButton = new QPushButton(FvUpdateWindow);
        installUpdateButton->setObjectName(QString::fromUtf8("installUpdateButton"));
        installUpdateButton->setAutoDefault(true);

        horizontalLayout_3->addWidget(installUpdateButton);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_6->addLayout(verticalLayout);


        retranslateUi(FvUpdateWindow);

        installUpdateButton->setDefault(true);


        QMetaObject::connectSlotsByName(FvUpdateWindow);
    } // setupUi

    void retranslateUi(QWidget *FvUpdateWindow)
    {
        FvUpdateWindow->setWindowTitle(QApplication::translate("FvUpdateWindow", "Software Update", nullptr));
        newVersionIsAvailableLabel->setText(QApplication::translate("FvUpdateWindow", "A new version of %1 is available!", nullptr));
        wouldYouLikeToDownloadLabel->setText(QApplication::translate("FvUpdateWindow", "%1 %2 is now available - you have %3. Would you like to download it now?", nullptr));
        groupBox->setTitle(QApplication::translate("FvUpdateWindow", "Release Notes:", nullptr));
        skipThisVersionButton->setText(QApplication::translate("FvUpdateWindow", "Skip This Version", nullptr));
        remindMeLaterButton->setText(QApplication::translate("FvUpdateWindow", "Remind Me Later", nullptr));
        installUpdateButton->setText(QApplication::translate("FvUpdateWindow", "Install Update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FvUpdateWindow: public Ui_FvUpdateWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FVUPDATEWINDOW_H
