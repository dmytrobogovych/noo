#include "config.h"
#include "helper.h"
#include "platforms/hidtracker.h"

#include <QCoreApplication>
#include <QDesktopServices>
#include <QMessageBox>
#include <QKeyEvent>

#ifdef TARGET_OSX

char* __strlcpy_chk (char* dest, const char* src, int len, int destcapacity)
{
  return NULL;
}

char* __strlcat_chk (char* dest, const char* src, int len, int destcapacity)
{
  return NULL;
}

#endif

QString TimeHelper::secondsToDisplay(int seconds, bool showSeconds)
{
  int hours = seconds / 3600;
  int minutes = (seconds % 3600) / 60;
  int secs = seconds % 60;
  if (showSeconds)
    return QString("%1:%2:%3").arg(hours, 2, 10, QLatin1Char('0')).arg(minutes, 2, 10, QLatin1Char('0')).arg(secs, 2, 10, QLatin1Char('0'));
  else
    return QString("%1:%2").arg(hours, 2, 10, QLatin1Char('0')).arg(minutes, 2, 10, QLatin1Char('0'));
}

QString PathHelper::pathToSettings()
{
#if QT_VERSION >= 0x050000
  QString folder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#else
  QString folder = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#endif
  QString path = folder + "/" + SETTINGS_FILENAME;
  return path;
}

QString PathHelper::pathToDatabase()
{
#if QT_VERSION >= 0x050000
  QString folder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#else
  QString folder = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#endif
  QString path = folder + "/" + DATABASENAME;
  return path;
}

QString PathHelper::pathToDesktop()
{
#if QT_VERSION >= 0x050000
  QString folder = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
#else
  QString folder = QDesktopServices::storageLocation(QDesktopServices::DesktopLocation);
#endif
  return folder;
}

QString PathHelper::pathToDatabaseTemplate()
{
#ifdef TARGET_WIN
  return QCoreApplication::applicationDirPath() + "/" + DATABASENAME;
#endif

#ifdef TARGET_OSX
  return QCoreApplication::applicationDirPath() + "/../Resources/" + DATABASENAME;
#endif
}

QString PathHelper::pathToLog()
{
#if QT_VERSION >= 0x050000
  QString folder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#else
  QString folder = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#endif
  return folder + "/" + LOGNAME;
}

bool ActivityTrackerHelper::ensureSmartTrackingIsPossible()
{
  bool result = false;
  HIDActivityTracker tracker;

  result = tracker.isPossible();
#ifdef TARGET_OSX
  if (!result && QSysInfo::MacintoshVersion <= QSysInfo::MV_10_8)
  {
    QMessageBox msgbox(QMessageBox::Question, QT_TR_NOOP("Permission required"),
                       QT_TR_NOOP("To use smart time tracking Litt needs access to OS X accessibility features.\
                          Please grant access in Security & Privacy preferences, location in System Preferences."),
                          QMessageBox::NoButton, nullptr);
    msgbox.addButton(QT_TR_NOOP("Open System Preferences"), QMessageBox::AcceptRole);
    msgbox.addButton(QT_TR_NOOP("Deny"), QMessageBox::RejectRole);
    int execResult = msgbox.exec();
    if (execResult == 0)
    {
      system("open /System/Library/PreferencePanes/UniversalAccessPref.prefPane");
      result = true;
    }
  }
  else
  if (QSysInfo::MacintoshVersion > QSysInfo::MV_10_8)
    result = true;
#endif
#ifdef TARGET_WIN
  result = false;
#endif
  return result;
}

EscapeKeyEventFilter::EscapeKeyEventFilter(QObject *parent)
  :QObject(parent)
{}

bool EscapeKeyEventFilter::eventFilter(QObject  *obj, QEvent * event)
{
  if (event->type() == QEvent::KeyPress && ((QKeyEvent*)event)->key() == Qt::Key_Escape )
  {
    emit escapePressed(obj);
  }
  if (event->type() == QEvent::FocusOut)
  {
    emit escapePressed(obj);
  }
  return false;
}
