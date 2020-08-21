#ifndef DEFINITIONCOMDATAFRAME_H
#define DEFINITIONCOMDATAFRAME_H
#include <QString>
#include <QMap>
//硬件类型 小车 流道 入库电梯 出库电梯  小车电梯 WMS
enum HWDEVICETYPE{
    RGVCAR = 1,
    ELEVATOR_IN = 2,
    ELEVATOR_OUT= 3,
    ELEVATOR_CAR = 4,
    RUNNER = 5,
    WMS = 6
};
//通讯协议的类型定义 TCP 服务器 客户端 串口 modbustcp等
enum HWDEVICEPROTYPE{
    Tcpserver = 1,
    KTcpClient = 2,
    KSerialPort = 3,
    KModbusTcpClient = 4 ,
    KHttpServer
};
//通讯参数配置部分结构体
struct  TcpStru{
    QString ID;
    int hwtype;
    int port = 0;
    QString ip = "";
};
struct SerialPortstru{
     QString ID;
     int hwtype;
    QString name = "";
    int BaudRate = 0;
    int DataBits = 0;
    int Parity = 0;
    int StopBits =0;
};
struct ModbusTcpClientstru{
     int hwtype;
     QString ID;
    QString url_str;
};

struct ComConfigStru{
    TcpStru hwTcpstru;
    SerialPortstru hwserialstru;
    ModbusTcpClientstru hwmodbustcpclistru;
};
///
/// \brief The HWComallconfigStru struct
///所有的通讯硬件相关的配置参数的内容部分
struct HWComallconfigStru{
    QMap<QString,TcpStru> hwTcpMap;
    QMap<QString,SerialPortstru> hwSerialPortMap;
    QMap<QString,ModbusTcpClientstru> hwmodbustcpcliMap;
};

//通讯数据包帧格式的定义
struct FrameBaseStru{
    int hwdevice;//操作的设备类型
    int hwprotype;//操作的协议类型
    QString frameId;
    int frameindex;

};
//RGV小车的结构接受帧格式结构体
struct RGVcarReceFrameStru :public FrameBaseStru
{
    int type;// 功能类型
    int childtype;//子类型
    int carstate;//小车状态
    double curvalue;// 小车的当前的数据
};
//RGV小车发送包帧的格式结构体
struct RGVcarSendFrameStru :public FrameBaseStru
{
    int  cmdtype;// 功能类型
    int cmdchildtype;//子类型
    double  value;//设置小车 数据
};
//流道通讯数据包格式结构体
struct RunnerSendFrameStru :public FrameBaseStru
{
    int  cmdtype;// 功能类型
    int cmdchildtype;//子类型
    double  setvalue;//设置数据
};
struct RunnerReceFrameStru :public FrameBaseStru
{
    int  cmdtype;// 功能类型
    int cmdchildtype;//子类型
    double  curvalue;//当前流道的状态
};
//入库电梯
//通讯数据包帧格式的定义
struct ComFrameStru{
    RGVcarReceFrameStru carRecFramestru;
    RGVcarSendFrameStru carSendFramestru;
    RunnerSendFrameStru runnersendFramestru;
    RunnerReceFrameStru  runnerReceFramestru;
};





#endif // DEFINITIONCOMDATAFRAME_H
