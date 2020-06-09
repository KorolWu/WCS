#include "addcar.h"
#include "../../UnitClass/databaseunit.h"
AddCar::AddCar(const QStringList &list, QWidget *parent = 0):DialogAbstractClass(list,parent)
{

}

void AddCar::onYesBtnClicked()
{

    QStringList list =  getContent();
    deviceStruct.deviceNum =  list[0];
    deviceStruct.deviceIp = list[1];
    deviceStruct.port = QString(list[2]).toInt();
    deviceStruct.deviceType = list[3];
    deviceStruct.remarks = list[4];

    QString sql = QString("INSERT t_device_info SET deviceNum = '%1',deviceIp = '%2',devicePort = '%3',deviceType = '%4',remarks = '%5';").arg(deviceStruct.deviceNum).arg(deviceStruct.deviceIp).arg(deviceStruct.port).arg(deviceStruct.deviceType);
    if(DataBaseUnit::GetInstance()->queryUseStr(sql))
    {
        // the same id,same ip
        emit insert_emit();
        this->hide();
        this->deleteLater();
    }
    else
        m_err_lab->setText("插入失败 请检查字段类型 或数据库链接情况");
    //handle deviceStruct
}
