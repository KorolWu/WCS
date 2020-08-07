#ifndef RGVORDER_H
#define RGVORDER_H

#include <QObject>
#include "abstractorder.h"
/**
 * @brief The RgvOrder class
 * AbstructOrder的基类,小车指令生成器
 */
class RgvOrder : public AbstractOrder
{
public:
    RgvOrder();

    // AbstractOrder interface
public:
    char *move_x(const int &value);
    char *move_y(const int &value);
    char *right_get();
    char *left_get();
    char *changeWhell();
    char *move_ElevatorNear();
    char *call_Elevator(const int layer);
    //进电梯
    char *in_elevator();
    //出电梯
    char *out_elevator();
    //左放货
    char *left_workbin();
    //右放货
    char *right_workbin();
    //呼叫出库电梯
    char *call_elevator_work_out(int layer);
    //呼叫入库电梯
    char *call_elevator_work_in(int layer);
};

#endif // RGVORDER_H
