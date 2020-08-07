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
    QString m_car_ip;
    int m_count_text;
    void lock_layer(int layer,QString lock_car_ip);
    void lock_car(QString car_ip);
};

#endif // DISPATCHCENTER_H
