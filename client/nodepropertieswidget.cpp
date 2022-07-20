#include "nodepropertieswidget.h"
#include "ui_nodepropertieswidget.h"
#include "settings.h"

NodePropertiesWidget::NodePropertiesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NodePropertiesWidget)
{
    ui->setupUi(this);
    ui->mFileListView->setParentWidget(this);
}

NodePropertiesWidget::~NodePropertiesWidget()
{
    delete ui;
}

void NodePropertiesWidget::setTask(const PTask& task)
{
    if (mTask != task)
    {
        mTask = task;
        refresh();
    }
}


PTask NodePropertiesWidget::task() const
{
    return mTask;
}

void NodePropertiesWidget::refresh()
{
    bool showSeconds = SETTINGS.data()[KEY_SHOW_SECONDS].toBool();

    if (mTask != nullptr)
    {
        ui->mFileListView->setTask(mTask);
        if (!mTask->timeline())
            mTask->loadContent();

        int spentSecondsToday = mTask->timeline()->today();
        int spentSecondsMonth = mTask->timeline()->month();
        ui->mTodaySpentTimeLabel->setText(QString::fromStdString(helper::chrono::secondsToDisplay(spentSecondsToday, showSeconds)));
        ui->mThisMonthSpentTimeLabel->setText(QString::fromStdString(helper::chrono::secondsToDisplay(spentSecondsMonth, showSeconds)));
    }
    else
    {
        ui->mTimeFrame->setVisible(false);
        ui->mFileListView->setTask(PTask());
    }
}
