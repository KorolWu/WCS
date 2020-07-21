#ifndef SELECTCAR_H
#define SELECTCAR_H

#include <QObject>
#include <QMap>
#include <math.h>
#include "datastructure.h"
#include "Myconfig.h"
/**
 * @brief The SelectCar class
 * 根据料箱位置选择合适的小车
 */
class SelectCar : public QObject
{
    Q_OBJECT
public:
    explicit SelectCar(QObject *parent = 0);
    QString getCarIp_out(const KPosition &p);
    QString getCarIp_in(const KPosition &p);
    //判断是否有可用车辆
    bool hasUseCar();

signals:

public slots:
};

#endif // SELECTCAR_H
