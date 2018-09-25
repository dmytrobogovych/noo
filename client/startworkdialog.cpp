#include "startworkdialog.h"
#include "ui_startworkdialog.h"

StartWorkDialog::StartWorkDialog(PTask task, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::StartWorkDialog)
{
  ui->setupUi(this);
  setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
  if (task)
    ui->mInfoLabel->setText(ui->mInfoLabel->text().replace("%TASK%", task->title()));
}

StartWorkDialog::~StartWorkDialog()
{
  delete ui;
}

void StartWorkDialog::onYesButtonTriggered()
{
  emit continueTracking();
  done(ContinueTracking);
}

void StartWorkDialog::onNoButtonTriggered()
{
  emit breakTracking();
  done(BreakTracking);
}

void StartWorkDialog::onFinishTimerTriggered()
{
  emit breakTracking();
  done(BreakTracking);
}
