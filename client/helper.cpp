#include "config.h"
#include "helper.h"
#include "platforms/hidtracker.h"

#include <QCoreApplication>
#include <QDesktopServices>
#include <QMessageBox>
#include <QKeyEvent>
#include <QTextStream>
#include <QApplication>

#ifdef TARGET_OSX

char* __strlcpy_chk (char* dest, const char* src, int len, int destcapacity)
{
    return nullptr;
}

char* __strlcat_chk (char* dest, const char* src, int len, int destcapacity)
{
    return nullptr;
}

#endif

#include "settings.h"

using namespace helper;

void theme::applyCurrent(Settings& settings)
{
    // Dark theme
    if (settings.data()[KEY_DARK_THEME].toBool())
    {
        QFile f(":qdarkstyle/style.qss");
        if (f.exists())
        {
            f.open(QFile::ReadOnly | QFile::Text);
            QTextStream ts(&f);
            qApp->setStyleSheet(ts.readAll());
        }
    }
    else
        qApp->setStyleSheet("");
}

date::date()
{}

date::date(int y, int m, int d)
    :mYear(y), mMonth(m), mDay(d)
{
}

time_t date::toTimestamp() const
{
    struct tm t;
    memset(&t, 0, sizeof t);
    t.tm_year = mYear - 1900;
    t.tm_mon = mMonth - 1;
    t.tm_mday = mDay;
    return mktime(&t);
}

date date::fromTimestamp(time_t timestamp, int options)
{
    struct tm t;
    memset(&t, 0, sizeof t);
    switch (options)
    {
    case To_GmtTime:       t = *gmtime(&timestamp); break;
    case To_LocalTime:     t = *localtime(&timestamp); break;
    }

    date r;
    r.mDay = t.tm_mday;
    r.mMonth = t.tm_mon + 1;
    r.mYear = t.tm_year + 1900;
    return r;
}

date date::today()
{
    date r = date::fromTimestamp(::time(nullptr), To_LocalTime);
    return r;
}

int date::daysInMonth(int y, int m)
{
    switch (m)
    {
     case 2:
        if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
            return 29;
        else
            return 28;

    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;

    default:
        return 30;
    }
}

bool date::operator < (const date& rhs)
{
    return std::tie(mYear, mMonth, mDay) < std::tie(rhs.mYear, rhs.mMonth, rhs.mDay);
}

bool date::operator > (const date& rhs)
{
    return std::tie(mYear, mMonth, mDay) > std::tie(rhs.mYear, rhs.mMonth, rhs.mDay);
}

bool date::operator == (const date& rhs)
{
    return std::tie(mYear, mMonth, mDay) == std::tie(rhs.mYear, rhs.mMonth, rhs.mDay);
}

bool date::operator >= (const date& rhs)
{
    return std::tie(mYear, mMonth, mDay) >= std::tie(rhs.mYear, rhs.mMonth, rhs.mDay);
}

time::time(int h, int m, int s)
    :mHour(h), mMinute(m), mSecond(s)
{}

std::string time::toString(bool showSeconds) const
{
    char buffer[32];
    if (showSeconds)
        sprintf(buffer, "%02d:%02d:%02d", mHour, mMinute, mSecond);
    else
        sprintf(buffer, "%02d:%02d", mHour, mMinute);

    return buffer;
}

helper::time time::fromTimestamp(time_t timestamp, int options)
{
    tm* t = nullptr;
    if (options == date::To_GmtTime)
        t = gmtime(&timestamp);
    else
        t = localtime(&timestamp);

    helper::time r;
    r.mHour = t->tm_hour;
    r.mMinute = t->tm_min;
    r.mSecond = t->tm_sec;
    return r;
}


std::string chrono::secondsToDisplay(int seconds, bool showSeconds)
{
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    int secs = seconds % 60;
    char r[32];
    if (showSeconds)
        sprintf(r, "%02d:%02d:%02d", hours, minutes, secs);
    else
        sprintf(r, "%02d:%02d", hours, minutes);

    return r;
}

std::string chrono::timeToStr(time_t timestamp)
{
    char buf[128];
    strftime(buf, sizeof buf, "%FT%TZ", gmtime(&timestamp));
    return buf;
}

/*
std::string chrono::timeToLocalStr(time_t timestamp)
{
    char buf[128];
    struct tm t = localtime(timestamp);
    strftime(buf, sizeof buf, "%FT%TZ", &t);
    return buf;
}
*/

time_t chrono::strToTime(const std::string& s)
{
    struct tm t;
    memset(&t, 0, sizeof t);
    strptime(s.c_str(), "%FT%TZ", &t);
    return timegm(&t);
}

QString path::pathToSettings()
{
#if QT_VERSION >= 0x050000
    QString folder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#else
    QString folder = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#endif
    QString path = folder + "/" + SETTINGS_FILENAME;
    return path;
}

QString path::pathToDatabase()
{
#if QT_VERSION >= 0x050000
    QString folder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#else
    QString folder = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#endif
    QString path = folder + "/" + DATABASENAME;
    return path;
}

QString path::pathToDesktop()
{
#if QT_VERSION >= 0x050000
    QString folder = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
#else
    QString folder = QDesktopServices::storageLocation(QDesktopServices::DesktopLocation);
#endif
    return folder;
}

QString path::pathToDatabaseTemplate()
{
#ifdef TARGET_WIN
    return QCoreApplication::applicationDirPath() + "/" + DATABASENAME;
#endif

#ifdef TARGET_OSX
    return QCoreApplication::applicationDirPath() + "/../Resources/" + DATABASENAME;
#endif
}

QString path::pathToLog()
{
#if QT_VERSION >= 0x050000
    QString folder = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#else
    QString folder = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#endif
    return folder + "/" + LOGNAME;
}

bool activityTracker::ensureSmartTrackingIsPossible()
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
