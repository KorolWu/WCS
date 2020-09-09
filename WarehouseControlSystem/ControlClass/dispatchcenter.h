#ifndef DISPATCHCENTER_H
#define DISPATCHCENTER_H

#include <QObject>
#include <QThread>
#include <QThreadPool>
#include "Myconfig.h"
#include "kdispatch.h"
#include "selectcar.h"
#include "basedatainfooperate.h"
#include "MysqlDataBase/crudbaseoperation.h"
#include "MysqlDataBase/readtabledata.h"
#include "../ControlClass/Instructions/abstructinstruction.h"
#include "../ControlClass/Instructions/runnerinstruction.h"
#include "../ControlClass/Instructions/scancodeinstruction.h"
/**
 * @brief The DispatchCenter class
 * @date 2020/07/17
 * @title 扫描任务队列，根据小车的状态（是否有空闲的小车）创建任务线程 --- move mainthread?
 *
 */
class DispatchCenter : public QObject
{
    Q_OBJECT
public:
    DispatchCenter();
    void dispatchTaskThread();
private:
    SelectCar *m_pSelectCar;
    TaskInfoStru m_task;
    ReadTableData m_writeData;
    int m_car_ip;
    int     m_car_id;
    int m_count_text;
    int m_in_cache_max;
    int m_out_cahce_max;
    void lock_layer(int layer, int lock_car_id);
    void set_car_task_position(const KPosition &p, const int &carId);
    void lock_car(int carId);
    void Task_execution_failed(const TaskInfoStru &t);
    void remove_task_from(QString task_num);
    void handle_out_task(TaskInfoStru &t);
    void handle_in_task(TaskInfoStru &t, QString frist_in_boxNum);
    void remove_out_task();
    void remove_in_task(const QString &frist_in_boxNum);
    void box_getCache();
    int getfreeCache();
    void scanCode();
};

#endif // DISPATCHCENTER_H
