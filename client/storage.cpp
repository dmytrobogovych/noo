#include "storage.h"
#include <QVariant>
#include <assert.h>
#include <encryption.h>

#ifdef TARGET_WIN
# include <WinSock2.h>
#endif
enum class DbProperty
{
    Version = 1,
    InternalCipher = 2
};

#define CURRENT_DBVERSION "0"

// Function to make encryption. Input is raw content blob, output is blob with IV, original length and encrypted data.
/*static void EncryptBlob(const QByteArray& input, QByteArray& output)
{
    TwofishCipher cipher;

    // Generate 16 bytes IV
    QByteArray iv(16, 0);
    IV::Generate(iv);
    cipher.setIV(iv);

    // Make padding
    int padded = (input.length() % cipher.blocksize()) ? (cipher.blocksize() - input.length() % cipher.blocksize()) : 0;

    // Prepare output buffer
    output.resize(iv.length() + 4 + input.length() + padded);

    // Copy IV
    memcpy(output.data(), iv.data(), iv.length());

    // Copy original length in network byte order
    uint32_t lengthNbo = htonl(input.length());
    memcpy(output.data() + iv.length(), &lengthNbo, 4);

    // Encrypt
    cipher.encrypt(input, 0, output, iv.length() + 4);
}*/

/*static void DecryptBlob(const QByteArray& input, QByteArray& output)
{
    TwofishCipher cipher;
    assert(input.length() >= cipher.blocksize() + 4);

    // Read IV
    QByteArray iv(input.data(), cipher.blocksize());

    // Read original length
    uint32_t lengthNbo;
    memcpy(&lengthNbo, input.data() + iv.length(), 4);

    // Prepare output buffer
    output.resize(input.length() - iv.length() - 4);

    // Set IV
    cipher.setIV(iv);

    // Decrypt data
    cipher.decrypt(input, iv.length() + 4, output, 0);

    // Truncate to original size
    output.truncate(ntohl(lengthNbo));
}*/


Storage::Storage()
{
}

Storage::~Storage()
{
    close();
}

QString Storage::path()
{
    return mPath;
}

void Storage::setPath(const QString &path)
{
    mPath = path;
}

QString Storage::key()
{
    return mKey;
}

void Storage::setKey(const QString &key)
{
    mKey = key;
}

SQLite::Database& Storage::database()
{
    return *mDatabase;
}

bool Storage::create()
{
    assert(!mPath.isEmpty());
    try
    {
        mDatabase = QSharedPointer<SQLite::Database>(new SQLite::Database(mPath.toStdString().c_str(), SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE ));
    }
    catch(std::exception& e)
    {
        return false;
    }

#ifdef USE_ENCRYPTED_DB
    try
    {
        std::string keyQuery = "pragma key='" + mKey.toStdString() + "'";
        mDatabase->exec(keyQuery.c_str());
        mDatabase->exec("pragma locking_mode=EXCLUSIVE");
        mDatabase->exec("pragma journal_mode=MEMORY");
        mDatabase->exec("pragma temp_store=MEMORY");
    }
    catch(std::exception& e)
    {
        return false;
    }
#endif

    try
    {
        // Timeline
        mDatabase->exec("CREATE TABLE timeline (id INTEGER PRIMARY KEY, removed INTEGER, taskid INTEGER, starttime TEXT, endtime TEXT, synctime TEXT)");
        mDatabase->exec("CREATE INDEX timeline_taskid_index ON timeline(taskid ASC)");

        // Tasks tree
        mDatabase->exec("CREATE TABLE task (type INTEGER, removed INTEGER, modifytime TEXT, id INTEGER PRIMARY KEY, parentid INTEGER, orderid INTEGER, title TEXT, html TEXT, flags INTEGER, synctime1 TEXT, synctime2 TEXT)");
        mDatabase->exec("CREATE INDEX task_parentid_index ON task(parentid ASC)");

        // Attachments
        mDatabase->exec("CREATE TABLE file (id INTEGER PRIMARY KEY, removed INTEGER, taskid INTEGER, filename TEXT, content BLOB, orderid INTEGER, synctime TEXT)");
        mDatabase->exec("CREATE INDEX file_taskid_index ON file(taskid ASC)");

        // Sync status
        mDatabase->exec("CREATE TABLE syncs (datetime TEXT, status TEXT)");
    }
    catch(std::exception& e)
    {
        return false;
    }

    return true;
}

