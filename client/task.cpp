#include "task.h"
#include "storage.h"
#include "helper.h"

#include <QVariant>
#include <assert.h>

#if defined(TARGET_OSX) || defined(TARGET_LINUX)
# include <uuid/uuid.h>
#endif

using namespace helper;

// -------- WorldId ------
WorldId::WorldId()
{
}

WorldId::WorldId(const WorldId& src)
{
    mId = src.mId;
}

WorldId::WorldId(const std::string &s)
    :mId(s)
{
}

WorldId::~WorldId()
{
}

WorldId& WorldId::operator = (const WorldId& src)
{
    mId = src.mId;
    return *this;
}

bool WorldId::operator == (const WorldId& src)
{
    return mId == src.mId;
}

bool WorldId::operator < (const WorldId& src)
{
    return mId < src.mId;
}

std::string WorldId::asString() const
{
    return mId;
}

WorldId WorldId::create()
{
    WorldId result;
#if defined(TARGET_OSX) || defined(TARGET_LINUX)
    uuid_t t;
    uuid_generate(t);
    char buffer[128];
    uuid_unparse(t, buffer);
    result.mId = buffer;
#endif

#if defined(TARGET_WIN)
#endif

    return result;
}

// -------- TimeRecord ----------
TimeRecord::TimeRecord()
    :mId(0), mTaskId(0), mSaved(false)
{}

TimeRecord::TimeRecord(const time_t &startTime, const time_t &endTime, Id taskId)
    :mId(0), mTaskId(taskId), mStartTime(startTime), mEndTime(endTime), mSaved(false)
{
}

TimeRecord::~TimeRecord()
{}

time_t TimeRecord::endTime() const
{
    return mEndTime;
}

void TimeRecord::setEndTime(const time_t &endTime)
{
    mEndTime = endTime;
}

time_t TimeRecord::startTime() const
{
    return mStartTime;
}

void TimeRecord::setStartTime(const time_t &startTime)
{
    mStartTime = startTime;
}

int TimeRecord::length()
{
    return static_cast<int>(mEndTime - mStartTime);
}

Id TimeRecord::id() const
{
    return mId;
}

void TimeRecord::setId(Id id)
{
    mId = id;
}

Id TimeRecord::taskId() const
{
    return mTaskId;
}

void TimeRecord::setTaskId(Id id)
{
    mTaskId = id;
}

WorldId TimeRecord::worldId() const
{
    return mWorldId;
}

void TimeRecord::setWorldId(const WorldId& id)
{
    mWorldId = id;
}

void TimeRecord::save()
{
    if (!mId)
    {
        SQLite::Statement q(Storage::instance().database(), "insert into timeline(id, starttime, endtime, taskid, removed) values (NULL, :starttime, :endtime, :taskid, :removed)");

        q.bind(":starttime", helper::chrono::timeToStr(mStartTime));
        q.bind(":endtime", helper::chrono::timeToStr(mEndTime));
        q.bind(":taskid", static_cast<sqlite3_int64>(mTaskId));
        q.bind(":removed", 0);
        if (q.exec())
            mId = Storage::instance().database().getLastInsertRowid();
    }
    else
    {
        SQLite::Statement q(Storage::instance().database(),
                            "update timeline set starttime = :starttime, endtime = :endtime, taskid = :taskid, removed = 0 where id = :id");
        q.bind(":starttime", helper::chrono::timeToStr(mStartTime));
        q.bind(":endtime", helper::chrono::timeToStr(mEndTime));
        q.bind(":taskid", static_cast<sqlite3_int64>(mTaskId));
        q.bind(":id", static_cast<sqlite3_int64>(mId));
        q.exec();
    }
}

void TimeRecord::deleteRecord()
{
    SQLite::Statement q(Storage::instance().database(), "update timeline set removed = 1 where id = :id");
    q.bind(":id", static_cast<sqlite3_int64>(mId));
    q.exec();
}

// -------------------- TimeLine --------------------
TimeLine::TimeLine()
    :mTaskId(0), mActive(false), mActiveTimeRecord(nullptr), mTotalTime(0)
{}

