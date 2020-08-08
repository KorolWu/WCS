#include "generateinputwarehousingorders.h"

GenerateInputWarehousingOrders::GenerateInputWarehousingOrders()
{
    m_taskQueue.clear();
}

GenerateInputWarehousingOrders::~GenerateInputWarehousingOrders()
{

}
///
/// \brief GenerateInputWarehousingOrders::SetPathParam
/// \param task_P
/// 设置需要把对应的料箱子放到指定的仓位
void GenerateInputWarehousingOrders::SetPathParam(KPosition task_P/*, KPosition carPosion*/,QString carid)
{
    m_trapos = task_P;
    m_carPos = Myconfig::GetInstance()->m_CarMap[carid].deveceStatus.carCurrentPosion;
    m_carid = carid;
}
///
/// \brief GenerateInputWarehousingOrders::Generationinstruction
/// 生成有指令功能函数部分
void GenerateInputWarehousingOrders::Generationinstruction()
{

    //货物电梯 和 流道部分的指令内容，等待小车进行取货的流程部分
    GetBoxelevatorOrders();
    //小车到达指定等待电梯位置点
    GetCartowaitElevatorPos();
    //呼叫小车电梯到达指定层数
    GetCarElevatorToCarlayOrders();
    //小车执行进电梯,从等待点到达进电梯
    GetCartoCarElevatoroeders();
    //呼叫电梯到达仓位所在楼层
    GetCarElevatorToBoxlayOrders();
    //小车执行出电梯到达取货电梯点并取货
    GetCarfromCarElevatortopickupBoxElevatorders();
    //小车到达目标仓位并放货动作
    GetfrompickupBoxElevatortoTraposorders();

}
///
/// \brief GenerateInputWarehousingOrders::GetBoxelevatorOrders
///呼叫货物电梯进行搬运货物，并送到对应的仓位层数
void GenerateInputWarehousingOrders::GetBoxelevatorOrders()
{
    //1.首先呼叫电梯到货物所在流道位置
    //1.1先判断流道位置与所在电梯为同一个位置，直接进入下一个流程，否则 呼叫电梯到该层数
    OrderStru orderstru;
    if(RUNNERLAY != m_InPutBoxElevatorstru.z)
    {

        orderstru.order = Elevator_In;
        orderstru.value = RUNNERLAY;
        m_taskQueue.append(orderstru);
        m_InPutBoxElevatorstru.z = RUNNERLAY;
    }
    //1.2 通知流道把货放入电梯
    orderstru.order = call_Runner_Putbox;
    m_taskQueue.append(orderstru);
    //1.3通知电梯把货物放到指定目标仓位层数
    if(m_trapos.z != m_InPutBoxElevatorstru.z)
    {
        orderstru.order = Elevator_In;
        orderstru.value = m_trapos.z;
        m_taskQueue.append(orderstru);
        m_InPutBoxElevatorstru.z = m_trapos.z;
    }
}
///
/// \brief GenerateInputWarehousingOrders::GetTraLayOrders
///小车到达指定等待电梯位置点的
void GenerateInputWarehousingOrders::GetCartowaitElevatorPos()
{
    OrderStru orderstru;
    if(m_carPos.z != m_trapos.z)
    {
        //到达换向的巷道位置
        double xpos = m_changeoverRoadstru.x - m_carPos.x;
        if(xpos != 0)
        {
            orderstru.order = X;
            orderstru.value = xpos;
            m_taskQueue.append(orderstru);
            m_carPos.z = m_trapos.z;

        }
        //到达对应小车电梯的y坐标的位置
        double ypos =  m_carwaitElevatorstru.y - m_carPos.y;
        if(ypos != 0)
        {
            orderstru.order = Y;
            orderstru.value = ypos;
            m_taskQueue.append(orderstru);
            m_carPos.y = m_carwaitElevatorstru.y;
        }
        //到达对应小车等待电梯的x坐标的位置
        double xelevator = m_carwaitElevatorstru.x - m_changeoverRoadstru.x ;
        if(xelevator != 0)
        {
            orderstru.order = X;
            orderstru.value = xelevator;
            m_taskQueue.append(orderstru);
            m_carPos.x = m_carwaitElevatorstru.x;
        }
    }

}
///
/// \brief GenerateInputWarehousingOrders::GetCarElevatorToCarlayOrders
///呼叫小车电梯到达小车所在的楼层

