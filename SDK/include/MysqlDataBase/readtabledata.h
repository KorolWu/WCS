#ifndef READTABLEDATA_H
#define READTABLEDATA_H

#include "readtabledata_global.h"
#include <datastructure.h>
#include <Myconfig.h>
#include <MysqlDataBase/crudbaseoperation.h>
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>
#include <QDateTime>


class READTABLEDATASHARED_EXPORT ReadTableData
{

public:
    ReadTableData();
    void readt_device_info();
    void readt_elevator();
    void readt_crrunt_task();
    void readt_runerInfo();
    void ReadStoreposinfoDataBase();
    bool WriteStoreposinfotoDataBase(QMap<QString,StorePosInfoStru> storeposInfoMap,QString &errorinfo);
    bool WriteLoginfo(int level,QString from,QString log_info);
    bool WriteUpdateInfoDataBase(QMap<QString,StorePosInfoStru> storeposInfoMap,QVector<QVariant> keyvalue,QString &errorinfo,bool updatestru=false);
    bool WriteAlarmInfo(ALARMINFOSTRU alarmstru ,QString &error);
    bool DelStoreposinfotoDataBaseByLayer(double z,QString &error);
    bool WriteInsertInfoDataBase(QMap<QString,StorePosInfoStru> storeposInfoMap,QString &errorinfo);
    void Readt_hwcomm_infotable();
private:
    QMutex m_mutex;

};

#endif // READTABLEDATA_H