TimeLine::~TimeLine()
{}

int TimeLine::findTotalTime()
{
    int result = 0;
    for(auto& t: mData)
    {
        int delta = static_cast<int>(t.endTime() - t.startTime());
        result += delta + 1;
    }
    return result;
}

int TimeLine::totalTime()
{
    return mTotalTime;
}

bool TimeLine::active()
{
    return mActive;
}

void TimeLine::start()
{
    if (mActive)
        return;

    // Mark timeline as active - it means it records time interval now
    mActive = true;

    // Find current time in UTC format
    time_t current = time(nullptr);

    // Check if current time point does not belong to any existing time interval
    if (hasTimePoint(current))
        mActiveTimeRecord = nullptr;
    else
        mActiveTimeRecord = makeNewRecord(current, current);
}

TimeRecord* TimeLine::makeNewRecord(time_t beginTime, time_t endTime)
{
    TimeRecord tr;
    tr.setStartTime(beginTime);
    tr.setEndTime(endTime);
    tr.setTaskId(mTaskId);
    tr.save();

    mData.push_back(tr);
    Id intervalId = tr.id();
    sortData();

    std::reverse_iterator<TimeArray::iterator> intervalIter = std::find_if(std::reverse_iterator<TimeArray::iterator>(mData.end()),
                                                                           std::reverse_iterator<TimeArray::iterator>(mData.begin()),
                                                                           [=] (const TimeRecord& tr)
    {
        return tr.id() == intervalId;
    });

    if (intervalIter != std::reverse_iterator<TimeArray::iterator>(mData.begin()))
        return &(*intervalIter);
    else
        return nullptr;
}

TimeRecord* TimeLine::hasTimePoint(time_t t)
{
    if (mData.empty())
        return nullptr;

    TimeRecord* tr = nullptr;
    TimeArray::iterator result;
    result = std::upper_bound(mData.begin(), mData.end(), t,
                              [](time_t t2, const TimeRecord& tr)
                              {
                                return tr.startTime() > t2;
                              });

    if (result == mData.end())
        tr = &mData.back();
    else
        if (result != mData.begin())
            tr = &(*(--result));
        else
            return nullptr;

    return (tr->startTime() <= t && tr->endTime() >= t) ? tr : nullptr;
}

void TimeLine::sortData()
{
    std::sort(mData.begin(), mData.end(), [](const TimeRecord& lhs, const TimeRecord& rhs) { return lhs.startTime() < rhs.startTime();});
}

bool TimeLine::hasIntersection(const TimeRecord &interval)
{
    if (mData.empty())
        return false;

    TimeArray::iterator result;
    result = std::upper_bound(mData.begin(), mData.end(), interval.startTime(),
                              [](time_t t2, const TimeRecord& tr)
    { return tr.startTime() > t2;});

    if (result == mData.end())
    {
        // There is time record which start point is lesser than interval.startTime()
        return (mData.back().endTime() >= interval.startTime());
    }
    else
        if (result != mData.begin())
        {
            TimeRecord& prev = *(result-1);
            TimeRecord& next = *result;
            if (prev.endTime() >= interval.startTime())
                return true;
            if (next.startTime() <= interval.endTime())
                return true;
        }
        else
        {
            if (mData.front().startTime() <= interval.endTime())
                return true;
        }
    return false;
}

void TimeLine::insertInterval(const TimeRecord &interval)
{
    mData.push_back(interval);
    mData.back().save();

    sortData();
}

bool TimeLine::removeInterval(const TimeRecord &interval)
{
    // Find interval by binary search
    if (mData.empty())
        return false;

    TimeArray::iterator result;
    result = std::upper_bound(mData.begin(), mData.end(), interval.startTime(),
                              [](time_t t2, const TimeRecord& tr)
    { return tr.startTime() > t2;});

    if (result == mData.end())
    {
        // There is time record which start point is lesser than interval.startTime()
        if (mData.back().id() == interval.id())
        {
            // Remove from DB
            mData.back().deleteRecord();

            // Remove from memory
            mData.erase(mData.begin() + mData.size() - 1);

            return true;
        }
    }
    else
        if (result != mData.begin())
        {
            result--;
            if (result->id() == interval.id())
            {
                // Remove from DB
                result->deleteRecord();

                // Remove from memory
                mData.erase(result);

                return true;
            }
        }
    return false;
}

