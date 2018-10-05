/****************************************************************************
** Meta object code from reading C++ file 'stopworkdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stopworkdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stopworkdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StopWorkDialog_t {
    QByteArrayData data[8];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StopWorkDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StopWorkDialog_t qt_meta_stringdata_StopWorkDialog = {
    {
QT_MOC_LITERAL(0, 0, 14), // "StopWorkDialog"
QT_MOC_LITERAL(1, 15, 16), // "continueTracking"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 13), // "breakTracking"
QT_MOC_LITERAL(4, 47, 8), // "stopTime"
QT_MOC_LITERAL(5, 56, 20), // "onYesButtonTriggered"
QT_MOC_LITERAL(6, 77, 19), // "onNoButtonTriggered"
QT_MOC_LITERAL(7, 97, 22) // "onFinishTimerTriggered"

    },
    "StopWorkDialog\0continueTracking\0\0"
    "breakTracking\0stopTime\0onYesButtonTriggered\0"
    "onNoButtonTriggered\0onFinishTimerTriggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StopWorkDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   43,    2, 0x08 /* Private */,
       6,    0,   44,    2, 0x08 /* Private */,
       7,    0,   45,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDateTime,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void StopWorkDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StopWorkDialog *_t = static_cast<StopWorkDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->continueTracking(); break;
        case 1: _t->breakTracking((*reinterpret_cast< const QDateTime(*)>(_a[1]))); break;
        case 2: _t->onYesButtonTriggered(); break;
        case 3: _t->onNoButtonTriggered(); break;
        case 4: _t->onFinishTimerTriggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (StopWorkDialog::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StopWorkDialog::continueTracking)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (StopWorkDialog::*_t)(const QDateTime & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StopWorkDialog::breakTracking)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject StopWorkDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_StopWorkDialog.data,
      qt_meta_data_StopWorkDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *StopWorkDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StopWorkDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StopWorkDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int StopWorkDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void StopWorkDialog::continueTracking()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void StopWorkDialog::breakTracking(const QDateTime & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
