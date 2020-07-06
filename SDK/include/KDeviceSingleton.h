#ifndef KDEVICESINGLETON_H
#define KDEVICESINGLETON_H
#include "../../WarehouseControlSystem/ControlClass/basedevice.h"
#include <QMap>

class KDeviceSingleton{

private:
    KDeviceSingleton(){
    m_DeviceMap.clear();
    }
public:
    //<Car_ip, BaseDevice*>
    QMap<QString ,BaseDevice*> m_DeviceMap;
    static KDeviceSingleton *getInstance()
    {
        static KDeviceSingleton Instance;
        return &Instance;
    }
};
#endif
