#ifndef TCOMMTCPCLIENT_H
#define TCOMMTCPCLIENT_H

#include <QObject>
#include "hwdeviceabstractinterface.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QStringList>
class TCommTCPclient:public HWdeviceabstractInterface
{
    Q_OBJECT
public:
    TCommTCPclient();
    ~TCommTCPclient();

    // HWdeviceabstractInterface interface
public:
    void SetCommParam(ComConfigStru paramstru);
    int GetNameID();
    int GetHWtype();
    int GetHWprotype();
    void CloseComm();
    bool creadTcpClient();
    bool connectServer(QString ip,qint16 port);
    bool reConnection();
    int write(QByteArray array);
    QTcpSocket *socket;//通讯套接字
    bool m_connectStatus;
    void onDisconnected();

private:
    QString m_ip;
    qint16 m_port;
    TcpStru m_config;
signals:
    void clientDisconnect(int ID,int hwtype);
    void signalClientconnectserver();
};

#endif // TCOMMTCPCLIENT_H