void TimeLine::cutInterval(const TimeRecord& interval)
{
    //  Find interval that startTime() time is greater than interval.endTime()
    TimeArray::iterator iter;
    iter = std::upper_bound(mData.begin(), mData.end(), interval.endTime(),
                            [](time_t t2, const TimeRecord& tr)
    { return tr.startTime() > t2;});

    // If all intervals begins later() than requested interval - exit silently
    if (iter == mData.begin())
        return;

    // Go to previous interval - it is first interval to check
    if (iter == mData.end())
        iter = mData.begin() + mData.size() - 1;
    else
        iter--;

    bool done = false;
    // Loop while current interval end time is greater than cut interval start time
    while (iter->endTime() >= interval.startTime())
    {
        if (iter->endTime() > interval.endTime())
        {
            if (iter->startTime() >= interval.startTime())
            {
                iter->setStartTime(iter->endTime() + 1); // Current interval starts in [interval.startTime(), interval.endTime()], but finishes later
                iter->save();
            }
            else
            {
                // Current interval starts before interval.startTime() and finishes later
                // So cut interval will split it to 2 new intervals
                // Also this operation will end loop
                TimeRecord toInsert(*iter);  // Backup current interval
                iter->setEndTime(interval.startTime() - 1);
                iter->save();
                toInsert.setStartTime(interval.endTime() + 1);
                mData.insert(++iter, toInsert);
                toInsert.save();
                done = true;
                break;
            }
        }
        else
        {
            if (iter->startTime() >= interval.startTime())
            {
                iter->deleteRecord();
                iter = mData.erase(iter); // Current interval fits into cut interval
            }
            else
            {
                // Current interval starts before cut interval but finishes in cut interval
                iter->setEndTime(interval.startTime() - 1);
                iter->save();
                done = true;
                break;
            }
        }
        if (iter == mData.begin())
            break;
        iter--;
    }

    // Look for exact the same interval as specified one
    if (!done)
    {
        iter = std::find_if(mData.begin(), mData.end(),
                            [=] (const TimeRecord& tr)
                            { return tr.id() == interval.id();});
        if (iter != mData.end())
            mData.erase(iter);
    }
}


TimeRecord* TimeLine::findIntervalById(Id id)
{
    TimeArray::iterator iter = std::find_if(mData.begin(), mData.end(),
                                            [=] (const TimeRecord& tr)
                                            { return tr.id() == id;});
    if (iter == mData.end())
        return nullptr;
    return &(*iter);
}

void TimeLine::stop(bool updateTimeline)
{
    if (!mActive)
        return;

    if (updateTimeline)
        flush(true, time(nullptr));

    mActive = false;
    mActiveTimeRecord = nullptr;
}

void TimeLine::flush(bool saveToDb, time_t currentUtc)
{
    if (!mActive)
        return;

    if (mActiveTimeRecord)
    {
        long delta = currentUtc - mActiveTimeRecord->endTime();
        mActiveTimeRecord->setEndTime(currentUtc);

        TimeRecord* tr = hasTimePoint(currentUtc);
        if (tr && tr != mActiveTimeRecord)
        {
            mActiveTimeRecord->setEndTime(currentUtc);
            mActiveTimeRecord->save();
            mActiveTimeRecord = nullptr;
        }
        if (saveToDb && mActiveTimeRecord)
            mActiveTimeRecord->save();

        mTotalTime += delta;
    }
    else
    {
        if (!hasTimePoint(currentUtc))
        {
            // Start new record here
            mActiveTimeRecord = makeNewRecord(currentUtc, currentUtc);
        }
    }
}

