#include "hidtrackerimpl.h"

HIDActivityTrackerImpl::HIDActivityTrackerImpl()
  :mInterval(600)
{}

HIDActivityTrackerImpl::~HIDActivityTrackerImpl()
{
}

void HIDActivityTrackerImpl::setInterval(int seconds)
{
  mInterval = seconds;
}

int HIDActivityTrackerImpl::interval() const
{
  return mInterval;
}
