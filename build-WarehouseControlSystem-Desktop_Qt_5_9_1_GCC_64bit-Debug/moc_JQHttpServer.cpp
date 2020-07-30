/****************************************************************************
** Meta object code from reading C++ file 'JQHttpServer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SDK/include/library/JQLibrary/include/JQHttpServer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'JQHttpServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_JQHttpServer__Session_t {
    QByteArrayData data[21];
    char stringdata0[233];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JQHttpServer__Session_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JQHttpServer__Session_t qt_meta_stringdata_JQHttpServer__Session = {
    {
QT_MOC_LITERAL(0, 0, 21), // "JQHttpServer::Session"
QT_MOC_LITERAL(1, 22, 9), // "replyText"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 9), // "replyData"
QT_MOC_LITERAL(4, 43, 14), // "httpStatusCode"
QT_MOC_LITERAL(5, 58, 14), // "replyRedirects"
QT_MOC_LITERAL(6, 73, 9), // "targetUrl"
QT_MOC_LITERAL(7, 83, 15), // "replyJsonObject"
QT_MOC_LITERAL(8, 99, 10), // "jsonObject"
QT_MOC_LITERAL(9, 110, 14), // "replyJsonArray"
QT_MOC_LITERAL(10, 125, 9), // "jsonArray"
QT_MOC_LITERAL(11, 135, 9), // "replyFile"
QT_MOC_LITERAL(12, 145, 8), // "filePath"
QT_MOC_LITERAL(13, 154, 8), // "fileName"
QT_MOC_LITERAL(14, 163, 8), // "fileData"
QT_MOC_LITERAL(15, 172, 10), // "replyImage"
QT_MOC_LITERAL(16, 183, 5), // "image"
QT_MOC_LITERAL(17, 189, 13), // "imageFilePath"
QT_MOC_LITERAL(18, 203, 10), // "replyBytes"
QT_MOC_LITERAL(19, 214, 5), // "bytes"
QT_MOC_LITERAL(20, 220, 12) // "replyOptions"

    },
    "JQHttpServer::Session\0replyText\0\0"
    "replyData\0httpStatusCode\0replyRedirects\0"
    "targetUrl\0replyJsonObject\0jsonObject\0"
    "replyJsonArray\0jsonArray\0replyFile\0"
    "filePath\0fileName\0fileData\0replyImage\0"
    "image\0imageFilePath\0replyBytes\0bytes\0"
    "replyOptions"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JQHttpServer__Session[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,  109,    2, 0x0a /* Public */,
       1,    1,  114,    2, 0x2a /* Public | MethodCloned */,
       5,    2,  117,    2, 0x0a /* Public */,
       5,    1,  122,    2, 0x2a /* Public | MethodCloned */,
       7,    2,  125,    2, 0x0a /* Public */,
       7,    1,  130,    2, 0x2a /* Public | MethodCloned */,
       9,    2,  133,    2, 0x0a /* Public */,
       9,    1,  138,    2, 0x2a /* Public | MethodCloned */,
      11,    2,  141,    2, 0x0a /* Public */,
      11,    1,  146,    2, 0x2a /* Public | MethodCloned */,
      11,    3,  149,    2, 0x0a /* Public */,
      11,    2,  156,    2, 0x2a /* Public | MethodCloned */,
      15,    2,  161,    2, 0x0a /* Public */,
      15,    1,  166,    2, 0x2a /* Public | MethodCloned */,
      15,    2,  169,    2, 0x0a /* Public */,
      15,    1,  174,    2, 0x2a /* Public | MethodCloned */,
      18,    2,  177,    2, 0x0a /* Public */,
      18,    1,  182,    2, 0x2a /* Public | MethodCloned */,
      20,    0,  185,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QUrl, QMetaType::Int,    6,    4,
    QMetaType::Void, QMetaType::QUrl,    6,
    QMetaType::Void, QMetaType::QJsonObject, QMetaType::Int,    8,    4,
    QMetaType::Void, QMetaType::QJsonObject,    8,
    QMetaType::Void, QMetaType::QJsonArray, QMetaType::Int,   10,    4,
    QMetaType::Void, QMetaType::QJsonArray,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   12,    4,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray, QMetaType::Int,   13,   14,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,   13,   14,
    QMetaType::Void, QMetaType::QImage, QMetaType::Int,   16,    4,
    QMetaType::Void, QMetaType::QImage,   16,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   17,    4,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Int,   19,    4,
    QMetaType::Void, QMetaType::QByteArray,   19,
    QMetaType::Void,

       0        // eod
};

