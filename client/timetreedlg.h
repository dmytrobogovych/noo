#ifndef TIMETREEDLG_H
#define TIMETREEDLG_H

#include <QDialog>
#include "task.h"
#include "settings.h"
#include "timetreemodel.h"
#include "timeintervaldlg.h"

namespace Ui {
class TimeTreeDlg;
}

class TimeTreeDlg : public QDialog
{
  Q_OBJECT

public:
  explicit TimeTreeDlg(QWidget *parent, PTimeLine timeline, Settings& settings);
  ~TimeTreeDlg();

private:
  Ui::TimeTreeDlg *ui;
  PTimeLine mTimeline;
  Settings& mSettings;
  TimeTreeModel* mModel;
  TimeIntervalDlg* mTimeIntervalDlg;

public slots:
  void addInterval();
  void removeInterval();
  void changeInterval();
  void onNewIntervalAccepted();
};

#endif // TIMETREEDLG_H
