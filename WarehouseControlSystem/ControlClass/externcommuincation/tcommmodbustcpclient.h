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
    void init_bitMap();
    int getBitValue(int start_bit);
private:
    bool GetConnect(const QString url_str);
    void write(int start_bit,int value,int address = 1);
    void readCoils (int start_bit, int address = 1);
    void readAll();
    void readRegisters(int start_bit,int adress =1);
    void readReady();
private:
    QModbusClient *modbusDevice;
    QMap<int,int> bit_map;
    //DiscreteInputs  Coils InputRegisters HoldingRegisters


    ModbusTcpClientstru m_configstru;
private slots:
    void SlotReadData(int type,int bit,int address);
    void SlotWriteValue(int type,int bit,int value,int address);
signals:
    void signalReadData(int type,int bit,int address);//读各种类型数据的状态 IO 寄存器 Vlaue  外部去写数据变化调用指令
    void signalWriteValue(int type,int bit,int value,int address );//写IO 寄存器的值

};



#endif // TCOMMMODBUSTCPCLIENT_H
