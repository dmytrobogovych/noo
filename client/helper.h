#ifndef HELPER_H
#define HELPER_H

#include <QString>
#include <QObject>

class Settings;
namespace helper
{
    class theme
    {
    public:
        static void applyCurrent(Settings& settings);
    };

    // date is always local. year, month & day number is natural (NO start from zero, NO delta with 1900 year etc.)
    struct date
    {
        int mYear = -1, mMonth = -1, mDay = -1;

        date();
        date(int y, int m, int d);

        // Timestamp is always UTC! But date is always local!
        time_t toTimestamp() const;

        enum
        {
            To_LocalTime,
            To_GmtTime
        };
        static date fromTimestamp(time_t timestamp, int options);
        static date today();
        static date fromTm(struct tm& t);
        static int daysInMonth(int y, int m);

        bool operator < (const date& rhs);
        bool operator > (const date& rhs);
        bool operator == (const date& rhs);
        bool operator >= (const date& rhs);
    };

    struct time
    {
        int mHour = 0, mMinute = 0, mSecond = 0;

        time() = default;
        time(int h, int m, int s);
        std::string toString(bool showSeconds = true) const;

        static time fromTimestamp(time_t timestamp, int options);
    };


    class chrono
    {
    public:
        // Seconds is number of seconds in a day. It is NOT a UNIX timestamp.
        static std::string secondsToDisplay(int seconds, bool showSeconds);
        static std::string timeToStr(time_t timestamp);
        static time_t strToTime(const std::string& s);
        static struct tm localtime(time_t timestamp);
        static int daysInMonth(int m, int y);
    };


    class path
    {
    public:
      static QString pathToDatabase();
      static QString pathToDesktop();
      static QString pathToSettings();
      static QString pathToDatabaseTemplate();
      static QString pathToLog();
    };

    class activityTracker
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

    class password
    {
    public:
        static QString load();
        static bool save(const QString& password);
    };
}

#endif
