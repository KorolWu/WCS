#ifndef GETOUTTRAJECTORY_H
#define GETOUTTRAJECTORY_H

#include <QObject>
#include "datastructure.h"
#include "Myconfig.h"
#include "unchangevalue.h"
#include <math.h>
/**
 * @brief The GetOutTrajectory class
 * @date
 */
class GetOutTrajectory
{
public:
    GetOutTrajectory(KPosition task_p, int car_id, const TaskInfoStru &task);
    QQueue<OrderStru> getTrajectory();
private:

     void getTrajectory_out();
     void getTrajectory_out_v1();
     void inElevator();
     void outElevator();
     void pickUp();
     QQueue<OrderStru> m_taskQueue;
     KPosition m_carBeginPosition;
     KPosition m_task_p;
     int   m_id;
     TaskInfoStru m_task;
     bool isLeftPickup(QString &str);
     const double m_isYTrack = 1000;
     const double m_elevatorX = 1000;
     const double m_elevatorY = 2000;
     const double m_elevator_workBin_x = 2323;
     const double m_elevator_workBin_y = 32323;
};

#endif // GETOUTTRAJECTORY_H
