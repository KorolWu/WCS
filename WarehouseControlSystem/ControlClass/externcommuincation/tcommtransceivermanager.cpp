#include "tcommtransceivermanager.h"

TCommtransceivermanager::TCommtransceivermanager()
{
    m_heartTimer = new QTimer;
    connect(m_heartTimer,&QTimer::timeout,this,&TCommtransceivermanager::UpdateState);
    m_Wcstocarframeindex.clear();
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
    //m_heartTimer->start(500);
}
///
/// \brief TCommtransceivermanager::SendcommandByExtern
/// \param cmd
/// \param Id
///外部传入参数进行处理 小车 流道 电梯指令 等
void TCommtransceivermanager::SendcommandByExtern(OrderStru cmd, int hwId)
{

    QMutexLocker locker(&m_TCommMutex);
    //先解析小车部分数据 发送帧格式内容
    if(m_HWdeviceMap.contains(hwId))
    {
        if(m_HWdeviceMap[hwId]->m_connectstate <= 0)
        {
            qDebug()<<"通讯异常:"<< hwId << m_HWdeviceMap[hwId]->m_connectstate;
            return;
        }
        int hwtype = m_HWdeviceMap[hwId]->GetHWtype();
        int protype = m_HWdeviceMap[hwId]->GetHWprotype();
        switch (hwtype) {
        case HWDEVICETYPE::RGVCAR://需要发送的是AGV小车的内容
        {
            int16_t wcsindex = GetWCStocarFrameIndex(hwId);//
            QByteArray frameData;
            int16_t childtype = 0;
            childtype = cmd.childtype;
            // qDebug()<<"wcsindex:"<<wcsindex;
            switch (childtype) {
            case 5: // 请求详细数据类型
            {
                SendCarCmdFrame wcssendframestru;
                wcssendframestru.cmdnbr = wcsindex;//指令编号:识别不同报文的唯一编号,该序号由WCS提供。

                wcssendframestru.carnbr = hwId;
                if(cmd.order == Left_Pickup)
                {
                    wcssendframestru.pickputdirection = 1;//左取货
                    wcssendframestru.cmdname = 3;//左取货
                }
                else if(cmd.order == Right_Pickup)
                {
                    wcssendframestru.pickputdirection = 2;//右取货
                    wcssendframestru.cmdname = 3;//取货
                }
                else if(cmd.order == Left_Putinto)
                {
                    wcssendframestru.pickputdirection = 3;//左放货
                    wcssendframestru.cmdname = 4;//放货
                }
                else if(cmd.order == Right_Putinto)
                {
                    wcssendframestru.pickputdirection = 4;//右放货
                    wcssendframestru.cmdname = 4;//放货
                }
                else if(cmd.order == X)
                {
                    wcssendframestru.cmdname = 1; //直行距离
                    wcssendframestru.Strdistance = cmd.value;
                }
                else if(cmd.order == Y)
                {
                    wcssendframestru.cmdname = 2;//横行距离
                    wcssendframestru.Tradistance = cmd.value;
                }
                frameData.append(reinterpret_cast<char*>(&wcssendframestru),sizeof(SendCarCmdFrame));
                break;

            }
            case 6://简易数据类型
            {
                SendCarCmdReqestFrame simplestru;
                simplestru.carnbr = hwId;
                simplestru.cmdnbr = wcsindex;
                simplestru.cmdname = cmd.value; // 请求指令数据 5 或者 6
                frameData.append(reinterpret_cast<char*>(&simplestru),sizeof(SendCarCmdReqestFrame));
                break;
            }
            default:
                break;
            }
            //WCS发送数据报文到小车
            if(frameData.size() > 0 && protype == KTcpClient)
            {
                emit m_HWdeviceMap[hwId]->signalSendHWdeviceData(frameData);//发送报文
            }
            break;
        }
        case HWDEVICETYPE::ELEVATOR_OUT:
        case HWDEVICETYPE::ELEVATOR_IN:
        case HWDEVICETYPE::ELEVATOR_CAR://小车电梯
        case HWDEVICETYPE::RUNNER://流道指令调用
        {
            if(m_HWdeviceMap[hwId]->GetHWprotype() == KModbusTcpClient)
            {
                TCommModbusTcpClient *modbusob = dynamic_cast<TCommModbusTcpClient *>(m_HWdeviceMap[hwId]);
                // if(cmd.order.call_Runner_Putbox)
                if(cmd.childtype == 5) //请求读数据
                {
                    //qDebug()<<"请求读数据" << cmd.Datatype<<cmd.startaddress<<cmd.numberOfEntries;
                    emit  modbusob->signalReadData(cmd.Datatype,cmd.startaddress,cmd.numberOfEntries);
                }
                else{ //请求写数据
                    emit  modbusob->signaWrite(cmd.Datatype,cmd.startaddress,cmd.values);
                }
            }
            break;
        }
        default:
            break;
        }
    }

}
///
/// \brief TCommtransceivermanager::sendDataToHWob
/// \param data
/// 发送数据到对应的硬件对象中,根据ID 找到对应的对象实施发送
void TCommtransceivermanager::sendDataToHWob(QByteArray datavalue,int id)
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
            case HWDEVICEPROTYPE::KModbusTcpClient:// 地址 类型 字节 值
            {
                //字节结构转换
                TCommModbusTcpClient *tob = dynamic_cast<TCommModbusTcpClient *>(it.value());
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
/// \brief TCommtransceivermanager::GetWCStocarFrameIndex
/// \return
///报文索引的生成方式
int16_t TCommtransceivermanager::GetWCStocarFrameIndex(int hwId)
{
    int16_t index = 0;
    if(!m_Wcstocarframeindex.contains(hwId))
    {
        int wcsindex = 0;
        QList<int16_t> indexlsit;
        indexlsit.append(wcsindex);
        m_Wcstocarframeindex.insert(hwId,indexlsit);
    }
    else{
        QList<int16_t> list = m_Wcstocarframeindex[hwId];
        // std::sort(list.begin(), list.end());
        int16_t endvalue = list[list.size()-1];
        endvalue++;
        if(endvalue > 32000)//不能超过65535
        {
            endvalue = 0;
            list.removeAt(0);// 自行删除 最前面的一条数据
            qDebug()<<"endvalue :>32000以上了...";
        }
        if(endvalue == 1000) //特殊索引号不要使用
        {
            endvalue = 1001;
        }
        if(endvalue == 2000)//特殊索引号不要使用
        {
            endvalue = 2001;
        }
        if(!list.contains(endvalue))
        {
            list.append(endvalue);
        }
        else
        {
            qDebug()<<"请求数据发送的数量已经达到32000条以上了";
            endvalue = -999;
            if(!list.contains(endvalue))
            {
                list.append(endvalue);
            }
        }
        m_Wcstocarframeindex[hwId] = list;
        index = endvalue;        
    }
    return index;
}

bool TCommtransceivermanager::ModifyCarReceFrameIndex(int ID, int wcsnbr)
{
    //删除响应结束的编号帧的数据编号
    if(m_Wcstocarframeindex.contains(ID))
    {
        int index  = m_Wcstocarframeindex[ID].indexOf(wcsnbr);
        if(index >= 0)
        {
            m_Wcstocarframeindex[ID].removeAt(index);
            return true;
        }
    }
    return false;
}
///
/// \brief TCommtransceivermanager::AnaysisCarFrame
/// \param dataframe
/// \param ID
///
void TCommtransceivermanager::AnalysisCarFrame(QByteArray tempData, int ID)
{
    if(m_HWdeviceMap.contains(ID))
    {
        if(m_HWdeviceMap[ID])
        {
            if(tempData.size() >= 10)
            {
                //分析报文类型
                int16_t nbr;//指令编号
                int16_t carnbr;//小车编号
                atoi16 nbrvalue;
                memcpy(nbrvalue.a,tempData.data(),2);
                nbr = nbrvalue.x;
                atoi16 carrvalue;
                memcpy(carrvalue.a,tempData.data()+2,2);
                carnbr = carrvalue.x;
                if(ID == carnbr)
                {
                    if(nbr== 2000 && tempData[4] == 'R' && tempData[5] == 'B')//RB报文
                    {
                        ReceCarRBFrame RBstru;//复位报文
                        memcpy((char*)&RBstru,tempData.data(),10);
                        qDebug()<<"RB报文:"<< RBstru.carnbr << RBstru.posinfo;
                    }
                    else if(tempData[4] == 'S' && tempData[5] == 'D'&&(tempData.size() >= 74))//详细报文数据
                    {
                        // if(ModifyCarReceFrameIndex(ID,nbr))//正确报文 之前请求的数据已经返回了结果了
                        {
                            //解析详细数据内容
                            ReceCarDetailFrame detailstru;//详细数据报文
                            memcpy((char*)&detailstru,tempData.data(),74);
                            qDebug()<<"详细数据报文:"<< detailstru.carnbr << detailstru.state;
                            UpdateCarStatus(ID,Opermode,detailstru.state);//自动 / 手动
                            UpdateCarStatus(ID,exestatus,detailstru.info.carinfo);// 电量 校准  就绪 等状态变化
                            UpdateCarStatus(ID,sensorstat,detailstru.statepic.goodsstate.carsensorstat);//货物状态变化情况
                        }
                    }
                    else if(tempData[4] == 'S' && tempData[5] == 'T')
                    {
                        //简易数据报文
                        ReceCarcmdsimFrame simstru;
                        memcpy((char*)&simstru,tempData.data(),10);
                        // if(ModifyCarReceFrameIndex(ID,nbr))//正确报文 之前请求的数据已经返回了结果了
                        {
                            UpdateCarStatus(ID,Opermode,simstru.carstate);//自动 / 手动
                            UpdateCarStatus(ID,exestatus,simstru.info.carinfo);// 电量 校准  就绪 等状态变化
                        }
                        // else
                        {
                            // if(nbr == 1000)
                            {
                                //不是回应指令动作
                                qDebug()<<" 主动发的简易数据指令报文:"<< simstru.carstate;
                                UpdateCarStatus(ID,Opermode,simstru.carstate);//自动 / 手动
                                UpdateCarStatus(ID,exestatus,simstru.info.carinfo);// 电量 校准  就绪 等状态变化
                            }
                        }
                        qDebug()<<"简易数据报文 小车的自动和手动状态:"<< simstru.carnbr << simstru.carstate << simstru.info.carinfo;
                    }
                    else
                    {
                        // if(ModifyCarReceFrameIndex(ID,nbr)) //回应发出去编号内容
                        {
                            ReceCarcmdActionFrame actionstru;//动作指令报文
                            memcpy((char*)&actionstru,tempData.data(),10);
                            UpdateCarStatus(ID,actioninfo,actionstru.cmdstate);
                            qDebug()<<"动作指令报文:"<< actionstru.carnbr <<actionstru.cmdname<<  actionstru.cmdstate<<actionstru.cmdnbr;
                        }
                    }
                }
            }
        }
    }
}
//////更新小车内存中相关的状态内容
/// \brief TCommtransceivermanager::UpdateCarStatus
/// \param carID
/// \param role
/// \param value
///
void TCommtransceivermanager::UpdateCarStatus(int carID, int role, int value)
{
    QMutexLocker locker(&Myconfig::GetInstance()->m_carMap_mutex);
    if(Myconfig::GetInstance()->m_CarMap.contains(carID))
    {
        switch (role) {
        case CarStatusrole::RBposinfo:
            break;
        case CarStatusrole::Opermode:
        {
            //1:手动 2：自动
            if(Myconfig::GetInstance()->m_CarMap[carID].deveceStatus.model != value)
            {
                Myconfig::GetInstance()->m_CarMap[carID].deveceStatus.model = value;
            }
            break;
        }
        case CarStatusrole::sensorstat://传感器sensor状态
        {
            int curvalue = Myconfig::GetInstance()->m_CarMap[carID].deveceStatus.senorgoodsstru.carsensorstat;
            if(curvalue != value)
            {
                Myconfig::GetInstance()->m_CarMap[carID].deveceStatus.senorgoodsstru.carsensorstat = value;
            }
            break;
        }
        case CarStatusrole::exestatus: //包含了状态信息 故障等信息
        {
            int curvalue = Myconfig::GetInstance()->m_CarMap[carID].deveceStatus.statusinfodstru.carstatusinfo;
            if(curvalue !=value )
            {
                Myconfig::GetInstance()->m_CarMap[carID].deveceStatus.statusinfodstru.carstatusinfo = value;
            }
            break;
        }
        case CarStatusrole::actioninfo://指令完成动作赋值
        {
            int curvalue = Myconfig::GetInstance()->m_CarMap[carID].deveceStatus.status;
            if(curvalue !=value)
            {
                Myconfig::GetInstance()->m_CarMap[carID].deveceStatus.status = value;
            }
        }
        default:
            break;
        }
    }
}
///
/// \brief TCommtransceivermanager::UpdateCarStatus
/// \param carID


///
/// \brief TCommtransceivermanager::ReceDataFromHWob
/// \param ID
/// \param hwtype
/// \param data
///接收小车硬件发过来的数据进行处理
void TCommtransceivermanager::ReceDataFromHWob(int ID, int hwtype, QByteArray data)
{
    QMutexLocker locker(&m_TCommMutex);
    //根据各个对象进行包解析 更新数据内容
    QByteArray  tempData;
    tempData.append(data);
    // memcpy(tempData.data(),data.data(),data.size());//临时字节
    //  qDebug()<<"temdata"<<tempData.toHex() << data.toHex();
    switch (hwtype) {
    case HWDEVICETYPE::RGVCAR:
    {
        qDebug()<<"ID"<<ID << tempData.toHex();
        AnalysisCarFrame(tempData,ID);
        break;
    }
    default:
        break;
    }
}
///
/// \brief TCommtransceivermanager::ReceModbusDataFromHWob
/// \param ID 硬件唯一编号
/// \param hwtype 流道 电梯 等硬件
/// \param datatype
/// \param Data
///modbus 协议接收的内容
void TCommtransceivermanager::ReceModbusDataFromHWob(int ID, int hwtype, int datatype, QMap<int, int> Data)
{
    QMutexLocker locker(&m_TCommMutex);
    QMutexLocker lockermyconfig(&Myconfig::GetInstance()->m_mutex);
    if(!m_HWdeviceMap.contains(ID))
        return ;
    switch (hwtype) {
    case HWDEVICETYPE::RUNNER: //流道
    {
        switch (datatype) {
        case 1: //DiscreteInputs
        {
            break;
        }
        case 2://Coils
            break;
        case 3://InputRegisters

            break;
        case 4://HoldingRegisters
        {
            for(auto it = Data.begin(); it!= Data.end();++it )
            {
                qDebug()<<"runner:recedata"<<QString("adress:%1;value:%2").arg(QString::number(it.key())).arg(QString::number(it.value()));
            }
            break;
        }
        default:
            break;
        }
        break;
    }
    case HWDEVICETYPE::ELEVATOR_CAR: // 小车电梯的值
    {   for(auto it = Data.begin(); it!= Data.end();++it )
        {
            if(Myconfig::GetInstance()->m_elevatorMap.contains(ID))
            {
                if(it.key() == 100) //读取楼层
                {

                    if(Myconfig::GetInstance()->m_elevatorMap[ID].status.curruntLayer != it.value())
                    {
                        Myconfig::GetInstance()->m_elevatorMap[ID].status.curruntLayer = it.value();
                    }
                }
                else if(it.key() ==102 )//读取缓存
                {
                    if(Myconfig::GetInstance()->m_elevatorMap[ID].status.curachelayer != it.value())
                    {
                        Myconfig::GetInstance()->m_elevatorMap[ID].status.curachelayer = it.value();
                    }
                }
                //qDebug()<<"ELEVATOR_CAR:recedata"<<QString("adress:%1;value:%2").arg(QString::number(it.key())).arg(QString::number(it.value()));
            }
        }
        break;
    }
    default:
        break;
    }
}

///
/// \brief TCommtransceivermanager::UpdateConntectState
///更新数据内容
void TCommtransceivermanager::UpdateState()
{


}
///
/// \brief TCommtransceivermanager::Slotdisconnect
/// \param ID
/// \param type
///通讯断开的信号
void TCommtransceivermanager::Slotconnectstate(int ID, int type,bool state)
{
    //接收到掉线信号自动重新连接 设备状态更新
    switch (type)
    {
    case HWDEVICETYPE::RGVCAR:
    {
        TCommTCPclient *tob = dynamic_cast<TCommTCPclient *>(m_HWdeviceMap[ID]);
        if(tob->GetHWprotype() == KTcpClient)
        {
            if(Myconfig::GetInstance()->m_CarMap[ID].deveceStatus.isOnline != state)
            {
                Myconfig::GetInstance()->m_CarMap[ID].deveceStatus.isOnline = state;
            }
        }
        break;
    }
    case HWDEVICETYPE::RUNNER:
    {
        break;
    }
    case HWDEVICETYPE::ELEVATOR_CAR:
    {
        //小车电梯的连接状态
        if(m_HWdeviceMap.contains(ID)&& Myconfig::GetInstance()->m_elevatorMap.contains(ID))
        {
            if(Myconfig::GetInstance()->m_elevatorMap[ID].status.isOnline != state)
            {
                Myconfig::GetInstance()->m_elevatorMap[ID].status.isOnline = state;
            }
        }
        break;
    }
    default:
        break;
    }
}
