#include "openorcreatedb_widget.h"
#include "ui_openorcreatedb_widget.h"

#include <QFileDialog>

OpenOrCreateDbWidget::OpenOrCreateDbWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpenOrCreateDbWidget)
{
    ui->setupUi(this);

    connect(ui->mNewPasswordEdit1, &QLineEdit::returnPressed, [this]() { ui->mNewPasswordEdit2->setFocus(); });
    connect(ui->mNewPasswordEdit2, &QLineEdit::returnPressed, [this]() { handleEnteredPasswords(); });
    connect(ui->mSelectDatabaseButton, &QPushButton::clicked, [this]() { askForDatabase(); });
    connect(ui->mDialogButtonBox, &QDialogButtonBox::accepted, [this]()
    {
        if (mDbPath.isEmpty())
            handleEnteredPasswords();
        else
            emit databaseChanged(ui->mSelectedDbLabel->text());
    });
}

OpenOrCreateDbWidget::~OpenOrCreateDbWidget()
{
    delete ui;
}

void OpenOrCreateDbWidget::handleEnteredPasswords()
{
    if (ui->mNewPasswordEdit1->text().isEmpty() && ui->mNewPasswordEdit2->text().isEmpty())
    {
        ui->mMessageLabel->setText("Password can't be empty. Please try again!");
    }
    if (ui->mNewPasswordEdit1->text() == ui->mNewPasswordEdit2->text())
        emit passwordEntered(ui->mNewPasswordEdit1->text());
    else
    {
        ui->mNewPasswordEdit1->setText("");
        ui->mNewPasswordEdit2->setText("");
        ui->mNewPasswordEdit1->setFocus();
        ui->mMessageLabel->setText("Passwords are not the same. Please try again!");
    }
}

void OpenOrCreateDbWidget::askForDatabase()
{
    QString path = QFileDialog::getOpenFileName(this, "Please select existing database", QString(), "*.noo");
    if (path.size())
    {
        mDbPath = path;
        ui->mSelectedDbLabel->setText(path);
    }
}

