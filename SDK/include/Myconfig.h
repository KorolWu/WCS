#ifndef MYCONFIG_H
#define MYCONFIG_H
#include "datastructure.h"
#include <QMutex>
#include <QMutexLocker>
#include <QWaitCondition>
#include <QQueue>
#include <datastructure.h>

class Myconfig
{
private:
    Myconfig()
    {
        //m_layerIsLocked<<false<<false<<false<<false<<false<<false<<false<<false<<false;
    }
public:
    static Myconfig* GetInstance()
    {
        static Myconfig Instance;
        return &Instance;
    }
    void InsertLog(int level,QString from,QString info)
    {
        LogInfoStru l;
        l.level = level;
        l.from = from;
        l.info = info;
        m_logQue.append(l);
    }
public:
    //carinfo <car_ip,car_info>
    QMap<QString, CarInfoStru> m_CarMap;
    QMutex m_carMap_mutex;
    QMap<QString, ElevatorInfoStru> m_elevatorMap;
    //QMap<QString, BaseDevice *> m_carCommnicationMap;
    QMutex m_mutex;
    QMap<QString, StorePosInfoStru> m_storeinfoMap;
    QMutex m_rmutex;
    //taskNum,task
    QMap<QString, TaskInfoStru> m_taskMap;
    QMutex m_mutex_taskMap;
    //task queue
    QQueue<TaskInfoStru> m_taskQueue;
    QMutex m_task_mutex;
    //in_task map<box_num,task>
    QMap<QString,TaskInfoStru> m_in_taskMap;
    //用来记录最新的入库扫码信息
    QString m_boxNum_in;
    QMutex m_in_task_mutex;
    DataBaseInfoStru m_databaseInfo;
    bool m_flag = true;
    QQueue<LogInfoStru> m_logQue;
    //
    QMutex m_mutex_sqlwrite;

    //runer
    RunerStru m_runer;
    //判断当前层是否锁住
    QMap<int,LayerStru> m_layerStatusMap;
    //指定小车任务的集合
    QMap<QString, QQueue<TaskInfoStru>> m_appointMap;
    //硬件通讯配置的数据结构体,从数据库中读出来的数据内容
    HWComallconfigStru m_hwcommstru;
};
#endif
