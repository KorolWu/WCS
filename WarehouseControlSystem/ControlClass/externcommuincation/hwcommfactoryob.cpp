#include "hwcommfactoryob.h"
#include "tcommtcpclient.h"
#include "tcommtcpserver.h"

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
    default:
        break;
    }
    return ob;
}
