#ifndef KCOMMUNICATION_H
#define KCOMMUNICATION_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QStringList>
#include <QMap>
#include <QDebug>
#include <QModbusClient>
#include <QModbusTcpClient>
#include <QModbusDataUnit>
#include <QUrl>
#include <QMutex>
#include <QMutexLocker>
/**
 *
 * @author korol
 * @email wuwenpeng@cowain.com.cn
 * @date 2020-06-29 09:55:59
 * use communication  tcpServer tcpCline RS modbusTcp
 */
namespace KCommunication {

///
/// \brief The KTcpserver class
/// TCP服务器
///
class KTcpserver : public QObject
{
    Q_OBJECT
public:
    explicit KTcpserver(QObject *parent = 0);
    ~KTcpserver();
    bool creatTcpserver(int port,QString ip = "");
    int write(QByteArray data);
private:
    QTcpServer *tcpserver;//监听套接字
    QTcpSocket *socket;//通讯套接字
signals:
    void onTcpServerResive(QByteArray array);
public slots:
};
///
/// \brief The KTcpClient class
/// TCP客户端
///
class KTcpClient : public QObject
{
    Q_OBJECT
public:
    KTcpClient(QObject *parent = 0);
    ~KTcpClient();
    bool creadTcpClient(QString ip, qint16 port);
    bool connectServer(QString ip,qint16 port);
    bool reConnection();
    int write(QByteArray array);
    QTcpSocket *socket;//通讯套接字
    bool m_connectStatus;
    void onDisconnected();

private:
    QString ip;
    qint16 port;
signals:
    void onTcpClientResive(QByteArray buff);
    void clientDisconnect();
};

///
/// \brief The KSerialPort class
/// 串口
///
class KSerialPort : public QObject
{
    Q_OBJECT
public:
    KSerialPort(QObject *parent);
    ~KSerialPort();
    bool foundPort();//寻找串口
    bool openPort(QString name,int BaudRate, int DataBits, int Parity, int StopBits);//打开串口
    void closePort();
    void readDate(); //读取数据
    void writeDate(QByteArray array);//写入数据
private:
     QSerialPort *serial;
     const int m_length = 1024;
     QString m_resive;
signals:
     void onSerialResive(QString str);
};
///
/// \brief The KModbusTcpClient class
///  ModbusTcpClient
///
class KModbusTcpClient : public QObject
{
    Q_OBJECT
public:
    KModbusTcpClient(QObject *parent = 0);
    bool GetConnect(const QString url_str);
    void write(int start_bit,int value,int address = 1);
    void readCoils (int start_bit, int address = 1);
    void readAll();
    void readRegisters(int start_bit,int adress =1);
    void readReady();
    int getBitValue(int start_bit);
    void init_bitMap();
private:
     QModbusClient *modbusDevice;
     QMap<int,int> bit_map;
};
}
#endif // COMMUNICATION_H
