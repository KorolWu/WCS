#include "rgvorder.h"

RgvOrder::RgvOrder()
{

}

char *RgvOrder::move_x(const int &value)
{
    QString str = QString("move_x (%1)").arg(value);
    QByteArray buff = str.toLatin1();
    return buff.data();
}

char *RgvOrder::move_y(const int &value)
{
     QString str = QString("move_y (%1)").arg(value);
    QByteArray buff = str.toLatin1();
    return buff.data();
}

char *RgvOrder::right_get()
{
    QString str = "Kright_get();";
    QByteArray buff = str.toLatin1();
    return buff.data();
}

char *RgvOrder::left_get()
{
    QString str = "Kleft_get();";
    QByteArray buff = str.toLatin1();
    return buff.data();
}

char *RgvOrder::changeWhell()
{
    QString str = "KchangeWhell();";
    QByteArray buff = str.toLatin1();
    return buff.data();
}

char *RgvOrder::move_ElevatorNear()
{
    QString str = "Kmove_ElevatorNear();";
    QByteArray buff = str.toLatin1();
    return buff.data();
}

char *RgvOrder::call_Elevator(const int layer)
{
    QString str = QString("Kcall_Elevator (%1);").arg(layer);
    QByteArray buff = str.toLatin1();
    return buff.data();
}

char *RgvOrder::in_elevator()
{
    QString str = "car_in_Elevator();";
    QByteArray buff = str.toLatin1();
    return buff.data();
}

char *RgvOrder::out_elevator()
{
    QString str = "car_out_Elevator();";
    QByteArray buff = str.toLatin1();
    return buff.data();
}

char *RgvOrder::left_workbin()
{
    QString str = "left_work_bin();";
    QByteArray buff = str.toLatin1();
    return buff.data();
}

char *RgvOrder::right_workbin()
{
    QString str = "right_work_bin();";
    QByteArray buff = str.toLatin1();
    return buff.data();
}

char *RgvOrder::call_elevator_work_out(int layer)
{
    QString str = QString("call_elevator_work_out (%1);").arg(layer);
    QByteArray buff = str.toLatin1();
    return buff.data();
}

char *RgvOrder::call_elevator_work_in(int layer)
{
QString str = QString("call_elevator_work_in (%1);").arg(layer);
    QByteArray buff = str.toLatin1();
    return buff.data();
}
