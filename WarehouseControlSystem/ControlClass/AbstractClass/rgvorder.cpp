#include "rgvorder.h"

RgvOrder::RgvOrder()
{

}

char *RgvOrder::move_x(const int &value)
{
    QString str = "Kmove_x"+ QString("%1").arg(value);
    QByteArray buff = str.toLatin1();
    return buff.data();
}

char *RgvOrder::move_y(const int &value)
{
    QString str = "Kmove_y"+ QString("%1").arg(value);
    QByteArray buff = str.toLatin1();
    return buff.data();
}

char *RgvOrder::right_get()
{
    QString str = "Kright_get";
    QByteArray buff = str.toLatin1();
    return buff.data();
}

char *RgvOrder::left_get()
{
    QString str = "Kleft_get";
    QByteArray buff = str.toLatin1();
    return buff.data();
}

char *RgvOrder::changeWhell()
{
    QString str = "KchangeWhell";
    QByteArray buff = str.toLatin1();
    return buff.data();
}

char *RgvOrder::move_ElevatorNear()
{
    QString str = "Kmove_ElevatorNear";
    QByteArray buff = str.toLatin1();
    return buff.data();
}

char *RgvOrder::call_Elevator(const int layer)
{
    QString str = "Kcall_Elevator"+QString("%1").arg(layer);
    QByteArray buff = str.toLatin1();
    return buff.data();
}
