#include "taskaction.h"
#include "storage.h"
#include "tasktreemodel.h"
#include "attachmentslist.h"
#include <QFile>
#include <QFileInfo>
#include <QByteArray>

TaskAction::TaskAction(PTask task)
    :mTask(task)
{
}

TaskAction::~TaskAction()
{
}

PTask TaskAction::task() const
{
    return mTask;
}

// ------------ History ------------------
ChangesHistory::ChangesHistory()
{

}

ChangesHistory::~ChangesHistory()
{

}

void ChangesHistory::setTaskTreeModel(TaskTreeModel* model)
{
    mTaskModel = model;
}

void ChangesHistory::setAttachmentsModel(AttachmentsListModel* model)
{
    mAttachmentsModel = model;
}

TaskTreeModel* ChangesHistory::taskTreeModel() const
{
    return mTaskModel;
}

AttachmentsListModel* ChangesHistory::attachmentsModel() const
{
    return mAttachmentsModel;
}

void ChangesHistory::add(PTaskAction action)
{
    // See if there are "undo"ed actions in the list now
    if (mRollbackCount > 0)
    {
        // Just delete from list - these changes are not in DB already
        mActionList.erase(mActionList.begin() + mActionList.size() - mRollbackCount, mActionList.end());
        mRollbackCount = 0;
    }

    // Apply change
    if (action->commit(mTaskModel, mAttachmentsModel))
        mActionList.push_back(action);
}

void ChangesHistory::undo()
{
    // If there are actions that can be "undo"
    if (mActionList.size() - mRollbackCount > 0)
    {
        mRollbackCount++;
        PTaskAction& action = mActionList[mActionList.size() - mRollbackCount];
        if (action->rollback(mTaskModel, mAttachmentsModel))
        {
        }
    }
}

void ChangesHistory::redo()
{
    if (mRollbackCount > 0)
    {
        PTaskAction& action = mActionList[mActionList.size() - mRollbackCount];
        mRollbackCount--;
        if (action->commit(mTaskModel, mAttachmentsModel))
        {
        }
    }
}

bool ChangesHistory::canRedo() const
{
    return mRollbackCount > 0;
}

bool ChangesHistory::canUndo() const
{
    return mRollbackCount < mActionList.size();
}

static ChangesHistory HistoryStaticInstance;
ChangesHistory& ChangesHistory::instance()
{
    return HistoryStaticInstance;
}

// ------------ ImportAttachmentAction ----
#define ImportAttachmentId int(1)

ImportAttachmentAction::ImportAttachmentAction(PTask task, const QString &path, int index)
    :TaskAction(task), mPath(path), mIndex(index)
{}

ImportAttachmentAction::~ImportAttachmentAction()
{}

bool ImportAttachmentAction::commit(TaskTreeModel* /*taskModel*/, AttachmentsListModel* /*attModel*/)
{
    QFile f(mPath);
    f.open(QFile::ReadOnly);
    if (!f.isOpen())
        return false;

    // Get data from file
    QByteArray content = f.readAll();

    // Compress them
    QByteArray compressed = qCompress(content);

    // Put it to Attachment instance
    QFileInfo fi(mPath);
    mAttachment = PAttachment(new Attachment());
    mAttachment->setTaskId(mTask->id())
            .setIndex(mIndex)
            .setFilename(fi.fileName())
            .saveMetadata()
            .saveContent(compressed);

    return true;
}

bool ImportAttachmentAction::rollback(TaskTreeModel* /*taskModel*/, AttachmentsListModel* /*attModel*/)
{
    Storage::instance().deleteAttachment(mAttachment);
    return true;
}

PAttachment ImportAttachmentAction::attachment() const
{
    return mAttachment;
}

// ------------ RenameAttachmentAction ---
#define RenameAttachmentId int(2)

RenameAttachmentAction::RenameAttachmentAction(PTask task, PAttachment attachment, const QString &newname)
    :TaskAction(task), mAttachment(attachment), mNewName(newname)
{
    mName = mAttachment->filename();
}

