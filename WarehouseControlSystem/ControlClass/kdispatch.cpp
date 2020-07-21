#include "kdispatch.h"

KDispatch::KDispatch(KPosition task_P, QString &ip, const TaskInfoStru task)
{
    qRegisterMetaType<OrderStru>("OrderStru");
    this->m_task_p = task_P;
    this->m_ip = ip;
    this->m_task = task;
    if(KDeviceSingleton::getInstance()->m_DeviceMap.contains(ip))
    {
        m_pCom = KDeviceSingleton::getInstance()->m_DeviceMap[ip];
        connect(this,&KDispatch::Ordered,m_pCom,&BaseDevice::handelOrder);
        RgvOrder *m_rgvOrder = new RgvOrder();
        m_pCom->m_pOrderStrategy = m_rgvOrder;
    }
    else
    {
        m_pCom = nullptr;
    }
    //test

}
//规划轨迹，生成子任务组，并将其保存在数据库里面
void KDispatch::getTrajectory()
{

    KPosition p2 = Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.carCurrentPosion;
    if(p2.y != m_task_p.y)//p2.z != m_task_p.z
    {
        OrderStru o;
        o.order = Order::X;
        o.value = p2.x - 0;
        m_taskQueue.enqueue(o);
        o.order = Order::ChangeWhell;
        m_taskQueue.enqueue(o);
        o.order = Order::Y;
        o.value = p2.y - m_task_p.y;
        m_taskQueue.enqueue(o);
        o.order = Order::ChangeWhell;
        m_taskQueue.enqueue(o);
        o.order = Order::X;
        o.value = m_task_p.x;
        m_taskQueue.enqueue(o);
        o.order = Order::Left;
        m_taskQueue.enqueue(o);
        o.order = Order::X;
        o.value = 0 - m_task_p.x;
        m_taskQueue.enqueue(o);
        o.order = Order::ChangeWhell;
        m_taskQueue.enqueue(o);
        // get elevator
        o.order = Order::Call;
        m_taskQueue.enqueue(o);
        //elevator near position y
        o.order = Order::Elevator_Near;
        m_taskQueue.enqueue(o);
    }
}

bool KDispatch::runSubTask()
{
    while(false == m_taskQueue.isEmpty())
    {
        OrderStru o = m_taskQueue.dequeue();
        struct timeval tpStart,tpEnd;
        float timeUse = 0;
        gettimeofday(&tpStart,NULL);
        while (true)
        {
            emit Ordered(o);
            qDebug()<<"emit order";
            if(m_inp == false)// 小车完成信号
            {   QEventLoop loop;
                QTimer::singleShot(1000,&loop,SLOT(quit()));
                loop.exec();
                break;
            }

            //time out return function,change car status Err isLocking
            gettimeofday(&tpEnd,NULL);
            timeUse = 1000 *(tpEnd.tv_sec - tpStart.tv_sec) + 0.001*(tpEnd.tv_usec - tpStart.tv_usec);
            if(timeUse >= TIMEOUT)
                break;
            QApplication::processEvents(QEventLoop::AllEvents,50);
        }
    }
    Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.isLocking = false;
    //delete crrunt task

    return false;
}

void KDispatch::run()
{
    getTrajectory();
    runSubTask();
    //保存当前任务完成的状态，完成 未完成，或者报警日志
     CRUDBaseOperation::getInstance()->removeCrruntTask(m_task);
}
