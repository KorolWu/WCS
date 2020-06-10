#ifndef ADDCAR_H
#define ADDCAR_H
#include <QWidget>
#include "../dialogabstractclass.h"
#include <QStringList>
#include "../SDK/include/datastructure.h"
#include "../SDK/include/Myconfig.h"
#include "../SDK/include/MysqlDataBase/crudbaseoperation.h"

class AddCar:public DialogAbstractClass
{
    Q_OBJECT
public:
    AddCar(const QStringList &list,QWidget *parent);

    // DialogAbstractClass interface
public:
    void onYesBtnClicked();
private:
    CarInfoStru deviceStruct;
signals:
    void insert_emit();
};

#endif // ADDCAR_H
