#ifndef TCOMMTRANSCEIVERMANAGER_H
#define TCOMMTRANSCEIVERMANAGER_H

#include <QObject>
#include "hwcommfactoryob.h"
#include <QTimer>
#include <datastructure.h>
#include <Myconfig.h>
#include "tcommtcpclient.h"
#include "tcommtcpserver.h"
#include <QMutexLocker>
///
/// \brief The TCommtransceivermanager class
///所有通讯收发的数据窗口管理器
class TCommtransceivermanager:public QObject
{
    Q_OBJECT
private:
    TCommtransceivermanager();
    ~TCommtransceivermanager();
public:
    void InitHWcommob();
    void sendDataToHWob(QByteArray data ,QString id);
    static TCommtransceivermanager* GetInstance()
    {
        static TCommtransceivermanager Instance;
        return &Instance;
    }
public slots:
    void ReceDataFromHWob(QString ID,int hwtype,QByteArray data);//数据接收内容
private:
    void AnalysisDataFrame(QByteArray dataframe);//解析帧内容
private slots:
    void UpdateState();
    void Slotconnectstate(QString ID,int type,bool state);
private:
    QTimer *m_heartTimer;
    QMap<QString,HWdeviceabstractInterface *> m_HWdeviceMap;
private://模板函数
    template<typename T1>
    void CreatObbyHWconfigData(QMap<QString,T1> datamap ,HWDEVICEPROTYPE type)
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
                    break;
                }
                case KModbusTcpClient:
                {
                    int len = sizeof(T1);
                    char buffer[len] = {0};
                    memcpy(buffer,&it.value(),len);
                    ModbusTcpClientstru *tstru =(ModbusTcpClientstru*)(buffer);
                    stru.hwmodbustcpclistru =*tstru;
                    break;
                }
                default:
                    break;
                }
                ob->SetCommParam(stru);
                m_HWdeviceMap.insert(it.key(),ob);
                connect(ob,&HWdeviceabstractInterface::signalReadHWdeviceData,this,&TCommtransceivermanager::ReceDataFromHWob);
                connect(ob,&HWdeviceabstractInterface::signalHWDisconnect,this,&TCommtransceivermanager::Slotconnectstate);
            }
        }
    }
};

#endif // TCOMMTRANSCEIVERMANAGER_H