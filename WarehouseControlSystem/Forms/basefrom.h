#ifndef BASEFROM_H
#define BASEFROM_H

#include <QObject>
#include <QWidget>
class BaseFrom:public QWidget
{
public:
    BaseFrom(QWidget *parent);
    int getClickIndex(QString str);
};

#endif // BASEFROM_H
