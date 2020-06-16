#include "adddevice.h"

AddDevice::AddDevice(QWidget *parent) : QWidget(parent)
{
    this->resize(400,256);
    w = new QWidget(this);
    w->resize(400,256);
    w->setStyleSheet("border-image:url(:/resouse/Image/grey2.png);");
    QLabel *number_lab = new QLabel("设备编号");
    number_lab->setStyleSheet("border-image:url();color:white");
    deviceNum = new QLineEdit();
    deviceNum->setStyleSheet("border-image:url();color:black");
    hbox = new QHBoxLayout();
    hbox->addWidget(number_lab);
    hbox->addSpacing(50);
    hbox->addWidget(deviceNum);
    vbox =new QVBoxLayout();
    vbox->addItem(hbox);

    QLabel *ip_lab = new QLabel("设备    IP");
    ip_lab->setStyleSheet("border-image:url();color:white");
    deviceIp = new QLineEdit();
    deviceIp->setStyleSheet("border-image:url();color:black");
    hbox = new QHBoxLayout();
    hbox->addWidget(ip_lab);
    hbox->addSpacing(50);
    hbox->addWidget(deviceIp);
    vbox->addItem(hbox);

    QLabel *port_lab = new QLabel("端口        ");
    port_lab->setStyleSheet("border-image:url();color:white");
    port = new QLineEdit();
    port->setStyleSheet("border-image:url();color:black");
    hbox = new QHBoxLayout();
    hbox->addWidget(port_lab);
    hbox->addSpacing(50);
    hbox->addWidget(port);
    vbox->addItem(hbox);

    QLabel *type_lab = new QLabel("设备类型");
    type_lab->setStyleSheet("border-image:url();color:white");
    deviceType = new QLineEdit();
    deviceType->setStyleSheet("border-image:url();color:black");
    hbox = new QHBoxLayout();
    hbox->addWidget(type_lab);
    hbox->addSpacing(50);
    hbox->addWidget(deviceType);
    vbox->addItem(hbox);

    QLabel *remarks_lab = new QLabel("说明        ");
    remarks_lab->setStyleSheet("border-image:url();color:white");
    remarks = new QLineEdit();
    remarks->setStyleSheet("border-image:url();color:black");
    hbox = new QHBoxLayout();
    hbox->addWidget(remarks_lab);
    hbox->addSpacing(50);
    hbox->addWidget(remarks);
    vbox->addItem(hbox);



    yesBtn = new QPushButton("确认");
    connect(yesBtn,&QPushButton::clicked,this,&AddDevice::addDevices);
    calenBtn = new QPushButton("取消");
    connect(calenBtn,&QPushButton::clicked,this,&AddDevice::cancelDevice);
    yesBtn->setStyleSheet("border-image:url();color:black");
    calenBtn->setStyleSheet("border-image:url();color:black");
    hbox = new QHBoxLayout();
    hbox->addWidget(yesBtn);
    hbox->addSpacing(100);
    hbox->addWidget(calenBtn);
    vbox->addItem(hbox);//QPushButton{border-radius:3px;width:70px;height:25;}
    this->setStyleSheet("QLabel{font: 14px;border-image:url();}QLineEdit{border-radius:3px;width:70px;height:25;border-image:url();}background-color:rgb(117, 117, 117)");
    w->setLayout(vbox);
    w->setWindowOpacity(1);

}

void AddDevice::addDevices()
{
    deviceStruct.deviceNum =  deviceNum->text();
    deviceStruct.deviceIp = deviceIp->text();
    deviceStruct.port = port->text().toInt();
    deviceStruct.deviceType = deviceType->text();
    deviceStruct.remarks = remarks->text();

    QString sql = QString("INSERT t_device_info SET deviceNum = '%1',deviceIp = '%1',devicePort = '%2',deviceType = '%3',remarks = '%4';").arg(deviceStruct.deviceNum).arg(deviceStruct.deviceIp).arg(deviceStruct.port).arg(deviceStruct.deviceType);
    if(CRUDBaseOperation::getInstance()->queryUseStr(sql))
    {
        // the same id,same ip
        emit insert_emit();
        this->hide();
        this->deleteLater();
    }
    //handle deviceStruct
}

void AddDevice::cancelDevice()
{
    this->hide();
    this->deleteLater();
}
