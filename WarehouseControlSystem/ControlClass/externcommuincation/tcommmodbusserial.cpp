#include "tcommmodbusserial.h"

Tcommmodbusserial::Tcommmodbusserial()
{
    modbusDevice = nullptr;
    connect(this,&Tcommmodbusserial::signalReadData,this,&Tcommmodbusserial::readDataRequest);
    connect(this,&Tcommmodbusserial::signaWrite,this,&Tcommmodbusserial::on_writeData_request);
}

void Tcommmodbusserial::SetCommParam(ComConfigStru paramstru)
{
    m_configstru = paramstru.hwserialstru;
    InitConnect();
}

int Tcommmodbusserial::GetNameID()
{
    return m_configstru.ID;
}

int Tcommmodbusserial::GetHWtype()
{
    return m_configstru.hwtype;
}

int Tcommmodbusserial::GetHWprotype()
{
    return m_configstru.protype;
}

void Tcommmodbusserial::CloseComm()
{
    modbusDevice->disconnectDevice();
}

void Tcommmodbusserial::InitConnect()
{
    if (modbusDevice) {
        modbusDevice->disconnectDevice();
        delete modbusDevice;
        modbusDevice = nullptr;
    }
    modbusDevice = new QModbusRtuSerialMaster(this);
    connect(modbusDevice, &QModbusClient::errorOccurred, [this](QModbusDevice::Error) {
        qDebug()<<(modbusDevice->errorString()) << "通讯发生了故障" << m_configstru.ID;
        m_connectstate = 0;
        emit signalHWDisconnect(m_configstru.ID,m_configstru.hwtype,false);
        return ;

    });
    connect(modbusDevice, &QModbusClient::stateChanged,this, &Tcommmodbusserial::onStateChanged);
    if (modbusDevice->state() != QModbusDevice::ConnectedState)
    {
        modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,
                                             m_configstru.name);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,
                                             m_configstru.Parity);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,
                                             m_configstru.BaudRate);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,
                                             m_configstru.DataBits);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,
                                             m_configstru.StopBits);
        modbusDevice->setTimeout(500);
        modbusDevice->setNumberOfRetries(3);
        if (!modbusDevice->connectDevice()) {
            //statusBar()->showMessage(tr("Connect failed: ") + modbusDevice->errorString(), 5000);
            qDebug()<<(tr("Connect failed: ") + modbusDevice->errorString());
        }
    }
}
///
/// \brief Tcommmodbusserial::readReady
///接收到的数据
void Tcommmodbusserial::readReady()
{
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();
        QMap<int,int> address_value_map;
        for (uint i = 0; i < unit.valueCount(); i++) {
            const QString entry = tr("Address: %1, Value: %2").arg(unit.startAddress())
                    .arg(QString::number(unit.value(i),
                                         unit.registerType() <= QModbusDataUnit::Coils ? 10 : 16));
            qDebug()<<"m_id:"<<m_configstru.ID<<entry;
            if(!address_value_map.contains(unit.startAddress()))
            {
                address_value_map.insert(unit.startAddress()+i,unit.value(i));
            }
            else
                address_value_map[unit.startAddress()+i] = unit.value(i);
        }
        if(address_value_map.size() > 0)
        {
            emit signalReceModbusHWdeviceData(m_configstru.ID,m_configstru.hwtype,unit.registerType(),address_value_map);
        }
    } else if (reply->error() == QModbusDevice::ProtocolError) {

        qDebug()<<"error:"<<m_configstru.ID<<(tr("Read response error: %1 (Mobus exception: 0x%2)").
                                              arg(reply->errorString()).
                                              arg(reply->rawResult().exceptionCode(), -1, 16));
        //        statusBar()->showMessage(tr("Read response error: %1 (Mobus exception: 0x%2)").
        //                                 arg(reply->errorString()).
        //                                 arg(reply->rawResult().exceptionCode(), -1, 16), 5000);
    } else {
        qDebug()<<"error:"<<m_configstru.ID<<(tr("Read response error: %1 (code: 0x%2)").
                                              arg(reply->errorString()).
                                              arg(reply->error(), -1, 16));
        //        statusBar()->showMessage(tr("Read response error: %1 (code: 0x%2)").
        //                                 arg(reply->errorString()).
        //                                 arg(reply->error(), -1, 16), 5000);
    }
    reply->deleteLater();
}

