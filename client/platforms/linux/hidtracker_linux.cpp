#import "config.h"
#import "hidtracker_linux.h"

HIDTrackerLinux::HIDTrackerLinux()
{

}

HIDTrackerLinux::~HIDTrackerLinux()
{

}


bool HIDTrackerLinux::isPossible()
{
    return false;
}

bool HIDTrackerLinux::start()
{
    return false;
}

void HIDTrackerLinux::stop()
{
}

bool HIDTrackerLinux::isUserActive()
{
    return true;
}

void HIDTrackerLinux::resetUserActive()
{
}
