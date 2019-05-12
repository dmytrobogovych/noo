#include "connectdb_widget.h"
#include "ui_connectdb_widget.h"

ConnectDbWidget::ConnectDbWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectDbWidget)
{
    ui->setupUi(this);
}

ConnectDbWidget::~ConnectDbWidget()
{
    delete ui;
}
