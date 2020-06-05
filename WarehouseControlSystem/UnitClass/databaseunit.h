#ifndef DATABASEUNIT_H
#define DATABASEUNIT_H
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QVariant>
#include <QDebug>

class DataBaseUnit
{
public:
    DataBaseUnit();
    bool openDB();
    void CreateTable(const QString &creatTableSql);
    QSqlQuery queryDb(const QString &querySql);
    bool queryUseStr(const QString &sqlStr);
    bool insertDb(const QString &table,QStringList &names,QStringList &values);
    bool updataDb(const QString &table,QStringList &names,QStringList &values,QString &condition);
    static DataBaseUnit * GetInstance();
    void closeDb();
private:
    QSqlDatabase data_base;
    static DataBaseUnit *Instance;

};

#endif // DATABASEUNIT_H
