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
private:
    QByteArray m_arry;
};

#endif // ABSTRACTORDER_H
