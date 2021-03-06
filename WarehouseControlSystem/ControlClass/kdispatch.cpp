#include "kdispatch.h"

KDispatch::KDispatch(KPosition task_P, QString &ip, int carId, const TaskInfoStru task)
{
    qRegisterMetaType<OrderStru>("OrderStru");
    this->m_task_p = task_P;
    this->m_ip = ip;
    this->m_task = task;
    this->m_carId = carId;
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
    m_pAbstructInstruction = nullptr;
}

KDispatch::~KDispatch()
{
    m_pCom = nullptr;
    delete m_pCom;
}
    
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
    if(CRUDBaseOperation::getInstance()->ExcBatchInsertDb("t_sub_taskInfo",field,values,errorInfo))
    {
        return true;
    }
    else{
        qDebug()<<"errorinfo:"<<errorInfo<<endl;
        return false;
    }
    return true;

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
                CRUDBaseOperation::getInstance()->changeSubtaskStatus(m_task.taskNum,"--","commamd",sequnce,sqlErr);
                //qDebug()<<"subtask"<<sqlErr;
                if(sqlErr != "")
                    GetSystemLogObj()->writeLog("change substatus to dbbase failed! ->"+sqlErr,2);
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
        sequnce++;
    }
    QMutexLocker locker(&Myconfig::GetInstance()->m_carMap_mutex);
    Myconfig::GetInstance()->m_CarMap[m_carId].deveceStatus.isLocking = false;
    Myconfig::GetInstance()->m_CarMap[m_carId].deveceStatus.status = 1;
    //delete crrunt task

    return false;
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

bool KDispatch::runInstrucation(OrderStru o, int &id)//id can`t write here
{
    o.box_num = m_task.boxNum;
    o.shelves = m_task.shelves;
    o.z = m_task_p.z;
    if(o.order == 0||o.order == 1||o.order == 3 ||o.order == 4 ||o.order == 9 ||o.order == 10)
    {
        m_pAbstructInstruction = new CarInstruction();
    }
    else if(o.order == 5)
    {
        m_pAbstructInstruction = new CarElevatorInstruction();
    }
    if(m_pAbstructInstruction != nullptr)
    {
        m_pAbstructInstruction->setParameter(o,id);
        m_pAbstructInstruction->runInstruction();
        QString exeResult = "";
        if(m_pAbstructInstruction->getResult(exeResult) != 0)
        {
            saveErrMassage(exeResult);
            return false;
        }
    }
    return true;
}

void KDispatch::saveErrMassage(const QString &message )
{
    ALARMINFOSTRU arm;
    arm.alarminfo = message;
    arm.alarmlevel = 4;
    arm.boxnumber = m_task.boxNum;
    arm.carcoordx = Myconfig::GetInstance()->m_CarMap[m_carId].deveceStatus.carCurrentPosion.x;
    arm.carcoordy = Myconfig::GetInstance()->m_CarMap[m_carId].deveceStatus.carCurrentPosion.y;
    arm.carcoordz = Myconfig::GetInstance()->m_CarMap[m_carId].deveceStatus.carCurrentPosion.z;
    arm.deviceid = m_ip;
    arm.errorcode = 006;
    arm.errortype = 1;
    arm.Operatestate = 1;
    arm.wmsTaskid = m_task.taskNum;
    QString sql_err;
    if(false == m_writeData.WriteAlarmInfo(arm,sql_err))
        GetSystemLogObj()->writeLog("在执行子任务时保存报错信息失败！message->"+message,2);
}

void KDispatch::run()
{
    if(m_task.taskNum.contains("O"))// 入库
    {
        GetOutTrajectory *t = new GetOutTrajectory(m_task_p,m_carId,m_task);
        m_taskQueue = t->getTrajectory();
        qDebug()<<"正在执行出库任务";
    }
    else
    {
        GenerateInputWarehousingOrders *t = new GenerateInputWarehousingOrders();
        t->SetPathParam(m_task_p,Myconfig::GetInstance()->m_CarMap[m_carId].deveceStatus.carCurrentPosion);
        m_taskQueue = t->GetInputWarehousingOrders();
        qDebug()<<"正在执行入库任务";
    }
//    getTrajectory_out();
    saveSubTaskInfo();
    runSubTask();
    //保存当前任务完成的状态，完成 未完成，或者报警日志
    m_task.status = "已完成";
    QString err = "";
    if(!CRUDBaseOperation::getInstance()->saveCompletedTask(m_task,err))
        GetSystemLogObj()->writeLog("完成任务保存失败!-->"+err,2);
    err = "";
    if(!CRUDBaseOperation::getInstance()->removeCrruntTask(m_task,err))
        GetSystemLogObj()->writeLog("移除执行完成任务失败!-->"+err,2);
}
