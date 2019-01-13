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
        static date fromTimestamp(time_t timestamp);
    };

    class chrono
    {
    public:
        static std::string secondsToDisplay(int seconds, bool showSeconds);
        static std::string timeToStr(time_t timestamp);
        static std::string timeToLocalStr(time_t timestamp);
        static time_t strToTime(const std::string& s);
        static struct tm localtime(time_t timestamp);
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
}

#endif
