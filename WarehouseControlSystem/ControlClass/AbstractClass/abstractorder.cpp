#include "abstractorder.h"
#define BASE_RETURN "empty string"
AbstractOrder::AbstractOrder()
{
    m_arry = "empty string";
}

char* AbstractOrder::move_x(const int &value)
{
    Q_UNUSED(value);
    return m_arry.data();
}

char* AbstractOrder::move_y(const int &value)
{
    Q_UNUSED(value);
    return m_arry.data();
}

char* AbstractOrder::right_get()
{
    return m_arry.data();
}

char* AbstractOrder::left_get()
{
    return m_arry.data();
}

char* AbstractOrder::changeWhell()
{
    return m_arry.data();
}

char* AbstractOrder::move_ElevatorNear()
{
    return m_arry.data();
}

char *AbstractOrder::call_Elevator(const int layer)
{
    Q_UNUSED(layer);
    return m_arry.data();
}

char *AbstractOrder::in_elevator()
{
    return m_arry.data();
}

char *AbstractOrder::out_elevator()
{
     return m_arry.data();
}

char *AbstractOrder::left_workbin()
{
    return m_arry.data();
}

char *AbstractOrder::right_workbin()
{
    return m_arry.data();
}

char *AbstractOrder::call_elevator_work_out(int layer)
{
    Q_UNUSED(layer);
    return m_arry.data();
}

char *AbstractOrder::call_elevator_work_in(int layer)
{
    Q_UNUSED(layer);
    return m_arry.data();
}
