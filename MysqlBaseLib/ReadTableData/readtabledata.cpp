#include "readtabledata.h"


ReadTableData::ReadTableData()
{
}

void ReadTableData::readt_device_info()
{
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
