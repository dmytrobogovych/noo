#include "attachmentslist.h"
#include "ui_attachmentslist.h"
#include "storage.h"
#include "taskaction.h"

#include <QMenu>
#include <QFileDialog>

AttachmentsListModel::AttachmentsListModel(PTask task, ChangesHistory& history, const AttachmentArray &items, QObject *parent)
  :QAbstractListModel(parent), mTask(task), mHistory(history), mData(items)
{
}

int AttachmentsListModel::rowCount(const QModelIndex &parent) const
{
  return mData.size();
}

QVariant AttachmentsListModel::data(const QModelIndex& index, int role) const
{
  // Check that the index is valid and within the correct range first:
  if (!index.isValid())
    return QVariant();
  if (index.row() >= mData.size())
    return QVariant();

  if (role == Qt::DisplayRole || role == Qt::EditRole)
  {
    // Only returns something for the roles you support (DisplayRole is a minimum)
    return QVariant(mData.at(index.row())->filename());
  }
  else
  if (role == Qt::DecorationRole)
  {
    QFileInfo fi(mData.at(index.row())->filename());
    QIcon icon = mIconProvider.icon(fi);
    return QVariant(icon);
  }
  else
    return QVariant();
}


Qt::ItemFlags AttachmentsListModel::flags(const QModelIndex &index) const
{
  Qt::ItemFlags result = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;// | Qt::ItemIsDropEnabled;
  //if (index.isValid())
  //  result |= Qt::ItemIsDragEnabled;

  return result;
}

bool AttachmentsListModel::setData(const QModelIndex &index, const QVariant &value, int role /* = Qt::EditRole */)
{
  PAttachment att = itemAt(index.row());
  switch (role)
  {
  case Qt::DisplayRole:
  case Qt::EditRole:
    MAKE_ACTION(new RenameAttachmentAction(mTask, att, value.toString()));
    break;
  }
  return true;
}

void AttachmentsListModel::addItem(PAttachment att, int index)
{
  if (index == -1)
  {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    mData.push_back(att);
    endInsertRows();
  }
  else
  {
    beginInsertRows(QModelIndex(), index, index);
    mData.insert(mData.begin() + index, att);
    endInsertRows();
  }
}

void AttachmentsListModel::removeItem(int row)
{
  beginRemoveRows(QModelIndex(), row, row);
  mData.erase(mData.begin() + row);
  endRemoveRows();
}

PAttachment AttachmentsListModel::itemAt(int row) const
{
  return mData[row];
}

int AttachmentsListModel::findRow(PAttachment att) const
{
  return mData.indexOf(att);
}



AttachmentsList::AttachmentsList(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::AttachmentsList)
{
  ui->setupUi(this);

}

AttachmentsList::~AttachmentsList()
{
  delete ui;
}

void AttachmentsList::setTask(PTask task)
{
  mTask = task;
  AttachmentArray aa;
  Storage::instance().loadAttachments(mTask, aa);

  // Create model
  mModel = new AttachmentsListModel(mTask, mHistory, aa);

  // Set model to history
  mHistory.setAttachmentsModel(mModel);

  // Set model to list view
  ui->mListView->setModel(mModel);
}

void AttachmentsList::setParentWidget(QWidget *w)
{
  mParentWidget = w;
}

void AttachmentsList::updateActionsState()
{
  bool hasSelectedItem = ui->mListView->currentIndex().isValid();
  ui->mRenameAction->setEnabled(hasSelectedItem);
  ui->mDeleteAction->setEnabled(hasSelectedItem);
  ui->mExportAction->setEnabled(hasSelectedItem);
}

void AttachmentsList::contextualMenu(const QPoint& point)
{
  updateActionsState();

  QMenu* menu = new QMenu();
  menu->addAction(ui->mRenameAction);
  menu->addAction(ui->mDeleteAction);
  menu->addAction(ui->mExportAction);
  menu->addAction(ui->mImportAction);

  //menu->addAction(tr("Add 10 mins to timeline"), this, SLOT(add10Mins()));
  menu->exec(this->window()->mapToGlobal(point));
}

void AttachmentsList::importFile()
{
  // Prepare file open dialog
  QFileDialog dlg(mParentWidget, Qt::Sheet);
  dlg.setWindowTitle(tr("Select file(s) for import"));
  dlg.setAcceptDrops(false);
  dlg.setAcceptMode(QFileDialog::AcceptOpen);
  dlg.setFileMode(QFileDialog::ExistingFiles);
  if (!dlg.exec())
    return;

  // Iterate selected files
  QStringList files = dlg.selectedFiles();
  for (QString filename: files)
  {
    QFile f(filename);
    f.open(QFile::ReadOnly);
    if (f.isOpen())
    {
      // Get data from file
      QByteArray content = f.readAll();

      // Compress them
      QByteArray compressed = qCompress(content);

      // Put it to Attachment instance
      PAttachment att(new Attachment());
      att->setTaskId(mTask->id());
      att->setIndex(mModel->rowCount());
      QFileInfo fi(filename);
      att->setFilename(fi.fileName());

      // Save everything
      att->save();
      att->saveContent(compressed);

      mModel->addItem(att);
    }
    f.close();
  }

  // Refresh hasAttachments property on owner task
  mTask->checkAttachments();
}

void AttachmentsList::exportFile()
{
  QModelIndexList mil = ui->mListView->selectionModel()->selectedIndexes();
  foreach (const QModelIndex& index, mil)
  {
    if (!index.isValid())
      continue;

    QFileDialog dlg(mParentWidget, Qt::Sheet);
    dlg.setWindowTitle(tr("Select file(s) for export"));
    dlg.setAcceptDrops(false);
    dlg.setAcceptMode(QFileDialog::AcceptSave);
    PAttachment att = mModel->itemAt(index.row());
    dlg.selectFile(att->filename());
    if (!dlg.exec())
      continue;

    QFile outputFile(dlg.selectedFiles().front());
    outputFile.open(QFile::WriteOnly);
    outputFile.write(qUncompress(att->loadContent()));
    outputFile.close();
  }
}

void AttachmentsList::deleteFile()
{
  QModelIndexList mil = ui->mListView->selectionModel()->selectedIndexes();
  foreach (const QModelIndex& index, mil)
  {
    if (!index.isValid())
      continue;
    PAttachment att = mModel->itemAt(index.row());

    // Remove from DB
    Storage::instance().deleteAttachment(att);

    // Remove from model
    mModel->removeItem(index.row());

    // Iterate other items and decrease their DB table's orderid field
    for (int row = index.row() + 1; row < mModel->rowCount(); row++)
    {
      Attachment& att = *mModel->itemAt(row);
      att.setIndex(att.index() - 1);
      att.save();
    }
  }

  // Refresh hasAttachment property value on task
  mTask->checkAttachments();
}

void AttachmentsList::renameFile()
{
  QModelIndex index = ui->mListView->currentIndex();
  if (index.isValid())
    ui->mListView->edit(index);
}
