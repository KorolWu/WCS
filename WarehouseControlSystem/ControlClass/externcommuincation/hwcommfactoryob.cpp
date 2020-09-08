#include "hwcommfactoryob.h"
#include "tcommtcpclient.h"
#include "tcommtcpserver.h"
#include "tcommmodbustcpclient.h"
#include "tcommserialport.h"
#include "tcommmodbusserial.h"

HWCommFactoryOb::HWCommFactoryOb()
{

}

HWdeviceabstractInterface *HWCommFactoryOb::CreatorHWCommFactoryOb(int protype)
{
    HWdeviceabstractInterface *ob = NULL;
    switch (protype)
    {
    case HWDEVICEPROTYPE::Tcpserver:
        ob = new TCommTCPserver();
        break;
    case HWDEVICEPROTYPE::KTcpClient:
        ob = new TCommTCPclient();
        break;
    case HWDEVICEPROTYPE::KModbusTcpClient:
        ob = new TCommModbusTcpClient();
        break;
    case HWDEVICEPROTYPE::KSerialPort:
        ob = new TcommSerialport();
        break;
    case HWDEVICEPROTYPE::KModbusSerialport:
        ob = new Tcommmodbusserial();
        break;
    default:
        break;
    }
    return ob;
}
