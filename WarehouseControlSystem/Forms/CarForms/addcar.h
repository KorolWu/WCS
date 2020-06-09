#ifndef ADDCAR_H
#define ADDCAR_H
#include <QWidget>
#include "../dialogabstractclass.h"
#include <QStringList>
#include "../../datastructure.h"

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
