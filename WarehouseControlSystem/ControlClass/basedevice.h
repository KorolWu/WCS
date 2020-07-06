#ifndef BASEDEVICE_H
#define BASEDEVICE_H

#include <QObject>
#include "UnitClass/KCommunication.h"
#include <QTimer>
#include "datastructure.h"
#include "Myconfig.h"
#include "observerbase.h"
#include <QVector>

/**
 * @brief The BaseDevice class
 * @date  2020/7/1
 * @author korol
 * @todo carbaseClass
 */

class BaseDevice :public QObject
{
    Q_OBJECT
public:
    BaseDevice(QString ip, qint16 port, QObject *parent = 0);
    bool init();
    void registObserver(ObserverBase *o);
    QTimer *m_pTimer;
    virtual void onResived(QByteArray array);
    virtual void onDisconnected();
    virtual void clearAlarm(QByteArray data);
    int write(QByteArray data);
private:
    QString m_ip;
    qint16 m_port;
    KCommunication::KTcpClient *m_pClient;
    QVector< ObserverBase *> m_ObserverVec;
    void reConnected();
    void noticeObserver();
};

#endif // BASEDEVICE_H
