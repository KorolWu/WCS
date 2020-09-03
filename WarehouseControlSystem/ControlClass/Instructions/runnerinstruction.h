#ifndef RUNNERINSTRUCTION_H
#define RUNNERINSTRUCTION_H

#include <QObject>
#include "abstructinstruction.h"

class RunnerInstruction : public AbstructInstruction
{
public:
    RunnerInstruction();

    // AbstructInstruction interface
public:
    void setParameter(OrderStru o, int device_id);
    int getResult(QString exeMsg);
    void runInstruction();
};

#endif // RUNNERINSTRUCTION_H