RenameAttachmentAction::~RenameAttachmentAction()
{
}

bool RenameAttachmentAction::commit(TaskTreeModel* /*taskModel*/, AttachmentsListModel* attModel)
{
    mAttachment->setFilename(mNewName)
            .saveMetadata();

    if (attModel)
    {
        int row = attModel->findRow(mAttachment);
        QModelIndex index = attModel->index(row, 0);
        attModel->dataChanged(index, index);
    }
    return true;
}

bool RenameAttachmentAction::rollback(TaskTreeModel* /*taskModel*/, AttachmentsListModel* /*attModel*/)
{
    mAttachment->setFilename(mName)
            .saveMetadata();
    return true;
}

// ------------ DeleteAttachmentAction ---

#define DeleteAttachmentId int(3)

DeleteAttachmentAction::DeleteAttachmentAction(PTask task, QModelIndexList& mil)
    :TaskAction(task), mIndexList(mil)
{}

DeleteAttachmentAction::~DeleteAttachmentAction()
{}

bool DeleteAttachmentAction::commit(TaskTreeModel* /*taskModel*/, AttachmentsListModel* attModel)
{
    if (!attModel)
        return false;

    mAttachments.clear();

    foreach (const QModelIndex& index, mIndexList)
    {
        if (!index.isValid())
            continue;

        PAttachment att = attModel->itemAt(index.row());

        // Remove from DB
        Storage::instance().deleteAttachment(att);

        // Remove from model
        attModel->removeItem(index.row());

        mAttachments.push_back(att);
    }

    // Iterate other items and decrease their DB table's orderid field
    for (int row = 0; row < attModel->rowCount(); row++)
    {
        Attachment& att = *attModel->itemAt(row);
        att.setIndex(row)
                .saveMetadata();
    }


    return true;
}

bool DeleteAttachmentAction::rollback(TaskTreeModel* /*taskModel*/, AttachmentsListModel* attModel)
{
    while (!mAttachments.isEmpty())
    {
        auto iter = std::min_element(mAttachments.begin(), mAttachments.end(), [] (const PAttachment& a, const PAttachment& b) { return a->index() < b->index();});
        PAttachment attToUndelete = *iter;

        // Restore attachment in database
        Storage::instance().undeleteAttachment(attToUndelete);

        attModel->addItem(attToUndelete);
    }

    return true;
}

// ------------ NewTaskAction ------------
#define NewTaskId int(4)

NewTaskAction::NewTaskAction(PTask parent, int index, const QString &title)
    :TaskAction(PTask()), mParent(parent), mIndex(index), mTitle(title)
{}

NewTaskAction::~NewTaskAction()
{}

bool NewTaskAction::commit(TaskTreeModel* taskModel, AttachmentsListModel* /*attModel*/)
{
    if (taskModel)
    {
        QModelIndex parentIndex = taskModel->getIndex(mParent);
        taskModel->beginInsertRows(parentIndex, mIndex, mIndex);
        //taskModel->rowCount(parentIndex), taskModel->rowCount(parentIndex));
    }
    if (!mTask)
    {
        mTask = Storage::instance().createTask(mParent, mIndex);
        mTask->setTitle(mTitle);
        mTask->save();
    }
    else
        Storage::instance().undeleteTask(mTask);

    if (taskModel)
        taskModel->endInsertRows();

    return true;
}

bool NewTaskAction::rollback(TaskTreeModel* taskModel, AttachmentsListModel* /*attModel*/)
{
    if (taskModel)
    {
        // Get parent index
        QModelIndex parentIndex = taskModel->getIndex(mTask->parent());
        int row = Storage::instance().findTaskIndexInParent(mTask);
        taskModel->beginRemoveRows(parentIndex, row, row);
    }

    Storage::instance().deleteTask(mTask, Storage::DeleteOption_Total);
    if (taskModel)
    {
        taskModel->endRemoveRows();
    }
    return true;
}

