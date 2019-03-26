#include "config.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tasktreemodel.h"
#include "timetreemodel.h"
#include "helper.h"
#include "newpassworddlg.h"
#include "passworddlg.h"
#include <QSettings>
#include <QPrinter>
#include <QPrintDialog>
#include <QMessageBox>
#include <QDir>
#include <QCloseEvent>
#include <QDesktopServices>

#include "appevents.h"
#include "preferencesdlg.h"
#include "timetreedlg.h"
#include "timereportwizard.h"
#include "aboutdlg.h"
#include "attachmentslist.h"
#include "attachmentsdialog.h"
#include "fvupdater.h"
#include "taskaction.h"
#include "finddialog.h"
#include "startworkdialog.h"
#include "stopworkdialog.h"
#include <QDesktopWidget>

#define SETTINGS mSettings->data()

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), mPasswordFailed(false), mFindInTasksDlg(this), mDockRecentMenu(nullptr)
{
    mSettings = QSharedPointer<Settings>(new Settings());

    helper::theme::applyCurrent(*mSettings);

    mAttachmentsAction = nullptr;
    mAttachmentsLabel = nullptr;

    this->setUpdatesEnabled(false);

    mDuplicationSignalLabel = nullptr;
    mCurrentIntervalLabel = nullptr;
    mTrayIcon = nullptr;

    ui->setupUi(this);

    // Hide Find line edit for now
    ui->mFindFrame->setVisible(false);
    helper::EscapeKeyEventFilter* eventFilter = new helper::EscapeKeyEventFilter(ui->mFindEdit);
    connect(eventFilter, SIGNAL(escapePressed(QObject*)), this, SLOT(findRejected(QObject*)));
    ui->mFindEdit->installEventFilter(eventFilter);

    QCoreApplication::setApplicationName(APPNAME);
    //QCoreApplication::setOrganizationName(COMPANY);
    // Set this to your own appcast URL, of course
    FvUpdater::sharedUpdater()->SetFeedURL("http://satorilight.com/LittAppCast.xml");

    initClient();
    QApplication::postEvent(this, new AttachDatabaseEvent());
}

MainWindow::~MainWindow()
{
    delete ui;
    //delete mCurrentIntervalLabel;
}


void MainWindow::attachDatabase()
{
    // Open database
    QString path = helper::path::pathToDatabase();
    if (mSettings->data()[KEY_DB_FILENAME_SPECIFIED].toBool())
        path = mSettings->data()[KEY_DB_FILENAME].toString();

    QString folder = QFileInfo(path).absoluteDir().path();
    Storage::instance().setPath(path);

    if (!QFile::exists(path))
    {
        QDir().mkpath(folder);

        // Ask about new password
        mNewPasswordDlg = new NewPasswordDlg(this);
        connect(mNewPasswordDlg, SIGNAL(finished(int)), this, SLOT(newPasswordDialogFinished(int)));
        mNewPasswordDlg->show();
    }
    else
    {
        // See if there is stored password
        QString password;
        if (mSettings->data()[KEY_AUTOSAVE_PASSWORD].toBool() && mSettings->data()[KEY_PASSWORD].toString() != NOPASSWORDSTRING)
            password = mSettings->data()[KEY_PASSWORD].toString();
        else
        {
            mPasswordDlg = new PasswordDlg(this);
            connect(mPasswordDlg, SIGNAL(finished(int)), this, SLOT(passwordDialogFinished(int)));
            mPasswordDlg->show();
        }
    }
    this->setUpdatesEnabled(true);
}

void MainWindow::openDatabase(const QString &password)
{
    Storage::instance().setKey(password);
    if (!Storage::instance().open())
    {
        mPasswordFailed = true;
        alertBox(tr("Error"), tr("Failed to open database"), AlertType_CannotOpen);
    }
    else
        if (mSettings->data()[KEY_AUTOSAVE_PASSWORD].toBool())
        {
            mSettings->data()[KEY_PASSWORD] = password;
            mSettings->save();
        }
}

void MainWindow::connectUiToDatabase()
{
    ui->mTaskTree->setModel(mTaskTreeModel = new TaskTreeModel(false));
    ui->mTaskTree->setItemDelegate(&mTaskItemDelegate);
    connect(mTaskTreeModel, SIGNAL(onTaskMoved(PTask)), this, SLOT(taskMoved(PTask)));

    ChangesHistory::instance().setTaskTreeModel(mTaskTreeModel);

    connect(ui->mTaskTree->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), SLOT(taskIndexChanged(QModelIndex,QModelIndex)));
    mUpdateTimer = new QTimer(this);
    connect(mUpdateTimer, SIGNAL(timeout()), SLOT(updateData()));
    mUpdateTimer->setInterval(1000);
    mUpdateTimer->setSingleShot(false);
    mUpdateTimer->start();

    connect(this, SIGNAL(onTimeFormatChanged()), this, SLOT(timeFormatChanged()));
    connect(this, SIGNAL(onTimeChanged()), this, SLOT(timeFormatChanged()));

    if (mTaskTreeModel->hasChildren())
        ui->mTaskTree->setCurrentIndex(mTaskTreeModel->index(0,0, QModelIndex()));

    mTaskTreeModel->setExpandedState(mSettings->data()[KEY_EXPANDED_TASKS].toString(), *ui->mTaskTree);
    mTaskTreeModel->setSelected(mSettings->data()[KEY_SELECTED_TASKS].toString(), *ui->mTaskTree);

    // Load recent tasks
    QString recent = mSettings->data()[KEY_RECENT_TASKS].toString();
    QStringList recentList = recent.split(";", QString::SkipEmptyParts);
    for (QString& s: recentList)
    {
        Task::Id id = s.toULongLong();
        PTask t = Storage::instance().findTaskById(id);
        if (t)
            mRecentTrackingTasks.push_back(t);
    }
    prepareRecentTasksMenu(ui->mStartRecentTaskMenu);
    if (mDockRecentMenu)
        prepareRecentTasksMenu(mDockRecentMenu);
}

