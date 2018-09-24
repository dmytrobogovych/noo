#include "sleeptracker_osx.h"
#include <CoreFoundation/CoreFoundation.h>
#include <Cocoa/Cocoa.h>

@interface SleepNotificationHandler: NSObject
{
  SleepTracker* mTracker;
}

- (id)initWithTracker:(SleepTracker*)tracker;
- (void)dealloc;
- (void)install;
- (void)uninstall;

- (void)appWillSleep:(NSNotification*)notification;
- (void)appDidWake:(NSNotification*)notification;
@end

@implementation SleepNotificationHandler

- (id)initWithTracker:(SleepTracker*)tracker
{
  if (![super init])
    return nil;

  mTracker = tracker;
  return self;
}

- (void)dealloc
{
  [super dealloc];
}

- (void)install
{
  NSNotificationCenter *center = [[NSWorkspace sharedWorkspace] notificationCenter];
  [center addObserver:self
             selector:@selector(appWillSleep:)
                 name:NSWorkspaceWillSleepNotification
               object:NULL];

  [center addObserver:self
             selector:@selector(appDidWake:)
                 name:NSWorkspaceDidWakeNotification
               object:NULL];
}

- (void)uninstall
{
  NSNotificationCenter *center = [[NSWorkspace sharedWorkspace] notificationCenter];
  [center removeObserver: self];
}

- (void)appWillSleep:(NSNotification*)notification
{
  if (self->mTracker)
    self->mTracker->onAppWillSleep();
}

- (void)appDidWake:(NSNotification*)notification
{
  if (self->mTracker)
    self->mTracker->onAppDidWake();
}
@end

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
  if (!mHandler)
  {
    mHandler = [[SleepNotificationHandler alloc] initWithTracker: this];
    [(id)mHandler install];
  }
}

void SleepTracker::uninstall()
{
  if (mHandler)
  {
    [(id)mHandler uninstall];
    [(id)mHandler release];
    mHandler = nullptr;
  }
}

void SleepTracker::onAppWillSleep()
{
  emit onSystemSleep();
}

void SleepTracker::onAppDidWake()
{
  emit onSystemResume();
}

