#ifndef SCANCODEINSTRUCTION_H
#define SCANCODEINSTRUCTION_H
#include "abstructinstruction.h"
#include "../externcommuincation/tcommtransceivermanager.h"
/**
 * @brief The ScanCodeInstruction class
 *   only scan the code
 */
class ScanCodeInstruction : public AbstructInstruction
{
public:
    ScanCodeInstruction();

    // AbstructInstruction interface
public:
    void setParameter(OrderStru o, int device_id);
    int getResult(QString &exeMsg);
    void runInstruction();
private:
    OrderStru m_order;
    int m_deviceId;
    int m_result;
};

#endif // SCANCODEINSTRUCTION_H
