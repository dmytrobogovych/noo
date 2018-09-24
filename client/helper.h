#ifndef HELPER_H
#define HELPER_H

#include <QString>
#include <QObject>

class TimeHelper
{
public:
  static QString secondsToDisplay(int seconds, bool showSeconds);
};

class PathHelper
{
public:
  static QString pathToDatabase();
  static QString pathToDesktop();
  static QString pathToSettings();
  static QString pathToDatabaseTemplate();
  static QString pathToLog();
};

class ActivityTrackerHelper
{
public:
  static bool ensureSmartTrackingIsPossible();
};

class EscapeKeyEventFilter: public QObject
{
  Q_OBJECT

public:
  explicit EscapeKeyEventFilter(QObject* parent = 0);
  bool eventFilter(QObject  *obj, QEvent * event);

signals:
  void escapePressed(QObject* obj);

};

#endif
