#ifndef CARINSTRUCTION_H
#define CARINSTRUCTION_H

#include <QObject>
#include "abstructinstruction.h"
#include "datastructure.h"
#include "Myconfig.h"
#include <QThread>
#include <QApplication>
#include <ctime>
#include <time.h>
#include <sys/time.h>
/**
 * @brief The CarInstruction class
 * @author korol
 * @title 负责小车 X Y的运动
 */
class CarInstruction : public AbstructInstruction
{
public:
    CarInstruction();
private:
    QString m_ip;
    OrderStru   m_order;
    int     m_result;

    // AbstructInstruction interface
public:
    void runInstruction();
    int getResult(QString exeMsg);
    void setParameter(OrderStru o, QString device_id);
};

#endif // CARINSTRUCTION_H