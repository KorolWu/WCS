#include "dispatchcenter.h"

DispatchCenter::DispatchCenter()
{
    m_pSelectCar = new SelectCar();
}

void DispatchCenter::dispatchTaskThread()
{
    while(true)
    {
        while(!Myconfig::GetInstance()->m_taskQueue.isEmpty())
        {
            if(m_pSelectCar->hasUseCar())
            {
                m_task =  Myconfig::GetInstance()->m_taskQueue.dequeue();
                KPosition task_p;//根据料箱号返回料箱所在坐标
                QString result = StoreInfo::BaseDataInfoOperate::GetWarehouselocationInfoForOut(m_task.boxNum,task_p);
                if(result != "")
                {
                    //根据坐标返回分配小车的坐标 会有个无车可用的情况
                    m_car_ip = m_pSelectCar->getCarIp_out(task_p);
                    // carP   boxP   elevatorP  in or out?
                    KDispatch *k = new KDispatch(task_p,m_car_ip,m_task);//完成的状态，完成的结果，写入数据库的时间??
                    m_writeData.WriteLoginfo(0,"Dispatch Info","将任务 "+m_task.taskNum +" 分配给"+m_car_ip);
                    QThreadPool::globalInstance()->start(k);

                }
                else
                {
                    //任务执行失败，没有找到目标库位
                    m_task.status = "执行失败";\
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
                    CRUDBaseOperation::getInstance()->saveCompletedTask(m_task);

                }
            }
            else
            {
                QThread::msleep(10);
            }

            QEventLoop loop;
            QTimer::singleShot(100,&loop,SLOT(quit()));
            loop.exec();
        }
        QThread::msleep(40);
    }
}
