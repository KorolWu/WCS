#include "crudbaseoperation.h"

CRUDBaseOperation *CRUDBaseOperation::Instance = new CRUDBaseOperation();
CRUDBaseOperation::CRUDBaseOperation()
{
}

bool CRUDBaseOperation::openDB()
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

void CRUDBaseOperation::createTable(const QString &creatTableSql)
{
    QSqlQuery query(data_base);
    query.exec(creatTableSql);
}

QSqlQuery CRUDBaseOperation::queryDb(const QString &querySql)
{
    QSqlQuery query(data_base);
    query.exec(querySql);
    return query;
}

bool CRUDBaseOperation::queryUseStr(const QString &sqlStr)
{
    QSqlQuery query(data_base);
    return query.exec(sqlStr);
}

CRUDBaseOperation *CRUDBaseOperation::getInstance()
{
    if (Instance != nullptr)
        return Instance;
}
