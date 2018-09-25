#ifndef STARTWORKDIALOG_H
#define STARTWORKDIALOG_H

#include <QDialog>
#include "task.h"

namespace Ui {
class StartWorkDialog;
}

class StartWorkDialog : public QDialog
{
  Q_OBJECT

public:
  enum Result
  {
    ContinueTracking,
    BreakTracking
  };

  explicit StartWorkDialog(PTask task, QWidget *parent = 0);
  ~StartWorkDialog();

signals:
  void continueTracking();
  void breakTracking();

private:
  Ui::StartWorkDialog *ui;
  QTimer* mFinishTimer;

private slots:
  void onYesButtonTriggered();
  void onNoButtonTriggered();
  void onFinishTimerTriggered();
};

#endif // STARTWORKDIALOG_H
