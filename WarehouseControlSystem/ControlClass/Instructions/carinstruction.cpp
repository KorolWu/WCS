#include "carinstruction.h"
#define TIMEOUT 10000
CarInstruction::CarInstruction()
{  
    m_result = 0;
}

void CarInstruction::setParameter(OrderStru o, int device_id)
{
    m_id = device_id;
    m_order = o;
}
void CarInstruction::runInstruction()
{
    Car_status s = Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus;
    //小车可以接受指令(无故障，就绪，可以接受指令)
    if(s.isOnline && s.statusinfodstru.berror != 1 && s.statusinfodstru.bunready != 1 && s.statusinfodstru.bready == 1)
    {
        // get box on elevator,moust be wait elevator ready
        if(m_order.order == 9 || m_order.order == 10)
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
                //判断电梯是否到位
                if(Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.status == 1)
                {
                    //发送指令
                    TCommtransceivermanager::GetInstance()->SendcommandByExtern(m_order,000000);
                    break;
                }

                gettimeofday(&tpEnd,NULL);
                timeUse = 1000 *(tpEnd.tv_sec - tpStart.tv_sec) + 0.001*(tpEnd.tv_usec - tpStart.tv_usec);
                if(timeUse >= TIMEOUT)
                    break;
                QThread::msleep(5);
                QApplication::processEvents();
            }
        }
        else   //normal move or get box on store
        {

        }
    }
    else
        m_result = 1;
}

int CarInstruction::getResult(QString exeMsg)
{
    if(m_result != 0)
    {
        exeMsg = QString("%1  Terminate!").arg(m_order.type);
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
            exeMsg = QString("%1  Terminate!").arg(m_order.type);
            return m_result;
        }
        //to check car status status 0--->1
        if(Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.statusinfodstru.berror != 1 && Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.statusinfodstru.bunready != 1 && Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.statusinfodstru.bready == 1)
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
    return m_result;

}

