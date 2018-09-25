#include "stopworkdialog.h"
#include "ui_stopworkdialog.h"

StopWorkDialog::StopWorkDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::StopWorkDialog),
  mFinishTimer(nullptr)
{
  ui->setupUi(this);
  setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
  mStopTimeUtc = QDateTime::currentDateTimeUtc();
  mStopTime = QDateTime::currentDateTime();

  // Put stop time to text
  QString newText = ui->mInfoLabel->text().replace("%TIME%", mStopTime.time().toString());
  ui->mInfoLabel->setText(newText);

  /*mFinishTimer = new QTimer(this);
  mFinishTimer->setSingleShot(true);
  mFinishTimer->setInterval(30000);
  connect(mFinishTimer, SIGNAL(timeout()), this, SLOT(onFinishTimerTriggered()));
  mFinishTimer->start();

  QTimer::singleShot(30000, this, SLOT(onFinishTimerTriggered()));
  */
}

StopWorkDialog::~StopWorkDialog()
{
  delete ui;
}

void StopWorkDialog::onYesButtonTriggered()
{
  emit continueTracking();
  done(ContinueTracking);
}

void StopWorkDialog::onNoButtonTriggered()
{
  emit breakTracking(mStopTimeUtc);
  done(BreakTracking);
}

void StopWorkDialog::onFinishTimerTriggered()
{
  emit breakTracking(mStopTimeUtc);
  done(BreakTracking);
}

