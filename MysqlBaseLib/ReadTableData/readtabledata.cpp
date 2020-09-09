#include "readtabledata.h"


ReadTableData::ReadTableData()
{

}

void ReadTableData::readt_device_info()
{
    QMutexLocker locker(&Myconfig::GetInstance()->m_mutex);
    QString sql = "SELECT * FROM t_device_info;";
    QSqlQuery query = CRUDBaseOperation::getInstance()->queryDb(sql);
    while (query.next()) {
        CarInfoStru car_info_stru;
        car_info_stru.deviceNum = query.value(1).toString();
        int carId = query.value(0).toInt();
        //        car_info_stru.deviceIp = query.value(2).toString();
        //        car_info_stru.port = query.value(3).toInt();
        //        car_info_stru.deviceType = query.value(4).toString();
        if( Myconfig::GetInstance()->m_CarMap.contains(carId))
        {
            Myconfig::GetInstance()->m_CarMap[carId].deveceStatus.carCurrentPosion.x = query.value(7).toDouble();
            Myconfig::GetInstance()->m_CarMap[carId].deveceStatus.carCurrentPosion.y = query.value(8).toDouble();
            Myconfig::GetInstance()->m_CarMap[carId].deveceStatus.carCurrentPosion.z = query.value(9).toDouble();
            qDebug()<<query.value(7).toDouble();
        }
        //Myconfig::GetInstance()->m_CarMap.insert(car_info_stru.deviceIp,car_info_stru);
    }
}

void ReadTableData::readt_elevator()
{
    QString sql = "SELECT * FROM t_elevator;";
    QSqlQuery query = CRUDBaseOperation::getInstance()->queryDb(sql);
    QMutexLocker locker(&Myconfig::GetInstance()->m_mutex);
    while (query.next()) {
        ElevatorInfoStru elevator_stru;
        elevator_stru.elevatorId = query.value(1).toInt();
        elevator_stru.elevatorType = query.value(2).toString();
        elevator_stru.elevatorIp = query.value(3).toString();
        elevator_stru.elevatorPort = query.value(4).toInt();

        elevator_stru.remarks = query.value(7).toString();
        elevator_stru.near_x = query.value(8).toDouble();
        elevator_stru.near_y = query.value(9).toDouble();
        elevator_stru.elevatorNearPos = QString("%1,%2").arg(elevator_stru.near_x).arg(elevator_stru.near_y);
        elevator_stru.elevator_x = query.value(10).toDouble();
        elevator_stru.elevator_y = query.value(11).toDouble();
        elevator_stru.elevatorPos = QString("%1,%2").arg(elevator_stru.elevator_x).arg(elevator_stru.elevator_y);
        Myconfig::GetInstance()->m_elevatorMap.insert(elevator_stru.elevatorId,elevator_stru);
    }
}

void ReadTableData::readt_crrunt_task()
{
    QString sql = "SELECT * FROM t_crrunt_task";
    QSqlQuery query = CRUDBaseOperation::getInstance()->queryDb(sql);
    QMutexLocker locker(&Myconfig::GetInstance()->m_mutex);
    while(query.next())
    {
        TaskInfoStru t;
        t.taskNum = query.value(1).toString();
        t.status = query.value(2).toString();
        t.boxNum = query.value(3).toString();
        t.pripty = query.value(4).toInt();
        t.from = query.value(5).toString();
        t.end = query.value(6).toString();
        t.carNum = query.value(7).toString();
        t.creatTime = query.value(8).toDateTime();
        //qDebug()<<query.value(8).toString().replace("T"," ")<<" :time"<<t.creatTime.toString("yyyy-MM-dd hh:mm:ss");
        Myconfig::GetInstance()->m_taskMap.insert(t.taskNum,t);
        Myconfig::GetInstance()->m_taskQueue.enqueue(t);
    }
}

