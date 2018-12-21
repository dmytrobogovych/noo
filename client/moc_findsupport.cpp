/****************************************************************************
** Meta object code from reading C++ file 'findsupport.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "findsupport.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'findsupport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FindResultsModel_t {
    QByteArrayData data[5];
    char stringdata0[46];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FindResultsModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FindResultsModel_t qt_meta_stringdata_FindResultsModel = {
    {
QT_MOC_LITERAL(0, 0, 16), // "FindResultsModel"
QT_MOC_LITERAL(1, 17, 7), // "addItem"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 14), // "FindResultItem"
QT_MOC_LITERAL(4, 41, 4) // "item"

    },
    "FindResultsModel\0addItem\0\0FindResultItem\0"
    "item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FindResultsModel[] = {

 // content:
       8,       // revision
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
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void FindResultsModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FindResultsModel *_t = static_cast<FindResultsModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addItem((*reinterpret_cast< const FindResultItem(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< FindResultItem >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FindResultsModel::staticMetaObject = { {
    &QAbstractTableModel::staticMetaObject,
    qt_meta_stringdata_FindResultsModel.data,
    qt_meta_data_FindResultsModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FindResultsModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FindResultsModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FindResultsModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int FindResultsModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_TaskSearch_t {
    QByteArrayData data[6];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TaskSearch_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TaskSearch_t qt_meta_stringdata_TaskSearch = {
    {
QT_MOC_LITERAL(0, 0, 10), // "TaskSearch"
QT_MOC_LITERAL(1, 11, 18), // "newResultAvailable"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 14), // "FindResultItem"
QT_MOC_LITERAL(4, 46, 4), // "item"
QT_MOC_LITERAL(5, 51, 14) // "searchComplete"

    },
    "TaskSearch\0newResultAvailable\0\0"
    "FindResultItem\0item\0searchComplete"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TaskSearch[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       5,    0,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

void TaskSearch::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TaskSearch *_t = static_cast<TaskSearch *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newResultAvailable((*reinterpret_cast< const FindResultItem(*)>(_a[1]))); break;
        case 1: _t->searchComplete(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< FindResultItem >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TaskSearch::*)(const FindResultItem & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TaskSearch::newResultAvailable)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TaskSearch::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TaskSearch::searchComplete)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TaskSearch::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_TaskSearch.data,
    qt_meta_data_TaskSearch,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TaskSearch::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TaskSearch::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TaskSearch.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int TaskSearch::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void TaskSearch::newResultAvailable(const FindResultItem & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TaskSearch::searchComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
