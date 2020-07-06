#include "basedevice.h"
/**
 * @author korol
 * @date  2020-7-2 09:27
 * @brief BaseDevice::BaseDevice
 * @param ip
 * @param port
 * @param parent
 * 建立客户端通讯，处理了断线重连，将收到的消息处理塞进对应的内存，将消息接受方法，断线重连方法，
   清除报警方法虚化，可由子类重写。
 */
BaseDevice::BaseDevice(QString ip, qint16 port, QObject *parent)
{
    Q_UNUSED(parent);
    this->m_ip = ip;
    this->m_port = port;
    m_pClient = new KCommunication::KTcpClient(this);
    connect(m_pClient,&KCommunication::KTcpClient::onTcpClientResive,this,&BaseDevice::onResived);
    connect(m_pClient,&KCommunication::KTcpClient::clientDisconnect,this,&BaseDevice::onDisconnected);

    m_pTimer = new QTimer(this);
    connect(m_pTimer,&QTimer::timeout,this,&BaseDevice::reConnected);
}
///
/// \brief BaseDevice::init
/// \return false mean creatClient failed;
///
bool BaseDevice::init()
{
    bool initResult = false;
    initResult =  m_pClient->creadTcpClient(m_ip,m_port);
    if(Myconfig::GetInstance()->m_CarMap.contains(this->m_ip))
    {
        if(initResult)
            Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.isOnline = true;
        else
        {
            Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.isOnline = false;
            //if(!m_pTimer->isActive())
                //m_pTimer->start(1000);
        }
    }
    noticeObserver();
    return initResult;
}

void BaseDevice::registObserver(ObserverBase *o)
{
    m_ObserverVec.append(o);
}
///
/// \brief BaseDevice::onResived
/// \param array
/// on client message changed
///
void BaseDevice::onResived(QByteArray array)
{
     if(Myconfig::GetInstance()->m_CarMap.contains(this->m_ip))
     {
         //将收到的数据解析好，塞到内存里面

     }
     qDebug()<<"handle array: "<<array;
}

///
/// \brief BaseDevice::onDisconnected
///
void BaseDevice::onDisconnected()
{
    if(Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.isOnline != false)
        Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.isOnline = false;
    noticeObserver();
    m_pTimer->start(1000);
}
///
/// \brief BaseDevice::write
/// \param data
/// \return -1 meam disconnect for server or Client object init failed
///
int BaseDevice::write(QByteArray data)
{
    if(m_pClient != nullptr)
        return m_pClient->write(data);
    return -1;
}

void BaseDevice::clearAlarm(QByteArray data)
{
    write(data);
}
///
/// \brief BaseDevice::reConnected
/// when get the disconnect signal,reconnect to server,
/// until connected to server,stop timer.
/// \return connectResult true is connected
///
void BaseDevice::reConnected()
{
    if(m_pClient == nullptr)
        return;
    if(m_pClient->reConnection())
    {
        Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.isOnline = true;
        noticeObserver();
        m_pTimer->stop();
    }
}

void BaseDevice::noticeObserver()
{
    for(int i = 0; i < m_ObserverVec.size();i++)
    {
       m_ObserverVec[i]->updateStatusOnBase();
    }
}
