#include "addelevatorform.h"
#include <QDebug>

AddElevatorForm::AddElevatorForm(const QStringList &list,QWidget *parent) :
    DialogAbstractClass(list,parent)
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
    QString sql = QString("INSERT t_elevator SET elevatorNum='%1',type='%2',ip_address='%3',port='%4',near_position='%5',position='%6'")
            .arg(list[0]).arg(list[1]).arg(list[2]).arg(list[3]).arg(list[4]).arg(list[5]);
    bool result = CRUDBaseOperation::getInstance()->queryUseStr(sql);
    if(true == result)
    {
        ElevatorInfoStru elevatorStru;
        elevatorStru.elevatorNum = list[0];
        elevatorStru.elevatorType = list[1];
        elevatorStru.elevatorIp = list[2];
        elevatorStru.elevatorPort = QString(list[3]).toInt();
        elevatorStru.elevatorNearPos = list[4];
        elevatorStru.elevatorPos = list[5];
        Myconfig::GetInstance()->m_elevatorMap.insert(elevatorStru.elevatorIp,elevatorStru);
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
