#include "httpclien_k.h"

HttpClien_k::HttpClien_k()
{
    m_result = -1;
}

void HttpClien_k::setParameter(OrderStru o, int device_id)
{
    this->m_devicdId = device_id;
    this->m_orderStru = o;
}

void HttpClien_k::runInstruction()
{
    m_repalyPair = JQNet::HTTP::post(m_orderStru.http.url,m_orderStru.http.body);
}

int HttpClien_k::getResult(QString &exeMsg)
{
    if(m_repalyPair.first == false)
    {
        m_result = -99;
        exeMsg = "request was aborted!";
    }
    else
    {
        exeMsg = m_repalyPair.second;
        m_result = 1;
    }
    return m_result;
}
