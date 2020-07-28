/****************************************************************************
** Meta object code from reading C++ file 'KCommunication.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../WarehouseControlSystem/UnitClass/KCommunication.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KCommunication.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_KCommunication__KTcpserver_t {
    QByteArrayData data[4];
    char stringdata0[52];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KCommunication__KTcpserver_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KCommunication__KTcpserver_t qt_meta_stringdata_KCommunication__KTcpserver = {
    {
QT_MOC_LITERAL(0, 0, 26), // "KCommunication::KTcpserver"
QT_MOC_LITERAL(1, 27, 17), // "onTcpServerResive"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 5) // "array"

    },
    "KCommunication::KTcpserver\0onTcpServerResive\0"
    "\0array"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KCommunication__KTcpserver[] = {

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
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,

       0        // eod
};

void KCommunication::KTcpserver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KTcpserver *_t = static_cast<KTcpserver *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onTcpServerResive((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KTcpserver::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KTcpserver::onTcpServerResive)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject KCommunication::KTcpserver::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KCommunication__KTcpserver.data,
      qt_meta_data_KCommunication__KTcpserver,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *KCommunication::KTcpserver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KCommunication::KTcpserver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KCommunication__KTcpserver.stringdata0))
        return static_cast<void*>(const_cast< KTcpserver*>(this));
    return QObject::qt_metacast(_clname);
}

int KCommunication::KTcpserver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void KCommunication::KTcpserver::onTcpServerResive(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_KCommunication__KTcpClient_t {
    QByteArrayData data[5];
    char stringdata0[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KCommunication__KTcpClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KCommunication__KTcpClient_t qt_meta_stringdata_KCommunication__KTcpClient = {
    {
QT_MOC_LITERAL(0, 0, 26), // "KCommunication::KTcpClient"
QT_MOC_LITERAL(1, 27, 17), // "onTcpClientResive"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 4), // "buff"
QT_MOC_LITERAL(4, 51, 16) // "clientDisconnect"

    },
    "KCommunication::KTcpClient\0onTcpClientResive\0"
    "\0buff\0clientDisconnect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KCommunication__KTcpClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       4,    0,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void,

       0        // eod
};

void KCommunication::KTcpClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KTcpClient *_t = static_cast<KTcpClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onTcpClientResive((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->clientDisconnect(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KTcpClient::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KTcpClient::onTcpClientResive)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (KTcpClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KTcpClient::clientDisconnect)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject KCommunication::KTcpClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KCommunication__KTcpClient.data,
      qt_meta_data_KCommunication__KTcpClient,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *KCommunication::KTcpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KCommunication::KTcpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KCommunication__KTcpClient.stringdata0))
        return static_cast<void*>(const_cast< KTcpClient*>(this));
    return QObject::qt_metacast(_clname);
}

int KCommunication::KTcpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void KCommunication::KTcpClient::onTcpClientResive(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KCommunication::KTcpClient::clientDisconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_KCommunication__KSerialPort_t {
    QByteArrayData data[4];
    char stringdata0[48];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KCommunication__KSerialPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KCommunication__KSerialPort_t qt_meta_stringdata_KCommunication__KSerialPort = {
    {
QT_MOC_LITERAL(0, 0, 27), // "KCommunication::KSerialPort"
QT_MOC_LITERAL(1, 28, 14), // "onSerialResive"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 3) // "str"

    },
    "KCommunication::KSerialPort\0onSerialResive\0"
    "\0str"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KCommunication__KSerialPort[] = {

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
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void KCommunication::KSerialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KSerialPort *_t = static_cast<KSerialPort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onSerialResive((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KSerialPort::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KSerialPort::onSerialResive)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject KCommunication::KSerialPort::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KCommunication__KSerialPort.data,
      qt_meta_data_KCommunication__KSerialPort,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *KCommunication::KSerialPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KCommunication::KSerialPort::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KCommunication__KSerialPort.stringdata0))
        return static_cast<void*>(const_cast< KSerialPort*>(this));
    return QObject::qt_metacast(_clname);
}

int KCommunication::KSerialPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void KCommunication::KSerialPort::onSerialResive(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_KCommunication__KModbusTcpClient_t {
    QByteArrayData data[1];
    char stringdata0[33];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KCommunication__KModbusTcpClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KCommunication__KModbusTcpClient_t qt_meta_stringdata_KCommunication__KModbusTcpClient = {
    {
QT_MOC_LITERAL(0, 0, 32) // "KCommunication::KModbusTcpClient"

    },
    "KCommunication::KModbusTcpClient"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KCommunication__KModbusTcpClient[] = {

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

void KCommunication::KModbusTcpClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject KCommunication::KModbusTcpClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KCommunication__KModbusTcpClient.data,
      qt_meta_data_KCommunication__KModbusTcpClient,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *KCommunication::KModbusTcpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KCommunication::KModbusTcpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KCommunication__KModbusTcpClient.stringdata0))
        return static_cast<void*>(const_cast< KModbusTcpClient*>(this));
    return QObject::qt_metacast(_clname);
}

int KCommunication::KModbusTcpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
