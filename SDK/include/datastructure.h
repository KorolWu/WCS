#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H
#include <QString>
#include <QMap>
#include <QVector>
#include <QSize>
#include <QObject>
#include <QDebug>
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
typedef struct _CarInfoStru
{
    //小车编号
    QString deviceNum = "";
    QString deviceIp = "";
    int port = 0;
    QString deviceType = "";
    QString remarks = "";

}CarInfoStru;
typedef struct _ElevatorInfoStru
{
    //"编号"<<"类型"<<"通讯地址"<<"端口"<<"靠近点位置"<<"位置"<<"remarks"
    QString elevatorNum;
    QString elevatorType;
    QString elevatorIp;
    int     elevatorPort;
    QString elevatorNearPos;
    QString elevatorPos;
    QString remarks;
    _ElevatorInfoStru()
    {
         elevatorNum = "";
         elevatorType = "";
         elevatorIp = "";
         elevatorPort = 0;
         elevatorNearPos = "";
         elevatorPos = "";
         remarks = "";
    }
}ElevatorInfoStru;
//用户登录信息结构体 1字节对齐
#pragma pack(1)
typedef struct  _LoginInfoStru {
char username[32];//登录用户名字
char prilevel;//用户权限级别等级0 管理员高级模式  1 工程师模式  2 普通员工模式  3游客模式，只能查看页面，可以点击登录按钮
char passwd[32];//用户密码
_LoginInfoStru(){
    memset(username,0,32);
    prilevel = 3;
    memset(passwd,0,32);
}
_LoginInfoStru& operator=(const _LoginInfoStru &other)
{
    strncpy(username,other.username,32);
    strncpy(passwd,other.passwd,32);
    return *this;
}
}LoginInfoStru;
typedef struct  _MapLoginInfoStru {
    QMap<QString,LoginInfoStru> loginInfoMap;
     _MapLoginInfoStru(){
         loginInfoMap.clear();
     }
}MapLoginInfoStru;
//用户登录信息----------------------------------------2020/06/01
//货架信息结构体描述指料箱所放置的位置-------------------------------2020/06/02
typedef struct  _StorePosInfoStru{
    char idnbr[64];//仓位编号信息
    char type; //仓位类型
    double coordx;//仓位的x坐标信息
    double coordy;//仓位的y坐标信息
    double coordz;//仓位的z坐标信息
    char boxnbr[64];//仓位对应料箱信息编号
    char storestat; //0 未使用   1  有 使用中  2 锁定状态 针对维修的情况  3
    char storepri; //仓位优先级
    _StorePosInfoStru(){
        memset(idnbr,0,64);
        type = 0;
        coordx = 0.0;
        coordy = 0.0;
        coordz =0.0;
       memset(boxnbr,0,64);
       storestat = 0;
       storepri = 0;
    }
    _StorePosInfoStru& operator=(const _StorePosInfoStru &other)
    {
        strncpy(idnbr,other.idnbr,64);
        strncpy(boxnbr,other.boxnbr,64);
        return *this;
    }
}StorePosInfoStru;
typedef struct  _MapStorePosInfoStru {
    QMap<QString,StorePosInfoStru> storeposInfoMap;
     _MapStorePosInfoStru(){
         storeposInfoMap.clear();
     }
}MapStorePosInfoStru;

//货架信息结构体描述指料箱所放置位置信息表------------------------------2020/06/02
#pragma pack()



#endif // DATASTRUCTURE_H
