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

void ReadTableData::readt_elevator()
{
    QString sql = "SELECT * FROM t_elevator;";
    QSqlQuery query = CRUDBaseOperation::getInstance()->queryDb(sql);
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
