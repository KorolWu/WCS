#ifndef READTABLEDATA_H
#define READTABLEDATA_H

#include "readtabledata_global.h"
#include "datastructure.h"
#include "Myconfig.h"
#include <MysqlDataBase/crudbaseoperation.h>

class READTABLEDATASHARED_EXPORT ReadTableData
{

public:
    ReadTableData();
    void readt_device_info();
    void readt_elevator();
};

#endif // READTABLEDATA_H
