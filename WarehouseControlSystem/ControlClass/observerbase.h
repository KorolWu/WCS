#ifndef OBSERVERBASE_H
#define OBSERVERBASE_H

//#include "basedevice.h"
#include <QObject>
#include <QDebug>
/**
 * @brief The ObserverBase class
 */
class ObserverBase
{
public:
    ObserverBase();
    virtual void updateStatusOnBase();
};

#endif // OBSERVERBASE_H
