#ifndef TIMEINTERVALDLG_H
#define TIMEINTERVALDLG_H

#include <QDialog>
#include "task.h"

namespace Ui {
class TimeIntervalDlg;
}

class TimeTreeModel;
class TimeIntervalDlg : public QDialog
{
  Q_OBJECT

public:
  enum class Type
  {
    New,
    Change
  };
  explicit TimeIntervalDlg(QWidget *parent, TimeTreeModel* model, PTimeLine timeline, Type type, const TimeRecord& interval);
  ~TimeIntervalDlg();

  void setTimeline();

  // These methods accept & return date in local time
  void setStartDate(const QDateTime& t);
  QDateTime startDate();
  void setFinishDate(const QDateTime& t);
  QDateTime finishDate();

  void accept();
  void reject();
  void closeEvent(QCloseEvent *event);

private:
  Ui::TimeIntervalDlg *ui;
  PTimeLine mTimeline;
  Type mType;
  TimeRecord mInterval;
  TimeTreeModel* mModel;

  bool validate();

public slots:
  void dataChanged(const QDateTime& changed);
};

#endif // TIMEINTERVALDLG_H