void MainWindow::alertBox(const QString &title, const QString &text, AlertType alertType)
{
    mAlertBox = new QMessageBox(alertType == AlertType_Critical ? QMessageBox::Critical : QMessageBox::Warning,
                                title, text, QMessageBox::Ok, this,
                                Qt::Sheet);
    switch (alertType)
    {
    case AlertType_Critical:
        connect(mAlertBox, SIGNAL(finished(int)), this, SLOT(criticalAlertFinished(int)));
        break;

    case AlertType_CannotOpen:
        connect(mAlertBox, SIGNAL(finished(int)), this, SLOT(openAlertFinished(int)));
        break;

    case AlertType_Warning:
        connect(mAlertBox, SIGNAL(finished(int)), this, SLOT(warningAlertFinished(int)));
        break;
    }

    mAlertBox->show();
}

void MainWindow::initClient()
{
    mFindStartIndex = 0;

    // Open settings
    mLogger = QSharedPointer<Logger>(new Logger());

    ui->mAboutAction->setMenuRole(QAction::AboutRole);
    ui->mExitAction->setMenuRole(QAction::QuitRole);
    ui->mPreferencesAction->setMenuRole(QAction::PreferencesRole);

    connect(ui->mAboutAction, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->mPreferencesAction, SIGNAL(triggered()), this, SLOT(preferences()));

    // Add Check for update to OS X application menu
    ui->mCheckForUpdatesAction->setMenuRole(QAction::ApplicationSpecificRole);

    // Build tray icon if system support this one
    if (QSystemTrayIcon::isSystemTrayAvailable() && mSettings->data()[KEY_SHOW_TRAY_ICON].toBool())
        initTrayIcon();

    loadGeometry();

    ui->mTaskTree->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->mTaskTree->setFocus();
    ui->mTaskTree->setDragEnabled(true);
    ui->mTaskTree->setAcceptDrops(true);
    ui->mTaskTree->setDropIndicatorShown(true);
    ui->mTaskTree->setDragDropMode(QAbstractItemView::InternalMove);
    ui->mTaskTree->setAttribute(Qt::WA_MacShowFocusRect, false);
    mCurrentIntervalLabel = new QLabel();
    ui->mStatusBar->addPermanentWidget(mCurrentIntervalLabel);

    mDuplicationSignalLabel = new QLabel();
    ui->mStatusBar->addPermanentWidget(mDuplicationSignalLabel);

    mModifiedLabel = new QLabel();
    ui->mStatusBar->addPermanentWidget(mModifiedLabel);

    mActivityTracker = QSharedPointer<HIDActivityTracker>(new HIDActivityTracker());
    connect(mActivityTracker.data(), SIGNAL(idleDetected()), this, SLOT(idleDetected()));
    connect(mActivityTracker.data(), SIGNAL(activityDetected()), this, SLOT(activityDetected()));

    // Configure toolbar
    connect(ui->mMainToolbar, SIGNAL(visibilityChanged(bool)), this, SLOT(toolbarVisibilityChanged(bool)));
    QWidget *spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacerWidget->setVisible(true);
    ui->mMainToolbar->addWidget(spacerWidget);

    mAttachmentsAction = new QAction(this);
    mAttachmentsAction->setIcon(QIcon(":/icons/icons/mail-attachment.png"));
    mAttachmentsAction->setText(tr("Attachments"));
    //ui->mMainToolbar->addAction(mAttachmentsAction);
    connect(mAttachmentsAction, SIGNAL(triggered()), this, SLOT(showAttachments()));

    mAttachmentsLabel = new QLabel(this);
    mAttachmentsLabel->setMargin(5);
    mAttachmentsLabel->setOpenExternalLinks(false);
    QFont f = mAttachmentsLabel->font();
    f.setUnderline(true);
    mAttachmentsLabel->setFont(f);
    mAttachmentsLabel->setTextFormat(Qt::RichText);
    //mAttachmentsLabel->setStyleSheet("QLabel { color:rgb(142,178,218); }");

    QPalette newPal(palette());
    newPal.setColor(QPalette::Link, QColor(0x100, 0x100, 0x100));
    newPal.setColor(QPalette::LinkVisited, QColor(0x100, 0x100, 0x100));
    mAttachmentsLabel->setPalette(newPal);

    ui->mMainToolbar->addWidget(mAttachmentsLabel);
    connect(mAttachmentsLabel, SIGNAL(linkActivated(QString)), this, SLOT(showAttachments()));
    updateAttachmentsLabel(PTask());

#ifdef TARGET_OSX
    mSleepTracker.install();
    connect(&mSleepTracker, SIGNAL(onSystemSleep()), this, SLOT(systemSleep()));
    connect(&mSleepTracker, SIGNAL(onSystemResume()), this, SLOT(systemResume()));
    installDockMenu();
#endif
    mTimeFrameHeight = 64;//ui->mTimeFrame->height();
    ui->mStartRecentTaskMenu->setEnabled(false);
}

void MainWindow::save()
{
    // Flush current task
    PTask t = mTaskTreeModel->getTask(ui->mTaskTree->currentIndex());
    if (t)
    {
        t->setHtml(ui->mNoteEdit->document()->toPlainText());
        t->save();
        mModifiedLabel->setText(tr("Saved"));
    }

    try
    {
        if (Storage::instance().isOpened())
            Storage::instance().save();
        saveGeometry();
    }
    catch(std::exception& e)
    {}
    catch(...)
    {}
}

QSharedPointer<QByteArray> MainWindow::getUndoStack() const
{
    QTextDocument* doc = ui->mNoteEdit->document();

    return QSharedPointer<QByteArray>(new QByteArray());
}

void MainWindow::saveGeometry()
{
    QRect geom = this->geometry();
    mSettings->data()[KEY_LEFT] = geom.left(); // "left"
    mSettings->data()[KEY_TOP] = geom.top(); // "top"
    mSettings->data()[KEY_WIDTH] = geom.width(); // "width"
    mSettings->data()[KEY_HEIGHT] = geom.height(); // "height"
    mSettings->data()[KEY_MAXIMIZED] = isMaximized(); // "maximized"
    QList<int> sizes = ui->mSplitter->sizes();
    if (!sizes.empty())
    {
        mSettings->data()[KEY_SPLITTEROFFSET1] = sizes[0]; // ("splitter_offset1", sizes[0]);
        mSettings->data()[KEY_SPLITTEROFFSET2] = sizes[1]; //("splitter_offset2", sizes[1]);
    }
    sizes = ui->mTimeSplitter->sizes();
    if (!sizes.empty())
    {
        SETTINGS[KEY_TIMESPLITTER_OFFSET1] = sizes[0];
        SETTINGS[KEY_TIMESPLITTER_OFFSET2] = sizes[1];
    }

    if (mTaskTreeModel)
    {
        mSettings->data()[KEY_EXPANDED_TASKS] = this->mTaskTreeModel->getExpandedState(*ui->mTaskTree);
        mSettings->data()[KEY_SELECTED_TASKS] = this->mTaskTreeModel->getSelected(*ui->mTaskTree);
    }

    // Save recent list
    QString recent;
    for (PTask t: mRecentTrackingTasks)
    {
        recent += QString::number(t->id()) + ";";
    }
    mSettings->data()[KEY_RECENT_TASKS] = recent;
    mSettings->save();
}

