#include "abstructdevice.h"

AbstructDevice::AbstructDevice(BaseDevice *b)
{
    this->m_pBaseDevice = b;
}
///
/// \brief AbstructDevice::getBaseData
/// \return
/// 返回基本的数据帧
char *AbstructDevice::getBaseData()
{
    char *o = new char[40];
    //指令编号
    kint16 oderNum;
    oderNum.v = 1;
    memcpy(o,oderNum.c,2);
    //Car Number
    kint16 carNum;
    carNum.v = 1;
    memcpy(o+2,carNum.c,2);
}
///
/// \brief AbstructDevice::move_x
/// Move relative position in X direction
/// \param value
/// \return Return true when the task is completed
///
bool AbstructDevice::move_x(const int &value)
{
    Kint64 k;
    k.v = value;
    char *out = new char[40];
    memcpy(out+12,k.c,8);
    m_pBaseDevice->write(out);

}
///
/// \brief AbstructDevice::move_y
/// \param value
/// Move relative position in X direction
/// \return
///
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
