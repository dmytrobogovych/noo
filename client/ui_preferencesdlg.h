/********************************************************************************
** Form generated from reading UI file 'preferencesdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCESDLG_H
#define UI_PREFERENCESDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PreferencesDlg
{
public:
    QVBoxLayout *verticalLayout_3;
    QCheckBox *mShowSecondsCheckbox;
    QCheckBox *mAutosavePasswordCheckbox;
    QCheckBox *mShowTrayIconCheckbox;
    QCheckBox *mDarkThemeCheckbox;
    QCheckBox *mCustomDatabaseFileCheckbox;
    QPushButton *mSelectDatabaseButton;
    QLabel *mDatabaseLocation;
    QVBoxLayout *stopTrackingRuleLayout;
    QHBoxLayout *horizontalLayout;
    QCheckBox *mSmartStopTracking;
    QLineEdit *mSmartStopIntervalInMinutes;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *mAskQuestionOnStopRadiobutton;
    QRadioButton *mAutomaticallyOnStopRadiobutton;
    QVBoxLayout *startTrackingRuleLayout;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *mSmartStartTracking;
    QLabel *label_2;
    QDialogButtonBox *buttonBox;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *PreferencesDlg)
    {
        if (PreferencesDlg->objectName().isEmpty())
            PreferencesDlg->setObjectName(QStringLiteral("PreferencesDlg"));
        PreferencesDlg->resize(444, 353);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PreferencesDlg->sizePolicy().hasHeightForWidth());
        PreferencesDlg->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(PreferencesDlg);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        mShowSecondsCheckbox = new QCheckBox(PreferencesDlg);
        mShowSecondsCheckbox->setObjectName(QStringLiteral("mShowSecondsCheckbox"));

        verticalLayout_3->addWidget(mShowSecondsCheckbox);

        mAutosavePasswordCheckbox = new QCheckBox(PreferencesDlg);
        mAutosavePasswordCheckbox->setObjectName(QStringLiteral("mAutosavePasswordCheckbox"));

        verticalLayout_3->addWidget(mAutosavePasswordCheckbox);

        mShowTrayIconCheckbox = new QCheckBox(PreferencesDlg);
        mShowTrayIconCheckbox->setObjectName(QStringLiteral("mShowTrayIconCheckbox"));

        verticalLayout_3->addWidget(mShowTrayIconCheckbox);

        mDarkThemeCheckbox = new QCheckBox(PreferencesDlg);
        mDarkThemeCheckbox->setObjectName(QStringLiteral("mDarkThemeCheckbox"));

        verticalLayout_3->addWidget(mDarkThemeCheckbox);

        mCustomDatabaseFileCheckbox = new QCheckBox(PreferencesDlg);
        mCustomDatabaseFileCheckbox->setObjectName(QStringLiteral("mCustomDatabaseFileCheckbox"));

        verticalLayout_3->addWidget(mCustomDatabaseFileCheckbox);

        mSelectDatabaseButton = new QPushButton(PreferencesDlg);
        mSelectDatabaseButton->setObjectName(QStringLiteral("mSelectDatabaseButton"));

        verticalLayout_3->addWidget(mSelectDatabaseButton);

        mDatabaseLocation = new QLabel(PreferencesDlg);
        mDatabaseLocation->setObjectName(QStringLiteral("mDatabaseLocation"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(mDatabaseLocation->sizePolicy().hasHeightForWidth());
        mDatabaseLocation->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(mDatabaseLocation);

        stopTrackingRuleLayout = new QVBoxLayout();
        stopTrackingRuleLayout->setSpacing(0);
        stopTrackingRuleLayout->setObjectName(QStringLiteral("stopTrackingRuleLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        mSmartStopTracking = new QCheckBox(PreferencesDlg);
        mSmartStopTracking->setObjectName(QStringLiteral("mSmartStopTracking"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(20);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(mSmartStopTracking->sizePolicy().hasHeightForWidth());
        mSmartStopTracking->setSizePolicy(sizePolicy2);
        mSmartStopTracking->setMinimumSize(QSize(240, 0));

        horizontalLayout->addWidget(mSmartStopTracking);

        mSmartStopIntervalInMinutes = new QLineEdit(PreferencesDlg);
        mSmartStopIntervalInMinutes->setObjectName(QStringLiteral("mSmartStopIntervalInMinutes"));
        mSmartStopIntervalInMinutes->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(mSmartStopIntervalInMinutes);

        label = new QLabel(PreferencesDlg);
        label->setObjectName(QStringLiteral("label"));
        label->setMargin(3);

        horizontalLayout->addWidget(label);


        stopTrackingRuleLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        mAskQuestionOnStopRadiobutton = new QRadioButton(PreferencesDlg);
        buttonGroup = new QButtonGroup(PreferencesDlg);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(mAskQuestionOnStopRadiobutton);
        mAskQuestionOnStopRadiobutton->setObjectName(QStringLiteral("mAskQuestionOnStopRadiobutton"));

        verticalLayout_2->addWidget(mAskQuestionOnStopRadiobutton);

        mAutomaticallyOnStopRadiobutton = new QRadioButton(PreferencesDlg);
        buttonGroup->addButton(mAutomaticallyOnStopRadiobutton);
        mAutomaticallyOnStopRadiobutton->setObjectName(QStringLiteral("mAutomaticallyOnStopRadiobutton"));

        verticalLayout_2->addWidget(mAutomaticallyOnStopRadiobutton);


        horizontalLayout_3->addLayout(verticalLayout_2);


        stopTrackingRuleLayout->addLayout(horizontalLayout_3);


        verticalLayout_3->addLayout(stopTrackingRuleLayout);

        startTrackingRuleLayout = new QVBoxLayout();
        startTrackingRuleLayout->setSpacing(0);
        startTrackingRuleLayout->setObjectName(QStringLiteral("startTrackingRuleLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        mSmartStartTracking = new QCheckBox(PreferencesDlg);
        mSmartStartTracking->setObjectName(QStringLiteral("mSmartStartTracking"));

        horizontalLayout_4->addWidget(mSmartStartTracking);

        label_2 = new QLabel(PreferencesDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);


        startTrackingRuleLayout->addLayout(horizontalLayout_4);


        verticalLayout_3->addLayout(startTrackingRuleLayout);

        buttonBox = new QDialogButtonBox(PreferencesDlg);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        verticalLayout_3->addWidget(buttonBox);


        retranslateUi(PreferencesDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), PreferencesDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PreferencesDlg, SLOT(reject()));
        QObject::connect(buttonGroup, SIGNAL(buttonClicked(int)), PreferencesDlg, SLOT(smartStopWayChanged()));

        QMetaObject::connectSlotsByName(PreferencesDlg);
    } // setupUi

    void retranslateUi(QDialog *PreferencesDlg)
    {
        PreferencesDlg->setWindowTitle(QApplication::translate("PreferencesDlg", "Dialog", Q_NULLPTR));
        mShowSecondsCheckbox->setText(QApplication::translate("PreferencesDlg", "Show seconds", Q_NULLPTR));
        mAutosavePasswordCheckbox->setText(QApplication::translate("PreferencesDlg", "Autosave password (requires app restart)", Q_NULLPTR));
        mShowTrayIconCheckbox->setText(QApplication::translate("PreferencesDlg", "Show tray icon", Q_NULLPTR));
        mDarkThemeCheckbox->setText(QApplication::translate("PreferencesDlg", "Use dark theme", Q_NULLPTR));
        mCustomDatabaseFileCheckbox->setText(QApplication::translate("PreferencesDlg", "Use database at custom location (requires app restart)", Q_NULLPTR));
        mSelectDatabaseButton->setText(QApplication::translate("PreferencesDlg", "Select file...", Q_NULLPTR));
        mDatabaseLocation->setText(QApplication::translate("PreferencesDlg", "Location of used database", Q_NULLPTR));
        mSmartStopTracking->setText(QApplication::translate("PreferencesDlg", "Stop tracking if idle detected for", Q_NULLPTR));
        label->setText(QApplication::translate("PreferencesDlg", "minutes", Q_NULLPTR));
        mAskQuestionOnStopRadiobutton->setText(QApplication::translate("PreferencesDlg", "Ask question", Q_NULLPTR));
        mAutomaticallyOnStopRadiobutton->setText(QApplication::translate("PreferencesDlg", "Automatically", Q_NULLPTR));
        mSmartStartTracking->setText(QApplication::translate("PreferencesDlg", "Start tracking after stop on idle when user activity detected. \n"
"This option requires enabled automatic stop tracking on idle.", Q_NULLPTR));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PreferencesDlg: public Ui_PreferencesDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCESDLG_H
