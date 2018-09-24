#ifndef FINDSUPPORT_H
#define FINDSUPPORT_H

#include <QAbstractListModel>
#include <QVector>
#include <QThread>
#include "task.h"

struct FindResultItem
{
  // Visible search result in list
  QString mPattern;

  // Found word
  QString mFoundWord;

  // Index of first found word in document
  int mIndex;

  // Number of discovered words from requested list. It is in range [0..length_of_query_list]
  int mOccurences;

  // Task
  PTask mTask;
};

Q_DECLARE_METATYPE(FindResultItem)

class FindResultsModel: public QAbstractTableModel
{
  Q_OBJECT
  friend class TaskSearch;
public:
  explicit FindResultsModel(QObject* parent = 0);
  int columnCount(const QModelIndex &parent) const;
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  void clear();
  const FindResultItem& getItem(int row) const;
public slots:
  void addItem(const FindResultItem& item);

protected:
  QVector<FindResultItem> mItemList;

};

class TaskSearch: public QThread
{
  Q_OBJECT

public:
  TaskSearch();
  ~TaskSearch();

  void start(const QString& request);
  void stop();
  bool isRunning();
  void run();

signals:
  void newResultAvailable(const FindResultItem& item);
  void searchComplete();

protected:
  QString mRequest;
  bool mShutdown;
};

#endif // FINDSUPPORT_H

