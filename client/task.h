#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDateTime>
#include <QSharedPointer>
#include <QVector>
#include <QTextDocument>
#include <QUuid>
#include <set>
#include <memory>
#include <map>
#include "SQLiteCpp/Database.h"
#include "helper.h"

typedef int64_t Id;

class WorldId
{
public:
    WorldId();
    WorldId(const WorldId& src);
    WorldId(const std::string& s);
    ~WorldId();
    WorldId& operator = (const WorldId& src);
    bool operator == (const WorldId& src);
    bool operator < (const WorldId& src);

    std::string asString() const;
    static WorldId create();
protected:
    std::string mId;
};

class TimeRecord
{
public:
    TimeRecord();
    TimeRecord(const time_t& startTime, const time_t& endTime, Id taskId);
    ~TimeRecord();

    time_t startTime() const;
    TimeRecord& setStartTime(const time_t& startTime);

    time_t endTime() const;
    TimeRecord& setEndTime(const time_t& endTime);

    int length();

    Id id() const;
    TimeRecord& setId(Id id);

    Id taskId() const;
    TimeRecord& setTaskId(Id id);

    WorldId worldId() const;
    TimeRecord& setWorldId(const WorldId& id);

    // Save record to DB. If record is new - id() property will be set after this call.
    void save();

    // Remove record from DB.
    void deleteRecord();

protected:
    Id mId, mTaskId;
    WorldId mWorldId;
    time_t mStartTime, mEndTime;
    bool mSaved;
};

typedef std::vector<TimeRecord> TimeArray;

typedef std::set<int> HoursSet;
typedef std::map<int, QSharedPointer<HoursSet> > DaysMap;
typedef std::map<int, QSharedPointer<DaysMap> > MonthesMap;
typedef std::map<int, QSharedPointer<MonthesMap> > YearsMap;


class TimeLine
{
    friend class Storage;
public:
    TimeLine();
    ~TimeLine();

    TimeArray& data();

    // Returns total time in seconds
    int totalTime();
    bool active();
    void start();
    void stop(bool updateTimeline = true);
    void flush(bool saveToDb, time_t currentUtc);

    void load();
    void save();

    Id taskId();
    TimeLine& setTaskId(Id id);

    // These methods work with local time
    // Returns set of available years in timeline
    std::set<int> getYears();

    // Returns set of availables monthes in timeline for specified year
    std::set<int> getMonthes(int year);

    // Returns set of available days in timeline for specified year & month
    std::set<int> getDays(int year, int month);

    int  getTime(int year, int month, int day, std::vector<TimeRecord>* intervals);

    // Returns number of seconds spent today
    int today();

    // Returns number of seconds spent in current month
    int month();

    // Returns number of seconds spent in interval
    int getSum(const helper::date& start, const helper::date& finish);

    // Checks if there duplicate & overllaping time intervals
    bool duplicateDetected() const;

    // Checks if specified interval has intersection
    bool hasIntersection(const TimeRecord& interval);

    // Inserts new interval to timeline. Saves new interval to DB.
    void insertInterval(const TimeRecord& interval);

    // Attempts to find & remove from timeline specified interval. Returns true if succeeded. Removes interval from DB too.
    // Search is made using start/finish time interval value - not id() value. Only whole TimeRecord can be deleted.
    bool removeInterval(const TimeRecord& interval);

    // Attempts to find & cut interval from timeline.
    // It does not mean whole TimeRecord will be removed. Depending on interval bounds existing TimeRecord can be removed/modified/add new records even.
    void cutInterval(const TimeRecord& interval);

    // Searches time interval by its id. Can return NULL if search failed.
    TimeRecord* findIntervalById(Id id);

    // Adds 10 minutes interval starting from current time. For debug/test purposes.
    void putDebugRecord();

protected:
    TimeArray mData;
    Id mTaskId;
    bool mActive;
    TimeRecord* mActiveTimeRecord;
    int mTotalTime;

    // Sums total time in timeline
    int findTotalTime();

    // Builds new time interval record with specified start/finish time
    TimeRecord* makeNewRecord(time_t begin, time_t end);

    // Looks for time record that includes specified time point
    TimeRecord* hasTimePoint(time_t t);

    // Sorts records in mData by startTime() value
    void sortData();

};

typedef QSharedPointer<TimeLine> PTimeLine;

class Task;
typedef QSharedPointer<Task> PTask;
typedef QVector<PTask> TaskArray;

class Task: public QObject
{
    Q_OBJECT
public:
    friend class Storage;

    typedef uint64_t Id;
    typedef uint32_t ModelId;
    enum Flag
    {
        Flag_NoTimeTracking = 1
    };

    Task();
    ~Task();

    void load(SQLite::Statement& q);

    Id id() const;
    Task& setId(Id id);

    Id parentId() const;
    Task& setParentId(Id id);

    WorldId worldId() const;
    Task& setWorldId(const WorldId& id);

    ModelId modelId() const;
    Task& setModelId(ModelId id);

    int index() const;
    Task& setIndex(int index, bool modified = true);

    void save();
    void saveAnyway();

    QString html() const;
    Task& setHtml(const QString& html);
    QString title() const;
    Task& setTitle(const QString& title, bool modified = true);

    QString path() const;

    PTask parent() const;
    Task& setParent(PTask task, bool modified = true);

    TaskArray& children();

    // Loads html and timeline
    void loadContent();
    bool isContentLoaded() const;

    // Unloads html and timeline
    void unloadContent(bool includeTimeline = true);

    PTimeLine timeline();

    // Returns true if task has attachments
    int getAttachmentCount();
    Task& setAttachmentCount(int count);
    int preloadAttachmentCount();

    // Service properties used in time reporting
    bool isChecked() const;
    Task& setChecked(bool checked);

    int getReportedTime() const;
    Task& setReportedTime(int t);

    int getChildrenReportedTime() const;
    Task& setChildrenReportedTime(int t);

    int flags() const;
    Task& setFlags(int value);

    int cursorPosition() const;
    Task& setCursorPosition(int position);

    /*
  QUndoStack* getUndoStack() const;
  void setUndoStack(QUndoStack* doc);
  */

protected:
    QString mHtml, mTitle;
    PTimeLine mTimeLine;
    Id mId, mParentId;
    WorldId mWorldId;
    ModelId mModelId;
    bool mTitleModified, mHtmlModified, mHtmlLoaded, mIndexModified, mParentModified;
    PTask mParent;
    TaskArray mChildren;
    int mIndex;
    bool mChecked;
    int mReportedTime, mChildrenReportedTime;
    int mAttachmentCount;
    int mFlags;
    QTextDocument* mDocument;
    int mCursorPosition;
};

class Attachment
{
    friend class Storage;
public:
    Attachment();
    ~Attachment();

    Task::Id id();
    Attachment& setId(Task::Id id);

    Task::Id taskId();
    Attachment& setTaskId(Task::Id id);

    WorldId worldId() const;
    Attachment& setWorldId(const WorldId& id);

    int index();
    Attachment& setIndex(int index);

    QByteArray loadContent();
    Attachment& saveContent(const QByteArray& content);

    Attachment& setFilename(const QString& filename);
    QString filename();

    Attachment& saveMetadata();
    Attachment& loadMetadata();
protected:
    Id mId, mTaskId;
    WorldId mWorldId;
    QString mFilename;
    int mIndex;
};

typedef QSharedPointer<Attachment> PAttachment;
typedef QVector<PAttachment> AttachmentArray;

#endif // TASK_H