void TimeLine::load()
{
    SQLite::Statement q(Storage::instance().database(), "select id, starttime, endtime from timeline where (taskid = :taskid) and ((removed is null) or (removed != 1)) order by id asc");
    q.bind(":taskid", mTaskId);
    while (q.executeStep())
    {
        time_t start = helper::chrono::strToTime(q.getColumn(1).getText());
        time_t stop = helper::chrono::strToTime(q.getColumn(2).getText());

        TimeRecord tr;
        tr.setId(q.getColumn(0).getInt64());
        tr.setStartTime(start);
        tr.setEndTime(stop);
        tr.setTaskId(mTaskId);
        mData.push_back(tr);
    }

    // Sort time intervals
    sortData();

    // Find current total time length
    mTotalTime = findTotalTime();
}

void TimeLine::save()
{
    // No need to save anything here - everything is saved right on creation/update
}

Id TimeLine::taskId()
{
    return mTaskId;
}

void TimeLine::setTaskId(Id id)
{
    mTaskId = id;
}

TimeArray& TimeLine::data()
{
    return mData;
}

std::set<int> TimeLine::getYears()
{
    std::set<int> r;
    if (mData.empty())
        return r;

    date t1 = date::fromTimestamp(mData.front().startTime(), date::To_LocalTime),
         t2 = date::fromTimestamp(mData.back().startTime(), date::To_LocalTime);

    r.insert(t1.mYear);

    // Find higher bound of years - it is last time record
    if (t1.mYear == t2.mYear)
        return r;

    // Try to find next year by binary search
    for (int year = t1.mYear + 1; year <= t2.mYear; year++)
    {
        date yearStart(year, 1, 1);
        TimeArray::iterator iter = std::lower_bound(mData.begin(), mData.end(), yearStart,
                                                    [&](const TimeRecord& lhs, date rhs)
        {
            return date::fromTimestamp(lhs.endTime(), date::To_LocalTime) < rhs;
        });

        if (iter != mData.end())
        {
            // Get found year
            date found_date = date::fromTimestamp(iter->startTime(), date::To_LocalTime);
            if (found_date.mYear <= year)
                r.insert(year);
        }
    }

    return r;
}

std::set<int> TimeLine::getMonthes(int year)
{
    std::set<int> r;

    for (int month = 1; month <= 12; month++)
    {
        date monthBegin(year, month, 1);
        date monthEnd(year, month, date::daysInMonth(year, month));

        // Find range for every month in year [lowest, higher)
        TimeArray::iterator lowest = std::lower_bound(mData.begin(), mData.end(), monthBegin,
                                                      [] (const TimeRecord& tr, const date& d)

        {
            return date::fromTimestamp(tr.endTime(), date::To_LocalTime) < d;
        });

        //TimeArray::iterator higher = std::upper_bound(mData.begin(), mData.end(), monthEnd, [] (const TimeRecord& tr, const QDate& d) { return tr.startTime().toLocalTime().date() < d;});
        if (lowest != mData.end())
        {
            // Current date is local time!
            helper::date currentDate = helper::date::fromTimestamp(lowest->startTime(), helper::date::To_LocalTime);
            if (currentDate.mYear > year)
                continue;
            if (currentDate.mYear == year && currentDate.mMonth > month)
                continue;

            r.insert(month);
        }
    }

    return r;
}

std::set<int> TimeLine::getDays(int year, int month)
{
    std::set<int> r;
    date monthBegin(year, month, 1);
    for (int day = 1; day <= date::daysInMonth(year, month); day++)
    {
        date currentDay(year, month, day);

        TimeArray::iterator lowest = std::lower_bound(mData.begin(), mData.end(), currentDay,
                                                      [] (const TimeRecord& tr, const date& d)
                                                      {
                                                          return date::fromTimestamp(tr.endTime(), date::To_LocalTime) < d;
                                                      });
        if (lowest != mData.end())
        {
            helper::date startDate = helper::date::fromTimestamp(lowest->startTime(), helper::date::To_LocalTime);
            if (startDate.mYear > year)
                continue;
            if (startDate.mYear == year && startDate.mMonth > month)
                continue;
            if (startDate.mYear == year && startDate.mMonth == month && startDate.mDay > day)
                continue;

            r.insert(day);
        }
    }
    return r;
}

