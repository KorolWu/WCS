#include "scancodeinstruction.h"

ScanCodeInstruction::ScanCodeInstruction()
{

}

void ScanCodeInstruction::setParameter(OrderStru o, int device_id)
{
    this->m_order = o;
    this->m_deviceId = device_id;
}

void ScanCodeInstruction::runInstruction()
{

}

int ScanCodeInstruction::getResult(QString &exeMsg)
{
    if(Myconfig::GetInstance()->m_ScanMap[m_deviceId].isOnline)
    {
         TCommtransceivermanager::GetInstance()->SendcommandByExtern(m_order,m_deviceId);
         exeMsg = "Successful execution";
         m_result = 1;
    }
    else
    {
        exeMsg = "Execution failed,Code scanning gun dropped!";
        m_result = -1;
    }
    return m_result;
}

