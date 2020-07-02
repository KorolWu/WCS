#include "KCommunication.h"

KCommunication::KTcpserver::KTcpserver(QObject *parent)
{
    Q_UNUSED(parent);
    tcpserver = nullptr;
    socket = nullptr;
}

KCommunication::KTcpserver::~KTcpserver()
{
    if(nullptr==socket)
    {
        return;
    }
    socket->disconnectFromHost();
    socket->close();
    socket=nullptr;
}

bool KCommunication::KTcpserver::creatTcpserver(int port, QString ip)
{
    tcpserver=new QTcpServer(this);
    QHostAddress address(QHostAddress::Any);
    if(ip != "")
         address = QHostAddress(ip);
   if(!tcpserver->listen(address,port))
       return false;
    connect(tcpserver,&QTcpServer::newConnection,
            [=](){
        //取出建立好的链接套接字
        socket= tcpserver->nextPendingConnection();
        //获取链接的端口号和ip
        int port = socket->peerPort();
        QString ip=socket->peerAddress().toString();
        QString str = QString("[%1 %2]Connet Successful").arg(port).arg(ip);
        qDebug()<<str;
        connect(socket,&QTcpSocket::readyRead,
                [=]()
        {
            QByteArray array= socket->readAll();
            emit onTcpServerResive(array);
        }
        );
    }
    );
    return true;
}

int KCommunication::KTcpserver::write(QByteArray data)
{
    if(nullptr == socket)
    {
        return 1;
    }
    return socket->write(data);
}
//----------------Client-------------------
KCommunication::KTcpClient::KTcpClient(QObject *parent)
{
    Q_UNUSED(parent);
    socket = nullptr;
    m_connectStatus = false;
}

bool KCommunication::KTcpClient::creadTcpClient(QString ip, qint16 port)
{
    this->ip = ip;
    this->port = port;
    socket = new QTcpSocket(this);
    connect(socket,&QTcpSocket::disconnected,this,&KTcpClient::onDisconnected);
    connect(socket,&QTcpSocket::connected,
            [=]()
    {
        m_connectStatus = true;
    } );
    connect(socket,&QTcpSocket::readyRead,
            [=]()
    {
        QByteArray array=socket->readAll();
        emit onTcpClientResive(array);
    });
    return connectServer(ip,port);
}

bool KCommunication::KTcpClient::connectServer(QString ip, qint16 port)
{
    if(socket == nullptr)
        return false;
    socket->connectToHost(QHostAddress(ip),port);
    if(socket->waitForConnected(1000))
    {
       return true;
    }
    else
    {
        return false;
    }
}

bool KCommunication::KTcpClient::reConnection()
{
    m_connectStatus = connectServer(this->ip,this->port);
    return m_connectStatus;
}

int KCommunication::KTcpClient::write(QByteArray array)
{
    if(socket == nullptr)
        return 1;
    return socket->write(array);
}

void KCommunication::KTcpClient::onDisconnected()
{
    m_connectStatus = false;
    emit clientDisconnect();
}

KCommunication::KTcpClient::~KTcpClient()
{
    if(socket == nullptr)
        return;
    socket->disconnectFromHost();
    socket->close();
    socket = nullptr;
}

//---------------Serial Port-----------------
KCommunication::KSerialPort::KSerialPort(QObject *parent)
{
    Q_UNUSED(parent);
    serial = nullptr;
}

KCommunication::KSerialPort::~KSerialPort()
{

}

bool KCommunication::KSerialPort::foundPort()
{
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serialfound;
        serialfound.setPort(info);
        if(serialfound.open(QIODevice::ReadWrite))
        {
            qDebug() << info.portName();
            serialfound.close();
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool KCommunication::KSerialPort::openPort(QString name, int BaudRate, int DataBits, int Parity, int StopBits)
{
    if(serial == nullptr)
    {
        QStringList portlist;
        serial = new QSerialPort;
        foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            serial->setPort(info);
            if(serial->open(QIODevice::ReadWrite))
            {
                portlist<<info.portName();
                serial->close();
            }
        }
        if(portlist.contains(name))
        {
            //设置串口名
            serial->setPortName(name);
            //打开串口
            serial->open(QIODevice::ReadWrite);
            serial->setReadBufferSize(m_length);
            //设置波特率
            //serial->setBaudRate(ui->BaudBox->currentText().toInt());
            serial->setBaudRate(BaudRate);
            //设置数据位数
            switch(DataBits)
            {
            case 8: serial->setDataBits(QSerialPort::Data8); break;
            case 7: serial->setDataBits(QSerialPort::Data7);break;
            case 6: serial->setDataBits(QSerialPort::Data6);break;
            case 5: serial->setDataBits(QSerialPort::Data5);break;
            default: break;
            }
            //设置奇偶校验
            switch(Parity)
            {
             case 0: serial->setParity(QSerialPort::NoParity); break;
             case 1: serial->setParity(QSerialPort::EvenParity);break;

            default: break;
            }
            //设置停止位
            switch(StopBits)
            {
            case 1: serial->setStopBits(QSerialPort::OneStop); break;
            case 2: serial->setStopBits(QSerialPort::TwoStop); break;
            default: break;
            }
            //设置流控制
            serial->setFlowControl(QSerialPort::NoFlowControl);
            serial->waitForReadyRead(50);

            //连接信号槽
            QObject::connect(serial, &QSerialPort::readyRead, this, &KSerialPort::readDate);
            return true;
        }
        else
        {
            return false;
        }
    }
    return true;
}

void KCommunication::KSerialPort::closePort()
{
    if(serial != nullptr)
    {
        serial->close();
        delete serial;
        serial = nullptr;
    }
}

void KCommunication::KSerialPort::readDate()
{
    if(serial == nullptr)
        return;
    char c[m_length];
    memset(c,0,m_length+1);
    serial->read(c,m_length);
    emit onSerialResive(QString(c));
}

void KCommunication::KSerialPort::writeDate(QByteArray array)
{
    serial->write(array);
}

//---------------Modbus--------------
KCommunication::KModbusTcpClient::KModbusTcpClient(QObject *parent)
{
    Q_UNUSED(parent);
    modbusDevice = nullptr;
}

bool KCommunication::KModbusTcpClient::GetConnect(const QString url_str)
{
    if(modbusDevice != nullptr)
        return false;

    modbusDevice = new QModbusTcpClient(this);
    connect(modbusDevice, &QModbusClient::errorOccurred, [this](QModbusDevice::Error) {
    qDebug()<<(modbusDevice->errorString(), 5000);
    });
    if(modbusDevice->state() != QModbusDevice::ConnectedState)
    {
        QUrl url = QUrl::fromUserInput(url_str);
        modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, url.port());
        modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, url.host());
        //客户端使用超时来确定等待服务器响应的时间。如果在所需超时内未收到响应，则设置TimeoutError
        modbusDevice->setTimeout(500);
        //设置客户端在请求失败前将执行的重试次数
        modbusDevice->setNumberOfRetries(3);
        if (!modbusDevice->connectDevice()) {
            qDebug()<<(tr("Connect failed: ") + modbusDevice->errorString(), 5000);
            return false;
        } else {
           qDebug()<<(tr("Connect successful"));
           //emit connect_success_signal();
           return true;
        }
    }

    return true;
}

