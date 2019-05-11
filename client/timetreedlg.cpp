#include "timetreedlg.h"
#include "ui_timetreedlg.h"
#include "timetreemodel.h"

TimeTreeDlg::TimeTreeDlg(QWidget *parent, PTimeLine timeline, Settings& settings) :
    QDialog(parent),
    ui(new Ui::TimeTreeDlg),
    mTimeline(timeline), mSettings(settings),
    mTimeIntervalDlg(nullptr)
{
    ui->setupUi(this);
    mModel = new TimeTreeModel(mTimeline, mSettings);
    ui->mTimeTree->setModel(mModel);
    connect(ui->mAddIntervalButton, SIGNAL(clicked()), this, SLOT(addInterval()));
    connect(ui->mRemoveIntervalButton, SIGNAL(clicked()), this, SLOT(removeInterval()));
}

TimeTreeDlg::~TimeTreeDlg()
{
    delete ui;
}

void TimeTreeDlg::addInterval()
{
    //QModelIndex index = ui->mTimeTree->currentIndex();
    if (mTimeIntervalDlg)
    {
        mTimeIntervalDlg->show();
        mTimeIntervalDlg->setFocus();
    }
    else
    {
        QDateTime current = QDateTime::currentDateTime();
        time_t t = current.toTime_t();
        //helper::time time_of_day = helper::time::fromTimestamp(t, helper::date::To_LocalTime);

        mTimeIntervalDlg = new TimeIntervalDlg(this, mModel, mTimeline, TimeIntervalDlg::Type::New, TimeRecord());
        connect(mTimeIntervalDlg, SIGNAL(accepted()), this, SLOT(onNewIntervalAccepted()));

        mTimeIntervalDlg->setStartDate(current.addSecs(-600));
        mTimeIntervalDlg->setFinishDate(current);
        //mTimeIntervalDlg->setModal(false);
        mTimeIntervalDlg->show();
    }
}

void TimeTreeDlg::removeInterval()
{
    QModelIndex index = ui->mTimeTree->currentIndex();
    if (!index.isValid())
        return;

    mModel->cutInterval(index);
    // Find interval in timeline by id
    // Compare if return from findInterval() is whole interval or part of existing
    // Depending on check result - delete or update existing interval
}

void TimeTreeDlg::changeInterval()
{
    QModelIndex index = ui->mTimeTree->currentIndex();
    if (!index.isValid())
        return;

    QDateTime current = QDateTime::currentDateTime();

    mTimeIntervalDlg = new TimeIntervalDlg(this, mModel, mTimeline, TimeIntervalDlg::Type::Change, TimeRecord());
    connect(mTimeIntervalDlg, SIGNAL(accepted()), this, SLOT(onNewIntervalAccepted()));

    mTimeIntervalDlg->setStartDate(current.addSecs(-600));
    mTimeIntervalDlg->setFinishDate(current);
    mTimeIntervalDlg->setModal(false);
    mTimeIntervalDlg->show();
}

void TimeTreeDlg::onNewIntervalAccepted()
{
    delete mModel;
    ui->mTimeTree->setModel(mModel = new TimeTreeModel(mTimeline, mSettings));
}
