#include "tcommtcpclient.h"

TCommTCPclient::TCommTCPclient()
{
    socket = nullptr;
    m_connectStatus = false;
    connect(this,&TCommTCPclient::signalSendHWdeviceData,this,&TCommTCPclient::write);
    connect(this,&TCommTCPclient::signalClientconnectserver,this,&TCommTCPclient::reConnection);
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
    creadTcpClient();
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
    if(socket == nullptr)
        return;
    socket->disconnectFromHost();
    socket->close();
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
        emit signalHWDisconnect(m_config.ID,m_config.hwtype,m_connectStatus);
    } );
    connect(socket,&QTcpSocket::readyRead,
            [=]()
    {
        QByteArray array=socket->readAll();
        emit signalReadHWdeviceData(m_config.ID,m_config.hwtype,array);
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
    if(m_connectStatus)//连接成功发出成功状态
    {
        emit signalHWDisconnect(m_config.ID,m_config.hwtype,m_connectStatus);
    }
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
    emit signalHWDisconnect(m_config.ID,m_config.hwtype,m_connectStatus);
}
