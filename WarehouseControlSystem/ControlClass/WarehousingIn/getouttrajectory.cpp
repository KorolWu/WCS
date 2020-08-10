#include "getouttrajectory.h"

GetOutTrajectory::GetOutTrajectory(KPosition task_p, QString car_ip, const TaskInfoStru task)
{
    this->m_task_p = task_p;
    this->m_ip = car_ip;
    this->m_task = task;
}

QQueue<OrderStru> GetOutTrajectory::getTrajectory()
{
    getTrajectory_out();
    return m_taskQueue;
}

void GetOutTrajectory::getTrajectory_out()
{
    OrderStru o;
    m_carBeginPosition = Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.carCurrentPosion;
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

//这里是一个流程，从电梯口相等的y到电梯口,到进电梯；
void GetOutTrajectory::inElevator()
{
    //先呼叫电梯，然后行走，到电梯口等待电梯到位 然后进电梯
    OrderStru o;
    o.order = Order::X;
    o.value =m_elevatorX - m_carBeginPosition.x;
    m_taskQueue.enqueue(o);
    o.order = Elevator_In;
    m_taskQueue.enqueue(o);
    //x_move in elevator
}

//出电梯，1电梯到位 2，走到换向道上
void GetOutTrajectory::outElevator()
{
    OrderStru o;
    o.order = Order::Elevator_Out;
    m_taskQueue.enqueue(o);
    o.order = Order::X;
    o.value =m_elevatorX - m_carBeginPosition.x;
    m_taskQueue.enqueue(o);
}
///
/// \brief KDispatch::pickUp
///小车从料箱所在的巷道，移动去取货
///
void GetOutTrajectory::pickUp()
{
    OrderStru o;
    o.order = Order::X;
    o.value = m_task_p.x - m_isYTrack ;
    m_taskQueue.enqueue(o);
    if(m_task.taskNum == "L")
    {
        o.order = Order::Left_Pickup;
    }
    else
    {
        o.order = Order::Right_Pickup;
    }
    m_taskQueue.enqueue(o);
    o.order = Order::X;
    o.value = m_isYTrack - m_task_p.x ;
    m_taskQueue.enqueue(o);

    //qudianti
    o.order = Order::Y;
    o.value = m_elevator_workBin_y - m_task_p.y;
    if(o.value != 0)
        m_taskQueue.enqueue(o);
    o.order = Order::X;
    o.value = m_elevator_workBin_x - m_isYTrack;
    m_taskQueue.enqueue(o);

    o.order = Order::Call_WorkBin_Out;
    o.value = m_task_p.z;
    m_taskQueue.enqueue(o);
    //chu huo so fangzai zuobian
    o.order = Order::Left_WorkBin;
    m_taskQueue.enqueue(o);
    o.order = Order::Call_WorkBin_Out;
    o.value = 1;
    m_taskQueue.enqueue(o);
    //发送缓存去库位号给流道
    //function
}
