#include "browserwidget.h"
#include "ui_browserwidget.h"

BrowserWidget::BrowserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BrowserWidget)
{
    ui->setupUi(this);
}

BrowserWidget::~BrowserWidget()
{
    delete ui;
}

void BrowserWidget::newRootTask()
{
    PTask rootTask = mTaskTreeModel->addTask(QModelIndex(), Storage::instance().topOfTaskTree().size());
    QModelIndex rootIndex = mTaskTreeModel->getIndex(rootTask);
    ui->mTaskTree->setCurrentIndex(rootIndex);
    ui->mTaskTree->edit(rootIndex);
}

void BrowserWidget::newTask()
{
    QModelIndex index = ui->mTaskTree->currentIndex();
    if (index.isValid())
        ui->mTaskTree->expand(index);
    PTask parent = mTaskTreeModel->getTask(index);
    if (!parent)
        return;

    PTask child = mTaskTreeModel->addTask(index, parent->children().size());
    if (!child)
        return;

    QModelIndex childIndex = mTaskTreeModel->getIndex(child);
    ui->mTaskTree->setCurrentIndex(childIndex);
    ui->mTaskTree->edit(childIndex);
}

void BrowserWidget::newSibling()
{
    QModelIndex index = ui->mTaskTree->currentIndex();
    if (!index.isValid())
        return;
    PTask currentTask = mTaskTreeModel->getTask(index);
    if (!currentTask)
        return;

    PTask t = mTaskTreeModel->addTask(index.parent(), index.row() + 1);
    QModelIndex i = mTaskTreeModel->getIndex(t);

    ui->mTaskTree->setCurrentIndex(i);
    ui->mTaskTree->edit(i);
}

void BrowserWidget::moveUp()
{
    QModelIndex index = ui->mTaskTree->currentIndex();
    if (!index.isValid())
        return;

    PTask currentTask = mTaskTreeModel->getTask(index);
    if (!currentTask)
        return;

    if (index.row() == 0)
        return;

    mTaskTreeModel->moveTask(currentTask, -1);
    ui->mTaskTree->setCurrentIndex(mTaskTreeModel->getIndex(currentTask));
}

void BrowserWidget::moveDown()
{
    QModelIndex index = ui->mTaskTree->currentIndex();
    if (!index.isValid())
        return;

    PTask currentTask = mTaskTreeModel->getTask(index);
    if (!currentTask)
        return;

    if (currentTask->parent())
    {
        if (index.row() == currentTask->parent()->children().size() - 1)
            return;
    }
    else
        if (index.row() == Storage::instance().topOfTaskTree().size() - 1)
            return;

    mTaskTreeModel->moveTask(currentTask, +1);
    ui->mTaskTree->setCurrentIndex(mTaskTreeModel->getIndex(currentTask));
}

void BrowserWidget::renameTask()
{
    QModelIndex index = ui->mTaskTree->currentIndex();
    if (index.isValid())
        ui->mTaskTree->edit(index);
}

void BrowserWidget::deleteTask()
{
    QModelIndex index = ui->mTaskTree->currentIndex();
    if (!index.isValid())
        return;

    PTask t = mTaskTreeModel->getTask(index);
    if (!t)
        return;

    // Check if deleted task
    if (mCurrentTask == t)
    {
        alertBox(tr("Problem"), tr("Impossible to delete active task. Please stop tracking before task delete."), AlertType_Warning);
    }
    else
    {
        if (mSettings->data()[KEY_ASK_BEFORE_DELETE].toBool())
        {
            auto reply = QMessageBox::question(this,
                                               tr("Are you sure?"),
                                               tr("Are you sure you want to delete ") + t->title(),
                                               QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::No)
                return;
        }

        if (mAutomaticTask == t)
            mAutomaticTask.reset();

        mTaskTreeModel->deleteTask(ui->mTaskTree->currentIndex());
    }
}
