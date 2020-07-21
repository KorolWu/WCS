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
        car_info_stru.deviceIp = query.value(2).toString();
        car_info_stru.port = query.value(3).toInt();
        car_info_stru.deviceType = query.value(4).toString();
        Myconfig::GetInstance()->m_CarMap.insert(car_info_stru.deviceIp,car_info_stru);
    }
}

void ReadTableData::readt_elevator()
{
    QString sql = "SELECT * FROM t_elevator;";
    QSqlQuery query = CRUDBaseOperation::getInstance()->queryDb(sql);
    QMutexLocker locker(&Myconfig::GetInstance()->m_mutex);
    while (query.next()) {
        ElevatorInfoStru elevator_stru;
        elevator_stru.elevatorNum = query.value(1).toString();
        elevator_stru.elevatorType = query.value(2).toString();
        elevator_stru.elevatorIp = query.value(3).toString();
        elevator_stru.elevatorPort = query.value(4).toInt();
        elevator_stru.elevatorNearPos = query.value(5).toString();
        elevator_stru.elevatorPos = query.value(6).toString();
        elevator_stru.remarks = query.value(7).toString();
        Myconfig::GetInstance()->m_elevatorMap.insert(elevator_stru.elevatorIp,elevator_stru);
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
        qDebug()<<query.value(8).toString().replace("T"," ")<<" :time"<<t.creatTime.toString("yyyy-MM-dd hh:mm:ss");
        Myconfig::GetInstance()->m_taskMap.insert(t.taskNum,t);
        Myconfig::GetInstance()->m_taskQueue.enqueue(t);
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
    QMutexLocker locker(&Myconfig::GetInstance()->m_mutex);
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
    QString sql = QString("INSERT INTO `t_log` (`level`,`from`,`loginfo`) VALUES ('%1','%2','%3');").arg(level).arg(from).arg(log_info);
    qDebug()<<sql;
    if(CRUDBaseOperation::getInstance()->queryUseStr(sql))
        return true;
    return false;
}

bool ReadTableData::WriteUpdateInfoDataBase(QMap<QString, StorePosInfoStru> storeposInfoMap, QVector<QVariant> keyvalue,QString &errorinfo)
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
    QVector<QVariantList> valueVec =values.toVector() ;
    QMutexLocker locker(&Myconfig::GetInstance()->m_mutex);
    if(CRUDBaseOperation::getInstance()->ExcBatchUpdateDB(tablename,names,valueVec,idname,keyvalue,errorinfo))
    {
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
    QMutexLocker locker(&Myconfig::GetInstance()->m_mutex);
    if(CRUDBaseOperation::getInstance()->ExcBatchInsertDb(tablename,names,values,error))
    {
        return true;
    }
    else{
        qDebug()<<"error:"<<error;
        return false;
    }
}

