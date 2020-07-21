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
};

#endif // RGVORDER_H
