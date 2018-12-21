/****************************************************************************
** Meta object code from reading C++ file 'preferencesdlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "preferencesdlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'preferencesdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PreferencesDlg_t {
    QByteArrayData data[9];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PreferencesDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PreferencesDlg_t qt_meta_stringdata_PreferencesDlg = {
    {
QT_MOC_LITERAL(0, 0, 14), // "PreferencesDlg"
QT_MOC_LITERAL(1, 15, 14), // "selectDatabase"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 8), // "accepted"
QT_MOC_LITERAL(4, 40, 23), // "smartStopSettingChanged"
QT_MOC_LITERAL(5, 64, 1), // "v"
QT_MOC_LITERAL(6, 66, 24), // "smartStartSettingChanged"
QT_MOC_LITERAL(7, 91, 19), // "smartStopWayChanged"
QT_MOC_LITERAL(8, 111, 27) // "allowStartAfterIdleControls"

    },
    "PreferencesDlg\0selectDatabase\0\0accepted\0"
    "smartStopSettingChanged\0v\0"
    "smartStartSettingChanged\0smartStopWayChanged\0"
    "allowStartAfterIdleControls"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PreferencesDlg[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    1,   46,    2, 0x08 /* Private */,
       6,    1,   49,    2, 0x08 /* Private */,
       7,    0,   52,    2, 0x08 /* Private */,
       8,    0,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PreferencesDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PreferencesDlg *_t = static_cast<PreferencesDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->selectDatabase(); break;
        case 1: _t->accepted(); break;
        case 2: _t->smartStopSettingChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->smartStartSettingChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->smartStopWayChanged(); break;
        case 5: _t->allowStartAfterIdleControls(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PreferencesDlg::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_PreferencesDlg.data,
    qt_meta_data_PreferencesDlg,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PreferencesDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PreferencesDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PreferencesDlg.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int PreferencesDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
