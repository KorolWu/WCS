#include "tcommmodbustcpclient.h"

TCommModbusTcpClient::TCommModbusTcpClient()
{
    modbusDevice = nullptr;
    connect(this,&TCommModbusTcpClient::signalReadData,this,&TCommModbusTcpClient::SlotReadData);
    connect(this,&TCommModbusTcpClient::signalWriteValue,this,&TCommModbusTcpClient::SlotWriteValue);
}

void TCommModbusTcpClient::SetCommParam(ComConfigStru paramstru)
{
    m_configstru = paramstru.hwmodbustcpclistru;
    GetConnect(m_configstru.url_str);

}

QString TCommModbusTcpClient::GetNameID()
{
    return m_configstru.ID;
}

int TCommModbusTcpClient::GetHWtype()
{
    return m_configstru.hwtype;
}

int TCommModbusTcpClient::GetHWprotype()
{
    return KModbusTcpClient;
}

void TCommModbusTcpClient::CloseComm()
{

}
///
/// \brief TCommModbusTcpClient::GetConnect
/// \param url_str
/// \return
///客户端modbus连接对方的数据部分内容
bool TCommModbusTcpClient::GetConnect(const QString url_str)
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
            emit signalHWDisconnect(m_configstru.ID,m_configstru.hwtype,false);
            return false;
        } else {
            qDebug()<<(tr("Connect successful"));
            //emit connect_success_signal();
            emit signalHWDisconnect(m_configstru.ID,m_configstru.hwtype,true);
            return true;
        }
    }

    return true;
}

void TCommModbusTcpClient::write(int start_bit, int value, int address)
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

void TCommModbusTcpClient::readCoils(int start_bit, int address)
{
    if (!modbusDevice)
        return;
    if (auto *reply = modbusDevice->sendReadRequest(QModbusDataUnit(QModbusDataUnit::RegisterType::Coils,start_bit,address), 1)) {
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, this, &TCommModbusTcpClient::readReady);
        }
        else
            delete reply; // broadcast replies return immediately
    } else {
        qDebug()<<(tr("Read error: ") + modbusDevice->errorString(), 5000);
    }
}

void TCommModbusTcpClient::readAll()
{

}

void TCommModbusTcpClient::readRegisters(int start_bit, int adress)
{
    if (!modbusDevice)
        return;

    if (auto *reply = modbusDevice->sendReadRequest(QModbusDataUnit(QModbusDataUnit::RegisterType::InputRegisters,start_bit,1), adress)) {
        if (!reply->isFinished())
            connect(reply, &QModbusReply::finished, this, &TCommModbusTcpClient::readReady);
        else
            delete reply; // broadcast replies return immediately
    } else {
        qDebug()<<(tr("Read error: ") + modbusDevice->errorString(), 5000);
    }
}
///
/// \brief TCommModbusTcpClient::readReady
///请求之后接收到的数据的
void TCommModbusTcpClient::readReady()
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

            //收到发过来的数据内容 前面四个字节代表地址 后边两个字节代表值
             QByteArray Databytearray;
             int bitaddr = unit.startAddress()+i;
             uint16_t value = unit.value(i);
             memcpy(Databytearray.data(),&bitaddr,4);
             memcpy(Databytearray.data()+4,&value,2);
      emit signalReadHWdeviceData(m_configstru.ID,m_configstru.hwtype,Databytearray);
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

int TCommModbusTcpClient::getBitValue(int start_bit)
{
    if(bit_map.contains(start_bit))
    {
        return bit_map[start_bit];
    }
    else
        return -1;
}

void TCommModbusTcpClient::init_bitMap()
{
    readCoils(0,20);
}

void TCommModbusTcpClient::SlotReadData(int type, int bit, int address)
{
    switch (type) {
    case QModbusDataUnit::RegisterType::Coils:
    {
        readCoils(bit,address);
        break;
    }
    case QModbusDataUnit::RegisterType::InputRegisters:
    {
        readRegisters(bit,address);
        break;
    }
    default:
        break;
    }

}

void TCommModbusTcpClient::SlotWriteValue(int type, int bit, int value, int address)
{
    switch (type) {
    case QModbusDataUnit::RegisterType::Coils:
    {
        write(bit,value,address);
        break;
    }
    default:
        break;
    }

}
