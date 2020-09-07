#include "abstructinstruction.h"

AbstructInstruction::AbstructInstruction()
{

}

AbstructInstruction::~AbstructInstruction()
{

}

void AbstructInstruction::setParameter(OrderStru o, int device_id)
{
    Q_UNUSED(o)
    Q_UNUSED(device_id)
}
///
/// \brief AbstructInstruction::getResult
/// \return 0 success 1 fail
///
int AbstructInstruction::getResult(QString &exeMsg)
{
    exeMsg = "";
   return 0;
}

void AbstructInstruction::runInstruction()
{

}
