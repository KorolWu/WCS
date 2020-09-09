#ifndef TCOMMSERIALPORT_H
#define TCOMMSERIALPORT_H

#include <QObject>
#include "hwdeviceabstractinterface.h"
#include <QDebug>
#include <QSerialPort>
class TcommSerialport:public HWdeviceabstractInterface
{
    Q_OBJECT
public:
    TcommSerialport();

    // HWdeviceabstractInterface interface
public:
    void SetCommParam(ComConfigStru paramstru);
    int GetNameID();
    int GetHWtype();
    int GetHWprotype();
    void CloseComm();
private:
    bool InitSerialport();
    SerialPortstru m_serialconfig;
    QSerialPort m_serialob;
private slots:
    void RevSerialDataFromHW();
    void SlotSendDataToHW(QByteArray  sendData);
};

#endif // TCOMMSERIALPORT_H