void MainWindow::loadGeometry()
{
    QVariantMap& settings = mSettings->data();

    QRect geom = this->geometry();
    if (settings.value(KEY_MAXIMIZED).toBool())
        this->showMaximized();
    else
    {
        if (settings.contains(KEY_LEFT))
            geom.setLeft(settings.value("left").toInt());
        if (settings.contains(KEY_TOP))
            geom.setTop(settings.value("top").toInt());
        if (settings.contains(KEY_WIDTH))
            geom.setWidth(settings.value(KEY_WIDTH).toInt());
        if (settings.contains(KEY_HEIGHT))
            geom.setHeight(settings.value(KEY_HEIGHT).toInt());
        setGeometry(geom);
    }

    // Set splitter position
    if (settings.contains(KEY_SPLITTEROFFSET1) && settings.contains(KEY_SPLITTEROFFSET2))
    {
        QList<int> sizes = ui->mSplitter->sizes();
        sizes[0] = settings.value(KEY_SPLITTEROFFSET1).toInt();
        sizes[1] = settings.value(KEY_SPLITTEROFFSET2).toInt();
        ui->mSplitter->setSizes(sizes);
    }

    if (settings.contains(KEY_TIMESPLITTER_OFFSET1) && settings.contains(KEY_TIMESPLITTER_OFFSET2))
    {
        QList<int> sizes = ui->mTimeSplitter->sizes();
        sizes[0] = settings.value(KEY_TIMESPLITTER_OFFSET1).toInt();
        sizes[1] = settings.value(KEY_TIMESPLITTER_OFFSET2).toInt();
        ui->mTimeSplitter->setSizes(sizes);
    }
}

void MainWindow::sync()
{
    alertBox(APPNAME, NOTIMPLEMENTEDTEXT, AlertType_Warning);
}

void MainWindow::closeEvent(QCloseEvent * ev)
{
    // Update DB if document was modified
    if (ui->mNoteEdit->document()->isModified())
    {
        // See if there is active selection
        QModelIndex index = ui->mTaskTree->currentIndex();
        if (index.isValid())
        {
            PTask task = mTaskTreeModel->getTask(index);
            task->setHtml(ui->mNoteEdit->document()->toPlainText());
            task->save();
        }
    }

    if (!mPasswordFailed)
        save();

    ev->accept();
}

void MainWindow::customEvent(QEvent *ev)
{
    switch (ev->type())
    {
    case (QEvent::Type)ClientInitId:
        // Process client initialization here
        initClient();
        break;

    case (QEvent::Type)ClientCloseId:
        close();
        break;

    case (QEvent::Type)AttachDatabaseId:
        attachDatabase();
        break;

    case (QEvent::Type)SelectTaskId:
    {
        QModelIndex index = mTaskTreeModel->getIndex(dynamic_cast<SelectTaskEvent*>(ev)->task());
        if (index.isValid())
        {
            ui->mTaskTree->setCurrentIndex(index);
        }
        break;
    }
    default:
        break;
    }
}

void MainWindow::preferences()
{
    PreferencesDlg pref(this, *mSettings);

    if (pref.exec() == QDialog::Accepted)
    {
        // Changes are saved into settings already
        // Repaint time labels if no tracking yet
        QModelIndex index = ui->mTaskTree->currentIndex();
        PTask t = mTaskTreeModel->getTask(index);

        // Reset time text where needed
        emit onTimeFormatChanged();

        // Delete autosaved password if needed
        if (mSettings->data()[KEY_AUTOSAVE_PASSWORD].toBool() == false)
        {
            mSettings->data()[KEY_PASSWORD] = NOPASSWORDSTRING;
            mSettings->save();
        }

        // Hide/Show tray icon if need
        if (mSettings->data()[KEY_SHOW_TRAY_ICON].toBool() && !mTrayIcon && QSystemTrayIcon::isSystemTrayAvailable())
            initTrayIcon();
        else
            if (!mSettings->data()[KEY_SHOW_TRAY_ICON].toBool() && mTrayIcon)
                removeTrayIcon();

        updateData();
    }
}

void MainWindow::about()
{
    AboutDlg dlg(this);
    dlg.exec();
}

void MainWindow::quit()
{
    // TODO - check if stop on idle dialog runs now and stop on idle time
    stopTracking(TSR_Manual);

    save();
#ifdef TARGET_OSX
    mSleepTracker.uninstall();
#endif
    close();
}

void MainWindow::newRootTask()
{
    PTask rootTask = mTaskTreeModel->addTask(QModelIndex(), Storage::instance().topOfTaskTree().size());
    QModelIndex rootIndex = mTaskTreeModel->getIndex(rootTask);
    ui->mTaskTree->setCurrentIndex(rootIndex);
    ui->mTaskTree->edit(rootIndex);
}

void MainWindow::newTask()
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

void MainWindow::newSibling()
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

void MainWindow::moveUp()
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

void MainWindow::moveDown()
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

void MainWindow::renameTask()
{
    QModelIndex index = ui->mTaskTree->currentIndex();
    if (index.isValid())
        ui->mTaskTree->edit(index);
}

void MainWindow::deleteTask()
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
        if (mAutomaticTask == t)
            mAutomaticTask.reset();

        mTaskTreeModel->deleteTask(ui->mTaskTree->currentIndex());
    }
}

