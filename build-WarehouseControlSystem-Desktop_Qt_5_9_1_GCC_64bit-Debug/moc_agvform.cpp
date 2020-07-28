/****************************************************************************
** Meta object code from reading C++ file 'agvform.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WarehouseControlSystem/Forms/CarForms/agvform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'agvform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AgvForm_t {
    QByteArrayData data[8];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AgvForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AgvForm_t qt_meta_stringdata_AgvForm = {
    {
QT_MOC_LITERAL(0, 0, 7), // "AgvForm"
QT_MOC_LITERAL(1, 8, 13), // "onEditClicked"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 12), // "onAddClicked"
QT_MOC_LITERAL(4, 36, 15), // "onDeleteClicked"
QT_MOC_LITERAL(5, 52, 15), // "tableRowClicked"
QT_MOC_LITERAL(6, 68, 12), // "refreshTable"
QT_MOC_LITERAL(7, 81, 11) // "randomValue"

    },
    "AgvForm\0onEditClicked\0\0onAddClicked\0"
    "onDeleteClicked\0tableRowClicked\0"
    "refreshTable\0randomValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AgvForm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,

       0        // eod
};

void AgvForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AgvForm *_t = static_cast<AgvForm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onEditClicked(); break;
        case 1: _t->onAddClicked(); break;
        case 2: _t->onDeleteClicked(); break;
        case 3: _t->tableRowClicked(); break;
        case 4: _t->refreshTable(); break;
        case 5: { int _r = _t->randomValue();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject AgvForm::staticMetaObject = {
    { &BaseFrom::staticMetaObject, qt_meta_stringdata_AgvForm.data,
      qt_meta_data_AgvForm,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AgvForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AgvForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AgvForm.stringdata0))
        return static_cast<void*>(const_cast< AgvForm*>(this));
    return BaseFrom::qt_metacast(_clname);
}

int AgvForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseFrom::qt_metacall(_c, _id, _a);
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
