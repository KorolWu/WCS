#ifndef RUNNERINSTRUCTION_H
#define RUNNERINSTRUCTION_H

#include <QObject>
#include "abstructinstruction.h"
#include "../externcommuincation/tcommtransceivermanager.h"
class RunnerInstruction : public AbstructInstruction
{
public:
    RunnerInstruction();

    // AbstructInstruction interface
public:
    void setParameter(OrderStru o, int device_id);
    int getResult(QString exeMsg);
    void runInstruction();
private:
    OrderStru m_order;
    int m_id;
    int m_result;
};

#endif // RUNNERINSTRUCTION_H