void MainWindow::taskTreeContextualMenu(const QPoint& point)
{
    PTask t = mTaskTreeModel->getTask(ui->mTaskTree->currentIndex());

    QMenu* menu = new QMenu();
    menu->addAction(ui->mNewRootTaskAction);
    menu->addAction(ui->mNewTaskAction);
    menu->addAction(ui->mRenameTaskAction);
    menu->addAction(ui->mDeleteTaskAction);
    menu->addAction(ui->mMoveUpAction);
    menu->addAction(ui->mMoveDownAction);
    menu->addSeparator();
    menu->addAction(ui->mTimelineAction);
    menu->addAction(mAttachmentsAction);
    menu->addSeparator();
    if (t)
    {
        ui->mTimeTrackableAction->setChecked(!(t->flags() & Task::Flag_NoTimeTracking));
        menu->addAction(ui->mTimeTrackableAction);
    }
    //menu->addAction(tr("Add 10 mins to timeline"), this, SLOT(add10Mins()));
    menu->exec(this->window()->mapToGlobal(point));
}

void MainWindow::taskIndexChanged(const QModelIndex& current, const QModelIndex& previous)
{
    PTask previousTask = mTaskTreeModel->getTask(previous);
    if (previousTask)
    {
        if (ui->mNoteEdit->document()->isModified())
        {
            // Copy modified text to task object
            previousTask->setHtml(ui->mNoteEdit->document()->toPlainText());

            // Flush new content to DB
            previousTask->save();

            // Remember corresponding QTextDocument also
            // task->setUndoStack(ui->mNoteEdit->document()->getUndoStack());
        }

        // Update status bar
        mModifiedLabel->setText(tr("Saved"));

        // Save cursor position
        previousTask->setCursorPosition(ui->mNoteEdit->textCursor().position());

        // Unload content
        previousTask->unloadContent(previousTask != mCurrentTask);
    }

    updateTrayIcon(Tray_SkipMessage);

    PTask t = mTaskTreeModel->getTask(ui->mTaskTree->currentIndex());
    if (!mCurrentTask)
    {
        if (t)
            ui->mStartOrStopTrackingAction->setText(tr("Start tracking ") + t->title());
        else
            ui->mStartOrStopTrackingAction->setText(tr("Start tracking"));
    }

    if (t)
    {
        mAttachmentsAction->setToolTip(tr("Attachments for ") + t->title());
        updateAttachmentsLabel(t);
    }

    if (current.isValid())
    {
        // Reset search position
        mFindStartIndex = 0;

        // Load doc
        PTask task = mTaskTreeModel->getTask(current);
        if (task)
        {
            task->loadContent();

            ui->mNoteEdit->document()->setPlainText(task->html());
            ui->mNoteEdit->document()->setModified(false);

            // Set cursor position to stored one
            if (task->cursorPosition() <= task->html().length())
            {
                QTextCursor tmpCursor = ui->mNoteEdit->textCursor();
                tmpCursor.setPosition(task->cursorPosition());
                ui->mNoteEdit->setTextCursor(tmpCursor);
                ui->mNoteEdit->ensureCursorVisible();
            }

            mModifiedLabel->setText(tr("Saved"));

            // Enable / disable Move up / move down actions
            ui->mMoveUpAction->setEnabled(current.row() > 0);
            if (task->parent())
                ui->mMoveDownAction->setEnabled(current.row() < (task->parent()->children().size() - 1));
            else
                ui->mMoveDownAction->setEnabled(current.row() < (Storage::instance().topOfTaskTree().size() - 1));

        }
        // Load corresponding undo stack
        //ui->mNoteEdit->document()->setUndoStack(task->getUndoStack());

        // Update total time
        emit onTimeChanged();

        // Set new timeline tree model
        /*int w = ui->mTaskTimeTree->columnWidth(0);
    ui->mTaskTimeTree->setModel(new TimeTreeModel(task->timeline(), *mSettings));
    ui->mTaskTimeTree->setColumnWidth(0, w);*/

        // Show or hide time table depending on type of loaded task
        handleTrackableState(task);

        ui->mTaskTree->selectionModel()->setCurrentIndex(current, QItemSelectionModel::SelectCurrent);
    }
}

void MainWindow::idleDetected()
{
    mActivityTracker->acceptIdleState();

    // Check if settings allow smart stop
    if (SETTINGS[KEY_SMART_STOP].toBool() && SETTINGS[KEY_SMART_STOP_MINUTES].toInt() > 0)
    {
        if (SETTINGS[KEY_ASK_STOP].toBool())
        {
            // Stop activity tracker to not be confused with following user activity
            mActivityTracker->stop();

            StopWorkDialog* dlg = new StopWorkDialog();
            connect(dlg, SIGNAL(continueTracking()), this, SLOT(continueOnIdle()));
            connect(dlg, SIGNAL(breakTracking(QDateTime)), this, SLOT(breakOnIdle(QDateTime)));
            showTrayWindow(dlg);
        }
        else
            stopTracking(TSR_Automatic);
    }
}

void MainWindow::activityDetected()
{
    mActivityTracker->acceptUserActiveState();

    // Check if settings allow smart start
    if (SETTINGS[KEY_SMART_START].toBool() && mStopReason == TSR_Automatic)
    {
        /*if (SETTINGS[KEY_ASK_START].toBool())
    {
      StartWorkDialog* dlg = new StartWorkDialog(mAutomaticTask);
      connect(dlg, SIGNAL(continueTracking()), this, SLOT(startOnActivity()));
      connect(dlg, SIGNAL(breakTracking()), this, SLOT(stopOnActivity()));
      showTrayWindow(dlg);
    }
    else*/
        {
            startTracking();
            if (mTrayIcon)
                mTrayIcon->showMessage(tr("Time tracking started"), mCurrentTask->path());
        }
    }
}

void MainWindow::handleTrackableState(PTask task)
{
    if (!task)
        return;

    bool trackable = !(task->flags() & Task::Flag_NoTimeTracking);
    if (!mCurrentTask)
        ui->mStartOrStopTrackingAction->setEnabled(trackable);
    QList<int> sizes;
    if (trackable)
    {
        sizes.push_back(ui->mTimeSplitter->height() - mTimeFrameHeight - ui->mTimeSplitter->handleWidth());
        sizes.push_back(mTimeFrameHeight);
        ui->mTimeSplitter->setHandleWidth(7);
    }
    else
    {
        sizes.push_back(ui->mTimeSplitter->height() - ui->mTimeSplitter->handleWidth());
        sizes.push_back(0);
        ui->mTimeSplitter->setHandleWidth(0);
    }
    ui->mTimeSplitter->setSizes(sizes);
}

