#ifndef TIMEREPORTWIZARD_H
#define TIMEREPORTWIZARD_H

#include <QWizard>
#include <QTreeView>
#include <QDateEdit>
#include <QTextEdit>
#include <QCalendarWidget>
#include <QCheckBox>

#include "tasktreemodel.h"
#include "settings.h"

class TaskTreePage: public QWizardPage
{
  Q_OBJECT

public:
  TaskTreePage(QWidget* parent = 0);

  void getSelectedTasks(TaskArray& selected);
protected:
  QTreeView* mTaskView;
  TaskTreeModel* mTaskModel;
public slots:
  void accepted();
};

class CumulativeOptionPage: public QWizardPage
{
  Q_OBJECT

public:
  CumulativeOptionPage(Settings& settings, QWidget* parent = 0);
  bool isCumulativeReportEnabled();

protected:
  QCheckBox* mCheckbox;
  Settings& mSettings;

public slots:
  void onChanged(bool value);

};

class DateIntervalPage: public QWizardPage
{
  Q_OBJECT

public:
  DateIntervalPage(QWidget* parent = 0);
  void getReportInterval(QDate& start, QDate& finish);

protected:
  QDateEdit* mStartIntervalEdit;
  QDateEdit* mFinishIntervalEdit;
};

class ReportViewPage: public QWizardPage
{
  Q_OBJECT

public:
  ReportViewPage(Settings& settings, TaskTreePage& taskTreePage, DateIntervalPage& dateIntervalPage, QWidget* parent = 0);
  void generateReport();
protected:
  Settings& mSettings;
  TaskTreePage& mTaskTreePage;
  DateIntervalPage& mDateIntervalPage;

  QTextEdit* mReportEdit;
};

class TimeReportWizard : public QWizard
{
  Q_OBJECT
public:
  TimeReportWizard(Settings& settings, QWidget* parent = 0);

protected:
  Settings& mSettings;

public slots:
  void wizardFinished();
  void wizardPageChanged(int pageId);
};

#endif // TIMEREPORTWIZARD_H
