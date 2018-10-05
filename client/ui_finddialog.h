/********************************************************************************
** Form generated from reading UI file 'finddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDDIALOG_H
#define UI_FINDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
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
            FindDialog->setObjectName(QStringLiteral("FindDialog"));
        FindDialog->resize(611, 392);
        verticalLayout = new QVBoxLayout(FindDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(FindDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        mQueryText = new QLineEdit(FindDialog);
        mQueryText->setObjectName(QStringLiteral("mQueryText"));

        horizontalLayout->addWidget(mQueryText);

        mSearchButton = new QPushButton(FindDialog);
        mSearchButton->setObjectName(QStringLiteral("mSearchButton"));
        mSearchButton->setAutoDefault(false);

        horizontalLayout->addWidget(mSearchButton);


        verticalLayout->addLayout(horizontalLayout);

        mResultList = new QTableView(FindDialog);
        mResultList->setObjectName(QStringLiteral("mResultList"));
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
        FindDialog->setWindowTitle(QApplication::translate("FindDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("FindDialog", "Text to search:", Q_NULLPTR));
        mSearchButton->setText(QApplication::translate("FindDialog", "Search", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FindDialog: public Ui_FindDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDDIALOG_H
