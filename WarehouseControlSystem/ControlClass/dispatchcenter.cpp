#include "dispatchcenter.h"

DispatchCenter::DispatchCenter()
{
    m_pSelectCar = new SelectCar();
    m_count_text = 1;
    m_in_cache_max = Myconfig::GetInstance()->m_runer.cache_in_max;
    m_out_cahce_max = Myconfig::GetInstance()->m_runer.cache_out_max;
    qDebug()<<"max"<<m_in_cache_max<<"out"<<m_out_cahce_max;
}

void DispatchCenter::dispatchTaskThread()
{
    while(Myconfig::GetInstance()->m_flag == true)
    {
        //扫描预定队列，如果里面有小车空闲，则安排她完成接下来的任务
        for(auto it = Myconfig::GetInstance()->m_appointMap.begin();it != Myconfig::GetInstance()->m_appointMap.end();it++)
        {
            if(it.value().isEmpty() == true)
            {
                Myconfig::GetInstance()->m_CarMap[it.key()].isLockByTask = false;
                continue;
            }
            QString ip = it.key();
            if(Myconfig::GetInstance()->m_CarMap[it.key()].deveceStatus.isLocking == false)
            {
                TaskInfoStru t = it.value().dequeue();
                KPosition task_p;//根据料箱号返回料箱所在坐标
                QString result = StoreInfo::BaseDataInfoOperate::GetWarehouselocationInfoForOut(t.boxNum,task_p);
                if(result != "")
                {
                    lock_car(ip);
                    KDispatch *k = new KDispatch(task_p,ip,t);//完成的状态，完成的结果，写入数据库的时间??
                    m_writeData.WriteLoginfo(0,"Dispatch Info","将任务 "+t.taskNum +" 分配给"+ip);
                    QThreadPool::globalInstance()->start(k);
                    qDebug()<<"正在执行预约任务";
                }
            }
        }
        m_car_ip = "";
        //qDebug()<<Myconfig::GetInstance()->m_runer.cache_in_current<<"-"<<Myconfig::GetInstance()->m_runer.cache_out_current;
        if(Myconfig::GetInstance()->m_runer.cache_in_current < m_in_cache_max*0.75 && Myconfig::GetInstance()->m_runer.cache_out_current < m_out_cahce_max)
        {
            qDebug()<<"out";
            if(!Myconfig::GetInstance()->m_taskQueue.isEmpty())
            {
                if(m_pSelectCar->hasUseCar())
                {
                    QMutexLocker locker(&Myconfig::GetInstance()->m_task_mutex);
                    m_task =  Myconfig::GetInstance()->m_taskQueue.dequeue();
                    remove_task_from(m_task.taskNum);
                    KPosition task_p;//根据料箱号返回料箱所在坐标
                    QString result = StoreInfo::BaseDataInfoOperate::GetWarehouselocationInfoForOut(m_task.boxNum,task_p);
                    if(result != "")
                    {
                        QString ip = Myconfig::GetInstance()->m_layerStatusMap[task_p.z].CarIP;
                        //先判断目标层是否有车
                        if(true == Myconfig::GetInstance()->m_layerStatusMap[task_p.z].isLocked )//&& Myconfig::GetInstance()->m_CarMap[ip].deveceStatus.isLocking
                        {
                            //将此任务分配给这个小车
                            //将这个车辆锁住（任务锁，意味着这辆车不可以被调到其他层）
                            //然后将这个任务放在一个集合里面，然后在大循环里面扫描这个集合，分配任务 Map<ip,queue<task>>
                            Myconfig::GetInstance()->m_appointMap[ip].enqueue(m_task);
                            Myconfig::GetInstance()->m_CarMap[ip].isLockByTask = true;
                            qDebug()<<"正在执行出库任务,当前层有车，且忙碌，将此任务提前分配给此小车";
                            continue;
                        }
                        //根据坐标返回分配小车的坐标
                        m_car_ip = m_pSelectCar->getCarIp_out(task_p);
                        //锁定小车即将到达的层
                        lock_layer(task_p.z,m_car_ip);
                        // carP   boxP   elevatorP  in or out?
                        KDispatch *k = new KDispatch(task_p,m_car_ip,m_task);//完成的状态，完成的结果，写入数据库的时间??
                        m_writeData.WriteLoginfo(0,"Dispatch Info","将任务 "+m_task.taskNum +" 分配给"+m_car_ip);
                        QThreadPool::globalInstance()->start(k);
                        qDebug()<<m_car_ip<<" Task Number: "+QString::number(m_count_text);
                        m_count_text++;

                    }
                    else
                    {
                        //任务执行失败，没有找到目标库位
                        Task_execution_failed(m_task);
                    }
                }
                else // no car use
                {
                    QThread::msleep(10);
                }

                QEventLoop loop;
                QTimer::singleShot(100,&loop,SLOT(quit()));
                loop.exec();
            }
        }
        else // 分配入库
        {qDebug()<<"in";
            if(false == Myconfig::GetInstance()->m_in_taskMap.isEmpty())
            {
                if(m_pSelectCar->hasUseCar())
                {
                    QString frist_in_boxNum = Myconfig::GetInstance()->m_boxNum_in;
                    qDebug()<<"box_num"<<frist_in_boxNum;
                    if(Myconfig::GetInstance()->m_in_taskMap.contains(frist_in_boxNum))
                    {
                        TaskInfoStru t = Myconfig::GetInstance()->m_in_taskMap[frist_in_boxNum];
                        KPosition task_p;//根据料箱号返回料箱所在坐标
                        QString result = StoreInfo::BaseDataInfoOperate::GetWarehouselocationInfoForOut(t.boxNum,task_p);
                        if(result != "")
                        {
                            remove_task_from(t.taskNum);
                            QString ip = Myconfig::GetInstance()->m_layerStatusMap[task_p.z].CarIP;
                            //先判断目标层是否有车
                            if(true == Myconfig::GetInstance()->m_layerStatusMap[task_p.z].isLocked )//&& Myconfig::GetInstance()->m_CarMap[ip].deveceStatus.isLocking
                            {
                                Myconfig::GetInstance()->m_appointMap[ip].enqueue(t);
                                Myconfig::GetInstance()->m_CarMap[ip].isLockByTask = true;
                                qDebug()<<"正在执行入库任务,当前层有车，且忙碌，将入库任务提前分配给此小车";
                                QMutexLocker locker(&Myconfig::GetInstance()->m_in_task_mutex);
                                Myconfig::GetInstance()->m_in_taskMap.remove(frist_in_boxNum);
                                continue;
                            }
                            //根据坐标返回分配小车的坐标
                            m_car_ip = m_pSelectCar->getCarIp_out(task_p);
                            //锁定小车即将到达的层
                            lock_layer(task_p.z,m_car_ip);
                            // carP   boxP   elevatorP  in or out?
                            KDispatch *k = new KDispatch(task_p,m_car_ip,t);//完成的状态，完成的结果，写入数据库的时间??
                            m_writeData.WriteLoginfo(0,"Dispatch Info","将任务 "+t.taskNum +" 分配给"+m_car_ip);
                            QThreadPool::globalInstance()->start(k);
                            qDebug()<<m_car_ip<<" runing in Task Number: "+QString::number(m_count_text);
                            QMutexLocker locker(&Myconfig::GetInstance()->m_in_task_mutex);
                            Myconfig::GetInstance()->m_in_taskMap.remove(frist_in_boxNum);
                            qDebug()<<"in size "<<Myconfig::GetInstance()->m_in_taskMap.size();
                        }
                        else
                        {
                            Task_execution_failed(t);
                        }
                    }
                    else
                        continue;
                }
            }
        }
        QThread::msleep(40);
    }
}

