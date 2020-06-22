#ifndef KHTTPSERVER_H
#define KHTTPSERVER_H
#include <QThread>
#include <QObject>
#include <QDebug>
#include <QQueue>
#include "JQHttpServer.h"
#include "UnitClass/c_systemlogmng.h"
#include "Myconfig.h"
/**
 *
 * @author korol
 * @email wuwenpeng@cowain.com.cn
 * @date 2020-06-08 16:02:59
 * use Httpserver线程
 */
class KHttpServer : public QThread
{
    Q_OBJECT
public:
    KHttpServer();
    static QQueue<QString> m_queue;
    // QThread interface
protected:
    void run();
signals:
    void replyReady(QString str);
};

#endif // KHTTPSERVER_H
