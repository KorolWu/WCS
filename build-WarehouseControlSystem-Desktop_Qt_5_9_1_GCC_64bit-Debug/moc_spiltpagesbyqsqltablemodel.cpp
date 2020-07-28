/****************************************************************************
** Meta object code from reading C++ file 'spiltpagesbyqsqltablemodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WarehouseControlSystem/UnitClass/TablepageWgClass/spiltpagesbyqsqltablemodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'spiltpagesbyqsqltablemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SpiltPagesByQSqlTableModel_t {
    QByteArrayData data[5];
    char stringdata0[64];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SpiltPagesByQSqlTableModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SpiltPagesByQSqlTableModel_t qt_meta_stringdata_SpiltPagesByQSqlTableModel = {
    {
QT_MOC_LITERAL(0, 0, 26), // "SpiltPagesByQSqlTableModel"
QT_MOC_LITERAL(1, 27, 11), // "slotprepage"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 12), // "slotNextpage"
QT_MOC_LITERAL(4, 53, 10) // "slotToPage"

    },
    "SpiltPagesByQSqlTableModel\0slotprepage\0"
    "\0slotNextpage\0slotToPage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SpiltPagesByQSqlTableModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    0,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SpiltPagesByQSqlTableModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SpiltPagesByQSqlTableModel *_t = static_cast<SpiltPagesByQSqlTableModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotprepage(); break;
        case 1: _t->slotNextpage(); break;
        case 2: _t->slotToPage(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SpiltPagesByQSqlTableModel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SpiltPagesByQSqlTableModel.data,
      qt_meta_data_SpiltPagesByQSqlTableModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SpiltPagesByQSqlTableModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpiltPagesByQSqlTableModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SpiltPagesByQSqlTableModel.stringdata0))
        return static_cast<void*>(const_cast< SpiltPagesByQSqlTableModel*>(this));
    return QWidget::qt_metacast(_clname);
}

int SpiltPagesByQSqlTableModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