void MainWindow::prepareRecentTasksMenu(QMenu* submenu)
{
    submenu->clear();
    submenu->setEnabled(!mRecentTrackingTasks.empty());
    for (PTask t: mRecentTrackingTasks)
    {
        QAction* action = submenu->addAction(t->title(), this, SLOT(startTrackingRecent()));
        action->setProperty("taskid", QVariant(t->id()));
    }
}

void MainWindow::updateAttachmentsLabel(PTask t)
{
    QString text = "<a href=\"localfile\" style=\"color: #3966A0\">" + tr("No attachments") + "</a>";

    if (t)
    {
        if (t->getAttachmentCount())
            text = "<a href=\"localfile\" style=\"color: #3966A0\">" + QString::number(t->getAttachmentCount()) + " " + tr("attachments") + "</a>";
    }
    mAttachmentsLabel->setText(text);
}

void MainWindow::startOrStopTracking()
{
    if (!mCurrentTask)
    {
        // Forget about automatic start - it is manual start
        mAutomaticTask.reset();
        startTracking();
    }
    else
        stopTracking(TSR_Manual);
}

void MainWindow::startTracking(PTask t)
{
    if (t->flags() & Task::Flag_NoTimeTracking)
        return;

    mCurrentTask = t;

    // Tell timeline to start
    if (!t->timeline())
        t->loadContent();

    mCurrentTask->timeline()->start();
    mLastTimelineFlush = QDateTime::currentDateTimeUtc();

    // Update UI
    ui->mStartOrStopTrackingAction->setText(tr("Stop tracking ") + mCurrentTask->title());
    QIcon icon(ACTION_STOP_ICON_NAME);
    ui->mStartOrStopTrackingAction->setIcon(icon);
    updateTrayIcon(Tray_ShowMessage);

    // Start activity tracker if needed
    if (mSettings->data()[KEY_SMART_STOP].toBool() && mSettings->data()[KEY_SMART_STOP_MINUTES].toInt() > 0)
    {
        mActivityTracker->setInterval(mSettings->data()[KEY_SMART_STOP_MINUTES].toInt() * 60);
        mActivityTracker->start();
    }
}

void MainWindow::startTracking()
{
    // Start tracking if any task is selected
    QModelIndex index = ui->mTaskTree->currentIndex();
    if (!index.isValid())
        return;

    // Trigger permission dialog if needed
    if (mSettings->data()[KEY_SMART_STOP].toBool())
    {
        if (!helper::activityTracker::ensureSmartTrackingIsPossible())
            mTrayIcon->showMessage(tr("No smart tracking stop/start"), tr("Problem with obtaining permissions"), QSystemTrayIcon::Warning);
    }

    // Get pointer to tracking task
    PTask t;
    if (mStopReason == TSR_Automatic && mAutomaticTask)
    {
        t = mAutomaticTask;
        mAutomaticTask.reset();
    }
    else
        t = mTaskTreeModel->getTask(index);

    if (t)
        startTracking(t);
}

void MainWindow::startTrackingRecent()
{
    QObject* sender = QObject::sender();
    if (dynamic_cast<QAction*>(sender))
    {
        QVariant taskId = sender->property("taskid");
        if (taskId.isValid() && !taskId.isNull())
        {
            PTask t = Storage::instance().findTaskById(taskId.toULongLong());
            if (t)
            {
                if (mCurrentTask)
                    stopTracking(TSR_Manual);

                startTracking(t);
            }
        }
    }
}

void MainWindow::stopTracking(TrackingStopReason reason, time_t current_utc)
{
    // Check if false call
    if (!mCurrentTask)
        return;

    // Save stop reason
    mStopReason = reason;

    // If stopping due to idle detection - save current task
    if (reason == TSR_Automatic)
        mAutomaticTask = mCurrentTask;


    // Tell current task to stop
    mCurrentTask->timeline()->flush(true /* save to DB */, current_utc);
    mCurrentTask->timeline()->stop(false /* do not update timeline - it is done in the previous line */);

    // Save stopped task name
    QString stoppedTaskName = mCurrentTask->path();

    // Update recent tracking tasks menu
    std::deque<PTask>::iterator taskIter = std::find(mRecentTrackingTasks.begin(), mRecentTrackingTasks.end(), mCurrentTask);
    if (taskIter == mRecentTrackingTasks.end())
    {
        mRecentTrackingTasks.push_front(mCurrentTask);
        if (mRecentTrackingTasks.size() > 7)
            mRecentTrackingTasks.pop_back();
    }
    else
    {
        mRecentTrackingTasks.erase(taskIter);
        mRecentTrackingTasks.push_front(mCurrentTask);
    }

    // Update UI
    prepareRecentTasksMenu(ui->mStartRecentTaskMenu);
    if (mDockRecentMenu)
        prepareRecentTasksMenu(mDockRecentMenu);

    // Reset pointer to current task
    mCurrentTask.clear();

    // Update UI
    PTask t = mTaskTreeModel->getTask(ui->mTaskTree->currentIndex());
    if (t)
        ui->mStartOrStopTrackingAction->setText(tr("Start tracking ") + t->title());
    else
        ui->mStartOrStopTrackingAction->setText(tr("Start tracking"));

    QIcon icon(ACTION_START_ICON_NAME);
    ui->mStartOrStopTrackingAction->setIcon(icon);

    if (mTrayIcon)
    {
        updateTrayIcon(Tray_SkipMessage);

        if (reason == TSR_Automatic)
            mTrayIcon->showMessage(tr("Time tracking stopped due to inactivity."), tr("Idle interval detected for ") + stoppedTaskName);
        else
            mTrayIcon->showMessage(tr("Time tracking stopped"), stoppedTaskName);
    }

    if (mCurrentIntervalLabel)
        mCurrentIntervalLabel->setText("");

    if (reason == TSR_Manual)
        mActivityTracker->stop();

    // Ensure start/stop buttons are enabled or disabled properly
    handleTrackableState(t);
}

