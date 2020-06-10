#ifndef READTABLEDATA_H
#define READTABLEDATA_H

#include "readtabledata_global.h"
#include "../../SDK/include/datastructure.h"
#include "../../SDK/include/Myconfig.h"
#include <../../SDK/include/MysqlDataBase/crudbaseoperation.h>

class READTABLEDATASHARED_EXPORT ReadTableData
{

public:
    ReadTableData();
    void readt_device_info();
    void readt_elevator();
};

#endif // READTABLEDATA_H
