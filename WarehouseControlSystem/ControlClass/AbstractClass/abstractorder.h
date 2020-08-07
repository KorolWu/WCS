#ifndef ABSTRACTORDER_H
#define ABSTRACTORDER_H

#include <QObject>
/**
 * @brief The AbstractOrder class
 * @date 2020/07/21
 * 生成指令的命令基类 AbstractStrategy
 */
class AbstractOrder
{
public:
    AbstractOrder();
    virtual char* move_x(const int &value);
    virtual char* move_y(const int &value);
    virtual char* right_get();
    virtual char* left_get();
    virtual char* changeWhell();
    virtual char* move_ElevatorNear();
    virtual char* call_Elevator(const int layer);
    //进电梯
    virtual char *in_elevator();
    //出电梯
    virtual char *out_elevator();
    //左放货
    virtual char *left_workbin();
    //右放货
    virtual char *right_workbin();
    //呼叫出库电梯
    virtual char *call_elevator_work_out(int layer);
    //呼叫入库电梯
    virtual char *call_elevator_work_in(int layer);
private:
    QByteArray m_arry;
};

#endif // ABSTRACTORDER_H
