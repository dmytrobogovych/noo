#include "hidtracker.h"
#include "hidtrackerimpl.h"
#include <QTimer>

#ifdef TARGET_OSX
# include "platforms/osx/hidtrackerimpl_osx.h"
#endif

HIDActivityTracker::HIDActivityTracker()
    :mInterval(600), mTrackerActive(false), mState(None)
{
#ifdef TARGET_OSX
    mImpl = new HIDTrackerImplOSX();
    mImpl->setInterval(mInterval);
#endif

    // Check timer belongs to this object
    mCheckTimer = new QTimer(this);
    mCheckTimer->setSingleShot(false);
    connect(mCheckTimer, SIGNAL(timeout()), this, SLOT(checkState()));
}

HIDActivityTracker::~HIDActivityTracker()
{
}

bool HIDActivityTracker::isPossible()
{
    if (!mImpl)
        return false;
    return mImpl->isPossible();
}

void HIDActivityTracker::setInterval(int seconds)
{
    if (mImpl)
        mImpl->setInterval(seconds);

    mInterval = seconds;
}

int HIDActivityTracker::interval() const
{
    return mInterval;
}

bool HIDActivityTracker::isTrackerActive()
{
    return mTrackerActive;
}

bool HIDActivityTracker::start()
{
    if (mTrackerActive)
        return true;

    if (mImpl)
        mTrackerActive = mImpl->start();

    mState = None;
    mIdleSignalSent = false;
    mActivitySignalSent = false;
    if (mTrackerActive)
        mCheckTimer->start(1000);

    return mTrackerActive;
}

void HIDActivityTracker::stop()
{
    if (!mTrackerActive)
        return;

    if (mImpl)
        mImpl->stop();

    mState = None;
    mCheckTimer->stop();
    mTrackerActive = false;
}

bool HIDActivityTracker::isUserActive()
{
    if (!mImpl)
        return true;

    return mImpl->isUserActive();
}

void HIDActivityTracker::resetUserActive()
{
    if (!mImpl)
        return;
    mState = None;
    mImpl->resetUserActive();
}

void HIDActivityTracker::acceptIdleState()
{
    mState = Idle;
}

void HIDActivityTracker::acceptUserActiveState()
{
    mState = UserActive;
}

void HIDActivityTracker::checkState()
{
    if (!mTrackerActive)
        return;

    // Now activity tracker is started, check if there was user activity during interval
    if (!mImpl->isUserActive())
    {
        switch (mState)
        {
        case None:
            mState = Idle;
            break;

        case Idle:
            break;

        case UserActive:
            if (!mIdleSignalSent)
            {
                mIdleSignalSent = true;
                mActivitySignalSent = false;
                emit idleDetected();
            }
            break;
        }
    }
    else
    {
        switch (mState)
        {
        case None:
            mState = UserActive;
            break;

        case UserActive:
            break;

        case Idle:
            if (!mActivitySignalSent)
            {
                mActivitySignalSent = true;
                mIdleSignalSent = false;
                emit activityDetected();
            }
            break;
        }
    }
}
