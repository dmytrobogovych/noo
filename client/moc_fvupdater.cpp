/****************************************************************************
** Meta object code from reading C++ file 'fvupdater.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "fervor/fvupdater.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fvupdater.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FvUpdater_t {
    QByteArrayData data[16];
    char stringdata0[292];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FvUpdater_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FvUpdater_t qt_meta_stringdata_FvUpdater = {
    {
QT_MOC_LITERAL(0, 0, 9), // "FvUpdater"
QT_MOC_LITERAL(1, 10, 15), // "CheckForUpdates"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 24), // "silentAsMuchAsItCouldGet"
QT_MOC_LITERAL(4, 52, 21), // "CheckForUpdatesSilent"
QT_MOC_LITERAL(5, 74, 24), // "CheckForUpdatesNotSilent"
QT_MOC_LITERAL(6, 99, 13), // "InstallUpdate"
QT_MOC_LITERAL(7, 113, 10), // "SkipUpdate"
QT_MOC_LITERAL(8, 124, 13), // "RemindMeLater"
QT_MOC_LITERAL(9, 138, 27), // "UpdateInstallationConfirmed"
QT_MOC_LITERAL(10, 166, 30), // "UpdateInstallationNotConfirmed"
QT_MOC_LITERAL(11, 197, 17), // "httpFeedReadyRead"
QT_MOC_LITERAL(12, 215, 30), // "httpFeedUpdateDataReadProgress"
QT_MOC_LITERAL(13, 246, 9), // "bytesRead"
QT_MOC_LITERAL(14, 256, 10), // "totalBytes"
QT_MOC_LITERAL(15, 267, 24) // "httpFeedDownloadFinished"

    },
    "FvUpdater\0CheckForUpdates\0\0"
    "silentAsMuchAsItCouldGet\0CheckForUpdatesSilent\0"
    "CheckForUpdatesNotSilent\0InstallUpdate\0"
    "SkipUpdate\0RemindMeLater\0"
    "UpdateInstallationConfirmed\0"
    "UpdateInstallationNotConfirmed\0"
    "httpFeedReadyRead\0httpFeedUpdateDataReadProgress\0"
    "bytesRead\0totalBytes\0httpFeedDownloadFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FvUpdater[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x0a /* Public */,
       1,    0,   77,    2, 0x2a /* Public | MethodCloned */,
       4,    0,   78,    2, 0x0a /* Public */,
       5,    0,   79,    2, 0x0a /* Public */,
       6,    0,   80,    2, 0x09 /* Protected */,
       7,    0,   81,    2, 0x09 /* Protected */,
       8,    0,   82,    2, 0x09 /* Protected */,
       9,    0,   83,    2, 0x09 /* Protected */,
      10,    0,   84,    2, 0x09 /* Protected */,
      11,    0,   85,    2, 0x08 /* Private */,
      12,    2,   86,    2, 0x08 /* Private */,
      15,    0,   91,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Bool, QMetaType::Bool,    3,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   13,   14,
    QMetaType::Void,

       0        // eod
};

void FvUpdater::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FvUpdater *_t = static_cast<FvUpdater *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->CheckForUpdates((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: { bool _r = _t->CheckForUpdates();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: { bool _r = _t->CheckForUpdatesSilent();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { bool _r = _t->CheckForUpdatesNotSilent();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->InstallUpdate(); break;
        case 5: _t->SkipUpdate(); break;
        case 6: _t->RemindMeLater(); break;
        case 7: _t->UpdateInstallationConfirmed(); break;
        case 8: _t->UpdateInstallationNotConfirmed(); break;
        case 9: _t->httpFeedReadyRead(); break;
        case 10: _t->httpFeedUpdateDataReadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 11: _t->httpFeedDownloadFinished(); break;
        default: ;
        }
    }
}

const QMetaObject FvUpdater::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FvUpdater.data,
      qt_meta_data_FvUpdater,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FvUpdater::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FvUpdater::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FvUpdater.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FvUpdater::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
