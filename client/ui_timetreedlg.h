/********************************************************************************
** Form generated from reading UI file 'timetreedlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMETREEDLG_H
#define UI_TIMETREEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
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
            TimeTreeDlg->setObjectName(QString::fromUtf8("TimeTreeDlg"));
        TimeTreeDlg->resize(400, 300);
        TimeTreeDlg->setModal(true);
        mAddIntervalAction = new QAction(TimeTreeDlg);
        mAddIntervalAction->setObjectName(QString::fromUtf8("mAddIntervalAction"));
        mRemoveIntervalAction = new QAction(TimeTreeDlg);
        mRemoveIntervalAction->setObjectName(QString::fromUtf8("mRemoveIntervalAction"));
        mChangeIntervalAction = new QAction(TimeTreeDlg);
        mChangeIntervalAction->setObjectName(QString::fromUtf8("mChangeIntervalAction"));
        gridLayout = new QGridLayout(TimeTreeDlg);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mTimeTree = new QTreeView(TimeTreeDlg);
        mTimeTree->setObjectName(QString::fromUtf8("mTimeTree"));

        gridLayout->addWidget(mTimeTree, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        mAddIntervalButton = new QPushButton(TimeTreeDlg);
        mAddIntervalButton->setObjectName(QString::fromUtf8("mAddIntervalButton"));

        verticalLayout->addWidget(mAddIntervalButton);

        mRemoveIntervalButton = new QPushButton(TimeTreeDlg);
        mRemoveIntervalButton->setObjectName(QString::fromUtf8("mRemoveIntervalButton"));

        verticalLayout->addWidget(mRemoveIntervalButton);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        mButtonBox = new QDialogButtonBox(TimeTreeDlg);
        mButtonBox->setObjectName(QString::fromUtf8("mButtonBox"));
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
        TimeTreeDlg->setWindowTitle(QApplication::translate("TimeTreeDlg", "Timeline", nullptr));
        mAddIntervalAction->setText(QApplication::translate("TimeTreeDlg", "Add...", nullptr));
        mRemoveIntervalAction->setText(QApplication::translate("TimeTreeDlg", "Remove", nullptr));
        mChangeIntervalAction->setText(QApplication::translate("TimeTreeDlg", "Change...", nullptr));
        mAddIntervalButton->setText(QApplication::translate("TimeTreeDlg", "Add...", nullptr));
        mRemoveIntervalButton->setText(QApplication::translate("TimeTreeDlg", "Remove", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TimeTreeDlg: public Ui_TimeTreeDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMETREEDLG_H
