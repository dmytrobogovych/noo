/****************************************************************************
** Meta object code from reading C++ file 'startworkdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "startworkdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'startworkdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_StartWorkDialog_t {
    QByteArrayData data[7];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StartWorkDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StartWorkDialog_t qt_meta_stringdata_StartWorkDialog = {
    {
QT_MOC_LITERAL(0, 0, 15), // "StartWorkDialog"
QT_MOC_LITERAL(1, 16, 16), // "continueTracking"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 13), // "breakTracking"
QT_MOC_LITERAL(4, 48, 20), // "onYesButtonTriggered"
QT_MOC_LITERAL(5, 69, 19), // "onNoButtonTriggered"
QT_MOC_LITERAL(6, 89, 22) // "onFinishTimerTriggered"

    },
    "StartWorkDialog\0continueTracking\0\0"
    "breakTracking\0onYesButtonTriggered\0"
    "onNoButtonTriggered\0onFinishTimerTriggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StartWorkDialog[] = {

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
       3,    0,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void StartWorkDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StartWorkDialog *_t = static_cast<StartWorkDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->continueTracking(); break;
        case 1: _t->breakTracking(); break;
        case 2: _t->onYesButtonTriggered(); break;
        case 3: _t->onNoButtonTriggered(); break;
        case 4: _t->onFinishTimerTriggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (StartWorkDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StartWorkDialog::continueTracking)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (StartWorkDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StartWorkDialog::breakTracking)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject StartWorkDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_StartWorkDialog.data,
      qt_meta_data_StartWorkDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *StartWorkDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StartWorkDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_StartWorkDialog.stringdata0))
        return static_cast<void*>(const_cast< StartWorkDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int StartWorkDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void StartWorkDialog::continueTracking()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void StartWorkDialog::breakTracking()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
