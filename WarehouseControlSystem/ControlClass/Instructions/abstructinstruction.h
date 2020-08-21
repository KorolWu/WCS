#ifndef ABSTRUCTINSTRUCTION_H
#define ABSTRUCTINSTRUCTION_H

#include <QObject>
#include "datastructure.h"
#include "Myconfig.h"

class AbstructInstruction
{
public:
    AbstructInstruction();
    virtual ~AbstructInstruction();
    virtual void setParameter(OrderStru o, QString device_id);
    virtual int getResult(QString exeMsg);
    virtual void runInstruction();

public:
    bool isTerminate;

};

#endif // ABSTRUCTINSTRUCTION_H
