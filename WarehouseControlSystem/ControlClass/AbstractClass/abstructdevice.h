#ifndef ABSTRUCTDEVICE_H
#define ABSTRUCTDEVICE_H

#include <QObject>
#include "../basedevice.h"
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
    union Kint64
    {
      qint64 v;
      char   c[8];
    };
    union kint16
    {
        qint16 v;
        char   c[2];
    };
    union kint32
    {
        qint32 v;
        char   c[4];
    };
};

#endif // ABSTRUCTDEVICE_H
