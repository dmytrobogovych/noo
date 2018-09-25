#include "config.h"
#include "tasktreemodel.h"
#include "taskaction.h"
#include <QIcon>
#include <QMimeData>
#include <QDebug>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <deque>

TaskTreeView::TaskTreeView(QWidget *widget)
  :QTreeView(widget)
{

}

void TaskTreeView::dragMoveEvent(QDragMoveEvent* event)
{
  QTreeView::dragMoveEvent(event);

  event->acceptProposedAction();
  event->accept();
}

void TaskTreeView::dragEnterEvent(QDragEnterEvent *event)
{
  QTreeView::dragEnterEvent(event);
  event->acceptProposedAction();
  event->accept();
}

void TaskTreeView::dragLeaveEvent(QDragLeaveEvent *event)
{
  QTreeView::dragLeaveEvent(event);
  event->accept();
}

void TaskTreeView::dropEvent(QDropEvent *event)
{
  QTreeView::dropEvent(event);
  event->acceptProposedAction();
  event->accept();
  //this->setCurrentIndex(this->indexAt(event->pos()));
}

TaskTreeModel::TaskTreeModel(bool allowCheckboxes)
  :mAllowCheckboxes(allowCheckboxes)
{
}

TaskTreeModel::~TaskTreeModel()
{}

QModelIndex TaskTreeModel::index(int row, int column, const QModelIndex &parent) const
{
  if (!hasIndex(row, column, parent))
    return QModelIndex();

  // Find task from parent index
  if (parent.isValid())
  {
    PTask parentTask = Storage::instance().findTaskByModelId(parent.internalId());
    PTask task = parentTask->children()[row];
    return createIndex(row, column, task->modelId());
  }
  else
  {
    if (row >= 0 && row < Storage::instance().topOfTaskTree().count())
    {
      PTask task = Storage::instance().topOfTaskTree()[row];
      return createIndex(row, column, task->modelId());
    }
    else
      return QModelIndex();
  }
}

QModelIndex TaskTreeModel::parent(const QModelIndex &child) const
{
  if (!child.isValid())
    return QModelIndex();

  PTask task = Storage::instance().findTaskByModelId(child.internalId());
  if (task)
  {
    PTask parentTask = task->parent();
    if (parentTask)
    {
      if (parentTask->parent())
      {
        int row = parentTask->parent()->children().indexOf(parentTask);
        return createIndex(row, 0, parentTask->modelId());
      }
      else
      {
        int row = Storage::instance().topOfTaskTree().indexOf(parentTask);
        return createIndex(row, 0, parentTask->modelId());
      }
    }
    else
      return QModelIndex();
  }
  return QModelIndex();
}

int TaskTreeModel::rowCount(const QModelIndex &parent) const
{
  if (parent.isValid())
  {
    PTask parentTask = Storage::instance().findTaskByModelId(parent.internalId());
    if (parentTask)
      return parentTask->children().count();
  }
  else
    return Storage::instance().topOfTaskTree().count();
  return 0;
}

int TaskTreeModel::columnCount(const QModelIndex& /*parent*/) const
{
  return 1;
}

QVariant TaskTreeModel::data(const QModelIndex &index, int role) const
{
  PTask task = Storage::instance().findTaskByModelId(index.internalId());
  if (!task)
    return QVariant();

  switch (role)
  {
  case Qt::DisplayRole:
  case Qt::EditRole:
    return task->title();

  case Qt::DecorationRole:
    return QIcon(":/icons/icons/text-x-generic.png");

  case Qt::CheckStateRole:
    if (mAllowCheckboxes)
      return task->isChecked() ? Qt::Checked : Qt::Unchecked;
    break;
  }
  
  return QVariant();
}

bool TaskTreeModel::setData(const QModelIndex &index, const QVariant &value, int role /* = Qt::EditRole */)
{
  PTask task = getTask(index);
  if (task)
  {
    switch (role)
    {
    case Qt::DisplayRole:
    case Qt::EditRole:
      // Save new title
      MAKE_ACTION(new RenameTaskAction(task, value.toString()));

      break;

    case Qt::CheckStateRole:
      QModelIndex br = makeTaskChecked(index, value.toInt() == Qt::Checked);
      dataChanged(index, br, QVector<int>(1, Qt::CheckStateRole));
      break;
    }
  }
  return true;
}