void DispatchCenter::lock_layer(int layer, QString lock_car_ip)
{
    if(Myconfig::GetInstance()->m_layerStatusMap.contains(layer))
    {
        Myconfig::GetInstance()->m_layerStatusMap[layer].isLocked = true;
        Myconfig::GetInstance()->m_layerStatusMap[layer].CarIP = lock_car_ip;
    }
    else
    {
        LayerStru v;
        v.CarIP = lock_car_ip;
        v.isLocked = true;
        Myconfig::GetInstance()->m_layerStatusMap.insert(layer,v);
    }
}

void DispatchCenter::lock_car(QString car_ip)
{
    Myconfig::GetInstance()->m_CarMap[car_ip].deveceStatus.isLocking = true;
}

void DispatchCenter::Task_execution_failed(TaskInfoStru &t)
{
    //任务执行失败，没有找到目标库位
    t.status = "执行失败";\
    qDebug()<<"执行失败";
    ALARMINFOSTRU arm;
    arm.alarminfo = "没有查到料箱对应的库位";
    arm.alarmlevel = 4;
    arm.boxnumber = m_task.boxNum;
    arm.carcoordx = Myconfig::GetInstance()->m_CarMap[m_car_ip].deveceStatus.carCurrentPosion.x;
    arm.carcoordy = Myconfig::GetInstance()->m_CarMap[m_car_ip].deveceStatus.carCurrentPosion.y;
    arm.carcoordz = Myconfig::GetInstance()->m_CarMap[m_car_ip].deveceStatus.carCurrentPosion.z;
    arm.deviceid = m_car_ip;
    arm.errorcode = 006;
    arm.errortype = 1;
    arm.Operatestate = 1;
    arm.wmsTaskid = m_task.taskNum;
    QString sql_err;
    if(false == m_writeData.WriteAlarmInfo(arm,sql_err))
        qDebug()<<"alarm insert failed!";
    //CRUDBaseOperation::getInstance()->saveCompletedTask(m_task);

}

void DispatchCenter::remove_task_from(QString task_num)
{
    if(Myconfig::GetInstance()->m_taskMap.contains(task_num))
    {
       QMutexLocker locker(&Myconfig::GetInstance()->m_mutex_taskMap);
        Myconfig::GetInstance()->m_taskMap.remove(task_num);
    }

}
