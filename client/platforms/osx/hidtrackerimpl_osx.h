#ifndef __USER_ACTIVITY_OSX_H
#define __USER_ACTIVITY_OSX_H

#include "platforms/hidtrackerimpl.h"
#include <CoreFoundation/CoreFoundation.h>

class HIDTrackerImplOSX: public HIDActivityTrackerImpl
{
public:
  HIDTrackerImplOSX();
  virtual ~HIDTrackerImplOSX();

  bool isPossible();

  bool start();
  void stop();
  bool isUserActive();
  void resetUserActive();

protected:
  CFMachPortRef mMachPortRef;
  CFRunLoopSourceRef mKeyboardEventSrc;
};

#endif