int TimeLine::getTime(int year, int month, int day, std::vector<TimeRecord>* intervals)
{
    int result = 0;
    QDate d(year, month, day);

    // Find range of related records [lowest, higher)
    TimeArray::iterator lowest = std::lower_bound(mData.begin(), mData.end(), d, [] (const TimeRecord& tr, const QDate& d)
                                                                                 {
                                                                                    return tr.endTime() < QDateTime(d).toTime_t();
                                                                                 });
    //TimeArray::iterator higher = std::upper_bound(mData.begin(), mData.end(), d, [] (const QDate& d, const TimeRecord& tr) { return tr.startTime().toLocalTime().date() < d;});

    for (;lowest != mData.end();/*&& lowest != higher;*/ lowest++)
    {
        TimeRecord& tr = *lowest;

        helper::date startDate = helper::date::fromTimestamp(tr.startTime(), date::To_LocalTime);

        if (startDate.mYear > year)
            break;
        if (startDate.mYear == year && startDate.mMonth > month)
            break;

        if (startDate.mYear == year &&
            startDate.mMonth == month &&
            startDate.mDay > day)
            break;

        time_t dayBegin = helper::date{year, month, day}.toTimestamp();
        time_t dayEnd = dayBegin + 86399;

        if (tr.startTime() > dayBegin)
            dayBegin = tr.startTime(); // Time record begin is later than begin of the day

        if (tr.endTime() < dayEnd)
            dayEnd = tr.endTime();

        if (intervals)
        {
            TimeRecord resultingRecord;
            resultingRecord.setStartTime(dayBegin);
            resultingRecord.setEndTime(dayEnd);
            resultingRecord.setId(tr.id());
            resultingRecord.setTaskId(tr.taskId());
            intervals->push_back(resultingRecord);
        }
        result++;
    }
    return result;
}


int TimeLine::today()
{
    int result = 0;

    // Find starting record related to today
    // Today is local time!
    date today = date::today();

    TimeArray::iterator lowIter = std::lower_bound(mData.begin(), mData.end(), today,
                                                   [] (const TimeRecord& lhs, const date& rhs)
    {
        return date::fromTimestamp(lhs.endTime(), date::To_LocalTime) < rhs;
    });

    for (;lowIter != mData.end(); lowIter++)
    {
        if (date::fromTimestamp(lowIter->startTime(), date::To_LocalTime) > today)
            break; // quit the loop

        if (date::fromTimestamp(lowIter->endTime(), date::To_LocalTime) >= today)
        {
            // Both are GMT time
            time_t dayBegin = date::today().toTimestamp();
            time_t dayEnd = dayBegin + 86359;

            int64_t secondsTo = lowIter->startTime() - dayBegin;
            if (secondsTo > 0)
                dayBegin = lowIter->startTime();

            int64_t secondsFrom = lowIter->endTime() - dayEnd;
            if (secondsFrom < 0)
                dayEnd = lowIter->endTime();

            int secondsSpent = dayEnd - dayBegin;
            result += secondsSpent;
        }
    }

    return result;
}

