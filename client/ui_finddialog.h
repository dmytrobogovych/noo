/********************************************************************************
** Form generated from reading UI file 'finddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDDIALOG_H
#define UI_FINDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FindDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *mQueryText;
    QPushButton *mSearchButton;
    QTableView *mResultList;

    void setupUi(QDialog *FindDialog)
    {
        if (FindDialog->objectName().isEmpty())
            FindDialog->setObjectName(QString::fromUtf8("FindDialog"));
        FindDialog->resize(611, 392);
        verticalLayout = new QVBoxLayout(FindDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(FindDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        mQueryText = new QLineEdit(FindDialog);
        mQueryText->setObjectName(QString::fromUtf8("mQueryText"));

        horizontalLayout->addWidget(mQueryText);

        mSearchButton = new QPushButton(FindDialog);
        mSearchButton->setObjectName(QString::fromUtf8("mSearchButton"));
        mSearchButton->setAutoDefault(false);

        horizontalLayout->addWidget(mSearchButton);


        verticalLayout->addLayout(horizontalLayout);

        mResultList = new QTableView(FindDialog);
        mResultList->setObjectName(QString::fromUtf8("mResultList"));
        mResultList->setSelectionBehavior(QAbstractItemView::SelectRows);
        mResultList->setShowGrid(false);
        mResultList->horizontalHeader()->setDefaultSectionSize(293);
        mResultList->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(mResultList);


        retranslateUi(FindDialog);

        mSearchButton->setDefault(false);


        QMetaObject::connectSlotsByName(FindDialog);
    } // setupUi

    void retranslateUi(QDialog *FindDialog)
    {
        FindDialog->setWindowTitle(QApplication::translate("FindDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("FindDialog", "Text to search:", nullptr));
        mSearchButton->setText(QApplication::translate("FindDialog", "Search", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindDialog: public Ui_FindDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDDIALOG_H
