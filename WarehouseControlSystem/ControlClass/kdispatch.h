#ifndef KDISPATCH_H
#define KDISPATCH_H

#include <QObject>
#include <QQueue>
#include <sys/time.h>
#include <QApplication>
#include <QThread>
#include "AbstractClass/abstructdevice.h"
#include "basedevice.h"
#include "selectcar.h"
#include "datastructure.h"
#include "KDeviceSingleton.h"
/**
 * @brief The KDispatch class
 * 扫描任务队列消费任务队列 拿到一个任务 并将其完成
 */
class KDispatch
{
public:
    KDispatch(TaskInfoStru task, QString &ip);
private:
    TaskInfoStru m_task;
    const int TIMEOUT = 30000;
    QString  m_ip;
    void getTrajectory();
    bool runSubTask();
    KPosition getPosition();
    BaseDevice *m_pCom;
    AbstructDevice *m_pDevice;
    QQueue<OrderStru> m_taskQueue;

};

#endif // KDISPATCH_H
