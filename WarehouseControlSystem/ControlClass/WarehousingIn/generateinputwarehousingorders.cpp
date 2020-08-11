#include "generateinputwarehousingorders.h"
#include <QDebug>

GenerateInputWarehousingOrders::GenerateInputWarehousingOrders()
{
    m_taskQueue.clear();
    m_pickupBoxElevatorstru.x = 23;
    m_pickupBoxElevatorstru.y = 2;
    m_changeoverRoadstru.x = 24;//换向位置坐标
    m_carwaitElevatorstru.x = 28; //小车每层等待点的坐标
    m_carwaitElevatorstru.y = 1;
    m_carElevatorstru.x = 30;//小车进电梯位置信息
    m_carElevatorstru.y = 1;
}

GenerateInputWarehousingOrders::~GenerateInputWarehousingOrders()
{


}
///
/// \brief GenerateInputWarehousingOrders::SetPathParam
/// \param task_P 目标仓位的信息 carPosion 小车当前的位置信息状态
/// 设置需要把对应的料箱子放到指定的仓位
void GenerateInputWarehousingOrders::SetPathParam(KPosition task_P, KPosition carPosion)
{
    m_trapos = task_P;
    m_carPos = carPosion;
}
///
/// \brief GenerateInputWarehousingOrders::GetInputWarehousingOrders
/// \return
///得到小车轨迹
QQueue<OrderStru> GenerateInputWarehousingOrders::GetInputWarehousingOrders(){
    m_taskQueue.clear();
    Generationinstruction();
    for(int i = 0; i < m_taskQueue.size();++i)
    {
        //qDebug()<<"指令名字:"<<m_taskQueue.at(i).order << "指令参数:"<<m_taskQueue.at(i).value;
    }

    return m_taskQueue;
}
///
/// \brief GenerateInputWarehousingOrders::Generationinstruction
/// 生成有指令功能函数部分
void GenerateInputWarehousingOrders::Generationinstruction()
{
    //货物电梯 和 流道部分的指令内容，等待小车进行取货的流程部分
    GetBoxelevatorOrders();
    if(m_carPos.z != m_trapos.z) //小车不在仓位所在的层数
    {
        //小车到达指定等待电梯位置点
        GetCartowaitElevatorPos();
        //呼叫小车电梯到达指定层数
        GetCarElevatorToCarlayOrders();
        //小车执行进电梯,从等待点到达进电梯
        GetCartoCarElevatoroeders();
        //呼叫电梯到达仓位所在楼层
        GetCarElevatorToBoxlayOrders();
        //呼叫小车出电梯并到达仓位换向位置
        GetfromCarElevatochangeroadorders();
    }
    //小车到达取货电梯点并取货
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
    //1.1呼叫入库电梯到达流道所的层数
    OrderStru orderstru;
    orderstru.order = Call_WorkBin_In;
    orderstru.value = RUNNERLAY;
    m_taskQueue.append(orderstru);
    //1.2通知流道把货放入电梯
    orderstru.order = call_Runner_Putbox;
    m_taskQueue.append(orderstru);
    //1.3通知入库电梯把货物放到指定目标仓位层数
    orderstru.order = Call_WorkBin_In;
    orderstru.value = m_trapos.z;
    m_taskQueue.append(orderstru);
}
///
/// \brief GenerateInputWarehousingOrders::GetTraLayOrders
///小车到达指定等待电梯位置点的
void GenerateInputWarehousingOrders::GetCartowaitElevatorPos()
{
    OrderStru orderstru;
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
        orderstru.order = Elevator_Near;
        orderstru.value = xelevator;
        m_taskQueue.append(orderstru);
        m_carPos.x = m_carwaitElevatorstru.x;
    }

}
///
/// \brief GenerateInputWarehousingOrders::GetCarElevatorToCarlayOrders
///呼叫小车电梯到达小车所在的楼层

void GenerateInputWarehousingOrders::GetCarElevatorToCarlayOrders()
{
    OrderStru orderstru;
    orderstru.order = Call;
    orderstru.value = m_carPos.z;
    m_taskQueue.append(orderstru);

}
///
/// \brief GenerateInputWarehousingOrders::GetCartoCarElevatoroeders
///呼叫小车从小车等待电梯点 到达 小车电梯内的指令
void GenerateInputWarehousingOrders::GetCartoCarElevatoroeders()
{
    OrderStru orderstru;
    if(m_carPos.x != m_carElevatorstru.x) //当前小车所在电梯的层数
    {
        orderstru.order = Elevator_In;
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
    //当前小车所在电梯的层数
    orderstru.order = Call;
    orderstru.value = m_trapos.z;
    m_taskQueue.append(orderstru);
    m_carPos.z = m_trapos.z;
}
///
/// \brief GenerateInputWarehousingOrders::GetCarfromCarElevatortopickupBoxElevatorders
///小车到达货物电梯位置取货
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
        orderstru.order = Left_Putinto;//左放货
        m_taskQueue.append(orderstru);

    }
    else{
        orderstru.order = Right_Putinto;//右放货
        m_taskQueue.append(orderstru);
    }
}
///
/// \brief GenerateInputWarehousingOrders::GetfromCarElevatochangeroadorders
///呼叫小车出电梯到达指定换向位置坐标
void GenerateInputWarehousingOrders::GetfromCarElevatochangeroadorders()
{
    OrderStru orderstru;
    if(m_carPos.x != m_changeoverRoadstru.x) //小车出电梯到达换向位置
    {
        orderstru.order = Elevator_Out;
        orderstru.value = m_changeoverRoadstru.x-m_carPos.x;
        m_taskQueue.append(orderstru);
        m_carPos.x = m_changeoverRoadstru.x;
    }
}

QString GenerateInputWarehousingOrders::GetorderNameByValue(int value)
{
    QString name;
    switch (value) {
    case X:
        name = "X方向移动";
        break;
    case Y:
        name = "Y方向移动";
        break;
    case ChangeWhell:
        name = "ChangeWhell";
        break;
    case Left_Pickup:
        name = "取仓位左边的箱子状态为0";
        break;
    case Right_Pickup:
        name = "取仓位右边的箱子状态为1";
        break;
    case Call:
        name = "呼叫小车电梯到指定层数";
        break;
    case Elevator_Near:
        name = "到达小车电梯临近点";
        break;
    case Elevator_In:
        name = "呼叫小车进电梯";
        break;
    case Elevator_Out:
        name = "呼叫小车出电梯";
        break;

    case Left_WorkBin:
        name = "放入出库电梯的货物";
        break;
    case Right_WorkBin:
        name = "取入库电梯的货物";
        break;
    case  Call_WorkBin_Out:
        name = "呼叫出库电梯到达指定层数";
        break;
    case Call_WorkBin_In:
        name = "呼叫入库电梯到达指定层数";
        break;
    case call_Runner_Putbox:
        name = "呼叫流道把箱子放入电梯";
        break;
    case Left_Putinto:
        name = "把箱子放入左边仓位状态为0";
        break;
    case Right_Putinto:
        name = "把箱子放入右边的仓位状态为1";
        break;
    default:
        break;
    }
    return name;
}