void MainWindow::updateData()
{
    // Update editor icons
    bool taskLoaded = ui->mTaskTree->currentIndex().isValid();
    bool hasSelection = ui->mNoteEdit->textCursor().hasSelection();
    bool inEditor = (ui->mNoteEdit->hasFocus());

    bool editCanUndo = ui->mNoteEdit->document()->availableUndoSteps();
    bool editCanRedo = ui->mNoteEdit->document()->availableRedoSteps();

    ui->mUndoEditAction->setEnabled((taskLoaded & inEditor && editCanUndo) || ChangesHistory::instance().canUndo());
    ui->mRedoEditAction->setEnabled((taskLoaded & inEditor && editCanRedo) || ChangesHistory::instance().canRedo());
    ui->mSelectAllEditAction->setEnabled(taskLoaded && inEditor);
    ui->mCutEditAction->setEnabled(hasSelection & taskLoaded && inEditor);
    ui->mPasteEditAction->setEnabled(ui->mNoteEdit->canPaste() & taskLoaded && inEditor);
    ui->mCopyEditAction->setEnabled( hasSelection & taskLoaded && inEditor);

    if (mCurrentTask)
    {
        // Ok, smth is tracking now

        // Save current time on tracking task
        QDateTime current = QDateTime::currentDateTimeUtc();
        bool saveToDb = mLastTimelineFlush.secsTo(current) >= TIMELINE_FLUSH_INTERVAL;

        if (saveToDb)
            mLogger->log("Flushing timeline to DB start");
        mCurrentTask->timeline()->flush(saveToDb, QDateTime::currentDateTimeUtc().toTime_t());
        if (saveToDb)
        {
            mLastTimelineFlush = QDateTime::currentDateTimeUtc();
            mLogger->log("Flushing timeline to DB end");
        }

        // Check if duplication detected
        bool duplication = mCurrentTask->timeline()->duplicateDetected();
        mDuplicationSignalLabel->setText(duplication ? tr("Duplication detected") : tr(""));

        // Tell subscribers about changed time
        //mLogger->log("Sending onTimeChanged() signal begin");
        emit onTimeChanged();
        //mLogger->log("Sending onTimeChanged() signal end");
    }

    if (ui->mNoteEdit->document() && taskLoaded)
    {
        if (ui->mNoteEdit->document()->isModified())
        {
            PTask t = mTaskTreeModel->getTask(ui->mTaskTree->currentIndex());
            if (t && QDateTime::currentDateTimeUtc().secsTo(mTextModificationTime) <= -TEXT_FLUSH_INTERVAL)
            {
                t->setHtml(ui->mNoteEdit->document()->toPlainText());
                t->save();
                ui->mNoteEdit->document()->setModified(false);
                mModifiedLabel->setText(tr("Saved"));
                mTextModificationTime = QDateTime();
            }
        }
    }
}

void MainWindow::add10Mins()
{
    // Start tracking if any task is selected
    QModelIndex index = ui->mTaskTree->currentIndex();
    if (!index.isValid())
        return;

    // Get current task
    PTask t = mTaskTreeModel->getTask(index);
    t->timeline()->load();
    t->timeline()->putDebugRecord();
}

void MainWindow::applyTextFormat(const QTextCharFormat& fmt)
{
    QTextCursor c = ui->mNoteEdit->textCursor();
    if (c.hasSelection())
    {
        c.mergeCharFormat(fmt);
        ui->mNoteEdit->mergeCurrentCharFormat(fmt);
    }
    else
    {
        QTextCharFormat f = ui->mNoteEdit->currentCharFormat();
        f.merge(fmt);
        ui->mNoteEdit->setCurrentCharFormat(f);
    }
}

void MainWindow::print()
{
    QTextDocument *document = ui->mNoteEdit->document();
    QPrinter printer;

    QPrintDialog *dlg = new QPrintDialog(&printer, this);
    if (dlg->exec() != QDialog::Accepted)
        return;

    document->print(&printer);
}

void MainWindow::editSelectionChanged()
{

}
void MainWindow::editPositionChanged()
{

}
void MainWindow::editFormatChanged(const QTextCharFormat& /*fmt*/)
{
}

void MainWindow::editUndo()
{
    if (ui->mNoteEdit->hasFocus())
    {
        ui->mNoteEdit->undo();
    }
    else
        if (ChangesHistory::instance().canUndo())
            ChangesHistory::instance().undo();
}

void MainWindow::editRedo()
{
    if (ui->mNoteEdit->hasFocus())
    {
        ui->mNoteEdit->redo();
    }
    else
        if (ChangesHistory::instance().canRedo())
            ChangesHistory::instance().redo();
}

void MainWindow::editCut()
{
    ui->mNoteEdit->cut();
}
void MainWindow::editCopy()
{
    ui->mNoteEdit->copy();
}
void MainWindow::editPaste()
{
    ui->mNoteEdit->paste();
}
void MainWindow::editDelete()
{
    ui->mNoteEdit->clear();
}
void MainWindow::editSelectAll()
{
    ui->mNoteEdit->selectAll();
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        //showTrayWindow();
        trayContextualMenu();
        /*if (ui->mStartOrStopTrackingAction->isEnabled())
      startOrStopTracking();*/
        break;

    default:
        ;
    }
}

void MainWindow::trayContextualMenu()
{
    // Build context menu for tray icon
    QMenu* menu = new QMenu();
    menu->addAction(ui->mStartOrStopTrackingAction);
    QMenu* recentMenu = menu->addMenu(ui->mStartRecentTaskMenu->title());
    recentMenu->setIcon(QIcon(":/icons/icons/empty.png"));
    prepareRecentTasksMenu(recentMenu);
    menu->addAction(ui->mShowLittAction);
    //menu->addAction(ui->mPreferencesAction);
    //connect(menu, SIGNAL(aboutToHide()), this, SLOT(recoverTrayIcon()));
    mTrayIcon->setContextMenu(menu);
}

