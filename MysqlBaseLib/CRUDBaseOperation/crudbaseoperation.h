#ifndef CRUDBASEOPERATION_H
#define CRUDBASEOPERATION_H

#include "crudbaseoperation_global.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlQuery>
class CRUDBASEOPERATIONSHARED_EXPORT CRUDBaseOperation
{

public:
    CRUDBaseOperation();
    bool openDB();
    void createTable(const QString &creatTableSql);
    QSqlQuery queryDb(const QString &querySql);
    bool queryUseStr(const QString &sqlStr);
    static CRUDBaseOperation* getInstance();
private:
    QSqlDatabase data_base;
    static CRUDBaseOperation* Instance;
};

#endif // CRUDBASEOPERATION_H
