#include "c_systemlogmng.h"
#include <QDir>
#include <QSettings>
#include <QApplication>
#include <QDebug>

static C_SYSTEMLOGMNG *instance = nullptr;
C_SYSTEMLOGMNG *GetSystemLogObj()
{
    if(nullptr == instance)
    {
        instance = new C_SYSTEMLOGMNG();
    }
    return instance;
}

C_SYSTEMLOGMNG::C_SYSTEMLOGMNG()
{
    QDir _applicationDir(QCoreApplication::applicationDirPath());
    _applicationDir.cdUp();

    if (!_applicationDir.exists(_applicationDir.path() + "/log"))
    {
        _applicationDir.mkpath(_applicationDir.path() + "/log");
    }
    _applicationDir.cd("log");
    QString date = QDate::currentDate().toString("yyyy-MM-dd");
    QString fileNamelog;
    fileNamelog += date;

    fileNamelog += LOG_IDENTIFIER;
    QString _path = _applicationDir.path() + "/" + date;
    if (!_applicationDir.exists(_path))
    {
        _applicationDir.mkpath(_path);
    }
    _applicationDir.cd(date);

    m_index = 0;

    m_log.setFileName(_applicationDir.path() + "/" + fileNamelog);
    if(m_log.exists())
    {
        //m_log.remove();
    }

    if(m_log.open(QIODevice::ReadWrite | QIODevice::Text | QFile::Append))
    {
        m_stream.setDevice(&m_log);
        QString _logTitle = QString::fromLocal8Bit("<html>\n<head>\n<title>System Log</title>\n</head>\n<body>\n");
        m_stream << _logTitle;
    }
    else
    {
        QString _err = m_log.errorString();
    }
}

C_SYSTEMLOGMNG::~C_SYSTEMLOGMNG()
{
    endLog();
}

void C_SYSTEMLOGMNG::writeLog(QString logStr, int _flag)
{
    QString time = QTime::currentTime().toString("hh:mm:ss");
    m_mutex.lock();
    if (_flag == LOG_INFO)
    {
       m_stream << "<br><font size=\"3\" color=\"#459EF6\"family= \"微软雅黑\">" << "[" << m_index << "]" << "(" << time << ")" << logStr<< "</font>";
    }
    else  if (_flag == LOG_WARNING)
    {
       m_stream << "<br><font size=\"3\" color=\"#0000FF\"family= \"微软雅黑\">" << "[" << m_index << "]" << "(" << time << ")" << logStr<< "</font>";
    }
    else if (_flag == LOG_ERROR)
    {
       m_stream << "<br><font size=\"3\" color=\"#FF0000\"family= \"微软雅黑\">" << "[" << m_index << "]" << "(" << time << ")" << logStr<< "</font>";
    }
    m_stream.flush();
    m_log.flush();
    m_index += 1;
    m_mutex.unlock();
}

void C_SYSTEMLOGMNG::endLog()
{
    if (m_log.isOpen())
    {
        m_stream << "</body>";
        m_stream.flush();
        m_log.flush();
        m_log.close();
    }
}
