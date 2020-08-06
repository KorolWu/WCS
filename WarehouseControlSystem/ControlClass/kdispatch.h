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
    void getTrajectory();
    void getTrajectory_out();
    void getTrajectory_in();
    bool saveSubTaskInfo();
    void inElevator();
    void outElevator();
    bool runSubTask();
    void pickUp();
    QString transformationOrder(int i);
    BaseDevice *m_pCom;
    QQueue<OrderStru> m_taskQueue;
    bool m_inp = false;
    const double m_isYTrack = 1000;
    const double m_elevatorX = 1000;
    const double m_elevatorY = 2000;
    KPosition p2;
    const double m_elevator_workBin_x = 2323;
    const double m_elevator_workBin_y = 32323;

    // QRunnable interface
public:
    void run();
signals:
    void Ordered(OrderStru o);
};

#endif // KDISPATCH_H
