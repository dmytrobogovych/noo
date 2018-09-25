/********************************************************************************
** Form generated from reading UI file 'stopworkdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STOPWORKDIALOG_H
#define UI_STOPWORKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_StopWorkDialog
{
public:
    QLabel *mInfoLabel;
    QToolButton *mYesButton;
    QToolButton *mNoButton;

    void setupUi(QDialog *StopWorkDialog)
    {
        if (StopWorkDialog->objectName().isEmpty())
            StopWorkDialog->setObjectName(QStringLiteral("StopWorkDialog"));
        StopWorkDialog->resize(386, 59);
        mInfoLabel = new QLabel(StopWorkDialog);
        mInfoLabel->setObjectName(QStringLiteral("mInfoLabel"));
        mInfoLabel->setGeometry(QRect(7, 3, 241, 41));
        QFont font;
        font.setPointSize(12);
        mInfoLabel->setFont(font);
        mInfoLabel->setScaledContents(false);
        mInfoLabel->setWordWrap(true);
        mYesButton = new QToolButton(StopWorkDialog);
        mYesButton->setObjectName(QStringLiteral("mYesButton"));
        mYesButton->setGeometry(QRect(270, 3, 111, 25));
        mYesButton->setFont(font);
        mNoButton = new QToolButton(StopWorkDialog);
        mNoButton->setObjectName(QStringLiteral("mNoButton"));
        mNoButton->setGeometry(QRect(270, 32, 111, 25));
        mNoButton->setFont(font);

        retranslateUi(StopWorkDialog);
        QObject::connect(mYesButton, SIGNAL(clicked()), StopWorkDialog, SLOT(onYesButtonTriggered()));
        QObject::connect(mNoButton, SIGNAL(clicked()), StopWorkDialog, SLOT(onNoButtonTriggered()));

        QMetaObject::connectSlotsByName(StopWorkDialog);
    } // setupUi

    void retranslateUi(QDialog *StopWorkDialog)
    {
        StopWorkDialog->setWindowTitle(QApplication::translate("StopWorkDialog", "Dialog", 0));
        mInfoLabel->setText(QApplication::translate("StopWorkDialog", "Litt discovered idle interval at %TIME%.\n"
"Should app to continue work tracking?", 0));
        mYesButton->setText(QApplication::translate("StopWorkDialog", "Yes", 0));
        mNoButton->setText(QApplication::translate("StopWorkDialog", "No", 0));
    } // retranslateUi

};

namespace Ui {
    class StopWorkDialog: public Ui_StopWorkDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STOPWORKDIALOG_H
