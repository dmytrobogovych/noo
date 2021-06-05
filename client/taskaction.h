#ifndef TASKACTION_H
#define TASKACTION_H

#include "task.h"
#include <QString>
#include <QDataStream>
#include <QModelIndexList>

class TaskTreeModel;
class AttachmentsListModel;

// Base class for all actions
class TaskAction
{
  friend class ChangesHistory;
public:
  TaskAction(PTask task);
  virtual ~TaskAction();

  // Associated task
  PTask task() const;

protected:
  PTask mTask;

  virtual bool commit(TaskTreeModel* taskModel, AttachmentsListModel* attModel) = 0;
  virtual bool rollback(TaskTreeModel* taskModel, AttachmentsListModel* attModel) = 0;
};

typedef QSharedPointer<TaskAction> PTaskAction;

class ChangesHistory
{
public:
  ChangesHistory();
  ~ChangesHistory();

  void setTaskTreeModel(TaskTreeModel* model);
  void setAttachmentsModel(AttachmentsListModel* model);
  TaskTreeModel* taskTreeModel() const;
  AttachmentsListModel* attachmentsModel() const;

  void add(PTaskAction action);
  void undo();
  void redo();
  bool canUndo() const;
  bool canRedo() const;

  static ChangesHistory& instance();
protected:
  TaskTreeModel* mTaskModel = nullptr;
  AttachmentsListModel* mAttachmentsModel = nullptr;
  QVector<PTaskAction> mActionList;
  int mRollbackCount = 0;
};

#define MAKE_ACTION(X) ChangesHistory::instance().add(PTaskAction(X))

class ImportAttachmentAction: public TaskAction
{
public:
  ImportAttachmentAction(PTask task, const QString& path, int index);
  ~ImportAttachmentAction();

  PAttachment attachment() const;

protected:
  QString mPath;
  PAttachment mAttachment;
  int mIndex;

  bool commit(TaskTreeModel* taskModel, AttachmentsListModel* attModel);
  bool rollback(TaskTreeModel* taskModel, AttachmentsListModel* attModel);
};

class RenameAttachmentAction: public TaskAction
{
public:
  RenameAttachmentAction(PTask task, PAttachment attachment, const QString& newname);
  ~RenameAttachmentAction();

protected:
  PAttachment mAttachment;
  QString mNewName, mName;

  bool commit(TaskTreeModel* taskModel, AttachmentsListModel* attModel);
  bool rollback(TaskTreeModel* taskModel, AttachmentsListModel* attModel);
};

class DeleteAttachmentAction: public TaskAction
{
public:
  DeleteAttachmentAction(PTask task, QModelIndexList& mil);
  ~DeleteAttachmentAction();

  bool commit(TaskTreeModel* taskModel, AttachmentsListModel* attModel);
  bool rollback(TaskTreeModel* taskModel, AttachmentsListModel* attModel);

protected:
  QModelIndexList mIndexList;
  QVector<PAttachment> mAttachments;
};

class NewTaskAction: public TaskAction
{
public:
  NewTaskAction(PTask parent, int index, const QString& title);
  ~NewTaskAction();

protected:
  PTask mParent;
  int mIndex;
  QString mTitle;

  bool commit(TaskTreeModel* taskModel, AttachmentsListModel* attModel);
  bool rollback(TaskTreeModel* taskModel, AttachmentsListModel* attModel);
  bool save(QDataStream& output);
};

class RenameTaskAction: public TaskAction
{
public:
  RenameTaskAction(PTask task, const QString& newTitle);
  ~RenameTaskAction();

protected:
  QString mNewTitle, mTitle;

  bool commit(TaskTreeModel* taskModel, AttachmentsListModel* attModel);
  bool rollback(TaskTreeModel* taskModel, AttachmentsListModel* attModel);
  bool save(QDataStream &output);
};


class MoveTaskAction: public TaskAction
{
public:
  MoveTaskAction(PTask task, PTask newParent, int newIndex);
  ~MoveTaskAction();

protected:
  int mIndex, mNewIndex;
  PTask mParent, mNewParent;

  bool commit(TaskTreeModel* taskModel, AttachmentsListModel* attModel);
  bool rollback(TaskTreeModel* taskModel, AttachmentsListModel* attModel);
};

class IncreaseLevelAction: public TaskAction
{
public:
  IncreaseLevelAction(PTask task);
  ~IncreaseLevelAction();

protected:
  PTask mOldParent;
  int mOldIndex;

  bool commit(TaskTreeModel* taskModel, AttachmentsListModel* attModel);
  bool rollback(TaskTreeModel* taskModel, AttachmentsListModel* attModel);
};

class DecreaseLevelAction: public TaskAction
{
public:
  DecreaseLevelAction(PTask task);
  ~DecreaseLevelAction();

protected:
  bool commit(TaskTreeModel *taskModel, AttachmentsListModel *attModel);
  bool rollback(TaskTreeModel *taskModel, AttachmentsListModel *attModel);
};

class DeleteTaskAction: public TaskAction
{
public:
  DeleteTaskAction(PTask task);
  ~DeleteTaskAction();

protected:
  int mIndex;

  bool commit(TaskTreeModel* taskModel, AttachmentsListModel* attModel);
  bool rollback(TaskTreeModel* taskModel, AttachmentsListModel* attModel);
};

class SaveTaskAction: public TaskAction
{
public:
    SaveTaskAction(const PTask& task);
    ~SaveTaskAction() override;

protected:
    bool commit(TaskTreeModel* taskModel, AttachmentsListModel* attModel);
    bool rollback(TaskTreeModel* taskModel, AttachmentsListModel* attModel);
};

#endif // TASKACTION_H