// ------------ RenameTaskAction ---------
RenameTaskAction::RenameTaskAction(PTask task, const QString &newTitle)
    :TaskAction(task), mNewTitle(newTitle)
{
    mTitle = mTask->title();
}

RenameTaskAction::~RenameTaskAction()
{

}

bool RenameTaskAction::commit(TaskTreeModel* taskModel, AttachmentsListModel* /*attModel*/)
{
    mTask->setTitle(mNewTitle);
    mTask->save();

    if (taskModel)
    {
        QModelIndex index = taskModel->getIndex(mTask);
        if (index.isValid())
            taskModel->dataChanged(index ,index);
    }
    return true;
}

bool RenameTaskAction::rollback(TaskTreeModel* taskModel, AttachmentsListModel* /*attModel*/)
{
    mTask->setTitle(mTitle);
    mTask->save();

    if (taskModel)
    {
        QModelIndex index = taskModel->getIndex(mTask);
        if (index.isValid())
            taskModel->dataChanged(index, index);
    }
    return true;
}

// ------------ MoveTaskAction ------------
MoveTaskAction::MoveTaskAction(PTask task, PTask newParent, int newIndex)
    :TaskAction(task), mNewIndex(newIndex), mNewParent(newParent)
{
    mIndex = mTask->index();
    mParent = mTask->parent();
}

MoveTaskAction::~MoveTaskAction()
{
}

bool MoveTaskAction::commit(TaskTreeModel* taskModel, AttachmentsListModel* /*attModel*/)
{
    taskModel->layoutAboutToBeChanged();

    // Detach it from old parent (if exists)
    if (taskModel)
    {
        QModelIndex parentIndex = taskModel->getIndex(mTask->parent());
        int row = Storage::instance().findTaskIndexInParent(mTask);
        taskModel->beginRemoveRows(parentIndex, row, row);
    }

    // Remove task from memory structures only
    Storage::instance().deleteTask(mTask, Storage::DeleteOption_FromParent);

    if (taskModel)
        taskModel->endRemoveRows();

    // Move task
    if (taskModel)
    {
        QModelIndex parentIndex = taskModel->getIndex(mNewParent);
        taskModel->beginInsertRows(parentIndex, mNewIndex, mNewIndex);
    }
    Storage::instance().moveTask(mTask, mNewParent, mNewIndex);
    if (taskModel)
        taskModel->endInsertRows();

    taskModel->layoutChanged();

    return true;
}

bool MoveTaskAction::rollback(TaskTreeModel* taskModel, AttachmentsListModel* /*attModel*/)
{
    if (taskModel)
    {
        QModelIndex parentIndex = taskModel->getIndex(mNewParent);

        // Tell about removing of row
        taskModel->beginRemoveRows(parentIndex, mNewIndex, mNewIndex);
    }

    // Delete from parent
    Storage::instance().deleteTask(mTask, Storage::DeleteOption_FromParent);
    if (taskModel)
        taskModel->endRemoveRows();

    // Reload task if needed
    mTask->loadContent();

    if (taskModel)
    {
        QModelIndex parentIndex = taskModel->getIndex(mParent);
        taskModel->beginInsertRows(parentIndex, mIndex, mIndex);
    }

    // Move task back
    Storage::instance().moveTask(mTask, mParent, mIndex);
    if (taskModel)
        taskModel->endInsertRows();

    return true;
}

// ------- IncreaseLevelAction -----------
IncreaseLevelAction::IncreaseLevelAction(PTask task)
    :TaskAction(task)
{
    mOldParent = task->parent();
    mOldIndex = task->index();
}

IncreaseLevelAction::~IncreaseLevelAction()
{

}

