/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[82];
    char stringdata0[1077];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 19), // "onTimeFormatChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 13), // "onTimeChanged"
QT_MOC_LITERAL(4, 46, 4), // "save"
QT_MOC_LITERAL(5, 51, 4), // "sync"
QT_MOC_LITERAL(6, 56, 5), // "about"
QT_MOC_LITERAL(7, 62, 11), // "preferences"
QT_MOC_LITERAL(8, 74, 5), // "print"
QT_MOC_LITERAL(9, 80, 4), // "quit"
QT_MOC_LITERAL(10, 85, 11), // "newRootTask"
QT_MOC_LITERAL(11, 97, 7), // "newTask"
QT_MOC_LITERAL(12, 105, 10), // "newSibling"
QT_MOC_LITERAL(13, 116, 6), // "moveUp"
QT_MOC_LITERAL(14, 123, 8), // "moveDown"
QT_MOC_LITERAL(15, 132, 10), // "renameTask"
QT_MOC_LITERAL(16, 143, 10), // "deleteTask"
QT_MOC_LITERAL(17, 154, 22), // "taskTreeContextualMenu"
QT_MOC_LITERAL(18, 177, 5), // "point"
QT_MOC_LITERAL(19, 183, 16), // "taskIndexChanged"
QT_MOC_LITERAL(20, 200, 12), // "idleDetected"
QT_MOC_LITERAL(21, 213, 16), // "activityDetected"
QT_MOC_LITERAL(22, 230, 19), // "startOrStopTracking"
QT_MOC_LITERAL(23, 250, 13), // "startTracking"
QT_MOC_LITERAL(24, 264, 19), // "startTrackingRecent"
QT_MOC_LITERAL(25, 284, 12), // "stopTracking"
QT_MOC_LITERAL(26, 297, 18), // "TrackingStopReason"
QT_MOC_LITERAL(27, 316, 6), // "reason"
QT_MOC_LITERAL(28, 323, 10), // "currentUtc"
QT_MOC_LITERAL(29, 334, 10), // "updateData"
QT_MOC_LITERAL(30, 345, 9), // "add10Mins"
QT_MOC_LITERAL(31, 355, 20), // "editSelectionChanged"
QT_MOC_LITERAL(32, 376, 19), // "editPositionChanged"
QT_MOC_LITERAL(33, 396, 17), // "editFormatChanged"
QT_MOC_LITERAL(34, 414, 15), // "QTextCharFormat"
QT_MOC_LITERAL(35, 430, 3), // "fmt"
QT_MOC_LITERAL(36, 434, 8), // "editUndo"
QT_MOC_LITERAL(37, 443, 8), // "editRedo"
QT_MOC_LITERAL(38, 452, 7), // "editCut"
QT_MOC_LITERAL(39, 460, 8), // "editCopy"
QT_MOC_LITERAL(40, 469, 9), // "editPaste"
QT_MOC_LITERAL(41, 479, 10), // "editDelete"
QT_MOC_LITERAL(42, 490, 13), // "editSelectAll"
QT_MOC_LITERAL(43, 504, 13), // "iconActivated"
QT_MOC_LITERAL(44, 518, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(45, 552, 17), // "timeFormatChanged"
QT_MOC_LITERAL(46, 570, 12), // "showTimeline"
QT_MOC_LITERAL(47, 583, 14), // "showTimeReport"
QT_MOC_LITERAL(48, 598, 25), // "newPasswordDialogFinished"
QT_MOC_LITERAL(49, 624, 6), // "status"
QT_MOC_LITERAL(50, 631, 22), // "passwordDialogFinished"
QT_MOC_LITERAL(51, 654, 21), // "criticalAlertFinished"
QT_MOC_LITERAL(52, 676, 17), // "openAlertFinished"
QT_MOC_LITERAL(53, 694, 20), // "warningAlertFinished"
QT_MOC_LITERAL(54, 715, 24), // "toolbarVisibilityChanged"
QT_MOC_LITERAL(55, 740, 7), // "visible"
QT_MOC_LITERAL(56, 748, 15), // "showHideToolbar"
QT_MOC_LITERAL(57, 764, 15), // "showAttachments"
QT_MOC_LITERAL(58, 780, 15), // "checkForUpdates"
QT_MOC_LITERAL(59, 796, 11), // "systemSleep"
QT_MOC_LITERAL(60, 808, 12), // "systemResume"
QT_MOC_LITERAL(61, 821, 23), // "changeTimeTrackableFlag"
QT_MOC_LITERAL(62, 845, 9), // "trackable"
QT_MOC_LITERAL(63, 855, 4), // "find"
QT_MOC_LITERAL(64, 860, 11), // "findInTasks"
QT_MOC_LITERAL(65, 872, 13), // "findRequested"
QT_MOC_LITERAL(66, 886, 12), // "findRejected"
QT_MOC_LITERAL(67, 899, 3), // "obj"
QT_MOC_LITERAL(68, 903, 15), // "taskTextChanged"
QT_MOC_LITERAL(69, 919, 9), // "taskMoved"
QT_MOC_LITERAL(70, 929, 5), // "PTask"
QT_MOC_LITERAL(71, 935, 4), // "task"
QT_MOC_LITERAL(72, 940, 13), // "focusTaskTree"
QT_MOC_LITERAL(73, 954, 13), // "focusTaskText"
QT_MOC_LITERAL(74, 968, 14), // "showMainWindow"
QT_MOC_LITERAL(75, 983, 14), // "continueOnIdle"
QT_MOC_LITERAL(76, 998, 11), // "breakOnIdle"
QT_MOC_LITERAL(77, 1010, 8), // "stopTime"
QT_MOC_LITERAL(78, 1019, 15), // "startOnActivity"
QT_MOC_LITERAL(79, 1035, 14), // "stopOnActivity"
QT_MOC_LITERAL(80, 1050, 19), // "trayWindowDestroyed"
QT_MOC_LITERAL(81, 1070, 6) // "object"

    },
    "MainWindow\0onTimeFormatChanged\0\0"
    "onTimeChanged\0save\0sync\0about\0preferences\0"
    "print\0quit\0newRootTask\0newTask\0"
    "newSibling\0moveUp\0moveDown\0renameTask\0"
    "deleteTask\0taskTreeContextualMenu\0"
    "point\0taskIndexChanged\0idleDetected\0"
    "activityDetected\0startOrStopTracking\0"
    "startTracking\0startTrackingRecent\0"
    "stopTracking\0TrackingStopReason\0reason\0"
    "currentUtc\0updateData\0add10Mins\0"
    "editSelectionChanged\0editPositionChanged\0"
    "editFormatChanged\0QTextCharFormat\0fmt\0"
    "editUndo\0editRedo\0editCut\0editCopy\0"
    "editPaste\0editDelete\0editSelectAll\0"
    "iconActivated\0QSystemTrayIcon::ActivationReason\0"
    "timeFormatChanged\0showTimeline\0"
    "showTimeReport\0newPasswordDialogFinished\0"
    "status\0passwordDialogFinished\0"
    "criticalAlertFinished\0openAlertFinished\0"
    "warningAlertFinished\0toolbarVisibilityChanged\0"
    "visible\0showHideToolbar\0showAttachments\0"
    "checkForUpdates\0systemSleep\0systemResume\0"
    "changeTimeTrackableFlag\0trackable\0"
    "find\0findInTasks\0findRequested\0"
    "findRejected\0obj\0taskTextChanged\0"
    "taskMoved\0PTask\0task\0focusTaskTree\0"
    "focusTaskText\0showMainWindow\0"
    "continueOnIdle\0breakOnIdle\0stopTime\0"
    "startOnActivity\0stopOnActivity\0"
    "trayWindowDestroyed\0object"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      66,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  344,    2, 0x06 /* Public */,
       3,    0,  345,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  346,    2, 0x0a /* Public */,
       5,    0,  347,    2, 0x0a /* Public */,
       6,    0,  348,    2, 0x0a /* Public */,
       7,    0,  349,    2, 0x0a /* Public */,
       8,    0,  350,    2, 0x0a /* Public */,
       9,    0,  351,    2, 0x0a /* Public */,
      10,    0,  352,    2, 0x0a /* Public */,
      11,    0,  353,    2, 0x0a /* Public */,
      12,    0,  354,    2, 0x0a /* Public */,
      13,    0,  355,    2, 0x0a /* Public */,
      14,    0,  356,    2, 0x0a /* Public */,
      15,    0,  357,    2, 0x0a /* Public */,
      16,    0,  358,    2, 0x0a /* Public */,
      17,    1,  359,    2, 0x0a /* Public */,
      19,    2,  362,    2, 0x0a /* Public */,
      20,    0,  367,    2, 0x0a /* Public */,
      21,    0,  368,    2, 0x0a /* Public */,
      22,    0,  369,    2, 0x0a /* Public */,
      23,    0,  370,    2, 0x0a /* Public */,
      24,    0,  371,    2, 0x0a /* Public */,
      25,    2,  372,    2, 0x0a /* Public */,
      25,    1,  377,    2, 0x2a /* Public | MethodCloned */,
      29,    0,  380,    2, 0x0a /* Public */,
      30,    0,  381,    2, 0x0a /* Public */,
      31,    0,  382,    2, 0x0a /* Public */,
      32,    0,  383,    2, 0x0a /* Public */,
      33,    1,  384,    2, 0x0a /* Public */,
      36,    0,  387,    2, 0x0a /* Public */,
      37,    0,  388,    2, 0x0a /* Public */,
      38,    0,  389,    2, 0x0a /* Public */,
      39,    0,  390,    2, 0x0a /* Public */,
      40,    0,  391,    2, 0x0a /* Public */,
      41,    0,  392,    2, 0x0a /* Public */,
      42,    0,  393,    2, 0x0a /* Public */,
      43,    1,  394,    2, 0x0a /* Public */,
      45,    0,  397,    2, 0x0a /* Public */,
      46,    0,  398,    2, 0x0a /* Public */,
      47,    0,  399,    2, 0x0a /* Public */,
      48,    1,  400,    2, 0x0a /* Public */,
      50,    1,  403,    2, 0x0a /* Public */,
      51,    1,  406,    2, 0x0a /* Public */,
      52,    1,  409,    2, 0x0a /* Public */,
      53,    1,  412,    2, 0x0a /* Public */,
      54,    1,  415,    2, 0x0a /* Public */,
      56,    0,  418,    2, 0x0a /* Public */,
      57,    0,  419,    2, 0x0a /* Public */,
      58,    0,  420,    2, 0x0a /* Public */,
      59,    0,  421,    2, 0x0a /* Public */,
      60,    0,  422,    2, 0x0a /* Public */,
      61,    1,  423,    2, 0x0a /* Public */,
      63,    0,  426,    2, 0x0a /* Public */,
      64,    0,  427,    2, 0x0a /* Public */,
      65,    0,  428,    2, 0x0a /* Public */,
      66,    1,  429,    2, 0x0a /* Public */,
      68,    0,  432,    2, 0x0a /* Public */,
      69,    1,  433,    2, 0x0a /* Public */,
      72,    0,  436,    2, 0x0a /* Public */,
      73,    0,  437,    2, 0x0a /* Public */,
      74,    0,  438,    2, 0x0a /* Public */,
      75,    0,  439,    2, 0x0a /* Public */,
      76,    1,  440,    2, 0x0a /* Public */,
      78,    0,  443,    2, 0x0a /* Public */,
      79,    0,  444,    2, 0x0a /* Public */,
      80,    1,  445,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   18,
    QMetaType::Void, QMetaType::QModelIndex, QMetaType::QModelIndex,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 26, QMetaType::QDateTime,   27,   28,
    QMetaType::Void, 0x80000000 | 26,   27,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 34,   35,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 44,   27,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   49,
    QMetaType::Void, QMetaType::Int,   49,
    QMetaType::Void, QMetaType::Int,   49,
    QMetaType::Void, QMetaType::Int,   49,
    QMetaType::Void, QMetaType::Int,   49,
    QMetaType::Void, QMetaType::Bool,   55,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   62,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QObjectStar,   67,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 70,   71,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDateTime,   77,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QObjectStar,   81,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onTimeFormatChanged(); break;
        case 1: _t->onTimeChanged(); break;
        case 2: _t->save(); break;
        case 3: _t->sync(); break;
        case 4: _t->about(); break;
        case 5: _t->preferences(); break;
        case 6: _t->print(); break;
        case 7: _t->quit(); break;
        case 8: _t->newRootTask(); break;
        case 9: _t->newTask(); break;
        case 10: _t->newSibling(); break;
        case 11: _t->moveUp(); break;
        case 12: _t->moveDown(); break;
        case 13: _t->renameTask(); break;
        case 14: _t->deleteTask(); break;
        case 15: _t->taskTreeContextualMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 16: _t->taskIndexChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 17: _t->idleDetected(); break;
        case 18: _t->activityDetected(); break;
        case 19: _t->startOrStopTracking(); break;
        case 20: _t->startTracking(); break;
        case 21: _t->startTrackingRecent(); break;
        case 22: _t->stopTracking((*reinterpret_cast< TrackingStopReason(*)>(_a[1])),(*reinterpret_cast< const QDateTime(*)>(_a[2]))); break;
        case 23: _t->stopTracking((*reinterpret_cast< TrackingStopReason(*)>(_a[1]))); break;
        case 24: _t->updateData(); break;
        case 25: _t->add10Mins(); break;
        case 26: _t->editSelectionChanged(); break;
        case 27: _t->editPositionChanged(); break;
        case 28: _t->editFormatChanged((*reinterpret_cast< const QTextCharFormat(*)>(_a[1]))); break;
        case 29: _t->editUndo(); break;
        case 30: _t->editRedo(); break;
        case 31: _t->editCut(); break;
        case 32: _t->editCopy(); break;
        case 33: _t->editPaste(); break;
        case 34: _t->editDelete(); break;
        case 35: _t->editSelectAll(); break;
        case 36: _t->iconActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 37: _t->timeFormatChanged(); break;
        case 38: _t->showTimeline(); break;
        case 39: _t->showTimeReport(); break;
        case 40: _t->newPasswordDialogFinished((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 41: _t->passwordDialogFinished((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 42: _t->criticalAlertFinished((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 43: _t->openAlertFinished((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 44: _t->warningAlertFinished((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 45: _t->toolbarVisibilityChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 46: _t->showHideToolbar(); break;
        case 47: _t->showAttachments(); break;
        case 48: _t->checkForUpdates(); break;
        case 49: _t->systemSleep(); break;
        case 50: _t->systemResume(); break;
        case 51: _t->changeTimeTrackableFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 52: _t->find(); break;
        case 53: _t->findInTasks(); break;
        case 54: _t->findRequested(); break;
        case 55: _t->findRejected((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 56: _t->taskTextChanged(); break;
        case 57: _t->taskMoved((*reinterpret_cast< PTask(*)>(_a[1]))); break;
        case 58: _t->focusTaskTree(); break;
        case 59: _t->focusTaskText(); break;
        case 60: _t->showMainWindow(); break;
        case 61: _t->continueOnIdle(); break;
        case 62: _t->breakOnIdle((*reinterpret_cast< const QDateTime(*)>(_a[1]))); break;
        case 63: _t->startOnActivity(); break;
        case 64: _t->stopOnActivity(); break;
        case 65: _t->trayWindowDestroyed((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::onTimeFormatChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::onTimeChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 66)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 66;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 66)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 66;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::onTimeFormatChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void MainWindow::onTimeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
