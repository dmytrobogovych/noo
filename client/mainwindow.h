#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QSettings>
#include <QTextCharFormat>
#include <QSystemTrayIcon>
#include <QMessageBox>

#include "tasktreemodel.h"
#include "settings.h"
#include "passworddlg.h"
#include "newpassworddlg.h"
#include "logger.h"
#include "platforms/hidtracker.h"
#include "finddialog.h"
#include <deque>

#ifdef TARGET_OSX
# include "platforms/osx/sleeptracker_osx.h"
#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
protected:
  void closeEvent(QCloseEvent *);
  void customEvent(QEvent *);

private:
  enum TrackingStopReason
  {
    TSR_None,    // Used to init only
    TSR_Manual,
    TSR_Automatic
  };

  QSharedPointer<Logger> mLogger;
  QSharedPointer<HIDActivityTracker> mActivityTracker;
  TrackingStopReason mStopReason;

  Ui::MainWindow *ui;
  TaskTreeModel* mTaskTreeModel;
  PTask mCurrentTask, mAutomaticTask;
  QTimer* mUpdateTimer;
  QLabel* mModifiedLabel;
  QLabel* mCurrentIntervalLabel;
  QLabel* mDuplicationSignalLabel;
  QSystemTrayIcon *mTrayIcon;
  QSharedPointer<Settings> mSettings;
  bool mPasswordFailed;
  PasswordDlg* mPasswordDlg;
  NewPasswordDlg* mNewPasswordDlg;
  QMessageBox* mAlertBox;

  // Time when current note was saved to DB last time
  QDateTime mLastTimelineFlush;

  // Attachments action
  QAction* mAttachmentsAction;

  // Attachments label
  QLabel* mAttachmentsLabel;

  // Delegate to draw task items in custom way
  TaskItemDelegate mTaskItemDelegate;

  // Find text in document start index
  int mFindStartIndex;
  QString mFindPattern;
  FindInTasksDialog mFindInTasksDlg;

#ifdef TARGET_OSX
  SleepTracker mSleepTracker;
#endif
  QSharedPointer<QByteArray> getUndoStack() const;
  int mTimeFrameHeight;

  QDateTime mTextModificationTime;
  std::deque<PTask> mRecentTrackingTasks;
  QMenu* mDockRecentMenu;
  QDialog* mTrayWindow = nullptr;

  void saveGeometry();
  void loadGeometry();
  void applyTextFormat(const QTextCharFormat& fmt);
  void initClient();

  // Checks if database exists, requests passwords etc.
  void attachDatabase();

  // Just open database via Storage::instance()
  void openDatabase(const QString& password);

  // Creates task tree model, adjusts UI
  void connectUiToDatabase();

  // Shows window with alert text and button OK
  enum AlertType
  {
    AlertType_Warning,
    AlertType_Critical,
    AlertType_CannotOpen
  };

  void alertBox(const QString& title, const QString& text, AlertType alertType);

  void showTimeForSelectedTask();
  void showTimeForTrackingTask();
  void initTrayIcon();
  void removeTrayIcon();

  enum TrayShowMessage
  {
    Tray_ShowMessage = 0,
    Tray_SkipMessage = 1
  };
  void updateTrayIcon(TrayShowMessage flag);
  void handleTrackableState(PTask task);
  void trayContextualMenu();
  int  showTrayWindow(QDialog* dlg);
  void installDockMenu();
  void startTracking(PTask t);
  void prepareRecentTasksMenu(QMenu* submenu);
  void updateAttachmentsLabel(PTask t);

signals:
  void onTimeFormatChanged();
  void onTimeChanged();

public slots:
  void save();
  void sync();
  void about();
  void preferences();
  void print();
  void quit();
  void newRootTask();
  void newTask();
  void newSibling();
  void moveUp();
  void moveDown();
  void renameTask();
  void deleteTask();
  void taskTreeContextualMenu(const QPoint& point);
  void taskIndexChanged(const QModelIndex&, const QModelIndex&);
  void idleDetected();
  void activityDetected();
  void startOrStopTracking();
  void startTracking();
  void startTrackingRecent();

  void stopTracking(TrackingStopReason reason, const QDateTime& currentUtc = QDateTime::currentDateTimeUtc());
  void updateData();
  void add10Mins();

  void editSelectionChanged();
  void editPositionChanged();
  void editFormatChanged(const QTextCharFormat& fmt);

  void editUndo();
  void editRedo();
  void editCut();
  void editCopy();
  void editPaste();
  void editDelete();
  void editSelectAll();

  void iconActivated(QSystemTrayIcon::ActivationReason reason);
  void timeFormatChanged();
  void showTimeline();
  void showTimeReport();

  void newPasswordDialogFinished(int status);
  void passwordDialogFinished(int status);
  void criticalAlertFinished(int status);
  void openAlertFinished(int status);
  void warningAlertFinished(int status);
  void toolbarVisibilityChanged(bool visible);
  void showHideToolbar();
  void showAttachments();
  void checkForUpdates();
  void systemSleep();
  void systemResume();
  void changeTimeTrackableFlag(bool trackable);
  void find();
  void findInTasks();
  void findRequested();
  void findRejected(QObject* obj);
  void taskTextChanged();
  void taskMoved(PTask task);
  void focusTaskTree();
  void focusTaskText();
  void showMainWindow();
  void continueOnIdle();
  void breakOnIdle(const QDateTime& stopTime);
  void startOnActivity();
  void stopOnActivity();
  void trayWindowDestroyed(QObject* object);
};

#endif // MAINWINDOW_H