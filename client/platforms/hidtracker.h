#ifndef __HID_TRACKER_H
#define __HID_TRACKER_H

class HIDActivityTrackerImpl;
class QTimer;

#include <QObject>

class HIDActivityTracker: public QObject
{
    Q_OBJECT

public:
    HIDActivityTracker();
    virtual ~HIDActivityTracker();

    bool isPossible();

    void setInterval(int seconds);
    int interval() const;

    bool isTrackerActive();
    bool start();
    void stop();
    bool isUserActive();
    void resetUserActive();

    // These methods must be called in response to idleDetected() / activityDetected() signals
    void acceptIdleState();
    void acceptUserActiveState();

signals:
    void idleDetected();
    void activityDetected();

protected:
    int mInterval;
    HIDActivityTrackerImpl* mImpl;
    bool mTrackerActive;
    QTimer* mCheckTimer;
    enum State
    {
        None,
        Idle,
        UserActive
    };
    State mState;
    bool mIdleSignalSent = false;
    bool mActivitySignalSent = false;

protected slots:
    void checkState();
};

#endif
