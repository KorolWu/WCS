#include "khttpserver.h"
QQueue<QString> KHttpServer::m_queue;
KHttpServer::KHttpServer()
{

}

void KHttpServer::run()
{
    JQHttpServer::TcpServerManage tcpServerManage( 2 ); // 设置最大处理线程数，默认2个

    tcpServerManage.setHttpAcceptedCallback( []( const QPointer< JQHttpServer::Session > &session )
    {
        session->replyText(QString("Whatever you ask, I'll only respond to sb"));
        QString requestBody = session->requestBody();
        m_queue.enqueue(requestBody);

    } );
    if (tcpServerManage.listen(QHostAddress::Any, 23412))
    {
        GetSystemLogObj()->writeLog("httpserver reboot successful",0);
    }
    else
        GetSystemLogObj()->writeLog("httpserver reboot fail",3);
    while(true == Myconfig::GetInstance()->m_flag)
    {
        if(!m_queue.isEmpty())
        {
            QString reply = m_queue.dequeue();
            emit replyReady(reply);
        }
        msleep(10);
    }
}