void ReadTableData::readt_runerInfo()
{
    QMutexLocker locker(&Myconfig::GetInstance()->m_mutex);
    QString sql = "SELECT * FROM t_runerInfo;";
    QSqlQuery query = CRUDBaseOperation::getInstance()->queryDb(sql);
    while (query.next()) {
        RunerStru runer_info_stru;
        runer_info_stru.deviceNum = query.value(1).toString();
        runer_info_stru.deviceIp = query.value(2).toString();
        runer_info_stru.port = query.value(3).toInt();
        runer_info_stru.cache_in_max = query.value(4).toInt();
        runer_info_stru.cache_out_max = query.value(5).toInt();
        runer_info_stru.request_in = query.value(6).toString();
        runer_info_stru.response_in = query.value(7).toString();
        runer_info_stru.request_out = query.value(8).toString();
        runer_info_stru.response_out = query.value(8).toString();
        Myconfig::GetInstance()->m_runer = runer_info_stru;
    }
}
///
/// \brief ReadTableData::ReadStoreposinfoDataBase
/// 读货架仓位信息表格数据库
void ReadTableData::ReadStoreposinfoDataBase()
{
    QString tablename = "t_storeposinfo";
    QMutexLocker locker(&Myconfig::GetInstance()->m_mutex);
    Myconfig::GetInstance()->m_storeinfoMap.clear();
    QSqlQuery query = CRUDBaseOperation::getInstance()->ExcBatchSelectDB(tablename);
    while (query.next()) {
        StorePosInfoStru stru ;
        QByteArray bytearrayid;
        //= query.value("id").toByteArray();
        //  strlist.append(QString::number(bytearrayid.toInt()));
        bytearrayid = query.value("idNbr").toByteArray();
        memcpy(stru.idnbr,bytearrayid,bytearrayid.size());
        bytearrayid = query.value("type").toByteArray();
        stru.type = bytearrayid.toInt();
        bytearrayid = query.value("coordx").toByteArray();
        stru.coordx = bytearrayid.toDouble();
        bytearrayid = query.value("coordy").toByteArray();
        stru.coordy = bytearrayid.toDouble();
        bytearrayid = query.value("coordz").toByteArray();
        stru.coordz = bytearrayid.toDouble();
        bytearrayid=  query.value("directionstate").toByteArray();
        stru.directionstate = bytearrayid.toInt();
        bytearrayid = query.value("boxnbr").toByteArray();
        memcpy(stru.boxnbr,bytearrayid,bytearrayid.size());
        bytearrayid= query.value("storestat").toByteArray();
        stru.storestat =bytearrayid.toInt();
        bytearrayid = query.value("storepri").toByteArray();
        stru.storepri = bytearrayid.toInt();
        bytearrayid=  query.value("unused").toByteArray();
        stru.unused = QString(bytearrayid);
        Myconfig::GetInstance()->m_storeinfoMap.insert(QString(stru.idnbr),stru);
    }
}
///
/// \brief ReadTableData::WriteStoreposinfotoDataBase
/// \param storeposInfoMap
/// \param errorinfo
/// \return
///写数据库的内容 以更新方式进行
bool ReadTableData::WriteStoreposinfotoDataBase(QMap<QString, StorePosInfoStru> storeposInfoMap, QString &errorinfo)
{
    QMutexLocker locker(&Myconfig::GetInstance()->m_mutex_sqlwrite);
    QString tablename = "t_storeposinfo";
    QStringList names;
    names<<"idNbr"<<"type"<<"coordx"<<"coordy"<<"coordz" << "directionstate"<<"boxnbr"<<"storestat"<<"storepri"<<"unused";
    QList<QVariantList> values;
    for(auto  it = storeposInfoMap.begin(); it != storeposInfoMap.end();++it)
    {
        QVariantList list;
        list.append(QString::fromUtf8(it.value().idnbr));
        list.append(it.value().type);
        list.append(it.value().coordx);
        list.append(it.value().coordy);
        list.append(it.value().coordz);
        list.append(it.value().directionstate);
        list.append(QString::fromUtf8(it.value().boxnbr));
        list.append(it.value().storestat);
        list.append(it.value().storepri);
        list.append(it.value().unused);
        values.append(list);
    }
    if(CRUDBaseOperation::getInstance()->ExcBatchReplaceDB(tablename,names,values,errorinfo))
    {
        return true;
    }
    else{
        qDebug()<<"errorinfo:"<<errorinfo;
        return false;
    }
}

bool ReadTableData::WriteLoginfo(int level, QString from, QString log_info)
{
    QMutexLocker locker(&Myconfig::GetInstance()->m_mutex_sqlwrite);
    QString sql = QString("INSERT INTO `t_log` (`level`,`from`,`loginfo`) VALUES ('%1','%2','%3');").arg(level).arg(from).arg(log_info);
    qDebug()<<sql;
    if(CRUDBaseOperation::getInstance()->queryUseStr(sql))
        return true;
    return false;
}