QModelIndex TaskTreeModel::makeTaskChecked(QModelIndex index, bool checked)
{
  QModelIndex result;

  std::deque<PTask> q;

  PTask t = getTask(index);
  q.push_back(t);
  while (!q.empty())
  {
    PTask current = q.front(); q.pop_front();
    if (current)
    {
      current->setChecked(checked);
      for (PTask child: current->children())
        q.push_back(child);

      result = getIndex(current);
    }
  }
  return result;
}

PTask TaskTreeModel::addTask(const QModelIndex& parent, int index)
{
  // Find parent task
  PTask parentTask = getTask(parent);

  // Run new task action
  PTaskAction action(new NewTaskAction(parentTask, index, tr("New task")));
  ChangesHistory::instance().add(action);

  // Get result
  PTask childTask = action->task();

  return childTask;
}

QModelIndex TaskTreeModel::getIndex(const PTask& task, bool includeModelId)
{
  if (!task)
    return QModelIndex();

  int row = 0;
  if (task->parent())
    row = task->parent()->children().indexOf(task);
  else
    row = Storage::instance().topOfTaskTree().indexOf(task);

  if (includeModelId)
    return createIndex(row, 0, task->modelId());
  else
    return createIndex(row, 0);
}

void TaskTreeModel::deleteTask(const QModelIndex& index)
{
  // Check if there is task
  PTask task = getTask(index);
  if (!task)
    return;

  // Run delete task action
  MAKE_ACTION(new DeleteTaskAction(task));
}

void TaskTreeModel::moveTask(const PTask& task, int offset)
{
  if (!task)
    return;
  MAKE_ACTION(new MoveTaskAction(task, task->parent(), task->index() + offset));
}

void TaskTreeModel::setTitle(const QModelIndex& index, const QString& title)
{
  setData(index, QVariant(title), Qt::DisplayRole);
}

Qt::ItemFlags TaskTreeModel::flags(const QModelIndex &index) const
{
  Qt::ItemFlags result = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsDropEnabled;
  if (index.isValid())
    result |= Qt::ItemIsDragEnabled;
  if (mAllowCheckboxes)
    result |= Qt::ItemIsUserCheckable;

  return result;
}

PTask TaskTreeModel::getTask(const QModelIndex& index) const
{
  if (!index.isValid())
    return PTask();

  return Storage::instance().findTaskByModelId(index.internalId());
}

QVariant TaskTreeModel::headerData(int /*section*/, Qt::Orientation /*orientation*/, int /*role = Qt::DisplayRole */) const
{
  return "";

  /*if (orientation != Qt::Horizontal)
    return QVariant();

  switch (role)
  {
  case Qt::DisplayRole:
    return QString(tr("Tasks"));
  }
  return QVariant();*/
}

Qt::DropActions TaskTreeModel::supportedDropActions() const
{
  return Qt::MoveAction;
}

Qt::DropActions TaskTreeModel::supportedDragActions() const
{
  return Qt::MoveAction;
}

QStringList TaskTreeModel::mimeTypes() const
{
  QStringList result;
  result << NODE_MIME_TYPE;
  return result;
}

QMimeData *TaskTreeModel::mimeData(const QModelIndexList &indexes) const
{
  //qDebug() << "Mime data requested for indexes list size " << indexes.size();

  QMimeData *mimeData = new QMimeData();
  QByteArray encodedData;

  QDataStream stream(&encodedData, QIODevice::WriteOnly);

  foreach (const QModelIndex &index, indexes)
  {
    if (index.isValid())
    {
      PTask task = getTask(index);
      stream << task->modelId();
    }
  }

  mimeData->setData(NODE_MIME_TYPE, encodedData);
  return mimeData;
}

