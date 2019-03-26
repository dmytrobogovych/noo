#include "timereportwizard.h"
#include <QLayout>
#include <QFormLayout>
#include <QDateEdit>
#include "helper.h"
#include "settings.h"

using namespace helper;

TaskTreePage::TaskTreePage(QWidget *parent)
  :QWizardPage(parent), mTaskView(nullptr), mTaskModel(nullptr)
{
  mTaskModel = new TaskTreeModel(true);
  // Add tree view
  mTaskView = new QTreeView();
  mTaskView->setModel(mTaskModel);

  QVBoxLayout* layout = new QVBoxLayout();
  layout->addWidget(mTaskView);
  setLayout(layout);
}

static void findSelectedTasks(PTask t, TaskArray& selected)
{
  if (t->isChecked())
    selected.push_back(t);

  for (auto task: t->children())
    findSelectedTasks(task, selected);
}

void TaskTreePage::getSelectedTasks(TaskArray& selected)
{
  // Iterate all tasks in model and find checked tasks
  selected.clear();
  TaskArray& top = Storage::instance().topOfTaskTree();
  for (PTask t: top)
    findSelectedTasks(t, selected);
}

void TaskTreePage::accepted()
{

}

CumulativeOptionPage::CumulativeOptionPage(Settings& settings, QWidget* parent)
  :QWizardPage(parent), mCheckbox(nullptr), mSettings(settings)
{
  mCheckbox = new QCheckBox();
  mCheckbox->setChecked(settings.data()[KEY_CUMULATIVE_REPORT].toBool());
  mCheckbox->setText(tr("Add summarized time of subtasks to its parents in report"));
  connect(mCheckbox, SIGNAL(clicked(bool)), this, SLOT(onChanged(bool)));

  QVBoxLayout* layout = new QVBoxLayout();
  layout->addWidget(mCheckbox);
  setLayout(layout);
}

bool CumulativeOptionPage::isCumulativeReportEnabled()
{
  return mCheckbox->isChecked();
}

void CumulativeOptionPage::onChanged(bool value)
{
  mSettings.data()[KEY_CUMULATIVE_REPORT] = value;
  mSettings.save();
}

DateIntervalPage::DateIntervalPage(QWidget *parent)
  :QWizardPage(parent), mStartIntervalEdit(nullptr), mFinishIntervalEdit(nullptr)
{
  mStartIntervalEdit = new QDateEdit;
  QDate monthBegin(QDate::currentDate().year(), 1, 1);

  mStartIntervalEdit->setDate(monthBegin);
  mStartIntervalEdit->setCalendarPopup(true);

  mFinishIntervalEdit = new QDateEdit;
  mFinishIntervalEdit->setDate(QDate::currentDate());
  mFinishIntervalEdit->setCalendarPopup(true);

  QFormLayout* fl = new QFormLayout;
  fl->addRow(tr("Start date:"), mStartIntervalEdit);
  fl->addRow(tr("End date:"), mFinishIntervalEdit);
  setLayout(fl);
}

void DateIntervalPage::getReportInterval(QDate& start, QDate& finish)
{
  start = mStartIntervalEdit->date();
  finish = mFinishIntervalEdit->date();
}

ReportViewPage::ReportViewPage(Settings& settings, TaskTreePage& taskTreePage, DateIntervalPage& dateIntervalPage, QWidget *parent)
  :QWizardPage(parent), mSettings(settings), mTaskTreePage(taskTreePage), mDateIntervalPage(dateIntervalPage), mReportEdit(nullptr)
{
  mReportEdit = new QTextEdit();
  mReportEdit->setAcceptRichText(false);

  QVBoxLayout* layout = new QVBoxLayout();
  layout->addWidget(mReportEdit);
  setLayout(layout);
}

void ReportViewPage::generateReport()
{
  QString report;
  TaskArray tasks;
  mTaskTreePage.getSelectedTasks(tasks);

  // Get start date and and date
  QDate startDate, finishDate;
  mDateIntervalPage.getReportInterval(startDate, finishDate);

  for (PTask t: tasks)
  {
    bool wasLoaded = false;
    if (!t->timeline())
    {
      wasLoaded = true;
      t->loadContent();
    }

    date start_date(startDate.year(), startDate.month(), startDate.day());
    date finish_date(finishDate.year(), finishDate.month(), finishDate.day());
    int seconds = t->timeline()->getSum(start_date, finish_date);
    t->setReportedTime(seconds);
    t->setChildrenReportedTime(0);
    if (wasLoaded)
      t->unloadContent(true);
  }

  for (PTask t: tasks)
  {
    for (PTask parent = t->parent(); parent; parent = parent->parent())
    {
      if (parent->isChecked())
        parent->setChildrenReportedTime(parent->getChildrenReportedTime() + t->getReportedTime());
    }
  }

  for (PTask t: tasks)
  {
    int individualTime = t->getReportedTime();
    bool showSeconds = mSettings.data()[KEY_SHOW_SECONDS].toBool();
    QString l1 = QString::fromStdString(chrono::secondsToDisplay(individualTime, showSeconds));
    report += t->path() + " : " + l1;
    //if (mSettings.data()[KEY_CUMULATIVE_REPORT].toBool())
    {
      int childrenTime = t->getChildrenReportedTime();
      if (childrenTime)
      {
        QString l2 = QString::fromStdString(chrono::secondsToDisplay(individualTime + childrenTime, showSeconds));
        report += ". Including subtasks time: " + l2;
      }
    }
    report += "\n";
  }

  mReportEdit->setPlainText(report);
}

TimeReportWizard::TimeReportWizard(Settings& settings, QWidget* parent)
  :QWizard(parent, Qt::Sheet), mSettings(settings)
{
  TaskTreePage* ttp = new TaskTreePage();
  addPage(ttp);

  DateIntervalPage* dip = new DateIntervalPage();
  addPage(dip);

  addPage(new ReportViewPage(settings, *ttp, *dip));

  setWindowTitle(tr("Time report wizard"));
  connect(this, SIGNAL(accepted()), this, SLOT(wizardFinished()));
  connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(wizardPageChanged(int)));
}

void TimeReportWizard::wizardFinished()
{

}

void TimeReportWizard::wizardPageChanged(int pageId)
{
  ReportViewPage* rvp = dynamic_cast<ReportViewPage*>(currentPage());
  if (rvp)
    rvp->generateReport();
}
