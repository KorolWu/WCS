#ifndef MYCONFIG_H
#define MYCONFIG_H
#include "datastructure.h"
#include <QMutex>
#include <QMutexLocker>
#include <QWaitCondition>
#include <QQueue>
class Myconfig
{
private:
    Myconfig()
    {

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
    QMap<QString,CarInfoStru> m_CarMap;
    QMap<QString,ElevatorInfoStru> m_elevatorMap;
    QMutex m_mutex;
    QMap<QString,StorePosInfoStru>m_storeinfoMap;
    DataBaseInfoStru m_databaseInfo;
    bool m_flag = true;
    QQueue<LogInfoStru> m_logQue;
};
#endif
