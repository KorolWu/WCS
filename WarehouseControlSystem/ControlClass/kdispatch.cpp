#include "kdispatch.h"

KDispatch::KDispatch(KPosition task_P, QString &ip, const TaskInfoStru task)
{
    qRegisterMetaType<OrderStru>("OrderStru");
    this->m_task_p = task_P;
    this->m_ip = ip;
    this->m_task = task;
    //这里还有通讯和流道
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

KDispatch::~KDispatch()
{
    m_pCom = nullptr;
    delete m_pCom;
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

void KDispatch::getTrajectory_out()
{
    OrderStru o;
    KPosition p2 = Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.carCurrentPosion;
    // same layer
    if(p2.z == m_task_p.z)
    {
        if(p2.x == m_isYTrack)// same y track  判断是否在Y巷道上，如果不在移动到料箱相同的Y
        {
             o.order = Order::Y;
             o.value = m_task_p.y - p2.y;
             m_taskQueue.enqueue(o);
        }
        else
        {
            o.order = Order::X;
            o.value = m_isYTrack - p2.x;
            m_taskQueue.enqueue(o);
            o.order = Order::Y;
            o.value = m_task_p.y - p2.y;
            m_taskQueue.enqueue(o);
        }
    }
    else
    {
        if(p2.x == m_isYTrack) // car at y track 判断是否在Y巷道上，如果不在移动到料箱相同的Y 然后进电梯 出电梯
        {
            if(p2.y == m_elevatorY)
            {
                inElevator();
            }
            else
            {
                o.order = Order::Y;
                o.value = m_elevatorY - p2.y;
                m_taskQueue.enqueue(o);
                inElevator();
            }
        }
        else
        {
            o.order = Order::X;
            o.value = m_isYTrack - p2.x;
            m_taskQueue.enqueue(o);

            o.order = Order::Y;
            o.value = m_elevatorY - p2.y;
            m_taskQueue.enqueue(o);
            inElevator();
        }
        o.order = Order::Call;
        o.value = m_task_p.z;
        m_taskQueue.enqueue(o);
        outElevator();
        o.order = Order::Y;
        o.value = m_task_p.y - m_elevatorY;
        m_taskQueue.enqueue(o);
    }
    pickUp();
}

void KDispatch::getTrajectory_in()
{

}
///
/// \brief KDispatch::saveSubTaskInfo
/// \return
/// 将轨迹产生的子任务保存到数据库里面
bool KDispatch::saveSubTaskInfo()
{
     QQueue<OrderStru> sub_task;
     sub_task = m_taskQueue;
     QStringList field;

     field<<"taskNum"<<"taskType"<<"subTaskNum"<<"sequence" << "state"<<"storeNum"<<"deviceIp"<<"commandData";
     QString taskType = "";
     int sequence = 1;
     if(m_task.taskNum.contains("L"))
        taskType = "出库";
     else
         taskType = "入库";
     QList<QVariantList> values;
     while(sub_task.isEmpty() == false)
     {
         OrderStru o = sub_task.dequeue();
         QVariantList value;
         value<<m_task.taskNum<<taskType<<transformationOrder(o.order)<<QString::number(sequence, 10)<<"Created"<<m_task.boxNum<<m_ip<<"commandDate";
         values.append(value);
         sequence ++;
     }
     QString errorInfo;
     if(CRUDBaseOperation::getInstance()->ExcBatchReplaceDB("t_sub_taskInfo",field,values,errorInfo))
     {
         return true;
     }
     else{
         qDebug()<<"errorinfo:"<<errorInfo<<endl;
         return false;
     }
     return true;

}

void KDispatch::inElevator()
{

}

void KDispatch::outElevator()
{

}

bool KDispatch::runSubTask()
{
    qDebug()<<QThread::currentThreadId();
    int sequnce = 1;
    while(false == m_taskQueue.isEmpty())
    {
        OrderStru o = m_taskQueue.dequeue();
        struct timeval tpStart,tpEnd;
        float timeUse = 0;
        gettimeofday(&tpStart,NULL);
        while (true)
        {
            emit Ordered(o);
            if(m_inp == false)// 小车完成信号
            {   QEventLoop loop;
                QTimer::singleShot(1000,&loop,SLOT(quit()));
                loop.exec();
                QString sqlErr = "";
                CRUDBaseOperation::getInstance()->changeSubtaskStatus(m_task.taskNum,"--",sequnce,sqlErr);
                break;
            }
            //test if sub task over
            //time out return function,change car status Err isLocking
            gettimeofday(&tpEnd,NULL);
            timeUse = 1000 *(tpEnd.tv_sec - tpStart.tv_sec) + 0.001*(tpEnd.tv_usec - tpStart.tv_usec);
            if(timeUse >= TIMEOUT)
                break;
            QApplication::processEvents(QEventLoop::AllEvents,50);
        }
    }
    QMutexLocker locker(&Myconfig::GetInstance()->m_carMap_mutex);
    Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.isLocking = false;
    Myconfig::GetInstance()->m_CarMap[m_ip].deveceStatus.status = 1;
    //delete crrunt task

    return false;
}
///
/// \brief KDispatch::pickUp
///小车从料箱所在的巷道，移动去取货
///
void KDispatch::pickUp()
{
    OrderStru o;
    o.order = Order::X;
    o.value = m_task_p.x - m_isYTrack ;
    m_taskQueue.enqueue(o);
    if(m_task.taskNum == "L")
    {
         o.order = Order::Left;
    }
    else
    {
        o.order = Order::Right;
    }
     m_taskQueue.enqueue(o);
     o.order = Order::X;
     o.value = m_isYTrack - m_task_p.x ;
     m_taskQueue.enqueue(o);

     //qudianti
     o.order = Order::Y;
     o.value = m_elevatorY - m_task_p.y;
     m_taskQueue.enqueue(o);
     o.order = Order::Call;
     o.value = m_task_p.z;
     //?
     inElevator();
     //发送缓存去库位号给流道
     //function

}

QString KDispatch::transformationOrder(int i)
{
    if(i == 0)
     return "横移车辆";
    else if(i == 1)
        return "竖移车辆";
    else if(i == 3)
       return "左取货";
    else if(i == 4)
        return " 右取货";
    else if(i == 5)
        return "呼叫电梯";
    else if(i == 6)
        return "进电梯";
     else if(i == 7)
       return "出电梯";
    return "unknow Order";
}

void KDispatch::run()
{
    getTrajectory();
    saveSubTaskInfo();
    runSubTask();
    //保存当前任务完成的状态，完成 未完成，或者报警日志
    m_task.status = "已完成";
    QString err = "";
    if(!CRUDBaseOperation::getInstance()->saveCompletedTask(m_task,err))
        GetSystemLogObj()->writeLog("完成任务保存失败!-->"+err,2);
    err = "";
    if(!CRUDBaseOperation::getInstance()->removeCrruntTask(m_task,err))
       GetSystemLogObj()->writeLog("移除执行完成任务失败!-->"+err,3);
}
