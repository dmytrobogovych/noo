#ifndef STOPWORKDIALOG_H
#define STOPWORKDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QDateTime>

namespace Ui {
class StopWorkDialog;
}

class StopWorkDialog : public QDialog
{
  Q_OBJECT

public:
  enum Result
  {
    ContinueTracking,
    BreakTracking
  };

  explicit StopWorkDialog(QWidget *parent = 0);
  ~StopWorkDialog();

signals:
  void continueTracking();
  void breakTracking(const QDateTime& stopTime);

private:
  Ui::StopWorkDialog *ui;
  QTimer* mFinishTimer;
  QDateTime mStopTimeUtc, mStopTime;

private slots:
  void onYesButtonTriggered();
  void onNoButtonTriggered();
  void onFinishTimerTriggered();
};

#endif // STOPWORKDIALOG_H