bool TaskTreeModel::dropMimeData(const QMimeData *mimeData, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
  qDebug() << "TaskTreeModel::dropMimeData";

  if (action == Qt::IgnoreAction)
      return true;

  if (!mimeData->hasFormat(NODE_MIME_TYPE))
      return false;

  if (column > 0)
      return false;

  // Find task
  QByteArray encodedData = mimeData->data(NODE_MIME_TYPE);
  QDataStream stream(&encodedData, QIODevice::ReadOnly);
  QStringList newItems;
  int rows = 0;
  PTask lastMovedTask;

  while (!stream.atEnd())
  {
    Task::ModelId modelId;
    stream >> modelId;
    ++rows;

    // Bring task instance
    PTask t = Storage::instance().findTaskByModelId(modelId);
    PTask parentTask = getTask(parent);
    int currentRow = 0;
    if (parentTask)
      currentRow = (row == -1) ? parentTask->children().size() : (row + rows - 1);
    else
      currentRow = Storage::instance().topOfTaskTree().size();

    lastMovedTask = t;
    PTaskAction action(new MoveTaskAction(t, parentTask, currentRow));
    ChangesHistory::instance().add(action);

/*    // Detach it from old parent (if exists)
    if (t->parent())
    {
      int index = t->parent()->children().indexOf(t);
      beginRemoveRows(getIndex(t->parent()), index, index);
      t->parent()->children().remove(index);
      endRemoveRows();
    }
    else
    {
      int index = Storage::instance().topOfTaskTree().indexOf(t);
      beginRemoveRows(QModelIndex(), index, index);
      Storage::instance().topOfTaskTree().remove(index);
      endRemoveRows();
    }

    // Load dragged task again because beginRemoveRows() will cause indexChanged() and it will cause Task::unloadContent()
    t->loadContent();

    // Attach to new parent
    if (parent.isValid())
    {
      PTask parentTask = getTask(parent);
      if (parentTask)
      {
        // Make task as child
        int currentRow = (row == -1) ? parentTask->children().size() : (row + rows - 1);

        beginInsertRows(parent, currentRow, currentRow);
        // Update hierarchy in memory - no need as Storage::moveTask() does it
        // parentTask->children().insert(currentRow, t);

        // Update hierarchy in file & memory
        if (!Storage::instance().moveTask(t, parentTask, currentRow))
          qDebug("failed to move task");

        endInsertRows();

      }
    }
    else
    {
      // Make it root item
      int currentRow = (row == -1) ? Storage::instance().topOfTaskTree().size() : (row + rows - 1);

      beginInsertRows(QModelIndex(), currentRow, currentRow);

      // Update hierarchy in file & memory
      if (!Storage::instance().moveTask(t, PTask(), currentRow))
        qDebug("failed to move task");

      endInsertRows();
    }*/
  }
  if (lastMovedTask)
    emit onTaskMoved(lastMovedTask);

  return true;
}

bool TaskTreeModel::canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const
{
  //qDebug() << "TaskTreeModel::canDropMimeData() called";
  return true;
}

bool TaskTreeModel::removeRows(int row, int count, const QModelIndex &parent)
{
  beginRemoveRows(parent, row, row+count-1);
  endRemoveRows();
  return true;

  // Called during drag and drop
  if (parent.isValid())
  {
    PTask parentTask = getTask(parent);
    for (int i=0; i<count; i++)
    {
      TaskArray& children = parentTask->children();
      if (children.size() > row)
      {
        beginRemoveRows(parent, row, row);
        children.erase(children.begin() + row);
        endRemoveRows();
      }
    }
  }
  else
  {
    TaskArray& top = Storage::instance().topOfTaskTree();
    for (int i=0; i<count; i++)
    {
      if (top.size() > row)
      {
        beginRemoveRows(parent, row, row);
        top.erase(top.begin() + row);
        endRemoveRows();
      }
    }
  }

  return true;
}

bool TaskTreeModel::insertRows(int /*row*/, int /*count*/, const QModelIndex& /*parent*/)
{
  qDebug("insertRows called");
  return false;
}

QString TaskTreeModel::getExpandedState(QTreeView& view) const
{
  // Iterate all indexes
  QStringList sl;
  foreach (QModelIndex index, this->persistentIndexList())
  {
    if (view.isExpanded(index))
    {
      PTask t = getTask(index);
      if (t)
        sl << QString::number(t->id());
    }
  }
  return sl.join(";");
}

void TaskTreeModel::setExpandedState(const QString& savedState, QTreeView& view)
{
  QStringList sl = savedState.split(";");
  foreach (QString item, sl)
  {
    qulonglong id = item.toLongLong();
    PTask task = Storage::instance().findTaskById((Task::Id)id);
    if (task)
    {
      QModelIndex index = this->getIndex(task);
      if (index.isValid())
        view.setExpanded(index, true);
    }
  }
}

QString TaskTreeModel::getSelected(QTreeView& view) const
{
  QModelIndex index = view.currentIndex();
  if (index.isValid())
  {
    PTask t = getTask(index);
    if (t)
      return QString::number((qulonglong)t->id());
  }
  return QString();
}

void TaskTreeModel::setSelected(const QString& savedState, QTreeView& view)
{
  qulonglong id = savedState.toULongLong();
  PTask t = Storage::instance().findTaskById(id);
  if (t)
  {
    QModelIndex index = getIndex(t);
    if (index.isValid())
      view.setCurrentIndex(index);
  }
}

