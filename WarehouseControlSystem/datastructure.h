#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H
#include <QString>
#include <QMap>
#include <QVector>
#include <QSize>
typedef struct _Car_status
{
    //小车编号
    QString carNum = "----";
    //电量
    int batter = 0;
    //小车ip
    QString carIp = "----";
    //小车坐标
    int x = 0;
    int y = 0;
    //是否启用
    bool enable = false;
    //是否在线
    bool isOnline = false;
    //目标坐标
    int x_end = 0;
    int y_end = 0;
    //货架编号
    QString shelves = "---";
    //status
    QString status = "---";
}Car_status;
#endif // DATASTRUCTURE_H
