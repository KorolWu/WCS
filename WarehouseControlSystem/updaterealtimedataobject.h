#ifndef UPDATEREALTIMEDATAOBJECT_H
#define UPDATEREALTIMEDATAOBJECT_H

#include <QObject>
#include <Myconfig.h>
#include <datastructure.h>
#include <MysqlDataBase/readtabledata.h>
#include "ControlClass/externcommuincation/tcommtransceivermanager.h"

class UpdateRealtimeDataObject: public QObject
{
    Q_OBJECT
public:
    explicit UpdateRealtimeDataObject();
    ~UpdateRealtimeDataObject();
    //保存数据库
    void SaveStoreinfotoDatabase();
    //定时更新数据任务
    void RequestTimingupdateHWinfo();
private:
    ReadTableData m_databaseopob;
    void UpdateCarDataRequest();
    void UpdateRunnerDataRequest();
};

#endif // UPDATEREALTIMEDATAOBJECT_H
