/********************************************************************************
** Form generated from reading UI file 'timeintervaldlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMEINTERVALDLG_H
#define UI_TIMEINTERVALDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TimeIntervalDlg
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *mStartTimeLabel;
    QDateTimeEdit *mStartTimeEdit;
    QLabel *mFinishTimeLabel;
    QDateTimeEdit *mFinishTimeEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *TimeIntervalDlg)
    {
        if (TimeIntervalDlg->objectName().isEmpty())
            TimeIntervalDlg->setObjectName(QStringLiteral("TimeIntervalDlg"));
        TimeIntervalDlg->resize(400, 134);
        TimeIntervalDlg->setModal(false);
        verticalLayout = new QVBoxLayout(TimeIntervalDlg);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        mStartTimeLabel = new QLabel(TimeIntervalDlg);
        mStartTimeLabel->setObjectName(QStringLiteral("mStartTimeLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, mStartTimeLabel);

        mStartTimeEdit = new QDateTimeEdit(TimeIntervalDlg);
        mStartTimeEdit->setObjectName(QStringLiteral("mStartTimeEdit"));
        mStartTimeEdit->setTime(QTime(1, 0, 0));
        mStartTimeEdit->setCalendarPopup(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, mStartTimeEdit);

        mFinishTimeLabel = new QLabel(TimeIntervalDlg);
        mFinishTimeLabel->setObjectName(QStringLiteral("mFinishTimeLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, mFinishTimeLabel);

        mFinishTimeEdit = new QDateTimeEdit(TimeIntervalDlg);
        mFinishTimeEdit->setObjectName(QStringLiteral("mFinishTimeEdit"));
        mFinishTimeEdit->setCalendarPopup(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, mFinishTimeEdit);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(TimeIntervalDlg);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(TimeIntervalDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), TimeIntervalDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TimeIntervalDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(TimeIntervalDlg);
    } // setupUi

    void retranslateUi(QDialog *TimeIntervalDlg)
    {
        TimeIntervalDlg->setWindowTitle(QApplication::translate("TimeIntervalDlg", "Time interval", Q_NULLPTR));
        mStartTimeLabel->setText(QApplication::translate("TimeIntervalDlg", "Start time:", Q_NULLPTR));
        mFinishTimeLabel->setText(QApplication::translate("TimeIntervalDlg", "Finish time:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TimeIntervalDlg: public Ui_TimeIntervalDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMEINTERVALDLG_H
