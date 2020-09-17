#ifndef HTTPCLIEN_K_H
#define HTTPCLIEN_K_H

#include <QObject>
#include "JQNet.h"
#include "Myconfig.h"
#include "abstructinstruction.h"
#include <QPair>
class HttpClien_k : public AbstructInstruction
{
public:
    HttpClien_k();

    // AbstructInstruction interface
public:
    void setParameter(OrderStru o, int device_id);
    int getResult(QString &exeMsg);
    void runInstruction();
private:
    int m_devicdId;
    int m_result;
    OrderStru m_orderStru;
    QPair<bool ,QByteArray> m_repalyPair;
};

#endif // HTTPCLIEN_K_H
