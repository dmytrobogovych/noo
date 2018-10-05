/****************************************************************************
** Meta object code from reading C++ file 'timereportwizard.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "timereportwizard.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'timereportwizard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TaskTreePage_t {
    QByteArrayData data[3];
    char stringdata0[23];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TaskTreePage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TaskTreePage_t qt_meta_stringdata_TaskTreePage = {
    {
QT_MOC_LITERAL(0, 0, 12), // "TaskTreePage"
QT_MOC_LITERAL(1, 13, 8), // "accepted"
QT_MOC_LITERAL(2, 22, 0) // ""

    },
    "TaskTreePage\0accepted\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TaskTreePage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void TaskTreePage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TaskTreePage *_t = static_cast<TaskTreePage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->accepted(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TaskTreePage::staticMetaObject = {
    { &QWizardPage::staticMetaObject, qt_meta_stringdata_TaskTreePage.data,
      qt_meta_data_TaskTreePage,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TaskTreePage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TaskTreePage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TaskTreePage.stringdata0))
        return static_cast<void*>(this);
    return QWizardPage::qt_metacast(_clname);
}

int TaskTreePage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_CumulativeOptionPage_t {
    QByteArrayData data[4];
    char stringdata0[38];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CumulativeOptionPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CumulativeOptionPage_t qt_meta_stringdata_CumulativeOptionPage = {
    {
QT_MOC_LITERAL(0, 0, 20), // "CumulativeOptionPage"
QT_MOC_LITERAL(1, 21, 9), // "onChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 5) // "value"

    },
    "CumulativeOptionPage\0onChanged\0\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CumulativeOptionPage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void CumulativeOptionPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CumulativeOptionPage *_t = static_cast<CumulativeOptionPage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CumulativeOptionPage::staticMetaObject = {
    { &QWizardPage::staticMetaObject, qt_meta_stringdata_CumulativeOptionPage.data,
      qt_meta_data_CumulativeOptionPage,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CumulativeOptionPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CumulativeOptionPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CumulativeOptionPage.stringdata0))
        return static_cast<void*>(this);
    return QWizardPage::qt_metacast(_clname);
}

int CumulativeOptionPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_DateIntervalPage_t {
    QByteArrayData data[1];
    char stringdata0[17];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DateIntervalPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DateIntervalPage_t qt_meta_stringdata_DateIntervalPage = {
    {
QT_MOC_LITERAL(0, 0, 16) // "DateIntervalPage"

    },
    "DateIntervalPage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DateIntervalPage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void DateIntervalPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject DateIntervalPage::staticMetaObject = {
    { &QWizardPage::staticMetaObject, qt_meta_stringdata_DateIntervalPage.data,
      qt_meta_data_DateIntervalPage,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DateIntervalPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DateIntervalPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DateIntervalPage.stringdata0))
        return static_cast<void*>(this);
    return QWizardPage::qt_metacast(_clname);
}

int DateIntervalPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_ReportViewPage_t {
    QByteArrayData data[1];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ReportViewPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ReportViewPage_t qt_meta_stringdata_ReportViewPage = {
    {
QT_MOC_LITERAL(0, 0, 14) // "ReportViewPage"

    },
    "ReportViewPage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ReportViewPage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void ReportViewPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ReportViewPage::staticMetaObject = {
    { &QWizardPage::staticMetaObject, qt_meta_stringdata_ReportViewPage.data,
      qt_meta_data_ReportViewPage,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ReportViewPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ReportViewPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ReportViewPage.stringdata0))
        return static_cast<void*>(this);
    return QWizardPage::qt_metacast(_clname);
}

int ReportViewPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_TimeReportWizard_t {
    QByteArrayData data[5];
    char stringdata0[58];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TimeReportWizard_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TimeReportWizard_t qt_meta_stringdata_TimeReportWizard = {
    {
QT_MOC_LITERAL(0, 0, 16), // "TimeReportWizard"
QT_MOC_LITERAL(1, 17, 14), // "wizardFinished"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 17), // "wizardPageChanged"
QT_MOC_LITERAL(4, 51, 6) // "pageId"

    },
    "TimeReportWizard\0wizardFinished\0\0"
    "wizardPageChanged\0pageId"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TimeReportWizard[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    1,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,

       0        // eod
};

void TimeReportWizard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TimeReportWizard *_t = static_cast<TimeReportWizard *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->wizardFinished(); break;
        case 1: _t->wizardPageChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject TimeReportWizard::staticMetaObject = {
    { &QWizard::staticMetaObject, qt_meta_stringdata_TimeReportWizard.data,
      qt_meta_data_TimeReportWizard,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TimeReportWizard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TimeReportWizard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TimeReportWizard.stringdata0))
        return static_cast<void*>(this);
    return QWizard::qt_metacast(_clname);
}

int TimeReportWizard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizard::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
