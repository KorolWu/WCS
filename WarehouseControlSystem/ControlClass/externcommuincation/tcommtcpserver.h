#ifndef TCOMMTCPSERVER_H
#define TCOMMTCPSERVER_H

#include <QObject>
#include "hwdeviceabstractinterface.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QStringList>
#include <QMap>
#include <QDebug>
#include <QModbusClient>
#include <QModbusTcpClient>
#include <QModbusDataUnit>
#include <QUrl>
#include <QMutex>
#include <QMutexLocker>

class TCommTCPserver:public HWdeviceabstractInterface
{
    Q_OBJECT
public:
    TCommTCPserver();
    ~TCommTCPserver();
    // HWdeviceabstractInterface interface
public:
    void SetCommParam(ComConfigStru paramstru);
    int GetNameID();
    int GetHWtype();
    int GetHWprotype();
    void CloseComm();
    bool creatTcpserver();
private:
    int write(QByteArray data);
    TcpStru m_config;
public slots:
    int writeData(QByteArray data);
private:
    QTcpServer *tcpserver;//监听套接字
    QTcpSocket *socket;//通讯套接字
};

#endif // TCOMMTCPSERVER_H
