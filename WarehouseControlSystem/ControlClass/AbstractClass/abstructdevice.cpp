#include "abstructdevice.h"

AbstructDevice::AbstructDevice(BaseDevice *b)
{
    this->m_pBaseDevice = b;
}

bool AbstructDevice::move_x(const int &value)
{
    Kint64 k;
    k.v = value;

    m_pBaseDevice->write("buff");
}

bool AbstructDevice::move_y(const int &value)
{
    m_pBaseDevice->write("buff");
}

bool AbstructDevice::right_get()
{
    m_pBaseDevice->write("right");
}

bool AbstructDevice::left_get()
{
    m_pBaseDevice->write("left");
}