int TimeLine::month()
{
    int result = 0;

    // Find first day of month
    QDate currentMonth = QDate::currentDate();
    currentMonth.setDate(currentMonth.year(), currentMonth.month(), 1);

    // Find position in time record array close to month begin
    TimeArray::iterator lowIter = std::lower_bound(mData.begin(), mData.end(), currentMonth, [] (const TimeRecord& lhs, const QDate& rhs) { return lhs.endTime().toLocalTime().date() < rhs; });

    for (;lowIter != mData.end(); lowIter++)
    {
        // See if start of current time period is later than current month
        if (lowIter->startTime().toLocalTime().date().month() > currentMonth.month())
            break; // quit the loop

        if (lowIter->endTime().toLocalTime().date().month() >= currentMonth.month())
        {
            QDateTime monthBegin(currentMonth, QTime(0,0));
            QDateTime monthEnd(QDate(currentMonth.year(), currentMonth.month(), currentMonth.daysInMonth()), QTime(23, 59, 59));

            int secondsTo = monthBegin.secsTo(lowIter->startTime().toLocalTime());
            if (secondsTo > 0)
                monthBegin = lowIter->startTime();

            int secondsFrom = monthEnd.secsTo(lowIter->endTime().toLocalTime());
            if (secondsFrom < 0)
                monthEnd = lowIter->endTime().toLocalTime();

            int secondsSpent = monthBegin.secsTo(monthEnd);
            result += secondsSpent;
        }
    }

    return result;
}

int TimeLine::getSum(const QDate& start, const QDate& finish)
{
    int result = 0;

    TimeArray::iterator lowest = std::lower_bound(mData.begin(), mData.end(), start, [] (const TimeRecord& tr, const QDate& d) { return tr.endTime().toLocalTime().date() < d;});
    //TimeArray::iterator higher = std::upper_bound(mData.begin(), mData.end(), finish, [] (const QDate& d, const TimeRecord& tr) { return tr.startTime().toLocalTime().date() < d;});

    for (;lowest != mData.end(); lowest++)
    {
        TimeRecord& tr = *lowest;
        if (tr.startTime().toLocalTime().date() > finish)
            break;

        QDateTime dayBegin(start, QTime(0, 0, 0));
        QDateTime dayEnd(finish, QTime(23, 59, 59));

        if (tr.startTime().toLocalTime().secsTo(dayBegin) < 0)
            dayBegin = tr.startTime().toLocalTime(); // Time record begin is later than begin of the interval

        if (tr.endTime().toLocalTime().secsTo(dayEnd) > 0)
            dayEnd = tr.endTime().toLocalTime();

        result += dayBegin.secsTo(dayEnd);
    }
    return result;
}

bool TimeLine::duplicateDetected() const
{
    return mActiveTimeRecord == nullptr;
}

void TimeLine::putDebugRecord()
{
    QDateTime current = QDateTime::currentDateTimeUtc();
    QDateTime end = current.addSecs(600);
    TimeRecord* r = makeNewRecord(current, end);
    r->save();
}

// -------------------- Task --------------------------
static Task::ModelId ModelIdGenerator = 0;

Task::Task()
    :mId(0), mTitleModified(false), mHtmlModified(false), mHtmlLoaded(false), mModelId(++ModelIdGenerator),
      mParentId(-1), mIndex(-1), mChecked(false), mIndexModified(false),
      mParentModified(false), mReportedTime(0), mChildrenReportedTime(0), mAttachmentCount(0),
      mDocument(nullptr), mCursorPosition(0)
{
}

Task::~Task()
{
}

void Task::load(SQLite::Statement &q)
{
    mId = q.getColumn(0).getInt64();
    mTitle = q.getColumn(1).getText();
    mIndex = q.getColumn(2).getInt();
    mFlags = q.getColumn(3).getInt();
    mAttachmentCount = q.getColumn(4).getInt();
}

Task::Id Task::id() const
{
    return mId;
}

void Task::setId(Id id)
{
    mId = id;
}

Task::Id Task::parentId() const
{
    return mParentId;
}

void Task::setParentId(Id id)
{
    if (mParentId != id)
    {
        mParentModified = true;
        mParentId = id;
    }
}

WorldId Task::worldId() const
{
    return mWorldId;
}

void Task::setWorldId(const WorldId& id)
{
    mWorldId = id;
}

Task::ModelId Task::modelId() const
{
    return mModelId;
}

void Task::setModelId(ModelId id)
{
    mModelId = id;
}

int Task::index() const
{
    return mIndex;
}

void Task::setIndex(int index, bool modified)
{
    if (index != mIndex)
    {
        if (modified)
            mIndexModified = true;
        mIndex = index;
    }
}

