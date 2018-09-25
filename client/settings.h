#ifndef SETTINGS_H
#define SETTINGS_H

#include "config.h"
#include <QString>
#include <QMap>
#include <QVariant>

#define KEY_AUTOSAVE_PASSWORD "AutosavePassword"
#define KEY_PASSWORD "Password"
#define KEY_SHOW_SECONDS "ShowSeconds"
#define KEY_DB_FILENAME "DbFilename"
#define KEY_DB_FILENAME_SPECIFIED "DbFilenameSpecified"
#define KEY_TIMECOUNTER_TYPE "TimecounterType"

#define KEY_LEFT "Left"
#define KEY_TOP "Top"
#define KEY_WIDTH "Width"
#define KEY_HEIGHT "Height"
#define KEY_MAXIMIZED "Maximized"
#define KEY_SPLITTEROFFSET1 "SplitterOffset1"
#define KEY_SPLITTEROFFSET2 "SplitterOffset2"

#define KEY_TIMESPLITTER_OFFSET1 "TimeSplitterOffset1"
#define KEY_TIMESPLITTER_OFFSET2 "TimeSplitterOffset2"

#define VALUE_TIMECOUNTER_THISDAY "ThisDay"
#define VALUE_TIMECOUNTER_THISSESSION "ThisSession"
#define VALUE_TIMECOUNTER_ALLTIME "AllTime"

#define KEY_SMART_START "SmartStart"
#define KEY_SMART_STOP  "SmartStop"
#define KEY_SMART_STOP_MINUTES "SmartStopIntervalInMinutes"
#define KEY_ASK_START "AskStart"
#define KEY_ASK_STOP "AskStop"

#define KEY_SHOW_TRAY_ICON "ShowTrayIcon"
#define KEY_CUMULATIVE_REPORT "CumulativeReport"

#define KEY_SELECTED_TASKS "SelectedTasks"
#define KEY_EXPANDED_TASKS "ExpandedTasks"
#define KEY_RECENT_TASKS "RecentTasks"

class Settings
{
public:
  Settings();
  ~Settings();

  void load();
  void save();
  QVariantMap& data();

  static Settings& instance();

protected:
  QVariantMap mData;
};

#endif // SETTINGS_H
