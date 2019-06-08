/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qmarkdowntextedit/qmarkdowntextedit.h"
#include "tasktreemodel.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *mSyncAction;
    QAction *mPrintAction;
    QAction *mExitAction;
    QAction *mPreferencesAction;
    QAction *mSaveAction;
    QAction *mDeleteTaskAction;
    QAction *mRenameTaskAction;
    QAction *mNewTaskAction;
    QAction *mNewRootTaskAction;
    QAction *mStartOrStopTrackingAction;
    QAction *mUndoEditAction;
    QAction *mRedoEditAction;
    QAction *mCutEditAction;
    QAction *mCopyEditAction;
    QAction *mPasteEditAction;
    QAction *mDeleteEditAction;
    QAction *mSelectAllEditAction;
    QAction *mAboutAction;
    QAction *mTimelineAction;
    QAction *mTimeReportAction;
    QAction *mShowToolbarAction;
    QAction *mAttachmentsAction;
    QAction *mCheckForUpdatesAction;
    QAction *mTimeTrackableAction;
    QAction *mActionSearchInTasks;
    QAction *mActionSearch;
    QAction *mShowLittAction;
    QAction *mFocusTaskTreeAction;
    QAction *mFocusTaskTextAction;
    QAction *mAddSiblingAction;
    QAction *mDecreaseLevelAction;
    QAction *mIncreaseLevelAction;
    QAction *mMoveUpAction;
    QAction *mMoveDownAction;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *mSplitter;
    TaskTreeView *mTaskTree;
    QFrame *frame;
    QGridLayout *gridLayout;
    QSplitter *mTimeSplitter;
    QFrame *mEditFrame;
    QVBoxLayout *verticalLayout;
    QMarkdownTextEdit *mNoteEdit;
    QFrame *mFindFrame;
    QHBoxLayout *mFindFrameLayout;
    QLabel *label;
    QLineEdit *mFindEdit;
    QFrame *mTimeFrame;
    QFormLayout *formLayout;
    QLabel *mTodayTextLabel;
    QLabel *mTodaySpentTimeLabel;
    QLabel *mThisMonthTextLabel;
    QLabel *mThisMonthSpentTimeLabel;
    QMenuBar *mMainMenu;
    QMenu *mFileMenu;
    QMenu *mEditMenu;
    QMenu *mToolsMenu;
    QMenu *mStartRecentTaskMenu;
    QMenu *mViewMenu;
    QToolBar *mMainToolbar;
    QStatusBar *mStatusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(647, 508);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setWindowTitle(QString::fromUtf8("Litt"));
        mSyncAction = new QAction(MainWindow);
        mSyncAction->setObjectName(QString::fromUtf8("mSyncAction"));
        mSyncAction->setEnabled(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/network-receive.png"), QSize(), QIcon::Normal, QIcon::Off);
        mSyncAction->setIcon(icon);
        mSyncAction->setVisible(false);
        mPrintAction = new QAction(MainWindow);
        mPrintAction->setObjectName(QString::fromUtf8("mPrintAction"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icons/document-print.png"), QSize(), QIcon::Normal, QIcon::Off);
        mPrintAction->setIcon(icon1);
        mExitAction = new QAction(MainWindow);
        mExitAction->setObjectName(QString::fromUtf8("mExitAction"));
        mPreferencesAction = new QAction(MainWindow);
        mPreferencesAction->setObjectName(QString::fromUtf8("mPreferencesAction"));
        mSaveAction = new QAction(MainWindow);
        mSaveAction->setObjectName(QString::fromUtf8("mSaveAction"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/document-save.png"), QSize(), QIcon::Normal, QIcon::Off);
        mSaveAction->setIcon(icon2);
        mDeleteTaskAction = new QAction(MainWindow);
        mDeleteTaskAction->setObjectName(QString::fromUtf8("mDeleteTaskAction"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/icons/list-remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        mDeleteTaskAction->setIcon(icon3);
        mRenameTaskAction = new QAction(MainWindow);
        mRenameTaskAction->setObjectName(QString::fromUtf8("mRenameTaskAction"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/icons/empty.png"), QSize(), QIcon::Normal, QIcon::Off);
        mRenameTaskAction->setIcon(icon4);
        mNewTaskAction = new QAction(MainWindow);
        mNewTaskAction->setObjectName(QString::fromUtf8("mNewTaskAction"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/icons/tree-add-child-small.png"), QSize(), QIcon::Normal, QIcon::Off);
        mNewTaskAction->setIcon(icon5);
        mNewRootTaskAction = new QAction(MainWindow);
        mNewRootTaskAction->setObjectName(QString::fromUtf8("mNewRootTaskAction"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/icons/tree-add-root-small.png"), QSize(), QIcon::Normal, QIcon::Off);
        mNewRootTaskAction->setIcon(icon6);
        mStartOrStopTrackingAction = new QAction(MainWindow);
        mStartOrStopTrackingAction->setObjectName(QString::fromUtf8("mStartOrStopTrackingAction"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/icons/clock-32x32.png"), QSize(), QIcon::Normal, QIcon::Off);
        mStartOrStopTrackingAction->setIcon(icon7);
        mUndoEditAction = new QAction(MainWindow);
        mUndoEditAction->setObjectName(QString::fromUtf8("mUndoEditAction"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/icons/edit-undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        mUndoEditAction->setIcon(icon8);
        mRedoEditAction = new QAction(MainWindow);
        mRedoEditAction->setObjectName(QString::fromUtf8("mRedoEditAction"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/icons/edit-redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        mRedoEditAction->setIcon(icon9);
        mCutEditAction = new QAction(MainWindow);
        mCutEditAction->setObjectName(QString::fromUtf8("mCutEditAction"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icons/icons/edit-cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        mCutEditAction->setIcon(icon10);
        mCopyEditAction = new QAction(MainWindow);
        mCopyEditAction->setObjectName(QString::fromUtf8("mCopyEditAction"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/icons/icons/edit-copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        mCopyEditAction->setIcon(icon11);
        mPasteEditAction = new QAction(MainWindow);
        mPasteEditAction->setObjectName(QString::fromUtf8("mPasteEditAction"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/icons/icons/edit-paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        mPasteEditAction->setIcon(icon12);
        mDeleteEditAction = new QAction(MainWindow);
        mDeleteEditAction->setObjectName(QString::fromUtf8("mDeleteEditAction"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/icons/icons/edit-clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        mDeleteEditAction->setIcon(icon13);
        mSelectAllEditAction = new QAction(MainWindow);
        mSelectAllEditAction->setObjectName(QString::fromUtf8("mSelectAllEditAction"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/icons/icons/edit-select-all.png"), QSize(), QIcon::Normal, QIcon::Off);
        mSelectAllEditAction->setIcon(icon14);
        mAboutAction = new QAction(MainWindow);
        mAboutAction->setObjectName(QString::fromUtf8("mAboutAction"));
        mTimelineAction = new QAction(MainWindow);
        mTimelineAction->setObjectName(QString::fromUtf8("mTimelineAction"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/icons/icons/office-calendar.png"), QSize(), QIcon::Normal, QIcon::Off);
        mTimelineAction->setIcon(icon15);
        mTimeReportAction = new QAction(MainWindow);
        mTimeReportAction->setObjectName(QString::fromUtf8("mTimeReportAction"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/icons/icons/appointment-new.png"), QSize(), QIcon::Normal, QIcon::Off);
        mTimeReportAction->setIcon(icon16);
        mShowToolbarAction = new QAction(MainWindow);
        mShowToolbarAction->setObjectName(QString::fromUtf8("mShowToolbarAction"));
        mShowToolbarAction->setCheckable(true);
        mShowToolbarAction->setChecked(true);
        mShowToolbarAction->setIcon(icon4);
        mAttachmentsAction = new QAction(MainWindow);
        mAttachmentsAction->setObjectName(QString::fromUtf8("mAttachmentsAction"));
        mAttachmentsAction->setIcon(icon4);
        mCheckForUpdatesAction = new QAction(MainWindow);
        mCheckForUpdatesAction->setObjectName(QString::fromUtf8("mCheckForUpdatesAction"));
        mTimeTrackableAction = new QAction(MainWindow);
        mTimeTrackableAction->setObjectName(QString::fromUtf8("mTimeTrackableAction"));
        mTimeTrackableAction->setCheckable(true);
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/icons/icons/accessories-calculator.png"), QSize(), QIcon::Normal, QIcon::Off);
        mTimeTrackableAction->setIcon(icon17);
        mActionSearchInTasks = new QAction(MainWindow);
        mActionSearchInTasks->setObjectName(QString::fromUtf8("mActionSearchInTasks"));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/icons/icons/folder-saved-search.png"), QSize(), QIcon::Normal, QIcon::Off);
        mActionSearchInTasks->setIcon(icon18);
        mActionSearch = new QAction(MainWindow);
        mActionSearch->setObjectName(QString::fromUtf8("mActionSearch"));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/icons/icons/edit-find.png"), QSize(), QIcon::Normal, QIcon::Off);
        mActionSearch->setIcon(icon19);
        mShowLittAction = new QAction(MainWindow);
        mShowLittAction->setObjectName(QString::fromUtf8("mShowLittAction"));
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/icons/icons/format-justify-fill.png"), QSize(), QIcon::Normal, QIcon::Off);
        mShowLittAction->setIcon(icon20);
        mFocusTaskTreeAction = new QAction(MainWindow);
        mFocusTaskTreeAction->setObjectName(QString::fromUtf8("mFocusTaskTreeAction"));
        mFocusTaskTreeAction->setIcon(icon4);
        mFocusTaskTextAction = new QAction(MainWindow);
        mFocusTaskTextAction->setObjectName(QString::fromUtf8("mFocusTaskTextAction"));
        mFocusTaskTextAction->setIcon(icon4);
        mAddSiblingAction = new QAction(MainWindow);
        mAddSiblingAction->setObjectName(QString::fromUtf8("mAddSiblingAction"));
        QIcon icon21;
        icon21.addFile(QString::fromUtf8(":/icons/icons/tree-add-sibling-small.png"), QSize(), QIcon::Normal, QIcon::Off);
        mAddSiblingAction->setIcon(icon21);
        mDecreaseLevelAction = new QAction(MainWindow);
        mDecreaseLevelAction->setObjectName(QString::fromUtf8("mDecreaseLevelAction"));
        mDecreaseLevelAction->setIcon(icon4);
        mIncreaseLevelAction = new QAction(MainWindow);
        mIncreaseLevelAction->setObjectName(QString::fromUtf8("mIncreaseLevelAction"));
        mIncreaseLevelAction->setIcon(icon4);
        mMoveUpAction = new QAction(MainWindow);
        mMoveUpAction->setObjectName(QString::fromUtf8("mMoveUpAction"));
        mMoveUpAction->setIcon(icon4);
        mMoveDownAction = new QAction(MainWindow);
        mMoveDownAction->setObjectName(QString::fromUtf8("mMoveDownAction"));
        mMoveDownAction->setIcon(icon4);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        mSplitter = new QSplitter(centralWidget);
        mSplitter->setObjectName(QString::fromUtf8("mSplitter"));
        sizePolicy.setHeightForWidth(mSplitter->sizePolicy().hasHeightForWidth());
        mSplitter->setSizePolicy(sizePolicy);
        mSplitter->setMinimumSize(QSize(600, 200));
        mSplitter->setOrientation(Qt::Horizontal);
        mTaskTree = new TaskTreeView(mSplitter);
        mTaskTree->setObjectName(QString::fromUtf8("mTaskTree"));
        mTaskTree->setContextMenuPolicy(Qt::CustomContextMenu);
        mTaskTree->setDragEnabled(true);
        mTaskTree->setDragDropMode(QAbstractItemView::InternalMove);
        mTaskTree->setDefaultDropAction(Qt::MoveAction);
        mSplitter->addWidget(mTaskTree);
        frame = new QFrame(mSplitter);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        mTimeSplitter = new QSplitter(frame);
        mTimeSplitter->setObjectName(QString::fromUtf8("mTimeSplitter"));
        mTimeSplitter->setMinimumSize(QSize(0, 0));
        mTimeSplitter->setLineWidth(0);
        mTimeSplitter->setOrientation(Qt::Vertical);
        mEditFrame = new QFrame(mTimeSplitter);
        mEditFrame->setObjectName(QString::fromUtf8("mEditFrame"));
        mEditFrame->setFrameShape(QFrame::StyledPanel);
        mEditFrame->setFrameShadow(QFrame::Plain);
        mEditFrame->setLineWidth(0);
        verticalLayout = new QVBoxLayout(mEditFrame);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        mNoteEdit = new QMarkdownTextEdit(mEditFrame);
        mNoteEdit->setObjectName(QString::fromUtf8("mNoteEdit"));
        sizePolicy.setHeightForWidth(mNoteEdit->sizePolicy().hasHeightForWidth());
        mNoteEdit->setSizePolicy(sizePolicy);
        mNoteEdit->setFrameShape(QFrame::NoFrame);
        mNoteEdit->setFrameShadow(QFrame::Plain);

        verticalLayout->addWidget(mNoteEdit);

        mFindFrame = new QFrame(mEditFrame);
        mFindFrame->setObjectName(QString::fromUtf8("mFindFrame"));
        mFindFrame->setAutoFillBackground(false);
        mFindFrame->setStyleSheet(QString::fromUtf8("background-color:white;"));
        mFindFrame->setFrameShape(QFrame::NoFrame);
        mFindFrame->setFrameShadow(QFrame::Raised);
        mFindFrame->setLineWidth(0);
        mFindFrameLayout = new QHBoxLayout(mFindFrame);
        mFindFrameLayout->setSpacing(5);
        mFindFrameLayout->setContentsMargins(11, 11, 11, 11);
        mFindFrameLayout->setObjectName(QString::fromUtf8("mFindFrameLayout"));
        mFindFrameLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(mFindFrame);
        label->setObjectName(QString::fromUtf8("label"));

        mFindFrameLayout->addWidget(label);

        mFindEdit = new QLineEdit(mFindFrame);
        mFindEdit->setObjectName(QString::fromUtf8("mFindEdit"));

        mFindFrameLayout->addWidget(mFindEdit);


        verticalLayout->addWidget(mFindFrame);

        mTimeSplitter->addWidget(mEditFrame);
        mTimeFrame = new QFrame(mTimeSplitter);
        mTimeFrame->setObjectName(QString::fromUtf8("mTimeFrame"));
        mTimeFrame->setMaximumSize(QSize(16777215, 70));
        mTimeFrame->setFrameShape(QFrame::StyledPanel);
        formLayout = new QFormLayout(mTimeFrame);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        mTodayTextLabel = new QLabel(mTimeFrame);
        mTodayTextLabel->setObjectName(QString::fromUtf8("mTodayTextLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, mTodayTextLabel);

        mTodaySpentTimeLabel = new QLabel(mTimeFrame);
        mTodaySpentTimeLabel->setObjectName(QString::fromUtf8("mTodaySpentTimeLabel"));

        formLayout->setWidget(0, QFormLayout::FieldRole, mTodaySpentTimeLabel);

        mThisMonthTextLabel = new QLabel(mTimeFrame);
        mThisMonthTextLabel->setObjectName(QString::fromUtf8("mThisMonthTextLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, mThisMonthTextLabel);

        mThisMonthSpentTimeLabel = new QLabel(mTimeFrame);
        mThisMonthSpentTimeLabel->setObjectName(QString::fromUtf8("mThisMonthSpentTimeLabel"));

        formLayout->setWidget(1, QFormLayout::FieldRole, mThisMonthSpentTimeLabel);

        mTimeSplitter->addWidget(mTimeFrame);

        gridLayout->addWidget(mTimeSplitter, 0, 0, 1, 1);

        mSplitter->addWidget(frame);

        horizontalLayout->addWidget(mSplitter);

        MainWindow->setCentralWidget(centralWidget);
        mMainMenu = new QMenuBar(MainWindow);
        mMainMenu->setObjectName(QString::fromUtf8("mMainMenu"));
        mMainMenu->setGeometry(QRect(0, 0, 647, 22));
        mFileMenu = new QMenu(mMainMenu);
        mFileMenu->setObjectName(QString::fromUtf8("mFileMenu"));
        mEditMenu = new QMenu(mMainMenu);
        mEditMenu->setObjectName(QString::fromUtf8("mEditMenu"));
        mToolsMenu = new QMenu(mMainMenu);
        mToolsMenu->setObjectName(QString::fromUtf8("mToolsMenu"));
        mStartRecentTaskMenu = new QMenu(mToolsMenu);
        mStartRecentTaskMenu->setObjectName(QString::fromUtf8("mStartRecentTaskMenu"));
        mStartRecentTaskMenu->setIcon(icon4);
        mViewMenu = new QMenu(mMainMenu);
        mViewMenu->setObjectName(QString::fromUtf8("mViewMenu"));
        MainWindow->setMenuBar(mMainMenu);
        mMainToolbar = new QToolBar(MainWindow);
        mMainToolbar->setObjectName(QString::fromUtf8("mMainToolbar"));
        mMainToolbar->setContextMenuPolicy(Qt::NoContextMenu);
        mMainToolbar->setMovable(false);
        mMainToolbar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mMainToolbar);
        mStatusBar = new QStatusBar(MainWindow);
        mStatusBar->setObjectName(QString::fromUtf8("mStatusBar"));
        MainWindow->setStatusBar(mStatusBar);

        mMainMenu->addAction(mFileMenu->menuAction());
        mMainMenu->addAction(mEditMenu->menuAction());
        mMainMenu->addAction(mToolsMenu->menuAction());
        mMainMenu->addAction(mViewMenu->menuAction());
        mFileMenu->addAction(mAboutAction);
        mFileMenu->addAction(mCheckForUpdatesAction);
        mFileMenu->addAction(mSaveAction);
        mFileMenu->addAction(mSyncAction);
        mFileMenu->addSeparator();
        mFileMenu->addAction(mPreferencesAction);
        mFileMenu->addAction(mPrintAction);
        mFileMenu->addAction(mExitAction);
        mEditMenu->addAction(mNewRootTaskAction);
        mEditMenu->addAction(mNewTaskAction);
        mEditMenu->addAction(mAddSiblingAction);
        mEditMenu->addAction(mDeleteTaskAction);
        mEditMenu->addAction(mRenameTaskAction);
        mEditMenu->addAction(mMoveUpAction);
        mEditMenu->addAction(mMoveDownAction);
        mEditMenu->addSeparator();
        mEditMenu->addAction(mUndoEditAction);
        mEditMenu->addAction(mRedoEditAction);
        mEditMenu->addAction(mCutEditAction);
        mEditMenu->addAction(mCopyEditAction);
        mEditMenu->addAction(mPasteEditAction);
        mEditMenu->addAction(mDeleteEditAction);
        mEditMenu->addAction(mSelectAllEditAction);
        mEditMenu->addSeparator();
        mEditMenu->addAction(mActionSearch);
        mEditMenu->addAction(mActionSearchInTasks);
        mToolsMenu->addAction(mActionSearchInTasks);
        mToolsMenu->addAction(mTimeReportAction);
        mToolsMenu->addAction(mStartOrStopTrackingAction);
        mToolsMenu->addAction(mStartRecentTaskMenu->menuAction());
        mToolsMenu->addSeparator();
        mToolsMenu->addAction(mFocusTaskTreeAction);
        mToolsMenu->addAction(mFocusTaskTextAction);
        mViewMenu->addAction(mShowToolbarAction);
        mMainToolbar->addAction(mNewRootTaskAction);
        mMainToolbar->addAction(mNewTaskAction);
        mMainToolbar->addAction(mAddSiblingAction);
        mMainToolbar->addAction(mDeleteTaskAction);
        mMainToolbar->addAction(mStartOrStopTrackingAction);

        retranslateUi(MainWindow);
        QObject::connect(mExitAction, SIGNAL(triggered()), MainWindow, SLOT(quit()));
        QObject::connect(mSaveAction, SIGNAL(triggered()), MainWindow, SLOT(save()));
        QObject::connect(mSyncAction, SIGNAL(triggered()), MainWindow, SLOT(sync()));
        QObject::connect(mTaskTree, SIGNAL(customContextMenuRequested(QPoint)), MainWindow, SLOT(taskTreeContextualMenu(QPoint)));
        QObject::connect(mNewTaskAction, SIGNAL(triggered()), MainWindow, SLOT(newTask()));
        QObject::connect(mRenameTaskAction, SIGNAL(triggered()), MainWindow, SLOT(renameTask()));
        QObject::connect(mDeleteTaskAction, SIGNAL(triggered()), MainWindow, SLOT(deleteTask()));
        QObject::connect(mNewRootTaskAction, SIGNAL(triggered()), MainWindow, SLOT(newRootTask()));
        QObject::connect(mStartOrStopTrackingAction, SIGNAL(triggered()), MainWindow, SLOT(startOrStopTracking()));
        QObject::connect(mPrintAction, SIGNAL(triggered()), MainWindow, SLOT(print()));
        QObject::connect(mCopyEditAction, SIGNAL(triggered()), MainWindow, SLOT(editCopy()));
        QObject::connect(mCutEditAction, SIGNAL(triggered()), MainWindow, SLOT(editCut()));
        QObject::connect(mDeleteEditAction, SIGNAL(triggered()), MainWindow, SLOT(editDelete()));
        QObject::connect(mPasteEditAction, SIGNAL(triggered()), MainWindow, SLOT(editPaste()));
        QObject::connect(mRedoEditAction, SIGNAL(triggered()), MainWindow, SLOT(editRedo()));
        QObject::connect(mUndoEditAction, SIGNAL(triggered()), MainWindow, SLOT(editUndo()));
        QObject::connect(mSelectAllEditAction, SIGNAL(triggered()), MainWindow, SLOT(editSelectAll()));
        QObject::connect(mTimelineAction, SIGNAL(triggered()), MainWindow, SLOT(showTimeline()));
        QObject::connect(mTimeReportAction, SIGNAL(triggered()), MainWindow, SLOT(showTimeReport()));
        QObject::connect(mShowToolbarAction, SIGNAL(changed()), MainWindow, SLOT(showHideToolbar()));
        QObject::connect(mAttachmentsAction, SIGNAL(triggered()), MainWindow, SLOT(showAttachments()));
        QObject::connect(mCheckForUpdatesAction, SIGNAL(triggered()), MainWindow, SLOT(checkForUpdates()));
        QObject::connect(mTimeTrackableAction, SIGNAL(toggled(bool)), MainWindow, SLOT(changeTimeTrackableFlag(bool)));
        QObject::connect(mActionSearch, SIGNAL(triggered()), MainWindow, SLOT(find()));
        QObject::connect(mActionSearchInTasks, SIGNAL(triggered()), MainWindow, SLOT(findInTasks()));
        QObject::connect(mFindEdit, SIGNAL(returnPressed()), MainWindow, SLOT(findRequested()));
        QObject::connect(mShowLittAction, SIGNAL(triggered()), MainWindow, SLOT(showMainWindow()));
        QObject::connect(mFocusTaskTreeAction, SIGNAL(triggered()), MainWindow, SLOT(focusTaskTree()));
        QObject::connect(mFocusTaskTextAction, SIGNAL(triggered()), MainWindow, SLOT(focusTaskText()));
        QObject::connect(mNoteEdit, SIGNAL(textChanged()), MainWindow, SLOT(taskTextChanged()));
        QObject::connect(mAddSiblingAction, SIGNAL(triggered()), MainWindow, SLOT(newSibling()));
        QObject::connect(mMoveDownAction, SIGNAL(triggered()), MainWindow, SLOT(moveDown()));
        QObject::connect(mMoveUpAction, SIGNAL(triggered()), MainWindow, SLOT(moveUp()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        mSyncAction->setText(QApplication::translate("MainWindow", "S&ync...", nullptr));
        mPrintAction->setText(QApplication::translate("MainWindow", "&Print...", nullptr));
        mExitAction->setText(QApplication::translate("MainWindow", "E&xit", nullptr));
        mPreferencesAction->setText(QApplication::translate("MainWindow", "Pre&ferences...", nullptr));
        mSaveAction->setText(QApplication::translate("MainWindow", "&Save", nullptr));
#ifndef QT_NO_SHORTCUT
        mSaveAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        mDeleteTaskAction->setText(QApplication::translate("MainWindow", "Delete task", nullptr));
#ifndef QT_NO_TOOLTIP
        mDeleteTaskAction->setToolTip(QApplication::translate("MainWindow", "Delete task", nullptr));
#endif // QT_NO_TOOLTIP
        mRenameTaskAction->setText(QApplication::translate("MainWindow", "Rename task", nullptr));
        mNewTaskAction->setText(QApplication::translate("MainWindow", "New child task", nullptr));
        mNewTaskAction->setIconText(QApplication::translate("MainWindow", "New child task", nullptr));
#ifndef QT_NO_TOOLTIP
        mNewTaskAction->setToolTip(QApplication::translate("MainWindow", "New child task", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        mNewTaskAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+N", nullptr));
#endif // QT_NO_SHORTCUT
        mNewRootTaskAction->setText(QApplication::translate("MainWindow", "New root task", nullptr));
#ifndef QT_NO_SHORTCUT
        mNewRootTaskAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_NO_SHORTCUT
        mStartOrStopTrackingAction->setText(QApplication::translate("MainWindow", "Start tracking", nullptr));
#ifndef QT_NO_SHORTCUT
        mStartOrStopTrackingAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+T", nullptr));
#endif // QT_NO_SHORTCUT
        mUndoEditAction->setText(QApplication::translate("MainWindow", "Undo", nullptr));
#ifndef QT_NO_SHORTCUT
        mUndoEditAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_NO_SHORTCUT
        mRedoEditAction->setText(QApplication::translate("MainWindow", "Redo", nullptr));
#ifndef QT_NO_SHORTCUT
        mRedoEditAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+Z", nullptr));
#endif // QT_NO_SHORTCUT
        mCutEditAction->setText(QApplication::translate("MainWindow", "Cut", nullptr));
#ifndef QT_NO_SHORTCUT
        mCutEditAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_NO_SHORTCUT
        mCopyEditAction->setText(QApplication::translate("MainWindow", "Copy", nullptr));
#ifndef QT_NO_SHORTCUT
        mCopyEditAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_NO_SHORTCUT
        mPasteEditAction->setText(QApplication::translate("MainWindow", "Paste", nullptr));
#ifndef QT_NO_SHORTCUT
        mPasteEditAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_NO_SHORTCUT
        mDeleteEditAction->setText(QApplication::translate("MainWindow", "Delete", nullptr));
        mSelectAllEditAction->setText(QApplication::translate("MainWindow", "Select all note", nullptr));
#ifndef QT_NO_SHORTCUT
        mSelectAllEditAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_NO_SHORTCUT
        mAboutAction->setText(QApplication::translate("MainWindow", "About...", nullptr));
        mTimelineAction->setText(QApplication::translate("MainWindow", "Timeline...", nullptr));
        mTimeReportAction->setText(QApplication::translate("MainWindow", "Time report...", nullptr));
        mShowToolbarAction->setText(QApplication::translate("MainWindow", "Show toolbar", nullptr));
        mAttachmentsAction->setText(QApplication::translate("MainWindow", "Attachments", nullptr));
#ifndef QT_NO_TOOLTIP
        mAttachmentsAction->setToolTip(QApplication::translate("MainWindow", "View&edit attachments", nullptr));
#endif // QT_NO_TOOLTIP
        mCheckForUpdatesAction->setText(QApplication::translate("MainWindow", "Check for updates...", nullptr));
        mTimeTrackableAction->setText(QApplication::translate("MainWindow", "Time trackable", nullptr));
        mActionSearchInTasks->setText(QApplication::translate("MainWindow", "Find in tasks...", nullptr));
#ifndef QT_NO_SHORTCUT
        mActionSearchInTasks->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+F", nullptr));
#endif // QT_NO_SHORTCUT
        mActionSearch->setText(QApplication::translate("MainWindow", "Find...", nullptr));
#ifndef QT_NO_SHORTCUT
        mActionSearch->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", nullptr));
#endif // QT_NO_SHORTCUT
        mShowLittAction->setText(QApplication::translate("MainWindow", "Show Litt window", nullptr));
#ifndef QT_NO_TOOLTIP
        mShowLittAction->setToolTip(QApplication::translate("MainWindow", "Bring Litt window to foreground", nullptr));
#endif // QT_NO_TOOLTIP
        mFocusTaskTreeAction->setText(QApplication::translate("MainWindow", "Switch to task tree", nullptr));
#ifndef QT_NO_SHORTCUT
        mFocusTaskTreeAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+1", nullptr));
#endif // QT_NO_SHORTCUT
        mFocusTaskTextAction->setText(QApplication::translate("MainWindow", "Switch to task text", nullptr));
#ifndef QT_NO_SHORTCUT
        mFocusTaskTextAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+2", nullptr));
#endif // QT_NO_SHORTCUT
        mAddSiblingAction->setText(QApplication::translate("MainWindow", "Add sibling", nullptr));
#ifndef QT_NO_TOOLTIP
        mAddSiblingAction->setToolTip(QApplication::translate("MainWindow", "Add sibling document", nullptr));
#endif // QT_NO_TOOLTIP
        mDecreaseLevelAction->setText(QApplication::translate("MainWindow", "Decrease level", nullptr));
#ifndef QT_NO_TOOLTIP
        mDecreaseLevelAction->setToolTip(QApplication::translate("MainWindow", "Decrease document level", nullptr));
#endif // QT_NO_TOOLTIP
        mIncreaseLevelAction->setText(QApplication::translate("MainWindow", "Increase level", nullptr));
#ifndef QT_NO_TOOLTIP
        mIncreaseLevelAction->setToolTip(QApplication::translate("MainWindow", "Increase document level", nullptr));
#endif // QT_NO_TOOLTIP
        mMoveUpAction->setText(QApplication::translate("MainWindow", "Move up", nullptr));
#ifndef QT_NO_TOOLTIP
        mMoveUpAction->setToolTip(QApplication::translate("MainWindow", "Move document up", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        mMoveUpAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+Up", nullptr));
#endif // QT_NO_SHORTCUT
        mMoveDownAction->setText(QApplication::translate("MainWindow", "Move down", nullptr));
#ifndef QT_NO_TOOLTIP
        mMoveDownAction->setToolTip(QApplication::translate("MainWindow", "Move document down", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        mMoveDownAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+Down", nullptr));
#endif // QT_NO_SHORTCUT
        label->setText(QApplication::translate("MainWindow", "Find:", nullptr));
        mTodayTextLabel->setText(QApplication::translate("MainWindow", "Today:", nullptr));
        mTodaySpentTimeLabel->setText(QApplication::translate("MainWindow", "0 hours 0 minutes", nullptr));
        mThisMonthTextLabel->setText(QApplication::translate("MainWindow", "This month:", nullptr));
        mThisMonthSpentTimeLabel->setText(QApplication::translate("MainWindow", "0 hours 0 minutes", nullptr));
        mFileMenu->setTitle(QApplication::translate("MainWindow", "&File", nullptr));
        mEditMenu->setTitle(QApplication::translate("MainWindow", "Edit", nullptr));
        mToolsMenu->setTitle(QApplication::translate("MainWindow", "&Tools", nullptr));
        mStartRecentTaskMenu->setTitle(QApplication::translate("MainWindow", "Track recent task", nullptr));
        mViewMenu->setTitle(QApplication::translate("MainWindow", "View", nullptr));
        mMainToolbar->setWindowTitle(QApplication::translate("MainWindow", "Toolbar", nullptr));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
