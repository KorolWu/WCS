#include "runnerinstruction.h"

RunnerInstruction::RunnerInstruction()
{
    m_result = 0;
}

void RunnerInstruction::setParameter(OrderStru o, int device_id)
{
    m_id = device_id;
    m_order = o;
    QVector<int> value;
    value.append(o.value);
    m_order.values= value;
}

int RunnerInstruction::getResult(QString exeMsg)
{
    if(m_result != 0)
    {
        exeMsg = "流道掉线执行失败";
    }
    return m_result;
}

void RunnerInstruction::runInstruction()
{

    if(Myconfig::GetInstance()->m_runer.isOnline)
    {
        int start_address = 0;
        if(m_order.order == 5)
        {
            start_address = 50;
        }
        else if(m_order.order == 21)
        {
            start_address = 52;
        }
        TCommtransceivermanager::GetInstance()->SendcommandByExtern(m_order,m_id);
    }
    else
        m_result = -99;
}
