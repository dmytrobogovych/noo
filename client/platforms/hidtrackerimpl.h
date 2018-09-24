#ifndef __HID_TRACKER_IMPL_H
#define __HID_TRACKER_IMPL_H

class HIDActivityTrackerImpl
{
public:
  HIDActivityTrackerImpl();
  virtual ~HIDActivityTrackerImpl();

  virtual bool isPossible() { return false; }

  void setInterval(int seconds);
  int interval() const;

  virtual bool start() = 0;
  virtual void stop() = 0;
  virtual bool isUserActive() = 0;
  virtual void resetUserActive() = 0;

protected:
  int mInterval;
};

#endif
