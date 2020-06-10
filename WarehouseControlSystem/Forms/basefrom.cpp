#include "basefrom.h"

BaseFrom::BaseFrom(QWidget *parent):QWidget(parent)
{

}

int BaseFrom::getClickIndex(QString str)
{

    QStringList list = str.split("_");
    if(list.size() != 2)
        return 0;
    return QString(list[1]).toInt();

}