bool Storage::open()
{
    assert(!mPath.isEmpty());

    try
    {
        mDatabase = QSharedPointer<SQLite::Database>(new SQLite::Database(mPath.toStdString().c_str(), SQLITE_OPEN_READWRITE));
        mDatabase->exec("pragma key='" + mKey.toStdString() + "'");
        SQLite::Statement q(*mDatabase, "select count(*) from sqlite_master");
        if (!q.executeStep())
            return false;
        mDatabase->exec("pragma locking_mode=EXCLUSIVE");
        mDatabase->exec("pragma journal_mode=MEMORY");
        mDatabase->exec("pragma temp_store=MEMORY");

    }
    catch(std::exception& e)
    {
        return false;
    }


    loadTaskTree();
    return true;
}

void Storage::close()
{
    if (mDatabase)
    {
        mDatabase.clear();
    }
}

bool Storage::hasTable(const QString& tablename)
{
    SQLite::Statement tableQuery(*mDatabase, "SELECT name FROM sqlite_master WHERE type='table' AND name=:tablename");
    tableQuery.bind(":tablename", tablename.toStdString());
    return tableQuery.executeStep();
}

bool Storage::upgrade()
{
    int currentVersion = 0;

    // Check if properties table is here
    if (!mDatabase)
        return false;

    if (!hasTable("properties"))
    {
        // If not - create it and consider database version 0
        SQLite::Statement createQuery(*mDatabase, "create table properties(type INTEGER, value TEXT)");
        if (!createQuery.exec())
            return false;

        // Insert version 0
        SQLite::Statement insertVersionQuery(*mDatabase, "insert into properties(type, value) values(:proptype, :proptext)");
        insertVersionQuery.bind(":proptype", (int)DbProperty::Version);
        insertVersionQuery.bind(":proptext", "0");
    }
    else
    {
        // If yes - get database version from 'dbversion' key
        SQLite::Statement versionQuery(*mDatabase, "select value from properties where type=:proptype");
        versionQuery.bind(":proptype", (int)DbProperty::Version);
        if (!versionQuery.executeStep())
            return false;

        QString dbVersionText = versionQuery.getColumn(0).getText("");
        if (dbVersionText.isEmpty())
            return false;

        bool ok = false;
        currentVersion = dbVersionText.toInt(&ok);
        if (!ok)
            return false;
    }

    // Depending on obtained version upgrade database
    switch (currentVersion)
    {
    case 0:
        if (!upgradeFromVersion0())
            return false;
        break;
    }

    // Update version number after upgrade
    SQLite::Statement updateVersion(*mDatabase, "update table properties set value=:proptext where type=:proptype");
    updateVersion.bind(":proptext", CURRENT_DBVERSION);
    updateVersion.bind(":proptype", (int)DbProperty::Version);
    updateVersion.exec();

    return true;
}

bool Storage::upgradeFromVersion0()
{
    /*
  // Upgrade tasks table
  SQLite::Statement addEncryptedTitle(*mDatabase, "alter table task add column title_encrypted BLOB");
  if (!addEncryptedTitle.exec())
    return false;

  SQLite::Statement addEncryptedContent(*mDatabase, "alter table task add column content_encrypted BLOB");
  if (!addEncryptedContent.exec())
    return false;

  SQLite::Statement addEncryptedAttachments(*mDatabase, "alter table attachment add column content_encrypted BLOB");
  if (!addEncryptedAttachments.exec())
    return false;

  // Database scheme is upgraded here, convert the data

  SQLite::Statement tasks(*mDatabase, "select id, title, html from task");
  while (tasks.executeStep())
  {
    // TODO
  }
  // Iterate all notes and attachments and make them Twofish encrypted
  mTaskToUpgrade.resize(topOfTaskTree().size());
  std::copy(topOfTaskTree().begin(), topOfTaskTree().end(), mTaskToUpgrade);
  for (PTask task: mTaskToUpgrade)
  {
    encryptTaskContent(task);
    //encryptTaskAttachment(task);

    // Add children to list
    int tl = mTaskToUpgrade.length();
    mTaskToUpgrade.resize(mTaskToUpgrade.size() + task->children().size());
    std::copy(task->children().begin(), task->children().end(), mTaskToUpgrade.begin() + tl);
  }
  */
    return true;
}

bool Storage::encryptTask(PTask task)
{
    return false;
}

bool Storage::encryptTaskContent(PTask task)
{
    return false;
}

bool Storage::encryptTaskAttachment(PAttachment attachment)
{
    return false;
}


PTask Storage::createTask(int index)
{
    if (!mDatabase)
        return PTask();

    SQLite::Statement insertQuery(*mDatabase, "insert into task(id, title, html, parentid, orderid, type, flags) values(NULL, :title, :html, NULL, :orderid, 0, 0)");
    insertQuery.bind(":title", "");
    insertQuery.bind(":html", "");
    insertQuery.bind(":orderid", index);
    if (insertQuery.exec())
    {
        PTask result(new Task());
        result->setId(database().getLastInsertRowid());
        result->setIndex(index);
        mTaskModelIdMap[result->modelId()] = result;
        mTaskIdMap[result->id()] = result;
        if (index > mTopTasks.size())
            mTopTasks.push_back(result);
        else
        {
            mTopTasks.insert(mTopTasks.begin() + index, result);
            // Assign new indexes for top tasks
            for (int i=0; i<mTopTasks.size(); i++)
            {
                mTopTasks[i]->setIndex(i);
                mTopTasks[i]->save();
            }
        }
        return result;
    }
    else
        return PTask();
}

