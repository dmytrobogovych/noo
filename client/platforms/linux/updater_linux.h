#ifndef UPDATER_OSX_H
#define UPDATER_OSX_H

#include <QString>
#include "../updater.h"

class CocoaInitializer
{
  public:
    CocoaInitializer();
    ~CocoaInitializer();

  private:
    class Private;
    Private* d;
};

class SparkleAutoUpdater : public AutoUpdater
{
  public:
    SparkleAutoUpdater(const QString url);
    ~SparkleAutoUpdater();
    virtual void checkForUpdates();
  private:
    class Private;
    Private* d;
};

#endif // UPDATER_OSX_H

