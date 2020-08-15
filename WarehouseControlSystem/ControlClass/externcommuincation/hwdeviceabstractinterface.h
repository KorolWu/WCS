#ifndef HWDEVICEABSTRACTINTERFACE_H
#define HWDEVICEABSTRACTINTERFACE_H

#include <QObject>
#include <QByteArray>
///
/// \brief The HWdeviceabstractInterface class
///为所有通讯统一接口类
class HWdeviceabstractInterface:public QObject
{
     Q_OBJECT
public:
    HWdeviceabstractInterface();
    ~HWdeviceabstractInterface();
    virtual void SetNameID(QString id);
    virtual void SetHWtype(int hwtype);
    virtual void SetHWprotype(int protype);
    virtual void GetNameID();
    virtual void GetHWtype();
    virtual void GetHWprotype();
    virtual int WriteHWdeviceData(QByteArray data);
    virtual QByteArray ReadHWdeviceData();
private:
    QString m_nameId;
    int m_hwtype;
    int m_protype;
};

#endif // HWDEVICEABSTRACTINTERFACE_H