PTask Storage::createTask(PTask parent, int index)
{
    if (!parent)
        return createTask(index);
    if (!mDatabase)
        return PTask();

    SQLite::Statement insertQuery(database(), "insert into task(id, title, html, parentid, orderid, type, flags) values(NULL, :title, :html, :parentid, :orderid, 0, 0)");
    insertQuery.bind(":title", "");
    insertQuery.bind(":html", "");
    insertQuery.bind(":parentid", (sqlite3_int64)parent->id());
    insertQuery.bind(":orderid", index);
    if (insertQuery.exec())
    {
        PTask result(new Task());
        result->setId(database().getLastInsertRowid());
        result->setIndex(index);
        result->setParent(parent);
        if (index > parent->children().size())
            parent->children().push_back(result);
        else
        {
            parent->children().insert(parent->children().begin() + index, result);
            for (int i=0; i<parent->children().size(); i++)
            {
                parent->children()[i]->setIndex(i);
                parent->children()[i]->save();
            }
        }

        mTaskModelIdMap[result->modelId()] = result;
        mTaskIdMap[result->id()] = result;
        return result;
    }
    return PTask();
}
/*
PTask Storage::loadTask(Task::Id id, PTask parent)
{
  PTask result(new Task());
  result->setId(id);
  result->load();
  result->setParent(parent);
  mTaskIdMap[result->modelId()] = result;

  return result;
}
*/

void Storage::saveTask(PTask task, Depth depth)
{
    if (depth == depthSingleTask)
        saveSingleTask(task);
    else
    {
        saveSingleTask(task);
        TaskArray& children = task->children();
        foreach(PTask child, children)
            saveTask(child, depthRecursive);
    }
}

bool Storage::moveTask(PTask task, PTask newParent, int indexToInsert)
{
    bool result = false;
    task->setParent(newParent);
    if (newParent)
    {
        SQLite::Statement updateParent(database(), "update task set parentid=:parentid where id=:id");
        updateParent.bind(":parentid", (sqlite3_int64)newParent->id());
        updateParent.bind(":id", (sqlite3_int64)task->id());
        result = updateParent.exec();

        // Insert into children list
        TaskArray& children = newParent->children();
        if (indexToInsert >= children.size())
            children.push_back(task);
        else
            children.insert(indexToInsert, task);
        for (int i=0; i<children.size(); i++)
        {
            children[i]->setIndex(i);
            children[i]->save();
        }
    }
    else
    {
        SQLite::Statement updateToRoot(database(), "update task set parentid = NULL where id=:id");
        updateToRoot.bind(":id", (sqlite3_int64)task->id());
        result = updateToRoot.exec();
        if (result)
            task->setParentId(0);

        // Insert into root list
        if (topOfTaskTree().size() > indexToInsert)
            topOfTaskTree().insert(indexToInsert, task);
        else
            topOfTaskTree().push_back(task);

        for (int i=0; i<topOfTaskTree().size(); i++)
        {
            topOfTaskTree()[i]->setIndex(i);
            topOfTaskTree()[i]->save();
        }
    }

    if (result)
    {
        task->save();
    }

    return result;
}

bool Storage::isOpened()
{
    return mDatabase != nullptr;
}

void Storage::save()
{
    foreach (PTask task, mTopTasks)
        saveTask(task, depthRecursive);

    database().exec("delete from task where removed = 1");
    database().exec("delete from timeline where removed = 1");
    database().exec("delete from file where removed = 1");
    //database().exec("delete from change where removed = 1");
}

void Storage::saveSingleTask(PTask task)
{
    task->save();
}

void Storage::loadTaskTree()
{
    mTopTasks.clear();

    SQLite::Statement q(database(), "select id, title, orderid, flags, (select count(*) from file where (file.taskid = task.id) and ((file.removed is null) or (file.removed = 0))) from task where (parentid is null) and ((removed != 1) or (removed is null)) order by orderid");
    int currentIndex = 0;
    while(q.executeStep())
    {
        PTask t(new Task());
        t->load(q);
        t->setIndex(currentIndex++);
        mTaskModelIdMap[t->modelId()] = t;
        mTaskIdMap[t->id()] = t;
        mTopTasks.push_back(t);
    }

    foreach (PTask task, mTopTasks)
        loadTaskChildren(task);
}

