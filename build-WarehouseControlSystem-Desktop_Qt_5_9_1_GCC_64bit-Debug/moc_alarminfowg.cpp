/****************************************************************************
** Meta object code from reading C++ file 'alarminfowg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WarehouseControlSystem/Forms/AlarmInfo/alarminfowg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'alarminfowg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MySqlTableModel_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MySqlTableModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MySqlTableModel_t qt_meta_stringdata_MySqlTableModel = {
    {
QT_MOC_LITERAL(0, 0, 15) // "MySqlTableModel"

    },
    "MySqlTableModel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MySqlTableModel[] = {

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

void MySqlTableModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject MySqlTableModel::staticMetaObject = {
    { &QSqlTableModel::staticMetaObject, qt_meta_stringdata_MySqlTableModel.data,
      qt_meta_data_MySqlTableModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MySqlTableModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MySqlTableModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MySqlTableModel.stringdata0))
        return static_cast<void*>(const_cast< MySqlTableModel*>(this));
    return QSqlTableModel::qt_metacast(_clname);
}

int MySqlTableModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSqlTableModel::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_AlarmInfoWg_t {
    QByteArrayData data[4];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AlarmInfoWg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AlarmInfoWg_t qt_meta_stringdata_AlarmInfoWg = {
    {
QT_MOC_LITERAL(0, 0, 11), // "AlarmInfoWg"
QT_MOC_LITERAL(1, 12, 18), // "slotSlectTableInfo"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 20) // "slotRefreshTableInfo"

    },
    "AlarmInfoWg\0slotSlectTableInfo\0\0"
    "slotRefreshTableInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AlarmInfoWg[] = {

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
       1,    0,   24,    2, 0x08 /* Private */,
       3,    0,   25,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AlarmInfoWg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AlarmInfoWg *_t = static_cast<AlarmInfoWg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotSlectTableInfo(); break;
        case 1: _t->slotRefreshTableInfo(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject AlarmInfoWg::staticMetaObject = {
    { &BaseFrom::staticMetaObject, qt_meta_stringdata_AlarmInfoWg.data,
      qt_meta_data_AlarmInfoWg,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AlarmInfoWg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AlarmInfoWg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AlarmInfoWg.stringdata0))
        return static_cast<void*>(const_cast< AlarmInfoWg*>(this));
    return BaseFrom::qt_metacast(_clname);
}

int AlarmInfoWg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseFrom::qt_metacall(_c, _id, _a);
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