/*
QMenu* TaskTreeModel::buildMenuTree(bool trackableOnly)
{
  QMenu* topMenu = new QMenu();
  internalBuildMenuTree(topMenu, Storage::instance().topOfTaskTree(), trackableOnly);
}

void TaskTreeModel::internalBuildMenuTree(QMenu* menu, TaskArray& children, bool trackableOnly)
{
  for (PTask t: children)
  {
    if (t->flags() & Task::Flag_NoTimeTracking)
      continue;
    QAction* action = menu->addAction(t->title());
    action->setData(t->id());
  }
}
*/

// ----------------- TaskItemDelegate ----------------------
TaskItemDelegate::TaskItemDelegate(QObject *parent)
    : QItemDelegate(parent)
{
}

void TaskItemDelegate::paint( QPainter * painter,
            const QStyleOptionViewItem & option,
            const QModelIndex & index ) const
{
    TaskTreeModel* model = (TaskTreeModel*)index.model();
    PTask task = model->getTask(index);
    if (!task)
      return;

    if (task->getAttachmentCount())
    {
      QIcon attachmentIcon = QIcon(":/icons/icons/mail-attachment.png");
      QPixmap attachmentPixmap = attachmentIcon.pixmap(option.decorationSize);
      QRect r = option.rect;
      QRect titleRect = r; titleRect.setWidth(r.width() - 24);
      QRect iconRect = r; iconRect.setLeft(r.right() - 24 );
      drawBackground(painter, option, index);
      drawDisplay(painter, option, titleRect, task->title());
      drawDecoration(painter, option, iconRect, attachmentPixmap);
      drawFocus(painter, option, r);
    }
    else
    {
      drawBackground(painter, option, index);
      drawDisplay(painter, option, option.rect, task->title());
      drawFocus(painter, option, option.rect);
    }
}

/*QSize TaskItemDelegate::sizeHint ( const QStyleOptionViewItem& option, const QModelIndex & index ) const
{
  return option.rect.size();
}*/

void TaskItemDelegate::updateEditorGeometry ( QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex& /*index*/ ) const
{
  editor->setGeometry(option.rect);
}

QRect TaskItemDelegate::calcDecorationRect(QRect mainRect, int horizontalAlignment, int verticalAlignment) const
{
    QRect rect;

    if(horizontalAlignment == Qt::AlignLeft)
    {
        if(verticalAlignment == Qt::AlignTop)
        {
            rect.setX(mainRect.x()+2);
            rect.setY(mainRect.y()+2);
            rect.setWidth(mainRect.width()/8);
            rect.setHeight((mainRect.height()/3)*2);
        }
//        else if(verticalAlignment == Qt::AlignBottom)
//        {
//            rect.setX(mainRect.x()+ 2);
//            rect.setY(mainRect.y()+ (mainRect.height()/3)*2 - 2);
//            rect.setWidth(mainRect.width()/8);
//            rect.setHeight(mainRect.height()/3);
//        }
    }
    if(horizontalAlignment == Qt::AlignRight)
    {
        if(verticalAlignment == Qt::AlignTop)
        {
            rect.setX(mainRect.x() + (mainRect.width()/8)*7 - 2);
            rect.setY(mainRect.y() + 2);
            rect.setWidth(mainRect.width()/8);
            rect.setHeight(mainRect.height()/3);
        }
        else if(verticalAlignment == Qt::AlignBottom)
        {
            rect.setX(mainRect.x() + (mainRect.width()/8)*7 - 2);
            rect.setY(mainRect.y()+ (mainRect.height()/3)*2 - 2);
            rect.setWidth(mainRect.width()/8);
            rect.setHeight(mainRect.height()/3);
        }
    }
    return rect;
}

QRect TaskItemDelegate::calcDisplayRect(QRect mainRect, int verticalAlignment) const
{
    QRect rect;
    if(verticalAlignment == Qt::AlignTop)
    {
        rect.setX(mainRect.x() + mainRect.width()/8 + 3 );
        rect.setY(mainRect.y() + 2);
        rect.setHeight(mainRect.height()/2 - 2);
        rect.setWidth(mainRect.width() - 2*(mainRect.width()/8));
    }
    else if(verticalAlignment == Qt::AlignBottom)
    {
        rect.setX(mainRect.x() + mainRect.width()/8 + 3 );
        rect.setY(mainRect.y() + 2 + mainRect.height()/2);
        rect.setHeight(mainRect.height()/2 - 2);
        rect.setWidth(mainRect.width() - 2*(mainRect.width()/8));
    }
    return rect;
}
