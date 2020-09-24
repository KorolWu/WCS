#include "carinstruction.h"
#define TIMEOUT 1000
CarInstruction::CarInstruction()
{  
    m_result = -4;
}

void CarInstruction::setParameter(OrderStru o, int device_id)
{
    m_id = device_id;
    m_order = o;
}
void CarInstruction::runInstruction()
{
    //小车可以接受指令(无故障，就绪，可以接受指令)
    //if((Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.isOnline) && (Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.statusinfodstru.berror == false) && (s.statusinfodstru.bunready == true) && (Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.statusinfodstru.bready == false))
    if(Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.isOnline)// && Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.statusinfodstru.carstatusinfo == 4)
    {
        // get box on elevator,moust be wait elevator ready
        if(m_order.order == 122227)//----------m_order.order == 7 || m_order.order == 8 || m_order.order == 9 || m_order.order == 10)
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
                if(m_order.order == 7 || m_order.order == 8)
                {
                    if(Myconfig::GetInstance()->m_elevatorMap[888888].status.curruntLayer == m_order.z)
                    {
                        //发送指令
                        TCommtransceivermanager::GetInstance()->SendcommandByExtern(m_order,m_id);
                        break;
                    }
                }
                else
                {
                    int layer = 31;
                    if(m_order.order == 9)
                    {
                        layer = 1;
                    }
                    else
                        layer = 2;
                    if(Myconfig::GetInstance()->m_elevatorMap[888888].status.curachelayer == layer)//and signal about runner can get box signal
                    {
                        //发送指令
                        TCommtransceivermanager::GetInstance()->SendcommandByExtern(m_order,m_id);
                        break;
                    }

                }

                gettimeofday(&tpEnd,NULL);
                timeUse = 1000 *(tpEnd.tv_sec - tpStart.tv_sec) + 0.001*(tpEnd.tv_usec - tpStart.tv_usec);
                if(timeUse >= TIMEOUT)
                    return ;
                QThread::msleep(5);
                QApplication::processEvents();
            }
        }
        else if(m_order.order == 0)
        {
            m_tempValue = Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.carCurrentPosion.x;
            m_tempValue += m_order.value;
            if(false == CRUDBaseOperation::getInstance()->updateCarPosition(m_id,"x",m_tempValue,m_instructMsg))
                m_result = 2;
        }
        else if(m_order.order == 1 || m_order.order == 7 ||m_order.order == 8)//7 8 is test
        {
            m_tempValue = Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.carCurrentPosion.y;
            m_tempValue += m_order.value;
            if(false == CRUDBaseOperation::getInstance()->updateCarPosition(m_id,"y",m_tempValue,m_instructMsg))
                m_result = 3;
        }
//        else if(m_order.order == 8) //car out of elevator y change z change too
//        {
//            m_tempValue = m_order.z;
//            if(false == CRUDBaseOperation::getInstance()->updateCarPosition(m_id,"z",m_tempValue,m_instructMsg))
//                m_result = 3;
//        }
        //normal move or get box on store
       TCommtransceivermanager::GetInstance()->SendcommandByExtern(m_order,m_id);
    }
    else
        m_result = -1;
}

int CarInstruction::getResult(QString &exeMsg)
{
    if(m_result == -4)
    {
        exeMsg = QString("%1  Terminate!").arg(m_order.type);
        return m_result;
    }
    else if(m_result == -1)
    {
        exeMsg = QString("%1  小车没有满足运动状态!").arg(m_order.type);
        return m_result;
    }
//    struct timeval tpStart,tpEnd;
//    float timeUse = 0;
//    gettimeofday(&tpStart,NULL);
//    while (timeUse > TIMEOUT)
//    {
//        if(isTerminate)
//        {
//            m_result = -99;
//            exeMsg = QString("%1  Terminate!").arg(m_order.type);
//            return m_result;
//        }
//        //to check car status status 0--->1
//       if(Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.statusinfodstru.berror == false && Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.statusinfodstru.bunready == false && Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.statusinfodstru.bready == false)
//        {
//            if(m_order.order == 0)
//            {
//                Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.carCurrentPosion.x = m_tempValue;
//            }
//            else if(m_order.order == 1)
//            {
//                 Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.carCurrentPosion.y = m_tempValue;
//            }
//            else if(m_order.order == 8)
//            {
//                 Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.carCurrentPosion.z = m_tempValue;
//            }
//            else if(m_order.order == 4 ||  m_order.order == 3) //pick up (shelves,box_num)
//            {
//                QByteArray buff("");
//                memcpy(Myconfig::GetInstance()->m_storeinfoMap[m_order.shelves].boxnbr,buff,sizeof(buff));
//                Myconfig::GetInstance()->m_storeinfoMap[m_order.shelves].update = true;
//            }
//            else if(m_order.order == 14 || m_order.order == 15) //putinto
//            {
//                memcpy(Myconfig::GetInstance()->m_storeinfoMap[m_order.shelves].boxnbr,m_order.box_num.toLocal8Bit(),sizeof(m_order.box_num));
//                Myconfig::GetInstance()->m_storeinfoMap[m_order.shelves].update = true;
//            }
//            m_result = 0;
//            exeMsg = QString("%1  Exec successful!").arg(m_order.type);
//            break;
//        }

//        gettimeofday(&tpEnd,NULL);
//        timeUse = 1000 *(tpEnd.tv_sec - tpStart.tv_sec) + 0.001*(tpEnd.tv_usec - tpStart.tv_usec);
//        if(timeUse >= TIMEOUT)
//            break;
//        QThread::msleep(5);
//        QApplication::processEvents();
//    }
    if(m_order.order == 0)
    {
        Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.carCurrentPosion.x = m_tempValue;
    }
    else if(m_order.order == 1 ||m_order.order == 7 || m_order.order == 8)//7 8 is test
    {
         Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.carCurrentPosion.y = m_tempValue;
    }
    qDebug()<<"Current position:"<<Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.carCurrentPosion.x <<" ,"<<Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.carCurrentPosion.y;
    return m_result;

}

