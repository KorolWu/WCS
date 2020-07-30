/****************************************************************************
** Meta object code from reading C++ file 'storeinfowidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WarehouseControlSystem/Forms/StorePosInfo/storeinfowidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'storeinfowidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StoreInfoWidget_t {
    QByteArrayData data[23];
    char stringdata0[298];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StoreInfoWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StoreInfoWidget_t qt_meta_stringdata_StoreInfoWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "StoreInfoWidget"
QT_MOC_LITERAL(1, 16, 14), // "signalfindinfo"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 7), // "nbrinfo"
QT_MOC_LITERAL(4, 40, 6), // "clomun"
QT_MOC_LITERAL(5, 47, 14), // "signalBatchDel"
QT_MOC_LITERAL(6, 62, 17), // "signalUpdatetable"
QT_MOC_LITERAL(7, 80, 3), // "row"
QT_MOC_LITERAL(8, 84, 14), // "slotaddnbrinfo"
QT_MOC_LITERAL(9, 99, 19), // "slotBatchDelnbrinfo"
QT_MOC_LITERAL(10, 119, 14), // "slotquenbrinfo"
QT_MOC_LITERAL(11, 134, 17), // "slotImportnbrinfo"
QT_MOC_LITERAL(12, 152, 17), // "slotExportnbrinfo"
QT_MOC_LITERAL(13, 170, 12), // "slotEditData"
QT_MOC_LITERAL(14, 183, 8), // "datalist"
QT_MOC_LITERAL(15, 192, 16), // "slottableeditbtn"
QT_MOC_LITERAL(16, 209, 18), // "slotSetCurPageData"
QT_MOC_LITERAL(17, 228, 5), // "ipage"
QT_MOC_LITERAL(18, 234, 16), // "SlotDelSinglerow"
QT_MOC_LITERAL(19, 251, 16), // "SlotBatchDelData"
QT_MOC_LITERAL(20, 268, 7), // "nbrlist"
QT_MOC_LITERAL(21, 276, 16), // "SlotupdatePageUI"
QT_MOC_LITERAL(22, 293, 4) // "size"

    },
    "StoreInfoWidget\0signalfindinfo\0\0nbrinfo\0"
    "clomun\0signalBatchDel\0signalUpdatetable\0"
    "row\0slotaddnbrinfo\0slotBatchDelnbrinfo\0"
    "slotquenbrinfo\0slotImportnbrinfo\0"
    "slotExportnbrinfo\0slotEditData\0datalist\0"
    "slottableeditbtn\0slotSetCurPageData\0"
    "ipage\0SlotDelSinglerow\0SlotBatchDelData\0"
    "nbrlist\0SlotupdatePageUI\0size"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StoreInfoWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   84,    2, 0x06 /* Public */,
       5,    0,   89,    2, 0x06 /* Public */,
       6,    2,   90,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   95,    2, 0x08 /* Private */,
       9,    0,   96,    2, 0x08 /* Private */,
      10,    0,   97,    2, 0x08 /* Private */,
      11,    0,   98,    2, 0x08 /* Private */,
      12,    0,   99,    2, 0x08 /* Private */,
      13,    1,  100,    2, 0x08 /* Private */,
      15,    2,  103,    2, 0x08 /* Private */,
      16,    1,  108,    2, 0x08 /* Private */,
      18,    2,  111,    2, 0x0a /* Public */,
      19,    1,  116,    2, 0x0a /* Public */,
      21,    1,  119,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList, QMetaType::Int,    2,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    7,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    7,
    QMetaType::Void, QMetaType::QVariantList,   20,
    QMetaType::Void, QMetaType::Int,   22,

       0        // eod
};

void StoreInfoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StoreInfoWidget *_t = static_cast<StoreInfoWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalfindinfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->signalBatchDel(); break;
        case 2: _t->signalUpdatetable((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->slotaddnbrinfo(); break;
        case 4: _t->slotBatchDelnbrinfo(); break;
        case 5: _t->slotquenbrinfo(); break;
        case 6: _t->slotImportnbrinfo(); break;
        case 7: _t->slotExportnbrinfo(); break;
        case 8: _t->slotEditData((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 9: _t->slottableeditbtn((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->slotSetCurPageData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->SlotDelSinglerow((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->SlotBatchDelData((*reinterpret_cast< QList<QVariant>(*)>(_a[1]))); break;
        case 13: _t->SlotupdatePageUI((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (StoreInfoWidget::*_t)(QString , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StoreInfoWidget::signalfindinfo)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (StoreInfoWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StoreInfoWidget::signalBatchDel)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (StoreInfoWidget::*_t)(QStringList , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StoreInfoWidget::signalUpdatetable)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject StoreInfoWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StoreInfoWidget.data,
      qt_meta_data_StoreInfoWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *StoreInfoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StoreInfoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StoreInfoWidget.stringdata0))
        return static_cast<void*>(const_cast< StoreInfoWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int StoreInfoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void StoreInfoWidget::signalfindinfo(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StoreInfoWidget::signalBatchDel()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void StoreInfoWidget::signalUpdatetable(QStringList _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
