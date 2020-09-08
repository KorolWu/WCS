#ifndef TCOMMMODBUSSERIAL_H
#define TCOMMMODBUSSERIAL_H

#include <QObject>
#include "hwdeviceabstractinterface.h"
#include <QModbusDataUnit>
#include <QUrl>
#include <QDebug>
#include <QModbusRtuSerialMaster>
class QModbusClient;
class QModbusReply;

class Tcommmodbusserial:public HWdeviceabstractInterface
{
  Q_OBJECT
public:
    Tcommmodbusserial();

    // HWdeviceabstractInterface interface
public:
    void SetCommParam(ComConfigStru paramstru);
    int GetNameID();
    int GetHWtype();
    int GetHWprotype();
    void CloseComm();
private:
    SerialPortstru m_configstru;
    QModbusClient *modbusDevice;
    void InitConnect();
private slots:
    void readReady();
private:
    QModbusDataUnit readRequest(int type, int startAddress, int numberOfEntries) const;

    QModbusDataUnit writeRequest(int type, int startAddress, int numberOfEntries) const;
private slots:
    void readDataRequest(int type, int startAddress, int numberOfEntries);
    void on_writeData_request(int type, int startAddress, QVector<int> values);
    void onStateChanged(int state);
signals:
    void signalReadData(int type,int startAddress,int numberOfEntries);//读各种类型数据的状态 IO 寄存器 Vlaue  外部去写数据变化调用指令
  //void signalRecRead(int ID,int hwtype,int datatype,QMap<int,int> Data); // 读数据类型 data,第一个是参数是地址 第二个参数是 值
    void signaWrite(int type, int startAddress, QVector<int> values); // 读数据类型 data,第一个是参数是地址 第二个参数是 值

};

#endif // TCOMMMODBUSSERIAL_H