int MainWindow::showTrayWindow(QDialog* dlg)
{
    if (!dlg)
        return -1;

    // Delete old window (if it exists)
    if (mTrayWindow)
        delete mTrayWindow;
    mTrayWindow = dlg;
    connect(mTrayWindow, SIGNAL(destroyed(QObject*)), this, SLOT(trayWindowDestroyed(QObject*)));
    dlg->setModal(false);

    int w = dlg->geometry().width();
    int h = dlg->geometry().height();
    QRect rec = QApplication::desktop()->screenGeometry();
    int desktopHeight = rec.height();
    int desktopWidth = rec.width();

    QRect iconRect;
    if (mTrayIcon)
        iconRect = mTrayIcon->geometry();
    else
        iconRect = QRect(desktopWidth - w - 10, 0, 24, 24);

#ifdef TARGET_OSX
    QRect windowRect(desktopWidth - w - 10, iconRect.bottom() + 10, w, h);
#endif
#ifdef TARGET_WIN

#endif
    dlg->setGeometry(windowRect);
    dlg->setVisible(true);
    dlg->show();
    dlg->raise();
    dlg->activateWindow();

    /*
#ifdef TARGET_WIN
  Qt::WindowFlags eFlags = windowFlags ();
  eFlags |= Qt::WindowStaysOnTopHint;
  setWindowFlags(eFlags);
  eFlags &= ~Qt::WindowStaysOnTopHint;
  setWindowFlags(eFlags);
  show();
#endif
*/
    return 0;
}

void MainWindow::installDockMenu()
{
    QMenu* menu = new QMenu();
    menu->addAction(ui->mStartOrStopTrackingAction);
    mDockRecentMenu = menu->addMenu(ui->mStartRecentTaskMenu->title());
    mDockRecentMenu->setIcon(QIcon(":/icons/icons/empty.png"));
    prepareRecentTasksMenu(mDockRecentMenu);

    qt_mac_set_dock_menu(menu);
}

void MainWindow::timeFormatChanged()
{
    // If there is selected task
    showTimeForSelectedTask();

    // Show stats for tracking task in status bar
    showTimeForTrackingTask();
}


void MainWindow::showTimeForSelectedTask()
{
    PTask t = mTaskTreeModel->getTask(ui->mTaskTree->currentIndex());
    bool showSeconds = mSettings->data()[KEY_SHOW_SECONDS].toBool();

    // Show stats for current task
    if (t)
    {
        if (!t->timeline())
            t->loadContent();

        int spentSecondsToday = t->timeline()->today();
        int spentSecondsMonth = t->timeline()->month();
        ui->mTodaySpentTimeLabel->setText(QString::fromStdString(helper::chrono::secondsToDisplay(spentSecondsToday, showSeconds)));
        ui->mThisMonthSpentTimeLabel->setText(QString::fromStdString(helper::chrono::secondsToDisplay(spentSecondsMonth, showSeconds)));
    }
}

void MainWindow::showTimeForTrackingTask()
{
    if (mCurrentTask)
    {
        bool showSeconds = mSettings->data()[KEY_SHOW_SECONDS].toBool();

        // Update status bar
        QString path;
        PTask t = mCurrentTask;
        while (t)
        {
            path.insert(0, " / " + t->title());
            t = t->parent();
        }
        int spentSecondsToday = mCurrentTask->timeline()->today();
        QString timeString = QString::fromStdString(helper::chrono::secondsToDisplay(spentSecondsToday, showSeconds));
        path += " : " + timeString;
        mCurrentIntervalLabel->setText(path);

        if (mTrayIcon)
        {
            QString tooltip = tr("Litt is tracking ") + mCurrentTask->title() + ".\n" +
                    tr("Time spent today for this task is ") + timeString;

            mTrayIcon->setToolTip(tooltip);
        }
    }
}

