#ifndef HWDEVICEABSTRACTINTERFACE_H
#define HWDEVICEABSTRACTINTERFACE_H

#include <QObject>
#include <QByteArray>
#include <definitioncomdataframe.h>
#include <QMetaType>

///
/// \brief The HWdeviceabstractInterface class
///为所有通讯统一接口类
class HWdeviceabstractInterface:public QObject
{
     Q_OBJECT
public:
    virtual void SetCommParam(ComConfigStru paramstru) = 0;
    virtual QString GetNameID(){return "";}
    virtual int GetHWtype(){return 0;}
    virtual int GetHWprotype(){ return 0 ;}
    virtual void CloseComm() = 0;
signals:
     void signalReadHWdeviceData(QString ID,int hwtype,QByteArray dataValue);
     void signalSendHWdeviceData(QByteArray  sendData);
     void signalHWDisconnect(QString ID,int hwtype,bool state);

};

#endif // HWDEVICEABSTRACTINTERFACE_H
