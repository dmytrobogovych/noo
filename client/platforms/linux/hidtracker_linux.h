#ifndef __USER_ACTIVITY_LINUX_H
#define __USER_ACTIVITY_LINUX_H

#include "platforms/hidtrackerimpl.h"

class HIDTrackerLinux: public HIDActivityTrackerImpl
{
public:
  HIDTrackerLinux();
  virtual ~HIDTrackerLinux();

  bool isPossible();

  bool start();
  void stop();
  bool isUserActive();
  void resetUserActive();

protected:
};

#endif
