#include "tcommtcpclient.h"

TCommTCPclient::TCommTCPclient()
{
    socket = nullptr;
    m_connectStatus = false;
    connect(this,&TCommTCPclient::SendHWdeviceData,this,&TCommTCPclient::write);
}

TCommTCPclient::~TCommTCPclient()
{
    if(socket == nullptr)
        return;
    socket->disconnectFromHost();
    socket->close();
    socket = nullptr;
}

void TCommTCPclient::SetCommParam(ComConfigStru paramstru)
{
    m_config = paramstru.hwTcpstru;
}

QString TCommTCPclient::GetNameID()
{
    return m_config.ID;
}

int TCommTCPclient::GetHWtype()
{
    return m_config.hwtype;
}

int TCommTCPclient::GetHWprotype()
{
    return KTcpClient;
}

void TCommTCPclient::CloseComm()
{

}

bool TCommTCPclient::creadTcpClient()
{
    this->m_ip = m_config.name;
    this->m_port = m_config.port;
    socket = new QTcpSocket(this);
    connect(socket,&QTcpSocket::disconnected,this,&TCommTCPclient::onDisconnected);
    connect(socket,&QTcpSocket::connected,
            [=]()
    {
        m_connectStatus = true;
    } );
    connect(socket,&QTcpSocket::readyRead,
            [=]()
    {
        QByteArray array=socket->readAll();
        emit ReadHWdeviceData(m_config.ID,m_config.hwtype,array);
    });
    return connectServer(m_ip,m_port);
}

bool TCommTCPclient::connectServer(QString ip, qint16 port)
{
    if(socket == nullptr)
        return false;
    socket->connectToHost(QHostAddress(ip),port);
    if(socket->waitForConnected(1000))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool TCommTCPclient::reConnection()
{
    m_connectStatus = connectServer(this->m_ip,this->m_port);
    return m_connectStatus;
}

int TCommTCPclient::write(QByteArray array)
{
    if(socket == nullptr)
        return 1;
    return socket->write(array);
}

void TCommTCPclient::onDisconnected()
{
    m_connectStatus = false;
    emit clientDisconnect(m_config.ID,m_config.hwtype);
}
