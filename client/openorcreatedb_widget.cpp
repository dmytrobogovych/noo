#include "openorcreatedb_widget.h"
#include "ui_openorcreatedb_widget.h"

OpenOrCreateDbWidget::OpenOrCreateDbWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpenOrCreateDbWidget)
{
    ui->setupUi(this);
}

OpenOrCreateDbWidget::~OpenOrCreateDbWidget()
{
    delete ui;
}
