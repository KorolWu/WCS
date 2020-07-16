#include "kdispatch.h"

KDispatch::KDispatch(TaskInfoStru task, QString &ip)
{
    this->m_task = task;
    this->m_ip = ip;
    if(KDeviceSingleton::getInstance()->m_DeviceMap.contains(ip))
    {
        m_pCom = KDeviceSingleton::getInstance()->m_DeviceMap[ip];
        m_pDevice = new AbstructDevice(m_pCom);
    }
    else
    {
        m_pCom = nullptr;
        m_pDevice = nullptr;
    }

}
//规划轨迹，生成子任务组，并将其保存在数据库里面
void KDispatch::getTrajectory()
{
    //料箱坐标
    KPosition p1 = getPosition();
    //    SelectCar select_car;
    //    QString car_ip = select_car.getCarIp_out(p1);
    //car ip
    KPosition p2;
    if(p2.y != p1.y)//p2.z != p1.z
    {
        OrderStru o;
        o.order = Order::X;
        o.value = p2.x - 0;
        m_taskQueue.enqueue(o);
        o.order = Order::ChangeWhell;
        m_taskQueue.enqueue(o);
        o.order = Order::Y;
        o.value = p2.y - p1.y;
        m_taskQueue.enqueue(o);
        o.order = Order::ChangeWhell;
        m_taskQueue.enqueue(o);
        o.order = Order::X;
        o.value = p1.x;
        m_taskQueue.enqueue(o);
        o.order = Order::Left;
        m_taskQueue.enqueue(o);
        o.order = Order::X;
        o.value = 0 - p1.x;
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
    if(m_pDevice == nullptr)
        return false;
    while(m_taskQueue.isEmpty())
    {
        OrderStru o = m_taskQueue.dequeue();
        struct timeval tpStart,tpEnd;
        float timeUse = 0;
        gettimeofday(&tpStart,NULL);
        while (timeUse < TIMEOUT)
        {
            //在预计时间类完成Order
            if(o.order == Order::X)
                m_pDevice->move_x(o.value);
            gettimeofday(&tpEnd,NULL);
            timeUse = 1000 *(tpEnd.tv_sec - tpStart.tv_sec) + 0.001*(tpEnd.tv_usec - tpStart.tv_usec);
            if(timeUse >= TIMEOUT)
                break;
            QThread::msleep(5);
            QApplication::processEvents(QEventLoop::AllEvents,50);
        }
    }
}

KPosition KDispatch::getPosition()
{
    KPosition p;
    return p;
}
