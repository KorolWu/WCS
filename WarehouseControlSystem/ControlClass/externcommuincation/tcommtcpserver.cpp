#include "tcommtcpserver.h"

TCommTCPserver::TCommTCPserver()
{
    tcpserver = nullptr;
    socket = nullptr;
    connect(this,&TCommTCPserver::signalSendHWdeviceData,this,&TCommTCPserver::writeData);

}

TCommTCPserver::~TCommTCPserver()
{
    if(nullptr==socket)
      {
          return;
      }
      socket->disconnectFromHost();
      socket->close();
      socket=nullptr;
}
///
/// \brief TCommTCPserver::SetCommParam
/// \param paramstru
///
void TCommTCPserver::SetCommParam(ComConfigStru paramstru)
{
  m_config = paramstru.hwTcpstru;
  creatTcpserver();
}

int TCommTCPserver::GetNameID()
{
    return m_config.ID;
}

int TCommTCPserver::GetHWtype()
{
  return m_config.hwtype;
}

int TCommTCPserver::GetHWprotype()
{
  return Tcpserver;
}


void TCommTCPserver::CloseComm()
{
    if(nullptr==socket)
      {
          return;
      }
      socket->disconnectFromHost();
      socket->close();
      socket=nullptr;
}

bool TCommTCPserver::creatTcpserver()
{
    QString ipname = m_config.name;
    int portvalue  = m_config.port;
    tcpserver=new QTcpServer(this);
    QHostAddress address(QHostAddress::Any);
    if(ipname != "")
        address = QHostAddress(ipname);
    if(!tcpserver->listen(address,portvalue))
        return false;
    connect(tcpserver,&QTcpServer::newConnection,
            [=](){
        //取出建立好的链接套接字
        socket= tcpserver->nextPendingConnection();
        //获取链接的端口号和ip
        int port = socket->peerPort();
        QString ip=socket->peerAddress().toString();
        QString str = QString("[%1 %2]Connet Successful").arg(port).arg(ip);
          m_connectstate  = 1;
        qDebug()<<str;
        connect(socket,&QTcpSocket::readyRead,
                [=]()
        {
            QByteArray array = socket->readAll();
            emit signalReadHWdeviceData(m_config.ID,m_config.hwtype,array);
        }
        );
    }
    );
    return true;
}

int TCommTCPserver::write(QByteArray data)
{
    if(nullptr == socket)
    {
        return 1;
    }
    return socket->write(data);
}

int TCommTCPserver::writeData(QByteArray data)
{
    return write(data);

}
