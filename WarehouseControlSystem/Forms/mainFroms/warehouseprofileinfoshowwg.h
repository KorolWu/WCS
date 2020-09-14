#ifndef WAREHOUSEPROFILEINFOSHOWWG_H
#define WAREHOUSEPROFILEINFOSHOWWG_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QLabel>

class WarehouseprofileInfoShowWg : public QWidget
{
        Q_OBJECT
public:
    WarehouseprofileInfoShowWg(int w, int h, QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *e);
};

#endif // WAREHOUSEPROFILEINFOSHOWWG_H