QString Task::html() const
{
    return mHtml;
}

void Task::setHtml(const QString &html)
{
    if (mHtml != html)
    {
        mHtml = html;
        mHtmlModified = true;
    }
}

QString Task::title() const
{
    return mTitle;
}

void Task::setTitle(const QString &title, bool modified)
{
    if (mTitle != title)
    {
        mTitle = title;
        if (modified)
            mTitleModified = true;
    }
}

void Task::save(SaveOptions options)
{
    if (!mTitleModified && !mHtmlModified && !mIndexModified && !mParentModified && options == Save_Automatic)
        return;

    const char* queryText = NULL;

    if (mTitleModified && mHtmlModified)
        queryText = "update task set parentid = :parentid, flags = :flags, title = :title, html = :html, orderid = :orderid where id = :id";
    else
        if (mTitleModified)
            queryText = "update task set parentid = :parentid, flags = :flags, title = :title, orderid = :orderid where id = :id";
        else
            if (mHtmlModified)
                queryText = "update task set parentid = :parentid, flags = :flags, html = :html, orderid = :orderid where id = :id";
            else
                queryText = "update task set parentid = :parentid, flags = :flags, orderid = :orderid where id = :id";

    SQLite::Statement q(Storage::instance().database(), queryText);
    if (mParent)
        q.bind(":parentid", (sqlite3_int64)mParent->id());
    else
        q.bind(":parentid");

    q.bind(":flags", mFlags);

    if (mTitleModified)
        q.bind(":title", mTitle.toStdString());
    if (mHtmlModified)
        q.bind(":html", mHtml.toStdString());

    q.bind(":id", (sqlite3_int64)mId);
    q.bind(":orderid", mIndex);
    q.exec();
    mIndexModified = mTitleModified = mHtmlModified = false;
}

/*void Task::load()
{
  SQLite::Statement q(Storage::instance().database(), "select parentid, title, html, orderid from task where (id = :id) and (type = 0)");
  q.bind(":id", (sqlite3_int64)mId);
  if (q.executeStep())
  {
    mParentId = q.getColumn(0).getInt64();
    mTitle = q.getColumn(1).getText();
    mHtml = q.getColumn(2).getText();
    mIndex = q.getColumn(3).getInt();
  }
  mTitleModified = mHtmlModified = false;
  mHtmlLoaded = true;

  checkAttachments();
}*/

QString Task::path() const
{
    QString result = this->title();
    if (parent())
        result.insert(0, parent()->path() + " / ");

    return result;
}

PTask Task::parent() const
{
    return mParent;
}

void Task::setParent(PTask task, bool modified)
{
    if (mParent != task)
    {
        mParent = task;
        if (task)
            mParentId = task->id();
        else
            mParentId = -1;
        if (modified)
            mTitleModified = true; // To force save()
    }
}

TaskArray& Task::children()
{
    return mChildren;
}

void Task::loadContent()
{
    SQLite::Statement htmlQuery(Storage::instance().database(), "select html from task where id = :id");
    htmlQuery.bind(":id", (sqlite3_int64)mId);
    if (htmlQuery.executeStep())
    {
        mHtml = htmlQuery.getColumn(0).getText();
        mHtmlLoaded = true;
        mHtmlModified = false;
    }

    if (!mTimeLine)
    {
        mTimeLine = PTimeLine(new TimeLine());
        mTimeLine->setTaskId(mId);
        mTimeLine->load();
    }
}

bool Task::isContentLoaded() const
{
    return mHtmlLoaded;
}

void Task::unloadContent(bool includeTimeline)
{
    mHtml.clear();
    mHtmlModified = mHtmlLoaded = false;
    if (includeTimeline)
        mTimeLine.clear();
}

PTimeLine Task::timeline()
{
    return mTimeLine;
}

int Task::getAttachmentCount()
{
    return mAttachmentCount;
}

void Task::setAttachmentCount(int count)
{
    mAttachmentCount = count;
}

