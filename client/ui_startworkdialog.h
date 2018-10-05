/********************************************************************************
** Form generated from reading UI file 'startworkdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTWORKDIALOG_H
#define UI_STARTWORKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_StartWorkDialog
{
public:
    QLabel *mInfoLabel;
    QToolButton *mYesButton;
    QToolButton *mNoButton;

    void setupUi(QDialog *StartWorkDialog)
    {
        if (StartWorkDialog->objectName().isEmpty())
            StartWorkDialog->setObjectName(QStringLiteral("StartWorkDialog"));
        StartWorkDialog->resize(394, 61);
        StartWorkDialog->setSizeGripEnabled(false);
        mInfoLabel = new QLabel(StartWorkDialog);
        mInfoLabel->setObjectName(QStringLiteral("mInfoLabel"));
        mInfoLabel->setGeometry(QRect(2, 2, 276, 51));
        QFont font;
        font.setPointSize(12);
        mInfoLabel->setFont(font);
        mInfoLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        mInfoLabel->setWordWrap(true);
        mInfoLabel->setMargin(4);
        mYesButton = new QToolButton(StartWorkDialog);
        mYesButton->setObjectName(QStringLiteral("mYesButton"));
        mYesButton->setGeometry(QRect(280, 4, 111, 25));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mYesButton->sizePolicy().hasHeightForWidth());
        mYesButton->setSizePolicy(sizePolicy);
        mYesButton->setFont(font);
        mYesButton->setPopupMode(QToolButton::DelayedPopup);
        mYesButton->setToolButtonStyle(Qt::ToolButtonTextOnly);
        mYesButton->setAutoRaise(true);
        mNoButton = new QToolButton(StartWorkDialog);
        mNoButton->setObjectName(QStringLiteral("mNoButton"));
        mNoButton->setGeometry(QRect(280, 34, 111, 25));
        sizePolicy.setHeightForWidth(mNoButton->sizePolicy().hasHeightForWidth());
        mNoButton->setSizePolicy(sizePolicy);
        mNoButton->setFont(font);
        mNoButton->setToolButtonStyle(Qt::ToolButtonTextOnly);

        retranslateUi(StartWorkDialog);
        QObject::connect(mYesButton, SIGNAL(clicked()), StartWorkDialog, SLOT(onYesButtonTriggered()));
        QObject::connect(mNoButton, SIGNAL(clicked()), StartWorkDialog, SLOT(onNoButtonTriggered()));

        QMetaObject::connectSlotsByName(StartWorkDialog);
    } // setupUi

    void retranslateUi(QDialog *StartWorkDialog)
    {
        StartWorkDialog->setWindowTitle(QApplication::translate("StartWorkDialog", "Dialog", Q_NULLPTR));
        mInfoLabel->setText(QApplication::translate("StartWorkDialog", "Litt discovered user activity after idle interval. \n"
"Should Litt start tracking on %TASK%?", Q_NULLPTR));
        mYesButton->setText(QApplication::translate("StartWorkDialog", "Yes", Q_NULLPTR));
        mNoButton->setText(QApplication::translate("StartWorkDialog", "No", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class StartWorkDialog: public Ui_StartWorkDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTWORKDIALOG_H
