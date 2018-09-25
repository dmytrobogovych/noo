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

typedef qulonglong Id;

class WorldId
{
public:
  WorldId();
  WorldId(const WorldId& src);
  WorldId(const QString& s);
  ~WorldId();
  WorldId& operator = (const WorldId& src);
  bool operator == (const WorldId& src);
  bool operator < (const WorldId& src);

  QString asString() const;
  static WorldId create();
protected:
  QUuid mId;
};

class TimeRecord
{
public:
  TimeRecord();
  TimeRecord(const QDateTime& startTime, const QDateTime& endTime, Id taskId);
  ~TimeRecord();

  QDateTime startTime() const;
  void setStartTime(const QDateTime& startTime);
  QDateTime endTime() const;
  void setEndTime(const QDateTime& endTime);
  int length();
  Id id() const;
  void setId(Id id);
  Id taskId() const;
  void setTaskId(Id id);
  WorldId worldId() const;
  void setWorldId(const WorldId& id);

  // Save record to DB. If record is new - id() property will be set after this call.
  void save();

  // Remove record from DB.
  void deleteRecord();

protected:
  Id mId, mTaskId;
  WorldId mWorldId;
  QDateTime mStartTime, mEndTime;
  bool mSaved;
};

typedef QVector<TimeRecord> TimeArray;

typedef std::set<int> HoursSet;
typedef std::map<int, QSharedPointer<HoursSet> > DaysMap;
typedef std::map<int, QSharedPointer<DaysMap> > MonthesMap;
typedef std::map<int, QSharedPointer<MonthesMap> > YearsMap;

class TimeLine
{
public:
  TimeLine();
  ~TimeLine();

  TimeArray& data();

  // Returns total time in seconds
  int totalTime();
  bool active();
  void start();
  void stop(bool updateTimeline = true);
  void flush(bool saveToDb, const QDateTime& currentUtc);

  void load();
  void save();

  Id taskId();
  void setTaskId(Id id);

  // These methods work with local time
  void getYears(std::set<int>& result);
  void getMonthes(int year, std::set<int>& result);
  void getDays(int year, int month, std::set<int>& result);
  int  getTime(int year, int month, int day, std::vector<TimeRecord>* intervals);

  int today();
  int month();
  int getSum(const QDate& start, const QDate& finish);
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
  TimeRecord* makeNewRecord(const QDateTime& begin, const QDateTime& end);

  // Looks for time record that includes specified time point
  TimeRecord* hasTimePoint(const QDateTime& t);

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
  typedef qulonglong Id;
  typedef quint32 ModelId;
  enum Flag
  {
    Flag_NoTimeTracking = 1
  };

  Task();
  ~Task();
  
  void load(SQLite::Statement& q);

  Id id() const;
  void setId(Id id);

  Id parentId() const;
  void setParentId(Id id);

  WorldId worldId() const;
  void setWorldId(const WorldId& id);

  ModelId modelId() const;
  void setModelId(ModelId id);

  int index() const;
  void setIndex(int index, bool modified = true);

  enum SaveOptions
  {
    Save_Automatic,
    Save_Forced
  };

  void save(SaveOptions options = Save_Automatic);

  QString html() const;
  void setHtml(const QString& html);
  QString title() const;
  void setTitle(const QString& title, bool modified = true);

  QString path() const;

  PTask parent() const;
  void setParent(PTask task, bool modified = true);

  TaskArray& children();
  
  // Loads html and timeline
  void loadContent();
  bool isContentLoaded() const;

  // Unloads html and timeline
  void unloadContent(bool includeTimeline = true);

  PTimeLine timeline();

  // Returns true if task has attachments
  int getAttachmentCount();
  void setAttachmentCount(int count);
  int checkAttachments();

  // Service properties used in time reporting
  bool isChecked() const;
  void setChecked(bool checked);

  int getReportedTime() const;
  void setReportedTime(int t);

  int getChildrenReportedTime() const;
  void setChildrenReportedTime(int t);

  int flags() const;
  void setFlags(int value);

  int cursorPosition() const;
  void setCursorPosition(int position);

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
public:
  Attachment();
  ~Attachment();

  Task::Id id();
  void setId(Task::Id id);

  Task::Id taskId();
  void setTaskId(Task::Id id);

  WorldId worldId() const;
  void setWorldId(const WorldId& id);

  int index();
  void setIndex(int index);

  QByteArray loadContent();
  void saveContent(const QByteArray& content);

  void setFilename(const QString& filename);
  QString filename();

  void save();
  void load();
protected:
  Id mId, mTaskId;
  WorldId mWorldId;
  QString mFilename;
  int mIndex;
};

typedef QSharedPointer<Attachment> PAttachment;
typedef QVector<PAttachment> AttachmentArray;

#endif // TASK_H
