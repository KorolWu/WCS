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
        int hwtype = m_HWdeviceMap[hwId]->GetHWtype();
        int protype = m_HWdeviceMap[hwId]->GetHWprotype();
        switch (hwtype) {
        case HWDEVICETYPE::RGVCAR://需要发送的是AGV小车的内容
        {
            int16_t wcsindex = GetWCStocarFrameIndex(hwId);//
            QByteArray frameData;
            int16_t childtype = 0;
            childtype = cmd.childtype;
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
                break;
                memcpy(frameData.data(),(char*)(&wcssendframestru),40);
            }
            case 6://简易数据类型
            {
                SendCarCmdReqestFrame simplestru;
                simplestru.carnbr = hwId;
                simplestru.cmdnbr = wcsindex;
                simplestru.cmdname = cmd.value; // 请求指令数据 5 或者 6
                memcpy(frameData.data(),(char*)(&simplestru),40);
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
        std::sort(list.begin(), list.end());
        int16_t endvalue = list[list.size()-1];
        endvalue++;
        if(endvalue > 65530)//不能超过65535
        {
            endvalue = 0;
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
        else{
            qDebug()<<"找不到对应的值了";
            endvalue = -999;
            if(!list.contains(endvalue))
            {
                list.append(endvalue);
            }
        }
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
                        if(ModifyCarReceFrameIndex(ID,nbr))//正确报文 之前请求的数据已经返回了结果了
                        {
                            //解析详细数据内容
                            ReceCarDetailFrame detailstru;//详细数据报文
                            memcpy((char*)&detailstru,tempData.data(),74);
                            qDebug()<<"详细数据报文:"<< detailstru.carnbr << detailstru.state;
                        }
                    }
                    else if(tempData[4] == 'S' && tempData[5] == 'T')
                    {
                        //简易数据报文
                        ReceCarcmdsimFrame simstru;
                        memcpy((char*)&simstru,tempData.data(),10);
                        qDebug()<<"简易数据报文:"<< simstru.carnbr << simstru.carstate << simstru.info.carinfo;
                        if(nbr == 1000)
                        {
                            //不是回应指令动作
                            qDebug()<<" 主动发的简易数据指令报文:"<< simstru.carstate;
                        }
                    }
                    else
                    {
                        if(ModifyCarReceFrameIndex(ID,nbr)) //回应发出去编号内容
                        {
                            ReceCarcmdActionFrame actionstru;//动作指令报文
                            memcpy((char*)&actionstru,tempData.data(),10);
                            qDebug()<<"动作指令报文:"<< actionstru.carnbr <<actionstru.cmdname<<  actionstru.cmdstate<<actionstru.cmdnbr;
                            switch (actionstru.cmdstate)
                            {
                            case 1://指令状态正在执行

                                break;
                            case 2://异常

                                break;
                            case 3://指令完成

                                break;
                            default:
                                break;
                            }
                        }
                    }

                }

            }
        }
    }
}
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
    memcpy(tempData.data(),data.data(),data.size());//临时字节
    switch (hwtype) {
    case HWDEVICETYPE::RGVCAR:
    {
        AnalysisCarFrame(tempData,  ID);
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
void TCommtransceivermanager::Slotconnectstate(int ID, int type,bool state)
{
    //接收到掉线信号自动重新连接 设备状态更新
    switch (type)
    {
    case HWDEVICEPROTYPE::KTcpClient:
    {
        TCommTCPclient *tob = dynamic_cast<TCommTCPclient *>(m_HWdeviceMap[ID]);
        if(tob->GetHWtype() == RGVCAR)
        {
            //小车状态更新
            if(state)
            {

            }
            emit SignalCarStatusUpdate();
        }
        break;
    }
    default:
        break;
    }
}
