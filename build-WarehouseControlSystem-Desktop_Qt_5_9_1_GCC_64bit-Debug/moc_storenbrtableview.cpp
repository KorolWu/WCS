/****************************************************************************
** Meta object code from reading C++ file 'storenbrtableview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WarehouseControlSystem/Forms/StorePosInfo/storenbrtableview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'storenbrtableview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StorenbrTableView_t {
    QByteArrayData data[20];
    char stringdata0[234];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StorenbrTableView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StorenbrTableView_t qt_meta_stringdata_StorenbrTableView = {
    {
QT_MOC_LITERAL(0, 0, 17), // "StorenbrTableView"
QT_MOC_LITERAL(1, 18, 17), // "signalEditRowData"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 7), // "nbrinfo"
QT_MOC_LITERAL(4, 45, 3), // "row"
QT_MOC_LITERAL(5, 49, 16), // "signalDelRowData"
QT_MOC_LITERAL(6, 66, 25), // "signalTableDataSizechange"
QT_MOC_LITERAL(7, 92, 4), // "size"
QT_MOC_LITERAL(8, 97, 20), // "SlotCheckstatChanged"
QT_MOC_LITERAL(9, 118, 5), // "check"
QT_MOC_LITERAL(10, 124, 3), // "nbr"
QT_MOC_LITERAL(11, 128, 18), // "SlotEditBtnClicked"
QT_MOC_LITERAL(12, 147, 6), // "column"
QT_MOC_LITERAL(13, 154, 17), // "SlotDelBtnClicked"
QT_MOC_LITERAL(14, 172, 15), // "SlotFindNbrinfo"
QT_MOC_LITERAL(15, 188, 4), // "info"
QT_MOC_LITERAL(16, 193, 14), // "SlotaddNbrInfo"
QT_MOC_LITERAL(17, 208, 4), // "list"
QT_MOC_LITERAL(18, 213, 12), // "SlotEditInfo"
QT_MOC_LITERAL(19, 226, 7) // "newlist"

    },
    "StorenbrTableView\0signalEditRowData\0"
    "\0nbrinfo\0row\0signalDelRowData\0"
    "signalTableDataSizechange\0size\0"
    "SlotCheckstatChanged\0check\0nbr\0"
    "SlotEditBtnClicked\0column\0SlotDelBtnClicked\0"
    "SlotFindNbrinfo\0info\0SlotaddNbrInfo\0"
    "list\0SlotEditInfo\0newlist"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StorenbrTableView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x06 /* Public */,
       5,    2,   69,    2, 0x06 /* Public */,
       6,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    3,   77,    2, 0x0a /* Public */,
      11,    2,   84,    2, 0x0a /* Public */,
      13,    2,   89,    2, 0x0a /* Public */,
      14,    2,   94,    2, 0x0a /* Public */,
      14,    1,   99,    2, 0x2a /* Public | MethodCloned */,
      16,    1,  102,    2, 0x0a /* Public */,
      18,    2,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString,    4,    9,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   15,   12,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QStringList,   17,
    QMetaType::Void, QMetaType::QStringList, QMetaType::Int,   19,    4,

       0        // eod
};

void StorenbrTableView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StorenbrTableView *_t = static_cast<StorenbrTableView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalEditRowData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->signalDelRowData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->signalTableDataSizechange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->SlotCheckstatChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 4: _t->SlotEditBtnClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->SlotDelBtnClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->SlotFindNbrinfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->SlotFindNbrinfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->SlotaddNbrInfo((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 9: _t->SlotEditInfo((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (StorenbrTableView::*_t)(QString , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StorenbrTableView::signalEditRowData)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (StorenbrTableView::*_t)(QString , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StorenbrTableView::signalDelRowData)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (StorenbrTableView::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StorenbrTableView::signalTableDataSizechange)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject StorenbrTableView::staticMetaObject = {
    { &QTableView::staticMetaObject, qt_meta_stringdata_StorenbrTableView.data,
      qt_meta_data_StorenbrTableView,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *StorenbrTableView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StorenbrTableView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StorenbrTableView.stringdata0))
        return static_cast<void*>(const_cast< StorenbrTableView*>(this));
    return QTableView::qt_metacast(_clname);
}

int StorenbrTableView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void StorenbrTableView::signalEditRowData(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StorenbrTableView::signalDelRowData(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void StorenbrTableView::signalTableDataSizechange(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