void MainWindow::initTrayIcon()
{
    if (QSystemTrayIcon::isSystemTrayAvailable() && !mTrayIcon)
    {
        mTrayIcon = new QSystemTrayIcon();
        connect(mTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
        updateTrayIcon(Tray_ShowMessage);

        mTrayIcon->setVisible(true);
    }
}

void MainWindow::removeTrayIcon()
{
    if (mTrayIcon)
    {
        delete mTrayIcon;
        mTrayIcon = nullptr;
    }
}

void MainWindow::updateTrayIcon(TrayShowMessage flag)
{
    if (!mTrayIcon)
        return;

    QString tooltip;
    if (mCurrentTask)
    {
        bool showSeconds = mSettings->data()[KEY_SHOW_SECONDS].toBool();
        int spentSecondsToday = mCurrentTask->timeline()->today();
        QString timeString = QString::fromStdString(helper::chrono::secondsToDisplay(spentSecondsToday, showSeconds));
        tooltip = tr("Litt is tracking ") + mCurrentTask->title() + ".\n" +
                tr("Time spent today for this task is ") + timeString;
    }
    else
    {
        tooltip = tr("Litt is not tracking now.");
    }

    mTrayIcon->setToolTip(tooltip);

    if (mCurrentTask)
    {
        QIcon icon(TRAY_RUNNING_ICON_NAME);
#if defined(TARGET_OSX)
        icon.setIsMask(true);
#endif
        mTrayIcon->setIcon(icon);
        if (flag == Tray_ShowMessage)
            mTrayIcon->showMessage(tr("Time tracking started"), mCurrentTask->path());
    }
    else
    {
        QIcon icon(TRAY_DEFAULT_ICON_NAME);
#if defined(TARGET_OSX)
        icon.setIsMask(true);
#endif
        mTrayIcon->setIcon(icon);
    }
}

void MainWindow::showTimeline()
{
    if (!ui->mTaskTree->currentIndex().isValid())
        return;

    PTask t = mTaskTreeModel->getTask(ui->mTaskTree->currentIndex());
    TimeTreeDlg dlg(this, t->timeline(), *mSettings);
    dlg.exec();

    // Refresh current timeline stats
    showTimeForSelectedTask();
}

void MainWindow::showTimeReport()
{
    TimeReportWizard trz(*mSettings, this);
    trz.exec();
}

void MainWindow::newPasswordDialogFinished(int status)
{
    if (status == QDialog::Accepted)
    {
        Storage::instance().setKey(mNewPasswordDlg->password());
        if (!Storage::instance().create())
        {
            // Quit application
            mPasswordFailed = true;
            alertBox(tr("Error"), tr("Failed to initialize database"), AlertType_Critical);
        }

        // Remember password if it is specified in settings
        if (mSettings->data()[KEY_AUTOSAVE_PASSWORD].toBool())
            mSettings->data()[KEY_PASSWORD] = mNewPasswordDlg->password();
        else
            mSettings->data()[KEY_PASSWORD] = NOPASSWORDSTRING;

        // Flush settings
        mSettings->save();

        connectUiToDatabase();
    }
    else
        close();
}

void MainWindow::passwordDialogFinished(int status)
{
    QString password;
    if (status == QDialog::Accepted)
    {
        password = mPasswordDlg->password();
        openDatabase(password);
        connectUiToDatabase();
    }
    else
    {
        mPasswordFailed = false;
        QApplication::postEvent(this, new ClientCloseEvent());
    }
}

void MainWindow::criticalAlertFinished(int /*status*/)
{
    QApplication::postEvent(this, new ClientCloseEvent());
}

void MainWindow::openAlertFinished(int /*status*/)
{
    mPasswordDlg = new PasswordDlg(this);
    connect(mPasswordDlg, SIGNAL(finished(int)), this, SLOT(passwordDialogFinished(int)));
    mPasswordDlg->show();
}

void MainWindow::warningAlertFinished(int /*status*/)
{
}

void MainWindow::toolbarVisibilityChanged(bool visible)
{
    ui->mShowToolbarAction->setChecked(visible);
}

void MainWindow::showHideToolbar()
{
    ui->mMainToolbar->setVisible(ui->mShowToolbarAction->isChecked());
}

void MainWindow::showAttachments()
{
    QModelIndex taskIndex = ui->mTaskTree->currentIndex();
    if (!taskIndex.isValid())
        return;

    PTask t = mTaskTreeModel->getTask(taskIndex);
    AttachmentsDialog dlg(t, this);
    dlg.exec();

    // Refresh current item in task tree to ensure attachment icon is shown/hidden
    mTaskTreeModel->dataChanged(taskIndex, taskIndex);

    // Refresh attachments link
    updateAttachmentsLabel(t);
}

void MainWindow::checkForUpdates()
{
    FvUpdater::sharedUpdater()->CheckForUpdatesNotSilent();
}

void MainWindow::systemSleep()
{
    //qDebug() << "System goes to sleep";
    stopTracking(TSR_Automatic, QDateTime::currentDateTimeUtc().toTime_t());
}

void MainWindow::systemResume()
{
    //qDebug() << "System raised from sleep";
    if (mStopReason == TSR_Automatic)
        startTracking();
}

void MainWindow::changeTimeTrackableFlag(bool trackable)
{
    QModelIndex index = ui->mTaskTree->currentIndex();
    if (!index.isValid())
        return;

    PTask t = mTaskTreeModel->getTask(index);
    if (!t)
        return;

    if (trackable)
        t->setFlags(t->flags() & ~Task::Flag_NoTimeTracking );
    else
        t->setFlags(t->flags() | Task::Flag_NoTimeTracking );

    // Stop task if it is marked as non tracking and it is running now
    if (!trackable && mCurrentTask == t)
        stopTracking(TSR_Manual, time(nullptr));

    // Update UI
    handleTrackableState(t);
}

void MainWindow::find()
{
    ui->mFindFrame->setVisible(true);
    ui->mFindEdit->setFocus();
}

void MainWindow::findInTasks()
{
    if (mFindInTasksDlg.exec() == QDialog::Accepted)
    {
        FindResultItem& r = mFindInTasksDlg.getResult();
        if (r.mTask)
        {
            // Find task in row and load its content to edit control
            QModelIndex taskIndex = mTaskTreeModel->getIndex(r.mTask);
            if (taskIndex.isValid())
            {
                ui->mTaskTree->setCurrentIndex(taskIndex);
                QTextCursor c = ui->mNoteEdit->document()->find(r.mFoundWord, 0);
                if (!c.isNull())
                    ui->mNoteEdit->setTextCursor(c);
            }
        }
    }
}

void MainWindow::findRequested()
{
    QString pattern = ui->mFindEdit->text();
    if (pattern.isEmpty())
        return;

    if (pattern != mFindPattern)
    {
        mFindPattern = pattern;
        mFindStartIndex = 0;
    }

    //ui->mFindEdit->setVisible(false);
    QTextCursor c = ui->mNoteEdit->document()->find(pattern, mFindStartIndex, nullptr);
    if (c.isNull())
    {
        mFindStartIndex = 0;
        c = ui->mNoteEdit->document()->find(pattern, mFindStartIndex, nullptr);
    }
    if (!c.isNull())
    {
        //c.select(QTextCursor::BlockUnderCursor);
        ui->mNoteEdit->setTextCursor(c);
        mFindStartIndex = c.position() + 1;
    }
}

void MainWindow::findRejected(QObject* obj)
{
    if (obj == ui->mFindEdit)
    {
        ui->mFindFrame->setVisible(false);
        ui->mNoteEdit->setFocus();
    }
}

void MainWindow::taskTextChanged()
{
    mModifiedLabel->setText(tr("Modified"));
    if (mTextModificationTime.isNull())
        mTextModificationTime = QDateTime::currentDateTimeUtc();
}

void MainWindow::taskMoved(PTask task)
{
    QApplication::postEvent(this, new SelectTaskEvent(task));

    //QModelIndex index = mTaskTreeModel->getIndex(task);

    //if (index.isValid())
    //  ui->mTaskTree->setCurrentIndex(index);
}

void MainWindow::focusTaskTree()
{
    ui->mTaskTree->setFocus();
}

void MainWindow::focusTaskText()
{
    ui->mNoteEdit->setFocus();
}

void MainWindow::showMainWindow()
{
    this->show();
    this->raise();
    this->activateWindow();

#ifdef TARGET_OSX
#endif

#ifdef TARGET_WIN
    Qt::WindowFlags eFlags = windowFlags ();
    eFlags |= Qt::WindowStaysOnTopHint;
    setWindowFlags(eFlags);
    eFlags &= ~Qt::WindowStaysOnTopHint;
    setWindowFlags(eFlags);
    show();
#endif
}

void MainWindow::continueOnIdle()
{
    // Disable idle detection at all - it is not needed in this session anymore
    mActivityTracker->stop();
}

void MainWindow::breakOnIdle(const QDateTime& stopTime)
{
    // Stop tracking
    stopTracking(TSR_Manual, stopTime.toUTC().toTime_t());
    showTimeForSelectedTask();
}

void MainWindow::startOnActivity()
{
    // Start tracking
    startTracking();

    // Show message if needed
    if (mTrayIcon)
        mTrayIcon->showMessage(tr("Time tracking started"), mCurrentTask->path());
}

void MainWindow::stopOnActivity()
{
    stopTracking(TSR_Manual);
}

void MainWindow::trayWindowDestroyed(QObject *object)
{
    mTrayWindow = nullptr;
}
