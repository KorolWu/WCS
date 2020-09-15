#include "basefrom.h"

BaseFrom::BaseFrom(QWidget *parent):QWidget(parent)
{
    this->setStyleSheet("QPushButton{font: 14px;width:100px;height:25;\
                         background-color:rgb(150,150,150);}QPushButton:hover{background: rgb(220, 220, 220);}\
                         QPushButton:pressed{background-color:rgb(85, 170, 255);}QLabel{font: 14px}");
}

int BaseFrom::getClickIndex(QString str)
{

    QStringList list = str.split("_");
    if(list.size() != 2)
        return 0;
    return QString(list[1]).toInt();

}
