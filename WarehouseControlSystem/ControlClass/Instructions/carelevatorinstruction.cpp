#include "carelevatorinstruction.h"
#define TIMEOUT 10000
CarElevatorInstruction::CarElevatorInstruction()
{
    m_result = 0;
}

void CarElevatorInstruction::setParameter(OrderStru o, int device_id)
{
    m_id = device_id;
    m_order = o;
}

void CarElevatorInstruction::runInstruction()
{
    struct timeval tpStart,tpEnd;
    float timeUse = 0;
    gettimeofday(&tpStart,NULL);
    while (timeUse < TIMEOUT)
    {
        if(isTerminate)
        {
            m_result = -99;
            return ;
        }
        //to check car status status 0--->1
        if(Myconfig::GetInstance()->m_elevatorMap[m_id].status.isLock == false)
        {
            Myconfig::GetInstance()->m_elevatorMap[m_id].status.isLock = true;
            //emit order to interface
            m_result = 0;
            return;
        }

        gettimeofday(&tpEnd,NULL);
        timeUse = 1000 *(tpEnd.tv_sec - tpStart.tv_sec) + 0.001*(tpEnd.tv_usec - tpStart.tv_usec);
        if(timeUse >= TIMEOUT)
            break;
        QThread::msleep(5);
        QApplication::processEvents();
    }
}

int CarElevatorInstruction::getResult(QString exeMsg)
{
    if(m_result == -99)
    {
        exeMsg = QString("%1  Terminate!").arg(m_order.type);
    }
    else if(m_result == 1)
    {
        exeMsg = " exec instruction Timeout!";
    }
    return m_result;
}

