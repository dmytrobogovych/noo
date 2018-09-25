#ifndef TASKTREEMODEL_H
#define TASKTREEMODEL_H

#include <QAbstractItemModel>
#include <QStyleOptionViewItem>
#include <QItemDelegate>
#include <QTreeView>
#include <QMenu>

#include "storage.h"

class TaskTreeView: public QTreeView
{
public:
  TaskTreeView(QWidget* widget = nullptr);
  void dragMoveEvent(QDragMoveEvent* event);
  void dragEnterEvent(QDragEnterEvent *event);
  void dragLeaveEvent(QDragLeaveEvent* event);
  void dropEvent(QDropEvent* event);
};

class TaskTreeModel: public QAbstractItemModel
{
  Q_OBJECT
  friend class TaskAction;
  friend class NewTaskAction;
  friend class DeleteTaskAction;
  friend class RenameTaskAction;
  friend class MoveTaskAction;

public:
  TaskTreeModel(bool allowCheckboxes);
  ~TaskTreeModel();

  QModelIndex index(int row, int column, const QModelIndex &parent) const;
  QModelIndex parent(const QModelIndex &child) const;
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role /* = Qt::EditRole */);
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const;
  Qt::DropActions supportedDropActions() const;
  Qt::DropActions supportedDragActions() const;
  QStringList mimeTypes() const;
  QMimeData* mimeData(const QModelIndexList &indexes) const;
  bool dropMimeData(const QMimeData *mimeData, Qt::DropAction action, int row, int column, const QModelIndex &parent);
  bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const;

  bool removeRows(int row, int count, const QModelIndex &parent);
  bool insertRows(int row, int count, const QModelIndex &parent);

  QModelIndex getIndex(const PTask& task, bool includeModelId = true);
  PTask addTask(const QModelIndex& parent, int index);
  void deleteTask(const QModelIndex& index);
  void moveTask(const PTask& task, int offset);

  PTask getTask(const QModelIndex& index) const;
  
  void setTitle(const QModelIndex& index, const QString& title);

  QString getExpandedState(QTreeView& view) const;
  void setExpandedState(const QString& savedState, QTreeView& view);
  QString getSelected(QTreeView& view) const;
  void setSelected(const QString& savedState, QTreeView& view);
  //QMenu* buildMenuTree(bool trackableOnly = true);

signals:
  void onTaskMoved(PTask t);

protected:
  bool mAllowCheckboxes;

  // Returns bottom right index
  QModelIndex makeTaskChecked(QModelIndex index, bool checked);
};

class TaskItemDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    TaskItemDelegate(QObject *parent = 0);

    void paint( QPainter * painter,
                const QStyleOptionViewItem & option,
                const QModelIndex & index ) const;
//    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    void updateEditorGeometry ( QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    QRect calcDecorationRect(QRect rect, int horizontalAlignment, int verticalAlignment ) const;
    QRect calcDisplayRect(QRect rect, int horizontalAlignment) const;
};

#endif // TASKTREEMODEL_H