void KCommunication::KModbusTcpClient::write(int start_bit, int value, int address)
{
    if (!modbusDevice)
        return;

    QModbusDataUnit writeUnit(QModbusDataUnit::RegisterType::Coils,start_bit,1);
    QModbusDataUnit::RegisterType table = writeUnit.registerType();
    for (uint i = 0; i < writeUnit.valueCount(); i++) {
        if (table == QModbusDataUnit::Coils)
            writeUnit.setValue(i, value);
        else
            writeUnit.setValue(i, value);
    }

    if (auto *reply = modbusDevice->sendWriteRequest(writeUnit, address)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, [this, reply]() {
                if (reply->error() == QModbusDevice::ProtocolError) {
                    qDebug()<<(tr("Write response error: %1 (Mobus exception: 0x%2)")
                        .arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16),
                        5000);
                } else if (reply->error() != QModbusDevice::NoError) {
                    qDebug()<<(tr("Write response error: %1 (code: 0x%2)").
                        arg(reply->errorString()).arg(reply->error(), -1, 16), 5000);
                }
                reply->deleteLater();
            });
        } else {
            // broadcast replies return immediately
            reply->deleteLater();
        }
    } else {
        qDebug()<<(tr("Write error: ") + modbusDevice->errorString(), 5000);
    }
}

void KCommunication::KModbusTcpClient::readCoils(int start_bit, int address)
{
    if (!modbusDevice)
        return;
    if (auto *reply = modbusDevice->sendReadRequest(QModbusDataUnit(QModbusDataUnit::RegisterType::Coils,start_bit,address), 1)) {
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, this, &KModbusTcpClient::readReady);
        }
        else
            delete reply; // broadcast replies return immediately
    } else {
        qDebug()<<(tr("Read error: ") + modbusDevice->errorString(), 5000);
    }
}

void KCommunication::KModbusTcpClient::readAll()
{

}

void KCommunication::KModbusTcpClient::readRegisters(int start_bit, int adress)
{
    if (!modbusDevice)
        return;

    if (auto *reply = modbusDevice->sendReadRequest(QModbusDataUnit(QModbusDataUnit::RegisterType::InputRegisters,start_bit,1), adress)) {
        if (!reply->isFinished())
            connect(reply, &QModbusReply::finished, this, &KModbusTcpClient::readReady);
        else
            delete reply; // broadcast replies return immediately
    } else {
        qDebug()<<(tr("Read error: ") + modbusDevice->errorString(), 5000);
    }

}

void KCommunication::KModbusTcpClient::readReady()
{
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;
    if (reply->error() == QModbusDevice::NoError)
    {
        const QModbusDataUnit unit = reply->result();
        for (uint i = 0; i < unit.valueCount(); i++)
        {
            const QString entry = tr("Address: %1, Value: %2").arg(unit.startAddress() + i).arg(QString::number(unit.value(i),
                                          unit.registerType() <= QModbusDataUnit::Coils ? 10 : 16));
            if(!bit_map.contains(unit.startAddress()))
            {
                bit_map.insert(unit.startAddress()+i,unit.value(i));
            }
            else
                bit_map[unit.startAddress()+i] = unit.value(i);
            //qDebug()<<entry;
        }
    }
    else if (reply->error() == QModbusDevice::ProtocolError)
    {
        qDebug()<<(tr("Read response error: %1 (Mobus exception: 0x%2)"). arg(reply->errorString()).
                                    arg(reply->rawResult().exceptionCode(), -1, 16), 5000);
    } else
    {
         qDebug()<<(tr("Read response error: %1 (code: 0x%2)"). arg(reply->errorString()).
                                    arg(reply->error(), -1, 16), 5000);
    }
    reply->deleteLater();
}

int KCommunication::KModbusTcpClient::getBitValue(int start_bit)
{
    //QMutexLocker locker(&mutex);
    if(bit_map.contains(start_bit))
    {
        return bit_map[start_bit];
    }
    else
        return -1;
}

void KCommunication::KModbusTcpClient::init_bitMap()
{
    readCoils(0,20);
}
