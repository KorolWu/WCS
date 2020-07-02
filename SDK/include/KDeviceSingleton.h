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
    QMap<QString ,BaseDevice*> m_DeviceMap;
    static KDeviceSingleton *getInstance()
    {
        static KDeviceSingleton Instance;
        return &Instance;
    }
};
#endif
