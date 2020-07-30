/****************************************************************************
** Meta object code from reading C++ file 'storenbrinfotablemodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WarehouseControlSystem/Forms/StorePosInfo/storenbrinfotablemodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'storenbrinfotablemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StorenbrInfoTablemodel_t {
    QByteArrayData data[6];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StorenbrInfoTablemodel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StorenbrInfoTablemodel_t qt_meta_stringdata_StorenbrInfoTablemodel = {
    {
QT_MOC_LITERAL(0, 0, 22), // "StorenbrInfoTablemodel"
QT_MOC_LITERAL(1, 23, 22), // "signalCheckDatachanged"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 8), // "rowindex"
QT_MOC_LITERAL(4, 56, 5), // "check"
QT_MOC_LITERAL(5, 62, 3) // "nbr"

    },
    "StorenbrInfoTablemodel\0signalCheckDatachanged\0"
    "\0rowindex\0check\0nbr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StorenbrInfoTablemodel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString,    3,    4,    5,

       0        // eod
};

void StorenbrInfoTablemodel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StorenbrInfoTablemodel *_t = static_cast<StorenbrInfoTablemodel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalCheckDatachanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (StorenbrInfoTablemodel::*_t)(int , bool , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StorenbrInfoTablemodel::signalCheckDatachanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject StorenbrInfoTablemodel::staticMetaObject = {
    { &QSqlQueryModel::staticMetaObject, qt_meta_stringdata_StorenbrInfoTablemodel.data,
      qt_meta_data_StorenbrInfoTablemodel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *StorenbrInfoTablemodel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StorenbrInfoTablemodel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StorenbrInfoTablemodel.stringdata0))
        return static_cast<void*>(const_cast< StorenbrInfoTablemodel*>(this));
    return QSqlQueryModel::qt_metacast(_clname);
}

int StorenbrInfoTablemodel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSqlQueryModel::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void StorenbrInfoTablemodel::signalCheckDatachanged(int _t1, bool _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
