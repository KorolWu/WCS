#include "tcommtransceivermanager.h"

TCommtransceivermanager::TCommtransceivermanager()
{
    m_heartTimer = new QTimer;
    connect(m_heartTimer,&QTimer::timeout,this,&TCommtransceivermanager::UpdateState);
}

TCommtransceivermanager::~TCommtransceivermanager()
{
    m_heartTimer->stop();
    delete m_heartTimer;
    m_HWdeviceMap.clear();

}///
/// \brief TCommtransceivermanager::InitHWcommob
///根据数据库内容创建所有通讯的对象，并存储到内存中
void TCommtransceivermanager::InitHWcommob()
{
    //读取内存的数据进行 创建通讯对象
    m_HWdeviceMap.clear();
    CreatObbyHWconfigData(Myconfig::GetInstance()->m_hwcommstru.hwTcpMap,KTcpClient);
    CreatObbyHWconfigData(Myconfig::GetInstance()->m_hwcommstru.hwmodbustcpcliMap,KModbusTcpClient);
    CreatObbyHWconfigData(Myconfig::GetInstance()->m_hwcommstru.hwSerialPortMap,KSerialPort);
    m_heartTimer->start(500);
}
///
/// \brief TCommtransceivermanager::sendDataToHWob
/// \param data
/// 发送数据到对应的硬件对象中,根据ID 找到对应的对象实施发送
void TCommtransceivermanager::sendDataToHWob(QByteArray datavalue,QString id)
{
    for(auto it = m_HWdeviceMap.begin();it!= m_HWdeviceMap.end();++it)
    {
        if(it.key() == id)
        {
            switch (it.value()->GetHWprotype())
            {
            case HWDEVICEPROTYPE::KTcpClient:
            {
                TCommTCPclient *tob = dynamic_cast<TCommTCPclient *>(it.value());
                emit tob->signalSendHWdeviceData(datavalue);
                break;
            }
            case HWDEVICEPROTYPE::Tcpserver:
            {
                TCommTCPserver *tob = dynamic_cast<TCommTCPserver *>(it.value());
                emit tob->signalSendHWdeviceData(datavalue);
                break;
            }
            default:
                break;
            }
            break;
        }
    }
}
///
/// \brief TCommtransceivermanager::ReceDataFromHWob
/// \param ID
/// \param hwtype
/// \param data
///接收硬件发过来的数据进行处理
void TCommtransceivermanager::ReceDataFromHWob(QString ID, int hwtype, QByteArray data)
{
   //根据各个对象进行包解析 更新数据内容

}

///
/// \brief TCommtransceivermanager::UpdateConntectState
///更新数据内容
void TCommtransceivermanager::UpdateState()
{
    for(auto it = m_HWdeviceMap.begin();it!= m_HWdeviceMap.end();++it)
    {
        switch (it.value()->GetHWprotype())
        {
        case HWDEVICEPROTYPE::KTcpClient:
        {
            // TCommTCPclient *tob = dynamic_cast<TCommTCPclient *>(it.value());

            //  break;
        }
        default:
            break;
        }
    }
}
///
/// \brief TCommtransceivermanager::Slotdisconnect
/// \param ID
/// \param type
///通讯断开的信号
void TCommtransceivermanager::Slotconnectstate(QString ID, int type,bool state)
{
    //接收到掉线信号自动重新连接
    switch (type)
    {
    case HWDEVICEPROTYPE::KTcpClient:
    {
        TCommTCPclient *tob = dynamic_cast<TCommTCPclient *>(m_HWdeviceMap[ID]);
        if(!state) //断开连接了
        {
            emit tob->signalClientconnectserver();
        }
        break;
    }
    default:
        break;
    }
}
