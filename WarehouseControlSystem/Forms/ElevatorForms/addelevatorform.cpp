#include "addelevatorform.h"
#include <QDebug>

AddElevatorForm::AddElevatorForm(const QStringList &list,QString flag,QWidget *parent) :
    DialogAbstractClass(list,flag,parent)
{

}

void AddElevatorForm::onYesBtnClicked()
{
    QStringList list = getContent();
    if(list.size() != 6)
    {
        m_err_lab->setText("insert fail");
        return;
    }
    QString sql = "";
    QString hw_sql = "";
    if(m_sql_flag == "Insert")
    {
     sql = QString("INSERT t_elevator SET elevatorNum='%1',type='%2',ip_address='%3',port='%4',near_position='%5',position='%6'")
            .arg(list[0]).arg(list[1]).arg(list[2]).arg(list[3]).arg(list[4]).arg(list[5]);
     hw_sql = QString("INSERT t_hwcomm_info SET ID = '%1',type = 'ELEVATOR',protype = 2, port = '%2',name = '%3';")
        .arg(QString(list[0]).toInt()).arg(list[0]).arg(list[2]);
    }
    else
    {
        sql = QString("UPDATE t_elevator SET elevatorNum='%1',type='%2',port='%4',near_position='%5',position='%6' WHERE ip_address='%7'")
               .arg(list[0]).arg(list[1]).arg(list[3]).arg(list[4]).arg(list[5]).arg(list[2]);
        hw_sql = QString("UPDATE t_hwcomm_info SET name = '%1', port = '%2',WHERE ID = '%5';")
                .arg(list[2]).arg(list[0]).arg(list[0].toInt());
    }
    bool result = CRUDBaseOperation::getInstance()->queryUseStr(sql);
    if(result)
        result = CRUDBaseOperation::getInstance()->queryUseStr(hw_sql);
    if(true == result)
    {
        ElevatorInfoStru elevatorStru;
        elevatorStru.elevatorNum = list[0];
        elevatorStru.elevatorType = list[1];
        elevatorStru.elevatorIp = list[2];
        elevatorStru.elevatorPort = QString(list[3]).toInt();
        elevatorStru.elevatorNearPos = list[4];
        elevatorStru.elevatorPos = list[5];
        if(m_sql_flag == "Insert")
            Myconfig::GetInstance()->m_elevatorMap.insert(elevatorStru.elevatorNum.toInt(),elevatorStru);
        else
        {
            if(Myconfig::GetInstance()->m_elevatorMap.contains(elevatorStru.elevatorNum.toInt()))
                Myconfig::GetInstance()->m_elevatorMap[elevatorStru.elevatorNum.toInt()] = elevatorStru;
        }
        emit insert_emit();
        this->hide();
        this->deleteLater();
    }
    else
        m_err_lab->setText("insert fail,check the pameter please!");
    // emit signal to update tableview
    qDebug()<<"query result "<<result <<endl<<sql;
}

void AddElevatorForm::onCleanBtnClicked()
{
    this->hide();
    this->deleteLater();
}
