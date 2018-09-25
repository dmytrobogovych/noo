#ifndef STORAGE_H
#define STORAGE_H

#include <QString>
#include <QMap>
#include "task.h"
#include "SQLiteCpp/Database.h"

class Storage
{
public:
  Storage();
  ~Storage();

  QString path();
  void setPath(const QString& path);
  QString key();
  void setKey(const QString& key);

  SQLite::Database& database();

  // New database. Returns true or false depending on success of call.
  bool create();

  // Open database, preload task tree. Returns true or false depending on success of operation.
  bool open();

  // Close database
  void close();

  // Ensure database is latest version
  bool upgrade();

  PTask createTask(int index);
  PTask createTask(PTask parent, int index);
  PTask loadTask(Task::Id id, PTask parent);

  // Remove task from database
  enum DeleteOption
  {
    DeleteOption_Total,
    DeleteOption_FromParentAndHash,
    DeleteOption_FromParent
  };

  void deleteTask(PTask task, DeleteOption option);

  // Undelete task
  void undeleteTask(PTask task);

  // Remove task from internal dictionaries - it makes task unadressable by its id/model id
  void removeTask(PTask task);

  enum Depth
  {
    depthSingleTask,
    depthRecursive
  };
  void saveTask(PTask task, Depth depth);
  bool moveTask(PTask task, PTask newParent, int indexToInsert);
  bool isOpened();
  void save();
  TaskArray& topOfTaskTree();
  PTask findTaskByModelId(Task::ModelId id);
  PTask findTaskById(Task::Id id);
  int findTaskIndexInParent(PTask task);
  void loadAttachments(PTask task, AttachmentArray& output);
  void deleteAttachment(PAttachment att);
  void undeleteAttachment(PAttachment att);

  static Storage& instance();

protected:
  QString mPath, mKey;
  QSharedPointer<SQLite::Database> mDatabase;
  TaskArray mTopTasks;
  typedef QMap<Task::ModelId, PTask> TaskModelIdMap;
  TaskModelIdMap mTaskModelIdMap;
  typedef QMap<Task::Id, PTask> TaskIdMap;
  TaskIdMap mTaskIdMap;

  TaskArray mTaskToUpgrade;

  bool hasTable(const QString& tablename);
  void saveSingleTask(PTask task);
  void loadTaskTree();
  void loadTaskChildren(PTask task);
  bool upgradeFromVersion0();
  bool encryptTask(PTask task);
  bool encryptTaskContent(PTask task);
  bool encryptTaskAttachment(PAttachment attachment);
};

#endif // STORAGE_H
