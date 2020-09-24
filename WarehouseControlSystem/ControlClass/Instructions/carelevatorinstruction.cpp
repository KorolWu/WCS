#include "carelevatorinstruction.h"
#define TIMEOUT 1000
CarElevatorInstruction::CarElevatorInstruction()
{
    m_result = 0;
}

void CarElevatorInstruction::setParameter(OrderStru o, int device_id)
{
    m_id = device_id;
    m_order = o;
    QVector<int> value;
    value.append(o.z);
    m_z = o.z;
    m_order.values= value;

}

void CarElevatorInstruction::runInstruction()
{

    //to check car status status 0--->1
//    if(Myconfig::GetInstance()->m_elevatorMap[m_id].status.isLock == false && Myconfig::GetInstance()->m_elevatorMap[m_id].status.isOnline == true)
//    {
        Myconfig::GetInstance()->m_elevatorMap[m_id].status.isLock = true;
        //emit order to interface
        TCommtransceivermanager::GetInstance()->SendcommandByExtern(m_order,m_id);
        m_result = 0;
        return ;
//    }
//    else
//        m_result = 99;
}

int CarElevatorInstruction::getResult(QString &exeMsg)
{

    if(m_result != 0)
    {
        exeMsg = " exec faild";
        Myconfig::GetInstance()->m_elevatorMap[m_id].status.isLock = true;
        return m_result;
    }
    struct timeval tpStart,tpEnd;
    float timeUse = 0;
    gettimeofday(&tpStart,NULL);
    while (timeUse < TIMEOUT)
    {
        if(isTerminate)
        {
            m_result = -99;
            break ;
        }
        if(Myconfig::GetInstance()->m_elevatorMap[m_id].status.curruntLayer == m_z)
        {
            m_result = 0;
            break;
        }

        gettimeofday(&tpEnd,NULL);
        timeUse = 1000 *(tpEnd.tv_sec - tpStart.tv_sec) + 0.001*(tpEnd.tv_usec - tpStart.tv_usec);
        if(timeUse >= TIMEOUT)
            break;
        QThread::msleep(5);
        QApplication::processEvents();
    }

    if(m_result == -99)
    {
        exeMsg = QString("%1  Terminate!").arg(m_order.type);
    }
    else if(m_result == 1)
    {
        exeMsg = " exec instruction Timeout!";
    }
    Myconfig::GetInstance()->m_elevatorMap[m_id].status.isLock = true;
    return m_result;
}

