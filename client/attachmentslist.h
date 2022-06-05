#ifndef ATTACHMENTSLIST_H
#define ATTACHMENTSLIST_H

#include <QWidget>
#include <QAbstractListModel>
#include <QFileIconProvider>

#include "task.h"
#include "taskaction.h"

namespace Ui {
class AttachmentsList;
}

class AttachmentsListModel: public QAbstractListModel
{
  Q_OBJECT

public:
  explicit AttachmentsListModel(PTask task, ChangesHistory& history, const AttachmentArray& items, QObject* parent = 0);
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role /* = Qt::EditRole */);

  void addItem(PAttachment att, int index = -1);
  void removeItem(int row);
  PAttachment itemAt(int row) const;
  int findRow(PAttachment att) const;

protected:
  PTask mTask;
  ChangesHistory& mHistory;
  AttachmentArray mData;
  QFileIconProvider mIconProvider;
};

class AttachmentsList : public QWidget
{
  Q_OBJECT

public:
  explicit AttachmentsList(QWidget *parent = 0);
  ~AttachmentsList();
  void setTask(const PTask& task);
  PTask task() const;
  void setParentWidget(QWidget* w);

private:
  Ui::AttachmentsList *ui;
  PTask mTask;
  QWidget* mParentWidget;
  AttachmentsListModel* mModel;
  ChangesHistory mHistory;

  void updateActionsState();
public slots:
  void contextualMenu(const QPoint& point);
  void importFile();
  void exportFile();
  void deleteFile();
  void renameFile();
};

#endif // ATTACHMENTSLIST_H
