#include "getouttrajectory.h"

GetOutTrajectory::GetOutTrajectory(KPosition task_p, int car_id, const TaskInfoStru &task)
{
    this->m_task_p = task_p;
    this->m_id = car_id;
    this->m_task = task;
}

QQueue<OrderStru> GetOutTrajectory::getTrajectory()
{
    getTrajectory_out_v1();
    return m_taskQueue;
}

void GetOutTrajectory::getTrajectory_out()
{
    OrderStru o;
    m_carBeginPosition = Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.carCurrentPosion;
    // same layer
    if(m_carBeginPosition.z == m_task_p.z)
    {
        if(m_carBeginPosition.x == m_isYTrack)// same y track  判断是否在Y巷道上，如果不在移动到料箱相同的Y
        {
            o.order = Order::Y;
            o.value = m_task_p.y - m_carBeginPosition.y;
            if(o.value != 0)
                m_taskQueue.enqueue(o);
        }
        else
        {
            if(m_carBeginPosition.y != m_task_p.y)
            {
                o.order = Order::X;
                o.value = m_isYTrack - m_carBeginPosition.x;
                m_taskQueue.enqueue(o);
                o.order = Order::Y;
                o.value = m_task_p.y - m_carBeginPosition.y;
                m_taskQueue.enqueue(o);
            }
        }
    }
    else
    {
        if(m_carBeginPosition.x == m_isYTrack) // car at y track 判断是否在Y巷道上，如果不在移动到料箱相同的Y 然后进电梯 出电梯
        {
            if(m_carBeginPosition.y == m_elevatorY)
            {
                inElevator();
            }
            else
            {
                o.order = Order::Y;
                o.value = m_elevatorY - m_carBeginPosition.y;
                m_taskQueue.enqueue(o);
                inElevator();
            }
        }
        else
        {
            if(m_carBeginPosition.y != m_elevatorY)
            {
                o.order = Order::X;
                o.value = m_isYTrack - m_carBeginPosition.x;
                m_taskQueue.enqueue(o);

                o.order = Order::Y;
                o.value = m_elevatorY - m_carBeginPosition.y;
                m_taskQueue.enqueue(o);
            }
            inElevator();
        }
        o.order = Order::Call;
        o.value = m_task_p.z;
        m_taskQueue.enqueue(o);
        outElevator();
        o.order = Order::Y;
        o.value = m_task_p.y - m_elevatorY;
        if(o.value != 0)
            m_taskQueue.enqueue(o);
    }
    pickUp();
}

void GetOutTrajectory::getTrajectory_out_v1()
{
    OrderStru o;
    m_carBeginPosition = Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.carCurrentPosion;
    // same layer
    if(m_carBeginPosition.z == m_task_p.z)
    {
        if(m_carBeginPosition.y == 0)// same x track  判断是否在Y巷道上，如果不在移动到料箱相同的Y
        {
            o.order = Order::X;
            o.value = m_task_p.x - m_carBeginPosition.x;
            if(o.value != 0)
                m_taskQueue.enqueue(o);
        }
        else
        {
            if(m_carBeginPosition.x != m_task_p.x)
            {
                o.order = Order::Y;
                o.value = 0 - m_carBeginPosition.y;
                m_taskQueue.enqueue(o);
                o.order = Order::X;
                o.value = m_task_p.x - m_carBeginPosition.x;
                m_taskQueue.enqueue(o);
            }
        }
    }
    else
    {
        if(m_carBeginPosition.y == 0) // car at y track 判断是否在Y巷道上,然后进电梯 出电梯
        {
            if(m_carBeginPosition.x == 0)
            {
                inElevator();
            }
            else
            {
                o.order = Order::X;
                o.value = 0 - m_carBeginPosition.x;
                m_taskQueue.enqueue(o);
                inElevator();
            }
        }
        else
        {
            if(m_carBeginPosition.x != 0)
            {
                o.order = Order::Y;
                o.value = 0 - m_carBeginPosition.y;
                m_taskQueue.enqueue(o);

                o.order = Order::X;
                o.value = 0 - m_carBeginPosition.x;
                m_taskQueue.enqueue(o);
            }
            inElevator();
        }
        o.order = Order::Call;
        o.value = m_task_p.z;
        m_taskQueue.enqueue(o);
        outElevator();
        o.order = Order::X;
        o.value = m_task_p.x - 0;
        if(o.value != 0)
            m_taskQueue.enqueue(o);
    }
    pickUp();
}

//这里是一个流程，从电梯口相等的y到电梯口,到进电梯；
void GetOutTrajectory::inElevator()
{
    //先呼叫电梯，然后行走，到电梯口等待电梯到位 然后进电梯
    OrderStru o;
    o.order = Order::Y;
    o.value =  903 + 520;
    m_taskQueue.enqueue(o);

    o.order = Elevator_In;
    o.z = m_task_p.z;
    o.value =  1258;
    m_taskQueue.enqueue(o);

    //将本层解锁
    o.order = Unlock_layer;
    o.value = Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.carCurrentPosion.z;
    Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.carCurrentPosion.z = m_task_p.z;
    m_taskQueue.enqueue(o);
    //x_move in elevator
}

//出电梯，1电梯到位 2，走到换向道上
void GetOutTrajectory::outElevator()
{
    OrderStru o;
    o.order = Order::Elevator_Out;
    o.z = m_task_p.z;
//    m_taskQueue.enqueue(o);
//    o.order = Order::X;
    o.value = 1258+520+903;
    m_taskQueue.enqueue(o);
}
///
/// \brief KDispatch::pickUp
///小车从料箱所在的巷道，移动去取货
///
void GetOutTrajectory::pickUp()
{
    OrderStru o;
    o.order = Order::Y;
    o.value = m_task_p.y - 0 ;
    m_taskQueue.enqueue(o);
    if(isLeftPickup(o.shelves))
    {
        o.order = Order::Left_Pickup;
    }
    else
    {
        o.order = Order::Right_Pickup;
    }
    m_taskQueue.enqueue(o);
    o.order = Order::Y;
    o.value = 0 - m_task_p.y ;
    m_taskQueue.enqueue(o);

    //qudianti
    o.order = Order::X;
    o.value = 0 - m_task_p.x;
    if(o.value != 0)
        m_taskQueue.enqueue(o);
    o.order = Order::Y;
    o.value = 520+903;
    m_taskQueue.enqueue(o);

    o.order = Order::Elevator_In;
    o.value = 1258;
    m_taskQueue.enqueue(o);

    o.order = Order::Call;
    o.value = 1;
    m_taskQueue.enqueue(o);
    //chu huo so fangzai zuobian
    o.order = Order::Left_WorkBin;
    m_taskQueue.enqueue(o);
    //发送缓存去库位号给流道
    //function
}

bool GetOutTrajectory::isLeftPickup(QString &str)
{
    QStringList list = str.split("-");
    if(list.size() == 5)
    {
        int i = QString (list[2]).mid(1).toInt();
        if(fmod(i,2) == 0)
        {
            return true;
        }
    }
  return false;
}
