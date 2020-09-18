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
    //carinfo < 小车编号,car_info>
    QMap<int, CarInfoStru> m_CarMap;
    QMutex m_carMap_mutex;
    QMap<int, ElevatorInfoStru> m_elevatorMap;
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
    QString m_boxNum_in = "BOX0001";
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
    QMap<int, QQueue<TaskInfoStru>> m_appointMap;
    //硬件通讯配置的数据结构体,从数据库中读出来的数据内容
    HWComallconfigStru m_hwcommstru;
    //run mode =0 is autoMode
    int m_run_mode = 1;
    //流道的缓存位1-8，是否有料箱 有true  无false；
    QMap<int ,bool> m_cacheRunerMap;
    QMap<int ,ScanInfoStru> m_ScanMap;
    //red from db,about requery parameter<pleace(out,or in),parameter>
    QMap<QString ,HttpParameter> m_requestParameter;
    //用户权限的等级
    char m_curLoginlevel = 4;
    //
    int m_pixel = 4;

};
#endif
