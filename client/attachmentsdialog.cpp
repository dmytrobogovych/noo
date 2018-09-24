#include "attachmentsdialog.h"
#include "ui_attachmentsdialog.h"

AttachmentsDialog::AttachmentsDialog(PTask task, QWidget *parent) :
  QDialog(parent, Qt::Sheet),
  ui(new Ui::AttachmentsDialog)
{
  ui->setupUi(this);
  ui->widget->setTask(task);
  ui->widget->setParentWidget(parent);
  this->setWindowTitle(tr("Attachments"));
}

AttachmentsDialog::~AttachmentsDialog()
{
  delete ui;
}
