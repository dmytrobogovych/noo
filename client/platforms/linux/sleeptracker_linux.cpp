#include "sleeptracker_linux.h"
SleepTracker STSharedInstance;

SleepTracker::SleepTracker(QObject *parent)
    :QObject(parent), mHandler(nullptr)

{
}

SleepTracker::~SleepTracker()
{
}

void SleepTracker::install()
{
}

void SleepTracker::uninstall()
{
}

void SleepTracker::onAppWillSleep()
{
    emit onSystemSleep();
}

void SleepTracker::onAppDidWake()
{
    emit onSystemResume();
}

