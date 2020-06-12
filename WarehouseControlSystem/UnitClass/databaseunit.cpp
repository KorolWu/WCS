#include "databaseunit.h"
DataBaseUnit * DataBaseUnit::Instance = new DataBaseUnit();
DataBaseUnit::DataBaseUnit()
{

}

bool DataBaseUnit::openDB()
{
    data_base = QSqlDatabase::addDatabase("QMYSQL");
    data_base.setHostName("192.168.188.103");
    data_base.setPort(3306);
    data_base.setDatabaseName("test_dev");
    data_base.setUserName("root");
    data_base.setPassword("orange");
    if(data_base.isOpen())
        return true;
    if(!data_base.open())
    {
        qDebug()<<"open database fail";
        return true;
    }
    return false;
}

void DataBaseUnit::CreateTable(const QString &creatTableSql)
{
    QSqlQuery query(data_base);
    query.exec(creatTableSql);
}

QSqlQuery DataBaseUnit::queryDb(const QString &querySql)
{
    QSqlQuery query(data_base);
    query.exec(querySql);
    return query;
}

bool DataBaseUnit::queryUseStr(const QString &sqlStr)
{
    QSqlQuery query(data_base);
    return query.exec(sqlStr);
}

bool DataBaseUnit::insertDb(const QString &table, QStringList &names, QStringList &values)
{
    if(names.size() != values.size())
    {
        return false;
    }
    QSqlQuery query(data_base);
    QString sql = QString("insert into %1 (").arg(table);
    int i;
    for (i=0; i < names.size(); i++)
    {
        sql = sql + names.value(i);
        if(i != names.size() -1)
            sql += QString(",");
    }
    sql +=  QString(") values (");
    for (i = 0; i < values.size(); i++)
    {
        sql +=  QString("'%1'").arg(values.value(i));
        if(i != values.size() -1)
            sql += QString(",");
    }
    sql += QString(")");
    qDebug()<<"sql:"<<sql;
    if(!query.exec(sql))
    {
        return false;
    }
    return true;
}

bool DataBaseUnit::updataDb(const QString &table, QStringList &names, QStringList &values, QString &condition)
{
    if (names.size() != values.size())
    {
        return false;
    }
    QSqlQuery query(data_base);
    QString sql = QString("update ")+ table + QString(" set ");
    for (int i = 0; i < names.size(); i++)
    {
        sql +=  names.value(i);
        sql +=  QString(" = '");
        sql +=  values.value(i);
        sql +=  QString("'");
        if (i != names.size()-1)
        {
            sql += QString(" ,");
        }
    }
    sql +=  QString(" where %1").arg(condition);
    if (!query.exec(sql))
    {
        return false;
    }
    return true;
}

DataBaseUnit *DataBaseUnit::GetInstance()
{
    return Instance;
}

void DataBaseUnit::closeDb()
{
    if(data_base.isOpen())
    {
        data_base.close();
    }
   // QSqlDatabase::removeDatabase(data_base.connectionName());
}
