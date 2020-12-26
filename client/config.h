#ifndef __APP_CONFIG_H
#define __APP_CONFIG_H

// Application name
#define APPNAME "Litt"

// Company name
#define COMPANY "voipobjects.com"

// Default database name
#define DATABASENAME "database.db"

// Log file name
#define LOGNAME "litt-log.txt"

// About text
#define ABOUTTEXT "Tiny outliner with time tracking capabilities"

// Text for message box with "not implemented" notification
#define NOTIMPLEMENTEDTEXT "Not implemented in this version"

// Settings file name
#define SETTINGS_FILENAME "litt.ini"

// No password string
#define NOPASSWORDSTRING ""

// Mime type of task items
#define NODE_MIME_TYPE "application/litt-node"

// Exit code to signal about problems with database
#define EXITCODE_NO_DATABASE (1)

// Timeline save to DB interval in seconds
#define TIMELINE_FLUSH_INTERVAL (300)

// Text flushing interval
#define TEXT_FLUSH_INTERVAL (10)

#define APP_VERSION_MAJOR 0
#define APP_VERSION_MINOR 9
#define APP_VERSION_SUFFIX 3

//#ifdef TARGET_OSX
#define TRAY_START_ICON_NAME ":/icons/icons/starttracking-osx.png"
#define TRAY_STOP_ICON_NAME ":/icons/icons/stoptracking-osx.png"

#define TRAY_DEFAULT_ICON_NAME ":/icons/icons/tray-default.png"
#define TRAY_RUNNING_ICON_NAME ":/icons/icons/tray-running.png"

#define ACTION_START_ICON_NAME ":/icons/icons/clock-32x32.png"
#define ACTION_STOP_ICON_NAME ":/icons/icons/process-stop.png"
//#endif

#define USE_ENCRYPTED_DB

#endif
