#include "logmanager.h"

LogManager::LogManager(QObject *parent)
{
    Q_UNUSED(parent);
}

void LogManager::run()
{
    ReadTableData r;
    while (true == Myconfig::GetInstance()->m_flag) {
        while (!Myconfig::GetInstance()->m_logQue.isEmpty()) {
            LogInfoStru l = Myconfig::GetInstance()->m_logQue.dequeue();
            if(!r.WriteLoginfo(l.level,l.from,l.info))
            {
                GetSystemLogObj()->writeLog("database log write fail!",3);
                return;
            }
        }
        QEventLoop loop;
        QTimer::singleShot(3000,&loop,SLOT(quit()));
        loop.exec();
    }
}