QModbusDataUnit Tcommmodbusserial::readRequest(int type, int startAddress, int numberOfEntries) const
{
    const auto table =
            static_cast<QModbusDataUnit::RegisterType> (type);

    //    int startAddress = ui->readAddress->value();
    //    Q_ASSERT(startAddress >= 0 && startAddress < 10);

    //    // do not go beyond 10 entries
    //    int numberOfEntries = qMin(ui->readSize->currentText().toInt(), 10 - startAddress);
    return QModbusDataUnit(table, startAddress, numberOfEntries);
}

QModbusDataUnit Tcommmodbusserial::writeRequest(int type, int startAddress, int numberOfEntries) const
{
    const auto table =
            static_cast<QModbusDataUnit::RegisterType> (type);

    //    int startAddress = ui->writeAddress->value();
    //    Q_ASSERT(startAddress >= 0 && startAddress < 10);

    //    // do not go beyond 10 entries
    //    int numberOfEntries = qMin(ui->writeSize->currentText().toInt(), 10 - startAddress);
    return QModbusDataUnit(table, startAddress, numberOfEntries);
}

void Tcommmodbusserial::readDataRequest(int type, int startAddress, int numberOfEntries)
{
    if (!modbusDevice)
        return;
    if(modbusDevice->state()!=QModbusDevice::ConnectedState)
    {
        qDebug()<<"未连接状态，请检查"<<modbusDevice->ConnectedState << m_configstru.ID;
        return;
    }
    if (auto *reply = modbusDevice->sendReadRequest(readRequest(type,startAddress,numberOfEntries), m_configstru.serveraddress))
    {
        if (!reply->isFinished())
            connect(reply, &QModbusReply::finished, this, &Tcommmodbusserial::readReady);
        else
            delete reply; // broadcast replies return immediately
    } else {
        m_connectstate =-4;
        qDebug()<< tr("Read error: ") + (modbusDevice->errorString(), 5000) << m_configstru.ID<<m_configstru.name;
    }
}

void Tcommmodbusserial::on_writeData_request(int type, int startAddress, QVector<int> values)
{
    int numberOfEntries = values.size();
    if (!modbusDevice)
        return;
    if(modbusDevice->state()!=QModbusDevice::ConnectedState)
    {
        m_connectstate = 0;
        qDebug()<<"未连接状态，请检查"<<modbusDevice->ConnectedState << m_configstru.ID;
        return;
    }
    QModbusDataUnit writeUnit = writeRequest(type,startAddress,numberOfEntries);
    QModbusDataUnit::RegisterType table = writeUnit.registerType();
    for (uint i = 0; i < writeUnit.valueCount(); i++) {
        if (table == QModbusDataUnit::Coils)
            writeUnit.setValue(i, values[i]);
        else
            writeUnit.setValue(i, values[i]);
    }
    if (auto *reply = modbusDevice->sendWriteRequest(writeUnit,m_configstru.serveraddress)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, [this, reply]() {
                if (reply->error() == QModbusDevice::ProtocolError) {
                    qDebug()<<  tr("Write response error: %1 (Mobus exception: 0x%2)")
                                .arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16);
                    m_connectstate = -3;
                    //5000);
                } else if (reply->error() != QModbusDevice::NoError) {
                    //                    statusBar()->showMessage(tr("Write response error: %1 (code: 0x%2)").
                    //                        arg(reply->errorString()).arg(reply->error(), -1, 16), 5000);
                    qDebug()<<"通讯硬件ID"<<m_configstru.ID <<tr("Write response error: %1 (code: 0x%2)").arg(reply->errorString()).arg(reply->error(), -1, 16);
                }
                reply->deleteLater();
            });
        } else {
            // broadcast replies return immediately
            reply->deleteLater();
        }
    } else {
        // statusBar()->showMessage(tr("Write error: ") + modbusDevice->errorString(), 5000);
        qDebug()<<"通讯硬件ID："<<m_configstru.ID <<tr("Write error: ") + modbusDevice->errorString();
    }
}

void Tcommmodbusserial::onStateChanged(int state)
{
    bool connected = (state != QModbusDevice::UnconnectedState);
    emit signalHWDisconnect(m_configstru.ID,m_configstru.hwtype,connected);
    if (state == QModbusDevice::UnconnectedState)
    {
        //emit signalHWDisconnect(m_configstru.ID,m_configstru.hwtype,state);
        // ui->connectButton->setText(tr("Connect"));
    }
    else if (state == QModbusDevice::ConnectedState)
    {
        // ui->connectButton->setText(tr("Disconnect"));
    }
}
