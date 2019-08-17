#ifndef BROWSERWIDGET_H
#define BROWSERWIDGET_H

#include <QWidget>

#include "task.h"
#include "settings.h"

namespace Ui {
class BrowserWidget;
}

class TaskTreeModel;
class QMessageBox;

class BrowserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BrowserWidget(QWidget *parent = 0);
    ~BrowserWidget();

private:
    Ui::BrowserWidget *ui;
    TaskTreeModel* mTaskTreeModel = nullptr;
    PTask mCurrentTask, mAutomaticTask;
    QSharedPointer<Settings> mSettings;
    QMessageBox* mAlertBox = nullptr;

    enum AlertType
    {
        AlertType_Warning,
        AlertType_Critical,
        AlertType_CannotOpen
    };
    void alertBox(const QString &title, const QString &text, AlertType alertType);

public slots:
    // Called when new root task has to be created. It will create both task in DB and UI.
    void onNewRootTask();

    // Called when new task has to be created.
    void onNewTask();

    // Called when new sibling is requested.
    void onNewSibling();

    // Called when node is moved up
    void onMoveUp();

    // Called when node is moved down
    void onMoveDown();

    // Called when node is to be renamed
    void onRenameTask();

    // Called when node has to be deleted
    void onDeleteTask();
};

#endif // BROWSERWIDGET_H
