#include "finddialog.h"
#include "ui_finddialog.h"

FindInTasksDialog::FindInTasksDialog(QWidget *parent) :
  QDialog(parent, Qt::Sheet),
  ui(new Ui::FindDialog)
{
  int typeId = qRegisterMetaType<FindResultItem>("FindResultItem");
  ui->setupUi(this);
  mModel = new FindResultsModel(this);
  ui->mResultList->setModel(mModel);
  mSearchHelper.moveToThread(&mSearchHelper);

  connect(ui->mSearchButton, SIGNAL(clicked()), this, SLOT(startSearch()));
  connect(ui->mQueryText, SIGNAL(returnPressed()), this, SLOT(startSearch()));
  connect(&mSearchHelper, SIGNAL(newResultAvailable(FindResultItem)), this, SLOT(onNewResult(FindResultItem)));
  connect(&mSearchHelper, SIGNAL(searchComplete()), this, SLOT(searchComplete()));
  connect(ui->mResultList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(resultSelected(QModelIndex)));
  connect(ui->mResultList, SIGNAL(activated(QModelIndex)), this, SLOT(resultSelected(QModelIndex)));
}

FindInTasksDialog::~FindInTasksDialog()
{
  delete ui;
}

FindResultItem& FindInTasksDialog::getResult()
{
  return mResult;
}

void FindInTasksDialog::startSearch()
{
  if (ui->mSearchButton->text() == tr("Stop"))
  {
    // Stop possible previous search
    mSearchHelper.stop();

    // Enable query edit again
    ui->mQueryText->setEnabled(true);
  }
  else
  {
    if (ui->mQueryText->text().isEmpty())
      return;

    // Stop possible previous search
    mSearchHelper.stop();

    // Clear from old results
    mModel->clear();

    ui->mSearchButton->setText(tr("Stop"));
    ui->mQueryText->setEnabled(false);
    // Start new search
    mSearchHelper.start(ui->mQueryText->text());
  }
}

void FindInTasksDialog::resultSelected(const QModelIndex& index)
{
  if (!index.isValid())
    return;

  mResult = mModel->getItem(index.row());
  accept();
  close();
}

void FindInTasksDialog::onNewResult(const FindResultItem &item)
{
  // Add new item to list
  mModel->addItem(item);

  // Move focus to list
  ui->mResultList->setFocus();
  if (mModel->rowCount() == 1)
  {
    ui->mResultList->selectRow(0);
  }
}

void FindInTasksDialog::searchComplete()
{
  // Sort found results by occurence count
  ui->mSearchButton->setText(tr("Search"));
  ui->mQueryText->setEnabled(true);
}