bool IncreaseLevelAction::commit(TaskTreeModel* /*taskModel*/, AttachmentsListModel* /*attModel*/)
{
    /*  if (taskModel)
  {
    QModelIndex parentIndex = taskModel->getIndex(mTask->parent());
    int row = Storage::instance().findTaskIndexInParent(mTask);
    taskModel->beginRemoveRows(parentIndex, row, row);
  }

  Storage::instance().deleteTask(mTask, Storage::DeleteOption_Total);
  if (taskModel)
    taskModel->endRemoveRows();
*/
    return true;
}

bool IncreaseLevelAction::rollback(TaskTreeModel* /*taskModel*/, AttachmentsListModel* /*attModel*/)
{
    /*
  if (taskModel)
  {
    QModelIndex parentIndex = taskModel->getIndex(mTask->parent());
    taskModel->beginInsertRows(parentIndex, mIndex, mIndex);
  }
  Storage::instance().undeleteTask(mTask);
  if (taskModel)
    taskModel->endInsertRows();
    */
    return true;
}

// ------- DecreaseLevelAction -----------
DecreaseLevelAction::DecreaseLevelAction(PTask task)
    :TaskAction(task)
{

}

DecreaseLevelAction::~DecreaseLevelAction()
{

}

bool DecreaseLevelAction::commit(TaskTreeModel* /*taskModel*/, AttachmentsListModel* /*attModel*/)
{
    /*  if (taskModel)
  {
    QModelIndex parentIndex = taskModel->getIndex(mTask->parent());
    int row = Storage::instance().findTaskIndexInParent(mTask);
    taskModel->beginRemoveRows(parentIndex, row, row);
  }

  Storage::instance().deleteTask(mTask, Storage::DeleteOption_Total);
  if (taskModel)
    taskModel->endRemoveRows();
*/
    return true;
}

bool DecreaseLevelAction::rollback(TaskTreeModel* /*taskModel*/, AttachmentsListModel* /*attModel*/)
{
    /*
  if (taskModel)
  {
    QModelIndex parentIndex = taskModel->getIndex(mTask->parent());
    taskModel->beginInsertRows(parentIndex, mIndex, mIndex);
  }
  Storage::instance().undeleteTask(mTask);
  if (taskModel)
    taskModel->endInsertRows();
  */
    return true;
}

// ------- DeleteTaskAction ---------------
DeleteTaskAction::DeleteTaskAction(PTask task)
    :TaskAction(task)
{
    mIndex = Storage::instance().findTaskIndexInParent(mTask);
}

DeleteTaskAction::~DeleteTaskAction()
{
}

bool DeleteTaskAction::commit(TaskTreeModel* taskModel, AttachmentsListModel* /*attModel*/)
{
    if (taskModel)
    {
        QModelIndex parentIndex = taskModel->getIndex(mTask->parent());
        int row = Storage::instance().findTaskIndexInParent(mTask);
        taskModel->beginRemoveRows(parentIndex, row, row);
    }

    Storage::instance().deleteTask(mTask, Storage::DeleteOption_Total);
    if (taskModel)
        taskModel->endRemoveRows();

    return true;
}

bool DeleteTaskAction::rollback(TaskTreeModel* taskModel, AttachmentsListModel* /*attModel*/)
{
    if (taskModel)
    {
        QModelIndex parentIndex = taskModel->getIndex(mTask->parent());
        taskModel->beginInsertRows(parentIndex, mIndex, mIndex);
    }
    Storage::instance().undeleteTask(mTask);
    if (taskModel)
        taskModel->endInsertRows();
    return true;
}


// ---------------- SaveTaskAction --------------
SaveTaskAction::SaveTaskAction(const PTask& task)
    :TaskAction(task)
{}

SaveTaskAction::~SaveTaskAction()
{}

bool SaveTaskAction::commit(TaskTreeModel* /*taskModel*/, AttachmentsListModel* /*attModel*/)
{
    if (mTask)
        mTask->save();


    return true;
}

bool SaveTaskAction::rollback(TaskTreeModel* /*taskModel*/, AttachmentsListModel* /*attModel*/)
{
    return false;
}
