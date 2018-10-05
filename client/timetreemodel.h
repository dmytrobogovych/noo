#ifndef TIMETREEMODEL_H
#define TIMETREEMODEL_H

#include <QAbstractItemModel>
#include "task.h"
#include "settings.h"

class TimeTreeModel: public QAbstractItemModel
{
public:
    TimeTreeModel(PTimeLine timeline, Settings& settings);
    ~TimeTreeModel();

    void setTimeLine(PTimeLine timeline);
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role /* = Qt::EditRole */);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const;
    void beginAddRow();
    void endAddRow();
    void timeUpdated();
    TimeRecord findInterval(const QModelIndex& index);
    void cutInterval(const QModelIndex& index);
    void insertInterval(const TimeRecord& interval);
protected:
    PTimeLine mTimeLine;
    Settings& mSettings;
    QString mTimeFormat;

public:
    enum Level
    {
        Level_Year = 0,
        Level_Month,
        Level_Day,
        Level_Time
    };

    struct Item
    {
        Level mLevel;
        int mYear, mMonth, mDay;
        quint64 mTimeIntervalId;
    };

protected:
    mutable int mItemIdGenerator;
    mutable std::map<int, Item> mId2Item;
    mutable std::map<Item, int> mItem2Id;

    int PackDate(Level l, int year, int month, int day, quint64 intervalId) const;
    void UnpackDate(int packed, Level& l, int& year, int& month, int& day, quint64& intervalId) const;
    QModelIndex dayToIndex(const QDate& date);
};

bool operator < (const TimeTreeModel::Item& lhs, const TimeTreeModel::Item& rhs);



#endif
