#ifndef TCOMMMODBUSTCPCLIENT_H
#define TCOMMMODBUSTCPCLIENT_H

#include <QObject>
#include "hwdeviceabstractinterface.h"
#include <QModbusClient>
#include <QModbusTcpClient>
#include <QModbusDataUnit>
#include <QUrl>
#include <QDebug>
class TCommModbusTcpClient:public HWdeviceabstractInterface
{
    Q_OBJECT
public:
    TCommModbusTcpClient();

    // HWdeviceabstractInterface interface
public:
    void SetCommParam(ComConfigStru paramstru);
    int GetNameID();
    int GetHWtype();
    int GetHWprotype();
    void CloseComm();
private:
    bool GetConnect(const QString url_str); //创建连接
    void readReady();//接收到从站发过来的数据
private:
    QModbusClient *modbusDevice;
    //DiscreteInputs  Coils InputRegisters HoldingRegisters
    ModbusTcpClientstru m_configstru;
    QModbusDataUnit readRequest(int type, int startAddress, int numberOfEntries) const;
    QModbusDataUnit writeRequest(int type, int startAddress, int numberOfEntries) const;
private slots:
    void readDataRequest(int type, int startAddress, int numberOfEntries);
    void on_writeData_request(int type, int startAddress, QVector<int> values);
signals:
    void signalReadData(int type,int startAddress,int numberOfEntries);//读各种类型数据的状态 IO 寄存器 Vlaue  外部去写数据变化调用指令
  //void signalRecRead(int ID,int hwtype,int datatype,QMap<int,int> Data); // 读数据类型 data,第一个是参数是地址 第二个参数是 值
    void signaWrite(int type, int startAddress, QVector<int> values); // 读数据类型 data,第一个是参数是地址 第二个参数是 值

};



#endif // TCOMMMODBUSTCPCLIENT_H
