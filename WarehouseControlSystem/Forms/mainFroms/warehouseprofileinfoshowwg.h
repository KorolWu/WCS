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
    void SetParam(int size,QString address,QString type,int state );
protected:
    void paintEvent(QPaintEvent *e);
private:
    int m_size;
    QString m_address;
    QString m_type;
    int m_state;

};

#endif // WAREHOUSEPROFILEINFOSHOWWG_H
