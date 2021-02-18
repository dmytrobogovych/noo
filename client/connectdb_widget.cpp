#include "connectdb_widget.h"
#include "ui_connectdb_widget.h"
#include <QSizePolicy>

ConnectDbWidget::ConnectDbWidget(const QString& message, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectDbWidget)
{
    ui->setupUi(this);
    ui->mMessageLabel->setText(message);
    connect(ui->mButtonBox, SIGNAL(accepted()), this, SLOT(onOk()));
    connect(ui->mButtonBox, SIGNAL(rejected()), this, SLOT(onCancel()));
    connect(ui->mPasswordEdit, SIGNAL(returnPressed()), this, SLOT(onOk()));

    this->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
}

ConnectDbWidget::~ConnectDbWidget()
{
    delete ui;
}

void ConnectDbWidget::onOk()
{
    emit passwordEntered(ui->mPasswordEdit->text());
}

void ConnectDbWidget::onCancel()
{
    emit cancelled();
}
