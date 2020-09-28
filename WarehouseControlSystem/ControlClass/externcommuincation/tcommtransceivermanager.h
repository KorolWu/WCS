#ifndef TCOMMTRANSCEIVERMANAGER_H
#define TCOMMTRANSCEIVERMANAGER_H

#include <QObject>
#include "hwcommfactoryob.h"
#include <QTimer>
#include <datastructure.h>
#include <Myconfig.h>
#include "tcommtcpclient.h"
#include "tcommtcpserver.h"
#include "tcommmodbustcpclient.h"
#include "tcommmodbusserial.h"
#include <QMutexLocker>
#include <QMutex>
#include <QMap>

///
/// \brief The TCommtransceivermanager class
///所有通讯收发的数据窗口管理器
///
struct ModbusStru{
    int type;
    int bit;
    int address;
    uint16_t value;
    int64_t data;
};
enum CarStatusrole
{
    RBposinfo =1,//条码位置信息
    Opermode =2,//自动/手动
    sensorstat  = 3,//左侧有货 右侧有货
    exestatus = 4,//穿梭车电量低 小车 自动状态下发生了故障 自动校准中 就绪中
    errorinfo = 5,// 故障信息图
    actioninfo = 6 // 动作指令反馈信息
};

class TCommtransceivermanager:public QObject
{
    Q_OBJECT
private:
    TCommtransceivermanager();
    ~TCommtransceivermanager();
public:
    void InitHWcommob();
    void SendcommandByExtern(OrderStru cmd,int Id);
    static TCommtransceivermanager* GetInstance()
    {
        static TCommtransceivermanager Instance;
        return &Instance;
    }
signals:
    void SignalCarStatusUpdate();
    void signalError(QString info);
public slots:
    void ReceDataFromHWob(int ID,int hwtype,QByteArray data);//数据接收内容
    void ReceModbusDataFromHWob(int ID,int hwtype,int datatype,QMap<int,int> Data);
private:
    void sendDataToHWob(QByteArray data ,int id);
    void AnalysisDataFrame(QByteArray dataframe);//解析帧内容
    int16_t GetWCStocarFrameIndex(int hwId);
    bool ModifyCarReceFrameIndex(int ID,int wcsnbr);
    void AnalysisCarFrame(QByteArray dataframe ,int ID);
    void UpdateCarStatus(int carID,int role,int value);
    void UpdateRunnerData(int datatype, QMap<int, int> Data);
    void UpdateCarelevatorData(int ID ,QMap<int, int> Data);
    void UpdateScanData(QByteArray dataframe ,int ID);

private slots:
    void UpdateState();
    void Slotconnectstate(int ID,int type,bool state);
    void SlotErrinfo(int ID,int type,QString info);
private:
    QTimer *m_heartTimer;
    QMap<int,HWdeviceabstractInterface *> m_HWdeviceMap;
    QMutex m_TCommMutex; //通讯对象部分数据读写锁
    QMap<int16_t,QList<int16_t>> m_Wcstocarframeindex; // 小车的id 和对应的报文的索引值

private://模板函数
    template<typename T1>
    void CreatObbyHWconfigData(QMap<int,T1> datamap ,HWDEVICEPROTYPE type)
    {
        for(auto it = datamap.begin();\
            it!= datamap.end();++it)
        {
            ComConfigStru stru;
            HWdeviceabstractInterface *ob = NULL;
            ob = HWCommFactoryOb::CreatorHWCommFactoryOb(it.value().protype);
            if(ob)
            {
                switch (type) {
                case KTcpClient:
                case Tcpserver:
                {
                    int len = sizeof(T1);
                    char buffer[len] = {0};
                    memcpy(buffer,&it.value(),len);
                    TcpStru *tstru =(TcpStru*)(buffer);
                    stru.hwTcpstru = *tstru;
                    break;
                }
                case KSerialPort:
                {
                    int len = sizeof(T1);
                    char buffer[len] = {0};
                    memcpy(buffer,&it.value(),len);
                    SerialPortstru *tstru =(SerialPortstru*)(buffer);
                    stru.hwserialstru =  *tstru;
                    if(tstru->protype == KModbusSerialport)
                    {
                        connect(ob,&HWdeviceabstractInterface::signalReceModbusHWdeviceData,this,&TCommtransceivermanager::ReceModbusDataFromHWob);
                    }
                    break;
                }
                case KModbusTcpClient:
                {
                    int len = sizeof(T1);
                    char buffer[len] = {0};
                    memcpy(buffer,&it.value(),len);
                    ModbusTcpClientstru *tstru =(ModbusTcpClientstru*)(buffer);
                    stru.hwmodbustcpclistru =*tstru;
                    connect(ob,&HWdeviceabstractInterface::signalReceModbusHWdeviceData,this,&TCommtransceivermanager::ReceModbusDataFromHWob);                                       
                    break;
                }
                default:
                    break;
                }
                m_HWdeviceMap.insert(it.key(),ob);
                connect(ob,&HWdeviceabstractInterface::signalHWDisconnect,this,&TCommtransceivermanager::Slotconnectstate);
                ob->SetCommParam(stru);
                connect(ob,&HWdeviceabstractInterface::signalReadHWdeviceData,this,&TCommtransceivermanager::ReceDataFromHWob);
                connect(ob,&HWdeviceabstractInterface::signalErrorInfo,this,&TCommtransceivermanager::SlotErrinfo);

            }
        }
    }
};

#endif // TCOMMTRANSCEIVERMANAGER_H
