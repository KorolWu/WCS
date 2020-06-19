#ifndef BASEFROM_H
#define BASEFROM_H

#include <QObject>
#include <QWidget>
class BaseFrom:public QWidget
{
public:
    BaseFrom(QWidget *parent);
    int getClickIndex(QString str);
    const  QString   headstlye ="QHeaderView:section{height:32px;font:12px;border:3;"
                                "color: rgb(250, 250, 250);background-color: rgba(68, 69, 71,200);}";
};

#endif // BASEFROM_H
