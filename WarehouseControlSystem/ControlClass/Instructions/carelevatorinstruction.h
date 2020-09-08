#ifndef CARELEVATORINSTRUCTION_H
#define CARELEVATORINSTRUCTION_H

#include <QObject>
#include "abstructinstruction.h"
#include "Myconfig.h"
#include <QThread>
#include <QApplication>
#include <ctime>
#include <time.h>
#include <sys/time.h>
#include "../externcommuincation/tcommtransceivermanager.h"
/**
 * @brief The CarElevatorInstruction class
 *
 * 这里只呼叫电梯，（在电梯可接受指令的时候，确保电梯接收到指令，可能会在等待电梯空闲时阻塞）
 * 这里会将电梯lock，组织被其他人调用
 * 在出电梯指令时将电梯解锁
 *
 */
class CarElevatorInstruction : public AbstructInstruction
{
public:
    CarElevatorInstruction();

    // AbstructInstruction interface
public:
    void setParameter(OrderStru o, int device_id);
    int getResult(QString &exeMsg);
    void runInstruction();
private:
    int m_id;
    int m_z;
    OrderStru   m_order;
    int     m_result;
};

#endif // CARELEVATORINSTRUCTION_H
