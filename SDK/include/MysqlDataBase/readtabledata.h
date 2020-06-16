#ifndef READTABLEDATA_H
#define READTABLEDATA_H

#include "readtabledata_global.h"
#include "datastructure.h"
#include "Myconfig.h"
#include <MysqlDataBase/crudbaseoperation.h>
#include <QMutex>
#include <QMutexLocker>

class READTABLEDATASHARED_EXPORT ReadTableData
{

public:
    ReadTableData();
    void readt_device_info();
    void readt_elevator();
    void ReadStoreposinfoDataBase();
    bool WriteStoreposinfotoDataBase(QMap<QString,StorePosInfoStru> storeposInfoMap,QString &errorinfo);
    bool WriteLoginfo(int level,QString from,QString log_info);
private:
    QMutex m_mutex;

};

#endif // READTABLEDATA_H
