#ifndef HWCOMMFACTORYOB_H
#define HWCOMMFACTORYOB_H

#include <QObject>
#include "hwdeviceabstractinterface.h"

class HWCommFactoryOb
{
public:
    HWCommFactoryOb();
    static HWdeviceabstractInterface *CreatorHWCommFactoryOb(int protype);
};

#endif // HWCOMMFACTORYOB_H