int Task::checkAttachments()
{
    SQLite::Statement q(Storage::instance().database(), "select count(*) from file where (taskid = :taskid) and ((removed = 0) or (removed is null))");
    q.bind(":taskid", (sqlite3_int64)mId);
    if (q.executeStep())
        mAttachmentCount = q.getColumn(0).getInt();
    else
        mAttachmentCount = 0;

    return mAttachmentCount;
}

bool Task::isChecked() const
{
    return mChecked;
}

void Task::setChecked(bool checked)
{
    mChecked = checked;
}

int Task::getReportedTime() const
{
    return mReportedTime;
}

void Task::setReportedTime(int t)
{
    mReportedTime = t;
}

int Task::getChildrenReportedTime() const
{
    return mChildrenReportedTime;
}

void Task::setChildrenReportedTime(int t)
{
    mChildrenReportedTime = t;
}

int Task::flags() const
{
    return mFlags;
}

void Task::setFlags(int value)
{
    mFlags = value;
    save(Save_Forced);
}

int Task::cursorPosition() const
{
    return mCursorPosition;
}

void Task::setCursorPosition(int position)
{
    mCursorPosition = position;
}

/*
QTextDocument* Task::getTextDocument() const
{
  return mDocument;
}

void Task::setTextDocument(QTextDocument* doc)
{
  mDocument = doc;
  if (mDocument)
    mDocument->setParent(this);
}
*/
// ----------- Attachment -------------
Attachment::Attachment()
    :mId(0), mTaskId(0)
{

}

Attachment::~Attachment()
{

}

Task::Id Attachment::id()
{
    return mId;
}

void Attachment::setId(Task::Id id)
{
    mId = id;
}

Task::Id Attachment::taskId()
{
    return mTaskId;
}

void Attachment::setTaskId(Task::Id id)
{
    mTaskId = id;
}

WorldId Attachment::worldId() const
{
    return mWorldId;
}

void Attachment::setWorldId(const WorldId& id)
{
    mWorldId = id;
}

int Attachment::index()
{
    return mIndex;
}

void Attachment::setIndex(int index)
{
    //TODO: introduce mIndexModified field and corresponding login in save()
    mIndex = index;
}

QByteArray Attachment::loadContent()
{
    SQLite::Statement q(Storage::instance().database(), "select content from file where id = :id");
    q.bind(":id", (sqlite3_int64)mId);
    if (q.executeStep())
        return QByteArray((const char*)q.getColumn(0).getBlob(), q.getColumn(0).size());
    else
        return QByteArray();
}

void Attachment::saveContent(const QByteArray& content)
{
    SQLite::Statement q(Storage::instance().database(), "update file set content = :content where id = :id");
    q.bind(":content", content.data(), content.size());
    q.bind(":id", (sqlite3_int64)mId);
    if (q.exec())
        ;
}

void Attachment::setFilename(const QString& filename)
{
    mFilename = filename;
}

QString Attachment::filename()
{
    return mFilename;
}

//    mDatabase->exec("CREATE TABLE file (id INTEGER PRIMARY KEY, removed INTEGER, taskid INTEGER, filename TEXT, content BLOB, orderid INTEGER, synctime TEXT)");

void Attachment::save()
{
    if (mId)
    {
        SQLite::Statement q(Storage::instance().database(), "update file set filename = :filename, orderid = :orderid where id = :id");
        q.bind(":filename", mFilename.toStdString().c_str());
        q.bind(":orderid", mIndex);
        q.bind(":id", (sqlite3_int64)mId);

        if (q.exec())
            ;
    }
    else
    {
        SQLite::Statement q(Storage::instance().database(), "insert into file (filename, taskid, orderid, removed) values(:filename, :taskid, :orderid, 0)");
        q.bind(":filename", mFilename.toStdString().c_str());
        q.bind(":taskid", (sqlite3_int64)mTaskId);
        q.bind(":orderid", mIndex);
        if (q.exec())
        {
            mId = Storage::instance().database().getLastInsertRowid();
        }
    }
}

void Attachment::load()
{
}
