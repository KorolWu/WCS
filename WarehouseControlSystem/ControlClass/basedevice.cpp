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
    qRegisterMetaType<OrderStru>("OrderStru");
    Q_UNUSED(parent);
    this->m_ip = ip;
    this->m_port = port;
    m_rflag = false;
    m_pClient = new KCommunication::KTcpClient(this);
    connect(m_pClient,&KCommunication::KTcpClient::onTcpClientResive,this,&BaseDevice::onResived);
    connect(m_pClient,&KCommunication::KTcpClient::clientDisconnect,this,&BaseDevice::onDisconnected);

    m_pTimer = new QTimer(this);
    connect(m_pTimer,&QTimer::timeout,this,&BaseDevice::reConnected);
    m_pOrderStrategy = new AbstractOrder();
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

void BaseDevice::removeObserver(ObserverBase *o)
{
    int index = m_ObserverVec.indexOf(o);
    if(index >-1)
        m_ObserverVec.remove(index);
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
         //将收到的数据解析好，塞到内存里面   1电量，2状态(是否可用  工作中、等待中)，3位置 4是否在线 5是否可用 6车上料箱 7自动/手动
         char *model = new char[2];
         char *c = array.data();
         //if(sizeof(c) ==40)
         //{
            memcpy(model,c+4,2);
            //详细信息
            //if(QString(QLatin1String(model)) == "SD")
            //{
                Rint16 r;
                memcpy(r.c,c+6,2);//model 1 Manual  2 automatic
                Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.model = r.v;
                memcpy(r.c,c+8,2);
                char byte = r.c[0];
                byte = r.c[0] >> 1 & 0x01; // =1 alram
                if(byte == 1)
                    Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.err_code = 1;
                else
                    Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.err_code = 0;
                byte = r.c[0] >> 2 & 0x01; // =1 battery low
                if(byte == 1)
                {
                    Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.batter = 20;
                    //qDebug()<<m_ip<<"batter"<< 20;
                }
                else
                {
                    Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.batter = 80;
                     //qDebug()<<m_ip<<"batter"<< 80;
                }
                byte = r.c[0] >> 3 & 0x01; // =1 standby can get order
                if(byte == 1 )
                    Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.status = 1;
                byte = r.c[0] >> 4 & 0x01; // =1 do working can`t get order
                if(byte == 1 )
                    Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.status = 2;
                byte = r.c[0] >> 5 & 0x01; // =1 not standby
                if(byte == 1 )
                    Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.status = 3;
                byte = r.c[0] >> 6 & 0x01; // =1 calibrationing


                Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.box_status = 0;
                byte = c[8] >> 1 & 0x01;  // 左有货
                if(byte == 1)
                    Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.box_status = 1;
                byte = c[8] >> 1 & 0x01;  //右有货
                if(byte == 1)
                    Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.box_status = 2;
                byte = c[8] >> 1 & 0x01;  //台上有货
                if(byte == 1)
                    Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.box_status = 3;
                //qDebug()<<"Resive message :"<<QString(QLatin1String(c));
            //}
//            else //简单信息
//            {

//            }
            noticeObserver();
         //}

     }
    // qDebug()<<"handle array: "<<array;
}

///
/// \brief BaseDevice::onDisconnected
///
void BaseDevice::onDisconnected()
{
    if(Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.isOnline != false)
        Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.isOnline = false;
    ReadTableData mysql;
    ALARMINFOSTRU arm;
    arm.alarminfo = "设备 "+m_ip+" 掉线";
    arm.alarmlevel = 0;
    arm.carcoordx = Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.carCurrentPosion.x;
    arm.carcoordy = Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.carCurrentPosion.y;
    arm.carcoordz = Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.carCurrentPosion.z;
    arm.deviceid = m_ip;
    QString err;
    mysql.WriteAlarmInfo(arm,err);
    noticeObserver();
    m_pTimer->start(3000);
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
void BaseDevice::handelOrder(OrderStru o)
{
    //qDebug()<<"handel";
    //在预计时间类完成Order
    if(o.order == Order::X)
        write(m_pOrderStrategy->move_x(20));
    else if(o.order == Order::Y)
        write(m_pOrderStrategy->move_y(20));
    else if(o.order == Order::ChangeWhell)
        write(m_pOrderStrategy->changeWhell());
    else if(o.order == Order::Left_Pickup)
        write(m_pOrderStrategy->left_get());
    else if(o.order == Order::Right_Pickup)
        write(m_pOrderStrategy->right_get());
    else if(o.order == Order::Elevator_Near)
        write(m_pOrderStrategy->move_ElevatorNear());
    else if(o.order == Order::Call)
        write(m_pOrderStrategy->call_Elevator(2));
    else if(o.order == Order::Elevator_In)
        write(m_pOrderStrategy->in_elevator());
    else if(o.order == Order::Elevator_Out)
        write(m_pOrderStrategy->out_elevator());
    else if(o.order == Order::Left_WorkBin)
        write(m_pOrderStrategy->left_workbin());
    else if(o.order == Order::Right_WorkBin)
        write(m_pOrderStrategy->right_workbin());
    else if(o.order == Order::Call_WorkBin_Out)
        write(m_pOrderStrategy->call_elevator_work_out(2));
    else if(o.order == Order::Call_WorkBin_In)
        write(m_pOrderStrategy->call_elevator_work_in(3));

}

