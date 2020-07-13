#ifndef KDISPATCH_H
#define KDISPATCH_H

#include <QObject>
#include "basedevice.h"
#include "selectcar.h"
#include "datastructure.h"
/**
 * @brief The KDispatch class
 * 扫描任务队列消费任务队列 拿到一个任务 并将其完成
 */
class KDispatch
{
public:
    KDispatch(TaskInfoStru task, BaseDevice *device);
private:
    TaskInfoStru m_task;
    BaseDevice *m_pBase;
    void testfunction();

};

#endif // KDISPATCH_H
