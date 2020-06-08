#include "addelevatorform.h"
#include <QDebug>

AddElevatorForm::AddElevatorForm(const QStringList &list,QWidget *parent) :
    DialogAbstractClass(list,parent)
{

}

void AddElevatorForm::onYesBtnClicked()
{
    QStringList list = getContent();
    qDebug()<<list;
}

void AddElevatorForm::onCleanBtnClicked()
{
    this->hide();
    this->deleteLater();
}
