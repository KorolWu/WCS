#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <QThread>
#include <QTimer>
#include <QEventLoop>
#include "Myconfig.h"
#include "MysqlDataBase/readtabledata.h"
#include "UnitClass/c_systemlogmng.h"

class LogManager : public QThread
{
    Q_OBJECT
public:
    explicit LogManager(QObject *parent = 0);

signals:

public slots:

    // QThread interface
protected:
    void run();
};

#endif // LOGMANAGER_H
