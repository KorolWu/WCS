#ifndef KDISPATCH_H
#define KDISPATCH_H

#include <QObject>
#include <QQueue>
#include <sys/time.h>
#include <QApplication>
#include <QThread>
#include "basedevice.h"
#include "selectcar.h"
#include "datastructure.h"
#include "KDeviceSingleton.h"
#include <QRunnable>
#include "UnitClass/c_systemlogmng.h"
#include "Myconfig.h"
#include "AbstractClass/rgvorder.h"
#include "MysqlDataBase/crudbaseoperation.h"
#include <QThread>
#include "WarehousingIn/getouttrajectory.h"
/**
 * @brief The KDispatch class
 * 扫描任务队列消费任务队列 拿到一个任务 并将其完成
 */
class KDispatch : public QObject,public QRunnable
{
    Q_OBJECT
public:
    KDispatch(KPosition task_P, QString &ip, const TaskInfoStru task );
    ~KDispatch();
private:
    TaskInfoStru m_task;
    KPosition m_task_p;
    const int TIMEOUT = 1000;
    QString  m_ip;
    bool saveSubTaskInfo();
    bool runSubTask();
    QString transformationOrder(int i);
    BaseDevice *m_pCom;
    QQueue<OrderStru> m_taskQueue;
    bool m_inp = false;
    // QRunnable interface
public:
    void run();
signals:
    void Ordered(OrderStru o);
};

#endif // KDISPATCH_H
