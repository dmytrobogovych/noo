#include "config.h"
#include "logger.h"
#include "helper.h"
#include <stdlib.h>
#include <time.h>

Logger::Logger(QObject *parent) :
  QObject(parent), mFile(nullptr)
{
  open();
}

Logger::~Logger()
{
  close();
}

void Logger::log(const char* msg)
{
  if (!mFile)
    return;

  char buffer[512];
  time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime (&rawtime);
  sprintf(buffer, "%s : %s\n", asctime(timeinfo), msg);

  puts(buffer);
  fputs(buffer, mFile);
  fflush(mFile);
}

void Logger::open()
{
#if defined(USE_LOGGER)
  if (mFile)
    return;

  QString p = PathHelper::pathToSettings();
  mFile = fopen(PathHelper::pathToLog().toStdString().c_str(), "wt");
#endif
}

void Logger::close()
{
  if (!mFile)
    return;
  fclose(mFile);
  mFile = nullptr;
}
