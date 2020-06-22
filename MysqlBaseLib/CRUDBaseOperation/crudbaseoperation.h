#ifndef CRUDBASEOPERATION_H
#define CRUDBASEOPERATION_H

#include "crudbaseoperation_global.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "Myconfig.h"
class CRUDBASEOPERATIONSHARED_EXPORT CRUDBaseOperation
{

public:
    CRUDBaseOperation();
    bool openDB();
    void closeDB();
    void createTable(const QString &creatTableSql);
    QSqlQuery queryDb(const QString &querySql);
    bool queryUseStr(const QString &sqlStr);  
    bool saveCrruntTask(TaskInfoStru taskStru);
   public:
  /*******批量操作数据库************************************2020-06-12*/
  bool ExcBatchDeleteDB(const QString &table,QString keyname, QList<QVariant> keys,QString &error);
  bool ExcBatchUpdateDB(const QString &table, QStringList &names, QVector<QVariantList> &valuesvec, \
                        QString keyname,QVector<QVariant> keyvalue,QString &sqlerror);
  QSqlQuery ExcBatchSelectDB(const QString table);
  bool ExcBatchReplaceDB(const QString &table, QStringList &names, QList<QVariantList> &values,QString &sqlerror);
private:
     QString GetKeyType(QString tablename,QString name);
     void  GettablesFromDb(QStringList &tablelist);
public:
    static CRUDBaseOperation* getInstance(); 
private:
    QSqlDatabase data_base;
    static CRUDBaseOperation* Instance;
};

#endif // CRUDBASEOPERATION_H