void GenerateInputWarehousingOrders::GetCarElevatorToCarlayOrders()
{
    OrderStru orderstru;
    if(m_carPos.z != m_carElevatorstru.z) //当前小车所在电梯的层数
    {
        orderstru.order = Call;
        orderstru.value = m_carPos.z;
        m_taskQueue.append(orderstru);
        m_carElevatorstru.z = m_carPos.z;
    }
}
///
/// \brief GenerateInputWarehousingOrders::GetCartoCarElevatoroeders
///呼叫小车从小车等待电梯点 到达 小车电梯内的指令
void GenerateInputWarehousingOrders::GetCartoCarElevatoroeders()
{
    OrderStru orderstru;
    if(m_carPos.x != m_carElevatorstru.x) //当前小车所在电梯的层数
    {
        orderstru.order = X;
        orderstru.value = m_carElevatorstru.x-m_carPos.x;
        m_taskQueue.append(orderstru);
        m_carPos.x = m_carElevatorstru.x;
    }
}
///
/// \brief GenerateInputWarehousingOrders::GetCarElevatorToBoxlayOrders
///呼叫小车电梯到达仓位所在的楼层
void GenerateInputWarehousingOrders::GetCarElevatorToBoxlayOrders()
{
    OrderStru orderstru;
    if(m_trapos.z != m_carElevatorstru.z) //当前小车所在电梯的层数
    {
        orderstru.order = Call;
        orderstru.value = m_trapos.z;
        m_taskQueue.append(orderstru);
        m_carElevatorstru.z = m_trapos.z;
        m_carPos.z = m_trapos.z;
    }
}
///
/// \brief GenerateInputWarehousingOrders::GetCarfromCarElevatortopickupBoxElevatorders
///小车出电梯并到达货物电梯位置取货
void GenerateInputWarehousingOrders::GetCarfromCarElevatortopickupBoxElevatorders()
{
    OrderStru orderstru;
    if(m_carPos.x != m_changeoverRoadstru.x)
    {
        orderstru.order = X;
        orderstru.value = m_changeoverRoadstru.x-m_carPos.x;
        m_taskQueue.append(orderstru);
        m_carPos.x = m_changeoverRoadstru.x;
    }
    if(m_pickupBoxElevatorstru.y != m_carPos.y)
    {
        orderstru.order = Y;
        orderstru.value = m_pickupBoxElevatorstru.y-m_carPos.y;
        m_taskQueue.append(orderstru);
        m_carPos.y = m_pickupBoxElevatorstru.y;
    }
    if(m_carPos.x!=m_pickupBoxElevatorstru.x )
    {
        orderstru.order = X;
        orderstru.value = m_pickupBoxElevatorstru.x-m_carPos.x;
        m_taskQueue.append(orderstru);
        m_carPos.x = m_pickupBoxElevatorstru.x;
    }
    //小车从入库电梯取货动作
    orderstru.order = Right_WorkBin;
    m_taskQueue.append(orderstru);
}
///
/// \brief GenerateInputWarehousingOrders::GetfrompickupBoxElevatortoTraposorders
///取到货物之后到达目标位置仓位放货
void GenerateInputWarehousingOrders::GetfrompickupBoxElevatortoTraposorders()
{
    OrderStru orderstru;
    if(m_carPos.x != m_changeoverRoadstru.x)
    {
        orderstru.order = X;
        orderstru.value = m_changeoverRoadstru.x-m_carPos.x;
        m_taskQueue.append(orderstru);
        m_carPos.x = m_changeoverRoadstru.x;
    }
    if(m_carPos.y != m_trapos.y)
    {
        orderstru.order = Y;
        orderstru.value = m_trapos.y-m_carPos.y;
        m_taskQueue.append(orderstru);
        m_carPos.y = m_trapos.y;
    }
    if(m_trapos.x != m_carPos.x)
    {
        orderstru.order = X;
        orderstru.value = m_trapos.x-m_carPos.x;
        m_taskQueue.append(orderstru);
        m_carPos.x = m_trapos.x;
    }
    //执行放货动作
    if(m_trapos.state == 0)
    {
        orderstru.order = Left_WorkBin;//左放货
        m_taskQueue.append(orderstru);

    }
    else{
        orderstru.order = Right_WorkBin;//右放货
        m_taskQueue.append(orderstru);
    }

}
