#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H
#include <QString>
#include <QMap>
#include <QVector>
#include <QSize>
#include <QObject>
#include <QDebug>
#include <QDateTime>
#include <definitioncomdataframe.h>
typedef struct KBaseStruct_{
    virtual QStringList getNameList(){QStringList list;list.clear();return list;}
    virtual QList<QVariant> getValueList(){QList<QVariant> list;list.clear();return list;}
    virtual ~KBaseStruct_(){ }
}KBaseStruct;
typedef struct KPosition_{
    double x;
    double y;
    double z;
    int state = 0;
}KPosition;
typedef union
{
    struct {
        int8_t
            berror:1, // bit0 值“1”穿梭车在自动状态下发生故障
            belectricity:1, // bit1 值“1”穿梭车电量低
            bready:1,//bit2 值“1”穿梭车就绪,可以接收指令
            bruning:1, //bit3 值“1”穿梭车正在执行指令中
            bunready:1,//bit4值“1”未就绪
            bcalibrating:1,//bit5 值“1”自校准中
            bundefined:2;//6-15 未定义的
    };
    int8_t carstatusinfo;
}CarstatusInfostru;//小车信息结构体
//传感器状态信息
typedef union
{
    struct {
        int8_t
        bLhavegoods:1, // bit0 0位 = 值“1”穿梭车左侧有货
            bRhavegoods:1, // bit1   穿梭车右侧有货
            bloadhavegoods:1,//bit2 值“ 1穿梭车载货台内有货
            undefined:5;//bit3-bit7 值“ 未定义
    };
    int8_t carsensorstat;
}CarSensorgoodsInfostru;//小车货传感器货物信息

typedef struct _Car_status
{
    //电量
    int batter = 20;//值是1 代表电量低 0 代表电量状态正常
    KPosition carCurrentPosion;
    //是否启用 int working warrn online  disonline
    bool enable = false;
    // 1 stand by, 2 working,
    int status = 1; //1 正在执行 2 异常 3 指令完成 小车的动作指令状态 2020/08/24解释状态
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
    //新增数据结构状态信息状态 和 传感器状态信息的结构体2020 08 24
    CarstatusInfostru statusinfodstru;
    CarSensorgoodsInfostru senorgoodsstru;
}Car_status;
enum Order{
    X = 0,                  //向X方向移动
    Y = 1,                  //向Y方向移动
    ChangeWhell = 2,        //换轮子
    Left_Pickup = 3,        //左取货
    Right_Pickup = 4,       //右取货
    Call = 5,               //呼叫换层电梯
    Elevator_Near = 6,      //电梯临近点
    Elevator_In = 7,        //小车进换层电梯
    Elevator_Out = 8,       //小车出换层电梯  unlock_elevator
    Left_WorkBin = 9,       //把料箱放在出货口电梯
    Right_WorkBin = 10,     //把料箱从入库口电梯取出
    Call_WorkBin_Out = 11,  //呼叫出库电梯
    Call_WorkBin_In = 12 ,  //呼叫入库电梯
    call_Runner_Putbox = 13, //呼叫流道放货到入库电梯
    Left_Putinto = 14,       //左放货
    Right_Putinto = 15,      //右放货
    Unlock_layer = 16,       //将小车锁定的层解锁（小车进电梯时）
    Scan_Code    = 17
};
typedef struct _HttpParameter
{
    QString url;
    QByteArray body;
}HttpParameter;
//子任务的结构 任务类型，值
typedef struct _OrderStru
{
    //order type car elevator runer
    QString type = "";//硬件类型
    QString strData = ""; //字符型参数  比如扫码抢
    int16_t childtype = 5 ;//同一个对象不同的数据帧类型
    Order order;
    double value;
    int layer_y;
    QString box_num;
    QString shelves;
    int z;
   //新增数据结构2020 08 29
    int startaddress = 0;
    int numberOfEntries = 1;
    int Datatype = 1;//io /线圈 寄存器 modbus
    QVector<int> values;//需要写的值
    HttpParameter http;
}OrderStru;
typedef struct _CarInfoStru
{
    //小车编号
    int carId = -1;
    QString deviceNum = "";
    QString deviceIp = "";
    int port = 0;
    QString deviceType = "";
    QString remarks = "";
    //被任务预定，锁定不被其他任务分配
    bool isLockByTask = false;
    Car_status deveceStatus;
    //记录正在执行的任务
    KPosition task_position;

    _CarInfoStru& operator = (const _CarInfoStru &other)
    {
        carId = other.carId;
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
        deveceStatus.isLocking = other.deveceStatus.isLocking;
        deveceStatus.inp = other.deveceStatus.inp;
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
typedef struct _ElevatorStatus
{
    int curruntLayer;
    int curachelayer;
    bool isLock;
    //是否可以呼叫
    bool usable;
    bool hasCar;
    bool isOnline;
}ElevatorStatus;
typedef struct _ElevatorInfoStru
{
    //"编号"<<"类型"<<"通讯地址"<<"端口"<<"靠近点位置"<<"位置"<<"remarks"
    int elevatorId;
    ElevatorStatus status;
    QString elevatorNum;
    QString elevatorType;
    QString elevatorIp;
    int     elevatorPort;
    QString elevatorNearPos;
    QString elevatorPos;
    QString remarks;
    double  near_x;
    double  near_y;
    double  elevator_x;
    double  elevator_y;
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
//新增流道信息结构体 2020 09 02
typedef struct _RunnerInfoStru
{
    QMap<int,int> holdresMap; //地址 后面地址对应的值 输出寄存器
    QMap<int,int> coilMap; //地址 后面地址对应的值 bit 物理线圈
    int connectresult = 0;
}RunnerInfoStru;
typedef struct _SerialportInfo
{
    QString SerialName;
    int     SerialPort;
    int     BaudRate;
    int     DataBit;
    int     Parity;
    int     StopBit;
}SerialportInfo;
typedef struct _ScanInfoStru
{
    int            deviceId;
    SerialportInfo hwInfo;
    bool           isOnline=false;

}ScanInfoStru;

//由WCS发过来的任务数据
typedef struct _TaskInfoStru : public KBaseStruct
{
    QString taskNum;
    QString shelves;
    QString status;
    QString boxNum;
    int pripty;
    QString from; //beging position
    QString end;  //end position
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

//流道
typedef struct _RunerStru
{
    QString deviceNum = "";
    QString deviceIp = "";
    int port = 0;
    bool isOnline = false;
    int cache_in_current = 0;
    int cache_in_max = 0;
    int cache_out_max = 0;
    int cache_out_current = 0;
    QString request_in = "";
    QString response_in = "";
    QString request_out = "";
    QString response_out = "";
    RunnerInfoStru runneratastru;
    _RunerStru& operator = (const _RunerStru &other)
    {
        deviceNum = other.deviceNum;
        deviceIp = other.deviceIp;
        port = other.port;
        cache_in_max = other.cache_in_max;
        cache_out_max = other.cache_out_max;
        request_in = other.request_in;
        response_in = other.response_in;
        request_out = other.request_out;
        response_out = other.response_out;
        return *this;
    }
}RunerStru;
// 关于层的一个结构体，用来判断当前层是否锁住，以及锁定的小车的ip
typedef struct _LayerStru
{
    bool isLocked = false;
    QString CarIP = "";
    int     carId = 9999;

}LayerStru;
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
    int storepri; //仓位优先级
    uint8_t directionstate = 0; //  新增 方向状态字段
    QString unused ="";//  新增 备用字段
    bool update = false;
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
