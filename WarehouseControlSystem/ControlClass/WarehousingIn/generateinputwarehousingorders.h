#ifndef GENERATEINPUTWAREHOUSINGORDERS_H
#define GENERATEINPUTWAREHOUSINGORDERS_H

#include <QObject>
#include <datastructure.h>
#include <QQueue>
#include <Myconfig.h>
///
/// 根据目标仓位逻辑的状态生成指令集合
/// 集合包括对小车指令 对流道指令 对料箱电梯指令 对小车电梯指令

//常量 换向巷道 坐标 x y
//常量 箱子电梯-取货点的坐标 x y z;
//常量 小车电梯-等待电梯点坐标 x y;
//常量 小车电梯-进入电梯点坐标 x y;
//流道所在层数 Z
//入箱子电梯 配置坐标 X Y Z

#define RUNNERLAY 0
struct InputCurConfig{
    double x;
    double y;
    double z;
};

class GenerateInputWarehousingOrders:public QObject
{
    Q_OBJECT
public:
    GenerateInputWarehousingOrders();
    ~GenerateInputWarehousingOrders();
    void SetPathParam(KPosition task_P, KPosition curcarPosion);
    QQueue<OrderStru> GetInputWarehousingOrders();
    //test
    void SetHWConfigData(double pickupx,double pickupy,double changeover,double carwaitElevatorx,\
                         double carwaitElevatory,double carElevatorx,double carElevatory );
private:
    QQueue<OrderStru> m_taskQueue;
    KPosition m_trapos;
    KPosition m_carPos;
    //InputCurConfig m_InPutBoxElevatorstru;//入库电梯的坐标 代表当前的信息状态
    InputCurConfig m_pickupBoxElevatorstru;//小车去入库电梯取货的坐标 代表当前的信息状态
    InputCurConfig m_changeoverRoadstru;//换向巷道坐标 代表当前的信息状态
    InputCurConfig m_carwaitElevatorstru;//等待电梯点坐标位置 代表当前的信息状态
    InputCurConfig m_carElevatorstru;//载车电梯的层数位置信息 代表当前的信息状态
private:
    void Generationinstruction();
    void GetBoxelevatorOrders();
    void GetCartowaitElevatorPos();
    void GetCarElevatorToCarlayOrders();
    void GetCartoCarElevatoroeders();
    void GetCarElevatorToBoxlayOrders();
    void GetCarfromCarElevatortopickupBoxElevatorders();
    void GetfrompickupBoxElevatortoTraposorders();
    void GetfromCarElevatochangeroadorders();
    QString GetorderNameByValue(Order value);
    //指令入库轨迹测试生成部分
    void GetPathcmdlist();
    InputCurConfig m_testpickuppos; //流道取货位置点 层数上的差别 与小车电梯位置点
    InputCurConfig m_testelevatorpos;//小车电梯位置点 Z x y
    InputCurConfig m_testCarChargingpos;//小车充电位置 在电梯旁位置
    double m_roady; //巷道位置的坐标



};

#endif // GENERATEINPUTWAREHOUSINGORDERS_H
