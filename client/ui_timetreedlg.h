/********************************************************************************
** Form generated from reading UI file 'timetreedlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMETREEDLG_H
#define UI_TIMETREEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TimeTreeDlg
{
public:
    QAction *mAddIntervalAction;
    QAction *mRemoveIntervalAction;
    QAction *mChangeIntervalAction;
    QGridLayout *gridLayout;
    QTreeView *mTimeTree;
    QVBoxLayout *verticalLayout;
    QPushButton *mAddIntervalButton;
    QPushButton *mRemoveIntervalButton;
    QDialogButtonBox *mButtonBox;

    void setupUi(QDialog *TimeTreeDlg)
    {
        if (TimeTreeDlg->objectName().isEmpty())
            TimeTreeDlg->setObjectName(QStringLiteral("TimeTreeDlg"));
        TimeTreeDlg->resize(400, 300);
        TimeTreeDlg->setModal(true);
        mAddIntervalAction = new QAction(TimeTreeDlg);
        mAddIntervalAction->setObjectName(QStringLiteral("mAddIntervalAction"));
        mRemoveIntervalAction = new QAction(TimeTreeDlg);
        mRemoveIntervalAction->setObjectName(QStringLiteral("mRemoveIntervalAction"));
        mChangeIntervalAction = new QAction(TimeTreeDlg);
        mChangeIntervalAction->setObjectName(QStringLiteral("mChangeIntervalAction"));
        gridLayout = new QGridLayout(TimeTreeDlg);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        mTimeTree = new QTreeView(TimeTreeDlg);
        mTimeTree->setObjectName(QStringLiteral("mTimeTree"));

        gridLayout->addWidget(mTimeTree, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        mAddIntervalButton = new QPushButton(TimeTreeDlg);
        mAddIntervalButton->setObjectName(QStringLiteral("mAddIntervalButton"));

        verticalLayout->addWidget(mAddIntervalButton);

        mRemoveIntervalButton = new QPushButton(TimeTreeDlg);
        mRemoveIntervalButton->setObjectName(QStringLiteral("mRemoveIntervalButton"));

        verticalLayout->addWidget(mRemoveIntervalButton);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        mButtonBox = new QDialogButtonBox(TimeTreeDlg);
        mButtonBox->setObjectName(QStringLiteral("mButtonBox"));
        mButtonBox->setOrientation(Qt::Horizontal);
        mButtonBox->setStandardButtons(QDialogButtonBox::Ok);
        mButtonBox->setCenterButtons(true);

        gridLayout->addWidget(mButtonBox, 1, 0, 1, 1);


        retranslateUi(TimeTreeDlg);
        QObject::connect(mButtonBox, SIGNAL(accepted()), TimeTreeDlg, SLOT(accept()));
        QObject::connect(mButtonBox, SIGNAL(rejected()), TimeTreeDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(TimeTreeDlg);
    } // setupUi

    void retranslateUi(QDialog *TimeTreeDlg)
    {
        TimeTreeDlg->setWindowTitle(QApplication::translate("TimeTreeDlg", "Timeline", 0));
        mAddIntervalAction->setText(QApplication::translate("TimeTreeDlg", "Add...", 0));
        mRemoveIntervalAction->setText(QApplication::translate("TimeTreeDlg", "Remove", 0));
        mChangeIntervalAction->setText(QApplication::translate("TimeTreeDlg", "Change...", 0));
        mAddIntervalButton->setText(QApplication::translate("TimeTreeDlg", "Add...", 0));
        mRemoveIntervalButton->setText(QApplication::translate("TimeTreeDlg", "Remove", 0));
    } // retranslateUi

};

namespace Ui {
    class TimeTreeDlg: public Ui_TimeTreeDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMETREEDLG_H
