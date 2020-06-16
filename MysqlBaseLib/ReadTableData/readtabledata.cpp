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
///
/// \brief ReadTableData::ReadStoreposinfoDataBase
/// 读货架仓位信息表格数据库
void ReadTableData::ReadStoreposinfoDataBase()
{
QString tablename = "t_storeposinfo";
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
    bytearrayid = query.value("boxnbr").toByteArray();
    memcpy(stru.boxnbr,bytearrayid,bytearrayid.size());
    bytearrayid= query.value("storestat").toByteArray();
    stru.storestat =bytearrayid.toInt();
    bytearrayid = query.value("storepri").toByteArray();
    stru.storepri = bytearrayid.toInt();
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
    QString tablename = "t_storeposinfo";
    QStringList names;
    names<<"idNbr"<<"type"<<"coordx"<<"coordy"<<"coordz"<<"boxnbr"<<"storestat"<<"storepri";
    QList<QVariantList> values;
    for(auto  it = storeposInfoMap.begin(); it != storeposInfoMap.end();++it)
    {
        QVariantList list;
        list.append(QString::fromUtf8(it.value().idnbr));
        list.append(it.value().type);
        list.append(it.value().coordx);
        list.append(it.value().coordy);
        list.append(it.value().coordz);
        list.append(QString::fromUtf8(it.value().boxnbr));
        list.append(it.value().storestat);
        list.append(it.value().storepri);
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

