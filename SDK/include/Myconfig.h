#ifndef MYCONFIG_H
#define MYCONFIG_H
#include "datastructure.h"
#include <QMutex>
#include <QMutexLocker>
#include <QWaitCondition>
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
public:
    //carinfo <car_ip,car_info>
    QMap<QString,CarInfoStru> m_CarMap;
    QMap<QString,ElevatorInfoStru> m_elevatorMap;
    QMutex m_mutex;
};
#endif
