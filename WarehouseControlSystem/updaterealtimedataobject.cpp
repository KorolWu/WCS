#include "updaterealtimedataobject.h"

UpdateRealtimeDataObject::UpdateRealtimeDataObject()
{

}

UpdateRealtimeDataObject::~UpdateRealtimeDataObject()
{

}
///
/// \brief UpdateRealtimeDataObject::SaveStoreinfotoDatabase
///1s 更新货架信息数据到本地数据库
void UpdateRealtimeDataObject::SaveStoreinfotoDatabase()
{
    QMutexLocker locker(&Myconfig::GetInstance()->m_rmutex);
    QMap<QString, StorePosInfoStru> updatemap;
    QVector<QVariant> keyvalue;
    auto it = Myconfig::GetInstance()->m_storeinfoMap.begin();
    for(;it !=Myconfig::GetInstance()->m_storeinfoMap.end(); ++it)
    {
        if(it.value().update)
        {
            updatemap.insert(it.key(),it.value());
            keyvalue.append(it.key());
        }
    }
    if(updatemap.size() > 0)
    {
        //写入数据库
        QString msg;
        if(!m_databaseopob.WriteUpdateInfoDataBase(updatemap,keyvalue,msg,false))
        {
            qDebug()<<"货架信息数据写入失败"<<msg;
        }
        else{ //更新成功
            //把状态更新的数据进行复位
            QMutexLocker locker(&Myconfig::GetInstance()->m_mutex);
            for(int i = 0; i < keyvalue.size(); ++i)
            {
                QString key = keyvalue[i].toString();
                if(Myconfig::GetInstance()->m_storeinfoMap.contains(key))
                {
                    Myconfig::GetInstance()->m_storeinfoMap[key].update = false;
                }
            }
        }
    }
}
///
/// \brief UpdateRealtimeDataObject::RequestTimingupdateHWinfo
///  小车信息数据一直请求更新 发送详细数据类型
///  流道信息请求 定时请求任务更新
void UpdateRealtimeDataObject::RequestTimingupdateHWinfo()
{
    UpdateCarDataRequest();
    UpdateRunnerDataRequest();
}
///
/// \brief UpdateRealtimeDataObject::UpdateCarDataRequest
///小车数据请求方式
void UpdateRealtimeDataObject::UpdateCarDataRequest()
{
    for(auto it = Myconfig::GetInstance()->m_hwcommstru.hwTcpMap.begin(); it !=Myconfig::GetInstance()->m_hwcommstru.hwTcpMap.end(); ++it  )
    {
        OrderStru carstru;
        carstru.childtype = 6;// 发送请求指令
        carstru.value = 5;//请求的数据指令，为详细类型
        if(it.value().hwtype == RGVCAR && it.value().protype == KTcpClient)
        {
            TCommtransceivermanager::GetInstance()->SendcommandByExtern(carstru,it.key());
            carstru.value = 6;
            TCommtransceivermanager::GetInstance()->SendcommandByExtern(carstru,it.key());
        }
    }
}
///
/// \brief UpdateRealtimeDataObject::UpdateRunnerDataRequest
///流道数据请求
void UpdateRealtimeDataObject::UpdateRunnerDataRequest()
{
    for(auto it = Myconfig::GetInstance()->m_hwcommstru.hwmodbustcpcliMap.begin(); \
        it !=Myconfig::GetInstance()->m_hwcommstru.hwmodbustcpcliMap.end(); ++it  )
    {
        if(it.value().hwtype == RUNNER && it.value().protype == KModbusTcpClient)
        {
            OrderStru runnerstru;
            runnerstru.childtype = 5;
            runnerstru.Datatype = 4; //寄存器 读写
            runnerstru.startaddress = 0;
            runnerstru.numberOfEntries = 10;
            TCommtransceivermanager::GetInstance()->SendcommandByExtern(runnerstru,it.key());//d0-d10
            runnerstru.startaddress = 11;
            runnerstru.numberOfEntries = 12;
            TCommtransceivermanager::GetInstance()->SendcommandByExtern(runnerstru,it.key());//d11-d22
            runnerstru.startaddress = 60;
            runnerstru.numberOfEntries = 15;
            TCommtransceivermanager::GetInstance()->SendcommandByExtern(runnerstru,it.key());//d60-d74
        }
    }
}
