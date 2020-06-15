#ifndef MYINICONFIG_H
#define MYINICONFIG_H
#include <QSettings>
#include <QStandardPaths>
#include <QDebug>
#include <QApplication>
class MyIniConfig
{
private:
    QString m_qstrFileName;
    QSettings *m_psetting;
public:
    MyIniConfig()
    {

    }
    ~MyIniConfig()
    {
        delete m_psetting;
        m_psetting = 0;
    }
    void Config(QString qstrfilename = "")
    {
        if (qstrfilename.isEmpty())
           {
               m_qstrFileName = QCoreApplication::applicationDirPath() + "/Config.ini";
           }
           else
           {
               m_qstrFileName = qstrfilename;
           }

           m_psetting = new QSettings(m_qstrFileName, QSettings::IniFormat);
           m_psetting->setIniCodec("UTF-8");
           qDebug() << m_qstrFileName;
    }
    void Set(QString nodename, QString strkeyname, QVariant qvarvalue)
    {
        m_psetting->setValue(QString("/%1/%2").arg(nodename).arg(strkeyname),qvarvalue);
    }

    QVariant Get(QString qstrnodename, QString qstrkeyname)
    {
        QVariant qvar = m_psetting->value(QString("/%1/%2").arg(qstrnodename).arg(qstrkeyname));
        return qvar;
    }

};

#endif // MYCONFIG_H
