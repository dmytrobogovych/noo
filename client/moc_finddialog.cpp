/****************************************************************************
** Meta object code from reading C++ file 'finddialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "finddialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'finddialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FindInTasksDialog_t {
    QByteArrayData data[9];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FindInTasksDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FindInTasksDialog_t qt_meta_stringdata_FindInTasksDialog = {
    {
QT_MOC_LITERAL(0, 0, 17), // "FindInTasksDialog"
QT_MOC_LITERAL(1, 18, 11), // "startSearch"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 14), // "resultSelected"
QT_MOC_LITERAL(4, 46, 5), // "index"
QT_MOC_LITERAL(5, 52, 14), // "searchComplete"
QT_MOC_LITERAL(6, 67, 11), // "onNewResult"
QT_MOC_LITERAL(7, 79, 14), // "FindResultItem"
QT_MOC_LITERAL(8, 94, 4) // "item"

    },
    "FindInTasksDialog\0startSearch\0\0"
    "resultSelected\0index\0searchComplete\0"
    "onNewResult\0FindResultItem\0item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FindInTasksDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    1,   35,    2, 0x0a /* Public */,
       5,    0,   38,    2, 0x0a /* Public */,
       6,    1,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void FindInTasksDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FindInTasksDialog *_t = static_cast<FindInTasksDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startSearch(); break;
        case 1: _t->resultSelected((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->searchComplete(); break;
        case 3: _t->onNewResult((*reinterpret_cast< const FindResultItem(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< FindResultItem >(); break;
            }
            break;
        }
    }
}

const QMetaObject FindInTasksDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FindInTasksDialog.data,
      qt_meta_data_FindInTasksDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FindInTasksDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FindInTasksDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FindInTasksDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int FindInTasksDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