bool ReadTableData::WriteUpdateInfoDataBase(QMap<QString, StorePosInfoStru> storeposInfoMap, QVector<QVariant> keyvalue,QString &errorinfo,bool updatestru)
{
    QString tablename = "t_storeposinfo";
    QStringList names;
    names<<"idNbr"<<"type"<<"coordx"<<"coordy"<<"coordz" << "directionstate"<<"boxnbr"<<"storestat"<<"storepri"<<"unused";
    QList<QVariantList> values;
    for(auto  it = storeposInfoMap.begin(); it != storeposInfoMap.end();++it)
    {
        QVariantList list;
        list.append(QString::fromUtf8(it.value().idnbr));
        list.append(it.value().type);
        list.append(it.value().coordx);
        list.append(it.value().coordy);
        list.append(it.value().coordz);
        list.append(it.value().directionstate);
        list.append(QString::fromUtf8(it.value().boxnbr));
        list.append(it.value().storestat);
        list.append(it.value().storepri);
        list.append(it.value().unused);
        values.append(list);
    }
    QString idname = "idNbr";
    QVector<QVariantList> valueVec = values.toVector();
    QMutexLocker locker(&Myconfig::GetInstance()->m_mutex);
    if(CRUDBaseOperation::getInstance()->ExcBatchUpdateDB(tablename,names,valueVec,idname,keyvalue,errorinfo))
    {
        //内存更新
        if(updatestru)
        {
            for(auto  it = storeposInfoMap.begin(); it != storeposInfoMap.end();++it)
            {
                if(Myconfig::GetInstance()->m_storeinfoMap.contains(it.key()))
                {
                    Myconfig::GetInstance()->m_storeinfoMap[it.key()] = it.value();

                }
            }
        }
        return true;
    }
    else{
        qDebug()<<"errorinfo:"<<errorinfo;
        return false;
    }
}
///
/// \brief ReadTableData::WriteAlarmInfo
/// \param alarmstru 报警信息结构体参数信息
/// \return
///实现报警信息的插入
bool ReadTableData::WriteAlarmInfo(ALARMINFOSTRU alarmstru, QString &error)
{
    QString tablename = "t_alarmInfo";
    QStringList names;
    names<<"Alarmlevel"<<"DeviceID"<<"ErrorType"<<"Errorcode"<<"Operatestate"<<"CarTaskID"<<"WMSTaskID"\
        <<"BoxNumber"<<"AlarmInfo"<<"Carcoordx"<<"Carcoordy"<<"Carcoordz";
    QVariantList list;
    QList<QVariantList> values;
    list<<alarmstru.alarmlevel<<alarmstru.deviceid<<alarmstru.errortype<<alarmstru.errorcode<<alarmstru.Operatestate<<alarmstru.cartaskid\
       <<alarmstru.wmsTaskid<<alarmstru.boxnumber<<alarmstru.alarminfo<<alarmstru.carcoordx<<alarmstru.carcoordy\
      <<alarmstru.carcoordz;
    values.append(list);
    if(CRUDBaseOperation::getInstance()->ExcBatchInsertDb(tablename,names,values,error))
    {
        return true;
    }
    else{
        qDebug()<<"error:"<<error;
        return false;
    }
}
///
/// \brief ReadTableData::DelStoreposinfotoDataBaseByLayer
/// \param z
/// \return
/// deldatabyinfo
bool ReadTableData::DelStoreposinfotoDataBaseByLayer(double z,QString &error)
{
    QString tablename = "t_storeposinfo";
    QString name = "coordz";
    QList<QVariant> values;
    values.append(z);
    QMutexLocker locker(&Myconfig::GetInstance()->m_mutex);
    if(CRUDBaseOperation::getInstance()->ExcBatchDeleteDB(tablename,name,values,error))
    {
        return true;
    }
    else{
        qDebug()<<"error:"<<error;
        return false;
    }
}
///
/// \brief ReadTableData::WriteInsertInfoDataBase
/// \param storeposInfoMap
/// \param errorinfo
/// \return  插入数据写入到数据库中
///
bool ReadTableData::WriteInsertInfoDataBase(QMap<QString, StorePosInfoStru> storeposInfoMap, QString &errorinfo)
{
    QString tablename = "t_storeposinfo";
    QStringList names;
    names<<"idNbr"<<"type"<<"coordx"<<"coordy"<<"coordz" << "directionstate"<<"boxnbr"<<"storestat"<<"storepri"<<"unused";
    QList<QVariantList> values;
    for(auto  it = storeposInfoMap.begin(); it != storeposInfoMap.end();++it)
    {
        QVariantList list;
        list.append(QString::fromUtf8(it.value().idnbr));
        list.append(it.value().type);
        list.append(it.value().coordx);
        list.append(it.value().coordy);
        list.append(it.value().coordz);
        list.append(it.value().directionstate);
        list.append(QString::fromUtf8(it.value().boxnbr));
        list.append(it.value().storestat);
        list.append(it.value().storepri);
        list.append(it.value().unused);
        values.append(list);
    }
    if(CRUDBaseOperation::getInstance()->ExcBatchInsertDb(tablename,names,values,errorinfo))
    {
        return true;
    }
    else{
        qDebug()<<"errorinfo:"<<errorinfo;
        return false;
    }
}
///
/// \brief ReadTableData::Readt_hwcomm_infotable
/// \return
///读通讯配置表格的内容
void ReadTableData::Readt_hwcomm_infotable()
{
    QString tablename = "t_hwcomm_info";
    QMutexLocker locker(&Myconfig::GetInstance()->m_mutex);//内存锁
    Myconfig::GetInstance()->m_hwcommstru.hwmodbustcpcliMap.clear();
    Myconfig::GetInstance()->m_hwcommstru.hwSerialPortMap.clear();
    Myconfig::GetInstance()->m_hwcommstru.hwTcpMap.clear();
    Myconfig::GetInstance()->m_CarMap.clear();
    QSqlQuery query = CRUDBaseOperation::getInstance()->ExcBatchSelectDB(tablename);

    while (query.next()) {
        int  Id;
        Id = query.value("ID").toInt();
        int type =  query.value("type").toInt();
        int protype =  query.value("protype").toInt();
        int childtype = query.value("childtype").toInt();
        QString unused = query.value("unused").toString();
        QString name = query.value("name").toString();
        switch (protype) {
        case HWDEVICEPROTYPE::Tcpserver:
        case HWDEVICEPROTYPE::KTcpClient:
        {
            TcpStru stru;
            stru.hwtype = type;
            stru.protype = protype;
            stru.ID = Id;
            stru.name = name;
            stru.childtype = childtype;
            stru.unused = unused;
            stru.port = query.value("port").toInt();
            Myconfig::GetInstance()->m_hwcommstru.hwTcpMap.insert(Id,stru);
            break;
        }
        case HWDEVICEPROTYPE::KSerialPort:
        case HWDEVICEPROTYPE::KModbusSerialport:
        {
            SerialPortstru stru;
            stru.hwtype = type;
            stru.protype = protype;
            stru.ID = Id;
            stru.name = name;
            stru.childtype = childtype;
            stru.unused = unused;
            stru.BaudRate =  query.value("BaudRate").toInt();
            stru.DataBits = query.value("DataBits").toInt();
            stru.Parity = query.value("Parity").toInt();
            stru.StopBits = query.value("StopBits").toInt();
            stru.serveraddress = query.value("port").toInt();
            Myconfig::GetInstance()->m_hwcommstru.hwSerialPortMap.insert(Id,stru);
            if(type == HWDEVICETYPE::BARCODE)
            {
                ScanInfoStru scanstru;
                scanstru.hwInfo.BaudRate = stru.BaudRate;
                scanstru.hwInfo.DataBit = stru.DataBits;
                scanstru.hwInfo.Parity = stru.Parity;
                scanstru.hwInfo.SerialName = name;
                scanstru.hwInfo.SerialPort = stru.serveraddress;
                scanstru.hwInfo.StopBit =  stru.StopBits;
                scanstru.deviceId = Id;
                Myconfig::GetInstance()->m_ScanMap.insert(Id,scanstru);
            }
            break;
        }
        case HWDEVICEPROTYPE::KModbusTcpClient:
        {
            ModbusTcpClientstru stru;
            stru.hwtype = type;
            stru.protype = protype;
            stru.ID = Id;
            stru.name = name;
            stru.childtype = childtype;
            stru.unused = unused;
            stru.url_str = name;
            stru.serveraddress =  query.value("port").toInt();;
            Myconfig::GetInstance()->m_hwcommstru.hwmodbustcpcliMap.insert(Id,stru);
            break;
        }
        case HWDEVICEPROTYPE::KHttpServer:
        {
            HttpServerStru stru;
            stru.hwtype = type;
            stru.protype = protype;
            stru.ID = Id;
            stru.name = name;
            stru.childtype = childtype;
            stru.unused = unused;
            Myconfig::GetInstance()->m_hwcommstru.hwhttpserverMap.insert(Id,stru);
            break;
        }
        default:
            break;
        }
        if(type == HWDEVICETYPE::RGVCAR)
        {
            CarInfoStru stru;
            stru.carId = Id;
            stru.deviceIp = name;
            stru.port = query.value("port").toInt();
            if(Myconfig::GetInstance()->m_CarMap.contains(Id))
            {
                Myconfig::GetInstance()->m_CarMap[Id]= stru;
            }
            else{
                Myconfig::GetInstance()->m_CarMap.insert(Id,stru);
            }
        }
        if(type == HWDEVICETYPE::RUNNER)
        {
            Myconfig::GetInstance()->m_runer.port = query.value("port").toInt();
            Myconfig::GetInstance()->m_runer.deviceIp = name;
            Myconfig::GetInstance()->m_runer.deviceNum = QString::number(Id);
        }
    }
}

