#ifndef SLEEPTRACKER_LINUX_H
#define SLEEPTRACKER_LINUX_H

#include <QObject>

class SleepTracker: public QObject
{
  Q_OBJECT
public:
  explicit SleepTracker(QObject* parent = nullptr);
  ~SleepTracker();

  void install();
  void uninstall();

  static SleepTracker& sharedInstance();

  // For internal calls only
  void onAppWillSleep();
  void onAppDidWake();

signals:
  void onSystemSleep();
  void onSystemResume();

protected:
  void* mHandler;
};

#endif // SLEEPTRACKER_OSX_H