void Storage::loadTaskChildren(PTask task)
{
    SQLite::Statement q(database(), "select id, title, orderid, flags, (select count(*) from file where (file.taskid = task.id) and ((file.removed is null) or (file.removed = 0))) from task where (task.parentid = :parentid) and ((task.removed != 1) or (task.removed is null)) order by task.orderid");
    q.bind(":parentid", (sqlite3_int64)task->id());
    int currentIndex = 0;
    while (q.executeStep())
    {
        PTask t(new Task());
        t->load(q);
        t->setIndex(currentIndex++);
        t->setParent(task, false);
        loadTaskChildren(t);
        mTaskModelIdMap[t->modelId()] = t;
        mTaskIdMap[t->id()] = t;
        task->children().push_back(t);
    }
}

PTask Storage::findTaskByModelId(Task::ModelId id)
{
    auto taskIter = mTaskModelIdMap.find(id);
    if (taskIter != mTaskModelIdMap.end())
        return *taskIter;
    else
        return PTask();
}

PTask Storage::findTaskById(Task::Id id)
{
    auto taskIter = mTaskIdMap.find(id);
    if (taskIter != mTaskIdMap.end())
        return *taskIter;
    else
        return PTask();
}

int Storage::findTaskIndexInParent(PTask task)
{
    if (task->parent())
        return task->parent()->children().indexOf(task);
    else
        return topOfTaskTree().indexOf(task);
}

TaskArray& Storage::topOfTaskTree()
{
    return mTopTasks;
}

void Storage::loadAttachments(PTask task, AttachmentArray& output)
{
    SQLite::Statement q(database(), "select id, filename, orderid from file where (taskid = :taskid) and ((removed != 1) or (removed is null)) order by orderid");
    q.bind(":taskid", (sqlite3_int64)task->id());
    while (q.executeStep())
    {
        PAttachment att(new Attachment());
        att->setId(q.getColumn(0).getInt64());
        att->setFilename(q.getColumn(1).getText());
        att->setTaskId(task->id());
        att->setIndex(q.getColumn(2).getInt());
        output.push_back(att);
    }
}

void Storage::deleteAttachment(PAttachment att)
{
    SQLite::Statement q(database(), "update file set removed=1 where id=:id");
    q.bind(":id", (sqlite3_int64)att->id());
    q.exec();
}

void Storage::undeleteAttachment(PAttachment att)
{
    SQLite::Statement q(database(), "update file set removed=0 where id=:id");
    q.bind(":id", (sqlite3_int64)att->id());
    q.exec();
}


Storage& Storage::instance()
{
    static Storage _instance;
    return _instance;
}


void Storage::deleteTask(PTask task, DeleteOption option)
{
    if (option != DeleteOption_FromParent)
    {
        // Remove from hash
        removeTask(task);
    }

    TaskArray& siblings = task->parent() ? task->parent()->children() : mTopTasks;
    siblings.removeOne(task);

    // Remove from database
    if (option == DeleteOption_Total)
    {
        SQLite::Statement q(database(), "update task set removed = 1 where id = :id");
        q.bind(":id", (sqlite3_int64)task->id());
        q.exec();
    }

#if 0
    int taskIndex = -1;
    // Update indexes
    for (int i=0; i<siblings.size(); i++)
    {
        if (siblings[i] == task)
            taskIndex = i;

        Task& t = *siblings[i];
        if (t.index() > task->index())
        {
            t.setIndex(t.index() - 1);
            t.save();
        }
    }

    // Remove from tree
    if (taskIndex >= 0)
        siblings.remove(taskIndex);
#endif
}

void Storage::undeleteTask(PTask task)
{
    SQLite::Statement q(database(), "update task set removed = 0 where id = :id");
    q.bind(":id", (sqlite3_int64)task->id());
    q.exec();

    // Find place where to insert task
    TaskArray& siblings = task->parent() ? task->parent()->children() : mTopTasks;

    TaskArray::iterator taskIter = std::lower_bound(siblings.begin(), siblings.end(), task->index(), [] (const PTask& t, int index) { return t->index() < index;});
    if (taskIter != siblings.end())
        siblings.insert(taskIter, task);
    else
        siblings.append(task);

    mTaskModelIdMap[task->modelId()] = task;
    mTaskIdMap[task->id()] = task;
}

void Storage::removeTask(PTask task)
{
    auto taskModelIter = mTaskModelIdMap.find(task->modelId());
    if (taskModelIter != mTaskModelIdMap.end())
        mTaskModelIdMap.erase(taskModelIter);

    auto taskIter = mTaskIdMap.find(task->id());
    if (taskIter != mTaskIdMap.end())
        mTaskIdMap.erase(taskIter);
}

