#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H
#include <QString>
#include <QMap>
#include <QVector>
#include <QSize>
#include <QObject>
#include <QDebug>
#include <QDateTime>
typedef struct KBaseStruct_{
    virtual QStringList getNameList(){QStringList list;list.clear();return list;}
    virtual QList<QVariant> getValueList(){QList<QVariant> list;list.clear();return list;}
}KBaseStruct;
typedef struct KPosition_{
    double x;
    double y;
    double z;
    int state = 0;
}KPosition;
typedef struct _Car_status
{
    //电量
    int batter = 20;
    KPosition carCurrentPosion;
    //是否启用 int working warrn online  disonline
    bool enable = false;
    // 1 stand by, 2 working,
    int status = 1;
    //locking 在执行多段任务过程中需要锁定小车
    bool isLocking = false;
    //error
    int err_code = 0;
    // 1手动 2自动
    int model = 1;
    //0 左右都没有 1左有货 2右有货 3顶上有货
    char box_status = 0;
    // 到位信号,任务完成后小车会发送完成信号
    bool inp = false;
    //是否在线
    bool isOnline = false;
    //目标坐标
    KPosition carEndPosion;

}Car_status;
enum Order{
    X = 0,
    Y = 1,
    ChangeWhell = 2,
    Left = 3,
    Right = 4,
    Call = 5,
    Elevator_Near = 6
};
//子任务的结构 任务类型，值
typedef struct _OrderStru
{
    Order order;
    double value;
}OrderStru;
typedef struct _CarInfoStru
{
    //小车编号
    QString deviceNum = "";
    QString deviceIp = "";
    int port = 0;
    QString deviceType = "";
    QString remarks = "";
    Car_status deveceStatus;

    _CarInfoStru& operator = (const _CarInfoStru &other)
    {
        deviceNum = other.deviceNum;
        deviceIp = other.deviceIp;
        port = other.port;
        deviceType = other.deviceType;
        remarks = other.remarks;
        deveceStatus.batter = other.deveceStatus.batter;
        deveceStatus.enable = other.deveceStatus.enable;
        deveceStatus.status = other.deveceStatus.status;
        deveceStatus.isOnline = other.deveceStatus.isOnline;
        deveceStatus.carCurrentPosion.x = other.deveceStatus.carCurrentPosion.x;
        deveceStatus.carCurrentPosion.y = other.deveceStatus.carCurrentPosion.y;
        deveceStatus.carCurrentPosion.z = other.deveceStatus.carCurrentPosion.z;
        deveceStatus.carEndPosion.x = other.deveceStatus.carEndPosion.x;
        deveceStatus.carEndPosion.y = other.deveceStatus.carEndPosion.y;
        deveceStatus.carEndPosion.z = other.deveceStatus.carEndPosion.z;
        return *this;
    }

}CarInfoStru;
//数据库配置参数
typedef struct _DataBaseInfoStru
{
    QString sqlName;
    QString databaseName;
    QString ip;
    int port;
    QString userName;
    QString passWord;
    _DataBaseInfoStru()
    {
        sqlName = "";
        databaseName = "";
        ip = "";
        port = 3306;
        userName = "";
        passWord = "";
    }

}DataBaseInfoStru;
// log struct
typedef struct _LogInfoStru
{
    QString from;
    int level;
    QString info;
    _LogInfoStru()
    {
        from = "";
        level = 0;
        info = "";
    }
}LogInfoStru;
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

//由WCS发过来的任务数据
typedef struct _TaskInfoStru : public KBaseStruct
{
    QString taskNum;
    QString status;
    QString boxNum;
    int pripty;
    QString from;
    QString end;
    QString carNum;
    QDateTime creatTime;
    _TaskInfoStru()
    {
        taskNum = "";
        status = "";
        boxNum = "";
        pripty = 1;
        from = "";
        end = "";
        carNum = "";
        creatTime = QDateTime::currentDateTime();
    }

    // KBaseStruct interface
public:
    QStringList getNameList(){QStringList list;list <<"taskNum"<<"taskStatus"<<"boxNum"<<"priority"<<"origin"<<"target"<<"beginTime";return list;}
    QList<QVariant> getValueList()
    {
        QList<QVariant> list;
        list.append(this->taskNum);
        list.append(this->status);
        list.append(this->boxNum);
        list.append(this->pripty);
        list.append(this->from);
        list.append(this->end);
        list.append(this->creatTime.toString("yyyy-MM-dd hh:mm:ss"));
        return list;
    }
}TaskInfoStru;
// Data Union
union Kint64
{
    qint64 v;
    char   c[8];
};
union kint16
{
    qint16 v;
    char   c[2];
};
union kint32
{
    qint32 v;
    char   c[4];
};
union Kbyte2
{
    QByteArray buff;
    char c[2];
};
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
    uint8_t directionstate = 0; //  新增 方向状态字段
    QString unused ="";//  新增 备用字段
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
//仓位状态的几种定义
enum STORESTATE{
    ENBLED = 0,
    USING = 1,
    LOCKING =2,
    UNDEFINED  =3
};
//货架信息结构体描述指料箱所放置位置信息表------------------------------2020/06/02
//报警信息结构体定义-----------------------------------------2020/07/15
typedef struct  _ALARMINFOSTRU {
    uint8_t alarmlevel = 1;
    QString deviceid =  "";
    uint8_t errortype = 1;
    int errorcode = 0;
    uint8_t Operatestate = 1;
    QString cartaskid = "";
    QString wmsTaskid = "";
    QString boxnumber= "";
    QString alarminfo= "";
    double carcoordx= 0;
    double carcoordy = 0;
    double carcoordz = 0;
    QString unused= "";
}ALARMINFOSTRU;
//alarmlevel 报警级别的定义
enum ALARMLEVEL{
    NONE = 0,
    ESPSERIOUS = 1, //一级是特别严重，颜色红色
    SERIOUS = 2,//严重，一般用橙色
    MORSERIOUS = 3,// 较重，一般用黄色
    COMSERIOUS  = 4,//一般，用蓝色表示
};
//故障类型定义
enum ERRORTYPE{
    COMM = 1,//通迅类型故障，小车通迅中断或者Wms通迅中断
    HARDWARE = 2,//小车故障，其他硬件故障
};
//操作状态定义
enum OPERATIONSTATUS{
    AUTO = 1,
    MANUAL = 2,
    OTHER = 3,
};
//报警信息结构体定义-----------------------------------------2020/07/15
#pragma pack()



#endif // DATASTRUCTURE_H
