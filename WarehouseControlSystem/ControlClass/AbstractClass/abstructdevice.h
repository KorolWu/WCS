#ifndef ABSTRUCTDEVICE_H
#define ABSTRUCTDEVICE_H

#include <QObject>
#include "../basedevice.h"
#include "datastructure.h"
/**
 * @brief The AbstructDevice class
 * @author korol
 * @date  2020-07-09
 * @details The base class of the driver defines some common functions of the driver,
 *  and the details are implemented by its subclasses
 */

class AbstructDevice
{
public:
    AbstructDevice(BaseDevice *b);
    char *getBaseData();
    virtual bool move_x(const int &value);
    virtual bool move_y(const int &value);
    virtual bool right_get();
    virtual bool left_get();
private:
    BaseDevice *m_pBaseDevice;

};

#endif // ABSTRUCTDEVICE_H