void JQHttpServer::Session::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Session *_t = static_cast<Session *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->replyText((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 1: _t->replyText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->replyRedirects((*reinterpret_cast< const QUrl(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 3: _t->replyRedirects((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 4: _t->replyJsonObject((*reinterpret_cast< const QJsonObject(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 5: _t->replyJsonObject((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 6: _t->replyJsonArray((*reinterpret_cast< const QJsonArray(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 7: _t->replyJsonArray((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 8: _t->replyFile((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 9: _t->replyFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->replyFile((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 11: _t->replyFile((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 12: _t->replyImage((*reinterpret_cast< const QImage(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 13: _t->replyImage((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 14: _t->replyImage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 15: _t->replyImage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: _t->replyBytes((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 17: _t->replyBytes((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 18: _t->replyOptions(); break;
        default: ;
        }
    }
}

const QMetaObject JQHttpServer::Session::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_JQHttpServer__Session.data,
      qt_meta_data_JQHttpServer__Session,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *JQHttpServer::Session::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JQHttpServer::Session::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_JQHttpServer__Session.stringdata0))
        return static_cast<void*>(const_cast< Session*>(this));
    return QObject::qt_metacast(_clname);
}

int JQHttpServer::Session::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}
struct qt_meta_stringdata_JQHttpServer__AbstractManage_t {
    QByteArrayData data[7];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JQHttpServer__AbstractManage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JQHttpServer__AbstractManage_t qt_meta_stringdata_JQHttpServer__AbstractManage = {
    {
QT_MOC_LITERAL(0, 0, 28), // "JQHttpServer::AbstractManage"
QT_MOC_LITERAL(1, 29, 12), // "readyToClose"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 10), // "onRedReady"
QT_MOC_LITERAL(4, 54, 5), // "reply"
QT_MOC_LITERAL(5, 60, 10), // "initialize"
QT_MOC_LITERAL(6, 71, 12) // "deinitialize"

    },
    "JQHttpServer::AbstractManage\0readyToClose\0"
    "\0onRedReady\0reply\0initialize\0deinitialize"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JQHttpServer__AbstractManage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    1,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   38,    2, 0x09 /* Protected */,
       6,    0,   39,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Void,

       0        // eod
};

void JQHttpServer::AbstractManage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AbstractManage *_t = static_cast<AbstractManage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readyToClose(); break;
        case 1: _t->onRedReady((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: { bool _r = _t->initialize();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->deinitialize(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AbstractManage::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbstractManage::readyToClose)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (AbstractManage::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbstractManage::onRedReady)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject JQHttpServer::AbstractManage::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_JQHttpServer__AbstractManage.data,
      qt_meta_data_JQHttpServer__AbstractManage,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *JQHttpServer::AbstractManage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JQHttpServer::AbstractManage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_JQHttpServer__AbstractManage.stringdata0))
        return static_cast<void*>(const_cast< AbstractManage*>(this));
    return QObject::qt_metacast(_clname);
}

int JQHttpServer::AbstractManage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void JQHttpServer::AbstractManage::readyToClose()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void JQHttpServer::AbstractManage::onRedReady(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_JQHttpServer__TcpServerManage_t {
    QByteArrayData data[1];
    char stringdata0[30];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JQHttpServer__TcpServerManage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JQHttpServer__TcpServerManage_t qt_meta_stringdata_JQHttpServer__TcpServerManage = {
    {
QT_MOC_LITERAL(0, 0, 29) // "JQHttpServer::TcpServerManage"

    },
    "JQHttpServer::TcpServerManage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JQHttpServer__TcpServerManage[] = {

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

void JQHttpServer::TcpServerManage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject JQHttpServer::TcpServerManage::staticMetaObject = {
    { &AbstractManage::staticMetaObject, qt_meta_stringdata_JQHttpServer__TcpServerManage.data,
      qt_meta_data_JQHttpServer__TcpServerManage,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *JQHttpServer::TcpServerManage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JQHttpServer::TcpServerManage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_JQHttpServer__TcpServerManage.stringdata0))
        return static_cast<void*>(const_cast< TcpServerManage*>(this));
    return AbstractManage::qt_metacast(_clname);
}

int JQHttpServer::TcpServerManage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractManage::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_JQHttpServer__SslServerManage_t {
    QByteArrayData data[1];
    char stringdata0[30];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JQHttpServer__SslServerManage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JQHttpServer__SslServerManage_t qt_meta_stringdata_JQHttpServer__SslServerManage = {
    {
QT_MOC_LITERAL(0, 0, 29) // "JQHttpServer::SslServerManage"

    },
    "JQHttpServer::SslServerManage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JQHttpServer__SslServerManage[] = {

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

void JQHttpServer::SslServerManage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject JQHttpServer::SslServerManage::staticMetaObject = {
    { &AbstractManage::staticMetaObject, qt_meta_stringdata_JQHttpServer__SslServerManage.data,
      qt_meta_data_JQHttpServer__SslServerManage,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *JQHttpServer::SslServerManage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JQHttpServer::SslServerManage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_JQHttpServer__SslServerManage.stringdata0))
        return static_cast<void*>(const_cast< SslServerManage*>(this));
    return AbstractManage::qt_metacast(_clname);
}

int JQHttpServer::SslServerManage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractManage::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_JQHttpServer__LocalServerManage_t {
    QByteArrayData data[1];
    char stringdata0[32];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JQHttpServer__LocalServerManage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JQHttpServer__LocalServerManage_t qt_meta_stringdata_JQHttpServer__LocalServerManage = {
    {
QT_MOC_LITERAL(0, 0, 31) // "JQHttpServer::LocalServerManage"

    },
    "JQHttpServer::LocalServerManage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JQHttpServer__LocalServerManage[] = {

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

void JQHttpServer::LocalServerManage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject JQHttpServer::LocalServerManage::staticMetaObject = {
    { &AbstractManage::staticMetaObject, qt_meta_stringdata_JQHttpServer__LocalServerManage.data,
      qt_meta_data_JQHttpServer__LocalServerManage,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *JQHttpServer::LocalServerManage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JQHttpServer::LocalServerManage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_JQHttpServer__LocalServerManage.stringdata0))
        return static_cast<void*>(const_cast< LocalServerManage*>(this));
    return AbstractManage::qt_metacast(_clname);
}

int JQHttpServer::LocalServerManage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractManage::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
