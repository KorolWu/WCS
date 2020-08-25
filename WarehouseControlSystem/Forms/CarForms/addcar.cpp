#include "addcar.h"

AddCar::AddCar(const QStringList &list,QString flag, QWidget *parent = 0):DialogAbstractClass(list,flag,parent)
{

}

void AddCar::onYesBtnClicked()
{

    QStringList list =  getContent();
    if(list.size()!= 5)
    {
        m_err_lab->setText("insert fail");
        return;
    }
    deviceStruct.deviceNum =  list[0];
    if(m_sql_flag == "Update")
    {
        if(!Myconfig::GetInstance()->m_CarMap.contains(QString(list[1]).toInt()))
        {
            m_err_lab->setText("不允许在线修改IP");
            return;
        }
       deviceStruct.deviceIp = Myconfig::GetInstance()->m_CarMap[QString(list[1]).toInt()].deviceIp;
    }
    deviceStruct.deviceIp = list[1];
    deviceStruct.port = QString(list[2]).toInt();
    deviceStruct.deviceType = list[3];
    deviceStruct.remarks = list[4];
    QString sql;
    if(m_sql_flag == "Insert") //protype = 1,mean device is car
    {
         sql = QString("INSERT t_hwcomm_info SET ID = '%1',type = 'RGV',protype = 1, port = '%2',name = '%3';")
            .arg(deviceStruct.deviceNum.toInt()).arg(deviceStruct.port).arg(deviceStruct.deviceIp);
    }
    else
    {
        sql = QString("UPDATE t_hwcomm_info SET name = '%1', port = '%2',WHERE ID = '%5';")
           .arg(deviceStruct.deviceIp).arg(deviceStruct.port).arg(deviceStruct.deviceNum.toInt());
    }
    if(CRUDBaseOperation::getInstance()->queryUseStr(sql))
    {
        // the same id,same ip
//        if(m_sql_flag == "Insert")
//            Myconfig::GetInstance()->m_CarMap.insert(deviceStruct.deviceIp,deviceStruct);
//        else if(m_sql_flag == "Update")
//        {
//             if(Myconfig::GetInstance()->m_CarMap.contains(deviceStruct.deviceIp))
//             {
//                 Myconfig::GetInstance()->m_CarMap[deviceStruct.deviceIp].deviceNum = deviceStruct.deviceNum;
//                 Myconfig::GetInstance()->m_CarMap[deviceStruct.deviceIp].port = deviceStruct.port;
//                 Myconfig::GetInstance()->m_CarMap[deviceStruct.deviceIp].deviceType = deviceStruct.deviceType;
//             }
//        }
        emit insert_emit();
        this->hide();
        this->deleteLater();
    }
    else
        m_err_lab->setText("插入失败 请检查字段类型 或数据库链接情况");
    qDebug()<<sql;
    //handle deviceStruct
}
