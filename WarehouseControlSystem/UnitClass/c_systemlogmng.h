#ifndef SYSTEMLOGMNG
#define SYSTEMLOGMNG

#include <QFile>
#include <QMutex>
#include <QDateTime>
#include <QTextStream>
#include <QString>
#include <stdio.h>

#define LOG_IDENTIFIER "systemLog.html"     //日志保存名

#define LOG_INFO        0                //日志等级
#define LOG_WARNING     1
#define LOG_ERROR       2

class C_SYSTEMLOGMNG
{
public:
    C_SYSTEMLOGMNG();
    ~C_SYSTEMLOGMNG();
    void writeLog(QString logStr, int _flag = LOG_INFO);

private:
    void openNewLog();
    void endLog();

private:
    QFile m_log;
    QMutex m_mutex;
    QTextStream m_stream;
    int m_index;
};

extern C_SYSTEMLOGMNG *GetSystemLogObj();
#endif // SYSTEMLOGMNG
