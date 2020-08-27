#include "CarStatusFrom.h"
#include <QDebug>
#include "ControlClass/externcommuincation/tcommtransceivermanager.h"
CarStatusFrom::CarStatusFrom(int carId, QWidget *parent) : QWidget(parent)
{
    CarInfoStru c = Myconfig::GetInstance()->m_CarMap[carId];
    desktop =  QApplication::desktop()->availableGeometry();
    this->setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    this->setStyleSheet("QLabel{background:transparent;; color:white}QPushButton{border:1px gray;background-color:gray;color:white;border-radius:3px;width:70px;height:25;} QPushButton:hover{background-color:white; color: black;}QPushButton:pressed{background-color:rgb(85, 170, 255);}");
    m_carNum = c.carId;
    m_id = carId;
    qDebug()<<"carid"<<m_id;
    QFont font("宋体",14);
    QLabel *back_lab = new QLabel(this);
    back_lab->resize(PAD_X,PAD_Y);
    back_lab->setStyleSheet("background-color:rgb(198,198,198)");

    header_lab = new QLabel(this);
    header_lab->resize(PAD_X,100);
    header_lab->setStyleSheet("background-color:rgb(24, 24, 72)");

    online_image = new QLabel(this);
    online_image->resize(15,15);
    online_image->setStyleSheet(c.deveceStatus.isOnline?"border-image:url(:/resouse/Image/green.png)":"border-image:url(:/resouse/Image/grey.png)");
    online_image->move(30,10);
    online_lab = new QLabel(c.deveceStatus.isOnline? "在线":"离线",this);
    online_lab->move (60,10);
    online_lab->setStyleSheet("color:white");
    int invacation_text = 10;




    closeBtn = new QPushButton(this);
    closeBtn->setStyleSheet("border-image:url(:/resouse/Image/close.png);background-color:rgb(24, 24, 72);");
    closeBtn->move(PAD_X-40,10);
    closeBtn->resize(30,30);
    connect(closeBtn,&QPushButton::clicked,this,&CarStatusFrom::fromClose);


    car_image = new QLabel(this);
    car_image->resize(50,50);
    car_image->setStyleSheet("border-image:url(:/resouse/Image/car.png);");
    int line1_y = 60;
    car_image->move(50,line1_y/2);
    car_number = new QLabel(this);
    car_number->resize(150,20);
    car_number->setText(c.deviceNum);
    car_number->move(70,line1_y-20);
    car_number->setFont(font);
    car_number->setAlignment(Qt::AlignCenter);
    car_number->setStyleSheet("color:white");
    l = new QLabel("---",this);
    l->setStyleSheet("color:white");
    l->move(120,line1_y);
    battery_image = new QLabel(this);
    battery_image->resize(30,50);
    battery_image->setStyleSheet("border-image:url(:/resouse/Image/battery.png);");
    battery_image->move(400,line1_y/2);
    battery_lab = new QLabel(this);
    battery_lab->resize(80,20);
    battery_lab->setText(QString::number(c.deveceStatus.batter)+"%");
    battery_lab->move(450,line1_y-20);
    battery_lab->setFont(font);
    battery_lab->setStyleSheet("color:white");

    QLabel *b = new QLabel("电池用量",this);
    b->setStyleSheet("color:white");
    b->move(450,line1_y);

   // this->setStyleSheet("QPushButton{border:1px gray;background-color:gray;color:white;border-radius:3px;width:70px;height:25;} QPushButton:hover{background-color:white; color: black;}QPushButton:pressed{background-color:rgb(85, 170, 255);}");
    table = new QTableWidget(this);
    table->setColumnCount(4);    //设置列数
    table->setRowCount(4);        //设置行数/
    table->resize(PAD_X-20,122);
    table->move(10,110);
    table->verticalHeader()->setVisible(false);
    table->horizontalHeader()->setVisible(false);
    table->horizontalScrollBar()->setEnabled(false);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //table->setHorizontalScrollMode(Qt::ScrollBarAlwaysOff);

    QTableWidgetItem *item = new QTableWidgetItem ("设备IP");
    table->setItem(0, 0, item);
    item = new QTableWidgetItem (c.deviceIp);
    table->setItem(0, 1, item);
    item = new QTableWidgetItem ("执行状态");
    table->setItem(0, 2, item);
    item = new QTableWidgetItem (c.deveceStatus.enable? "enable" : "disable");
    table->setItem(0, 3, item);
    item = new QTableWidgetItem ("设备名称");
    table->setItem(1, 0, item);
    item = new QTableWidgetItem (c.deviceNum);
    table->setItem(1, 1, item);
    item = new QTableWidgetItem ("货架名称");
    table->setItem(1, 2, item);
    item = new QTableWidgetItem ("");
    table->setItem(1, 3, item);

    item = new QTableWidgetItem ("当前位置");
    table->setItem(2, 0, item);
    m_crunt_item = new QTableWidgetItem (QString("%1,%2").arg(c.deveceStatus.carCurrentPosion.x).arg(c.deveceStatus.carCurrentPosion.y));
    table->setItem(2, 1, m_crunt_item);
    item = new QTableWidgetItem ("目标位置");
    table->setItem(2, 2, item);
    item = new QTableWidgetItem (QString("%1,%2").arg(c.deveceStatus.carEndPosion.x).arg(c.deveceStatus.carEndPosion.y));
    table->setItem(2, 3, item);

    item = new QTableWidgetItem ("是否可用");
    table->setItem(3, 0, item);
    item = new QTableWidgetItem (c.deveceStatus.enable? "enable" : "disable");
    table->setItem(3, 1, item);
    item = new QTableWidgetItem ("任务编号");
    table->setItem(3, 2, item);
    item = new QTableWidgetItem ("---");
    table->setItem(3, 3, item);
    table->setStyleSheet("background:#FFFFFF;border:none;font-size:14px;font-family:Microsoft YaHei;color:#666666;");
    int interval = 90;
    up_btn = new QPushButton("左取货",this);
    up_btn->move(10,242);//10+interval*2,242
    down_btn = new QPushButton("右取货",this);
    down_btn->move(10+interval*1,242);//10+interval*3,242

    m_pMove_x = new QPushButton("移动X",this);
    connect(m_pMove_x,&QPushButton::clicked,this,&CarStatusFrom::relative_move_x);
    m_pMove_x->move(10+interval*3,242);

    m_pLineEdit_x = new QSpinBox(this);
    m_pLineEdit_x->resize(80,27);
    m_pLineEdit_x->move(10+interval*2,242);

    m_pLineEdit_y = new QSpinBox(this);

    m_pLineEdit_y->resize(80,27);
    m_pLineEdit_y->move(10+interval*4,242);
    m_pMove_y = new QPushButton("移动Y",this);
    connect(m_pMove_y,&QPushButton::clicked,this,&CarStatusFrom::relative_move_y);
    m_pMove_y->move(10+interval*5,242);

    int interval_image = 65;
    int interval_y = 288;
    int interval_image_text = 32;
    QLabel *ca = new QLabel("校准中",this);
    ca->move(interval_image_text,interval_y);
    autoCalibration = new QLabel(this);
    autoCalibration->resize(15,15);
    autoCalibration->move(15,interval_y);
    autoCalibration->setStyleSheet(c.deveceStatus.statusinfodstru.bcalibrating?"border-image:url(:/resouse/Image/green.png)":"border-image:url(:/resouse/Image/grey.png)");

    QLabel *e = new QLabel("故障",this);
    e->move(interval_image_text+interval_image,interval_y);
    err_lab = new QLabel(this);
    err_lab->resize(15,15);
    err_lab->setStyleSheet(c.deveceStatus.statusinfodstru.berror?"border-image:url(:/resouse/Image/green.png)":"border-image:url(:/resouse/Image/grey.png)");
    err_lab->move(15+interval_image,interval_y);

    QLabel *r = new QLabel("就绪",this);
    r->move(interval_image_text+interval_image*2,interval_y);
    ready_lab = new QLabel(this);
    ready_lab->resize(15,15);
    ready_lab->setStyleSheet(c.deveceStatus.statusinfodstru.bready?"border-image:url(:/resouse/Image/green.png)":"border-image:url(:/resouse/Image/grey.png)");
    ready_lab->move(15+interval_image*2,interval_y);

    QLabel *w = new QLabel("执行中",this);
    w->move(interval_image_text+interval_image*3,interval_y);
    working_lab = new QLabel(this);
    working_lab->resize(15,15);
    working_lab->setStyleSheet(c.deveceStatus.statusinfodstru.bruning?"border-image:url(:/resouse/Image/green.png)":"border-image:url(:/resouse/Image/grey.png)");
    working_lab->move(15+interval_image*3,interval_y);

    QLabel *n = new QLabel("未就绪",this);
    n->move(interval_image_text+interval_image*4,interval_y);
    notReady_lab = new QLabel(this);
    notReady_lab->resize(15,15);
    notReady_lab->setStyleSheet(c.deveceStatus.statusinfodstru.bunready?"border-image:url(:/resouse/Image/green.png)":"border-image:url(:/resouse/Image/grey.png)");
    notReady_lab->move(15+interval_image*4,interval_y);


    invacation_text += 7;
    QLabel *l = new QLabel("左有货",this);
    l->move(interval_image_text+interval_image*5,interval_y);
    m_pLeft_haveBox = new QLabel(this);
    m_pLeft_haveBox->resize(15,15);
    m_pLeft_haveBox->move(15+interval_image*5,interval_y);
    m_pLeft_haveBox->setStyleSheet(c.deveceStatus.statusinfodstru.bcalibrating?"border-image:url(:/resouse/Image/green.png)":"border-image:url(:/resouse/Image/grey.png)");

    QLabel *rb = new QLabel("右有货",this);
    rb->move(interval_image_text+interval_image*6,interval_y);
    m_pRight_haveBox = new QLabel(this);
    m_pRight_haveBox->resize(15,15);
    m_pRight_haveBox->move(15+interval_image*6,interval_y);
    m_pRight_haveBox->setStyleSheet(c.deveceStatus.statusinfodstru.bcalibrating?"border-image:url(:/resouse/Image/green.png)":"border-image:url(:/resouse/Image/grey.png)");

    QLabel *t = new QLabel("上有货",this);
    t->move(interval_image_text+interval_image*7,interval_y);
    m_pTop_haveBox = new QLabel(this);
    m_pTop_haveBox->resize(15,15);
    m_pTop_haveBox->move(15+interval_image*7,interval_y);
    m_pTop_haveBox->setStyleSheet(c.deveceStatus.statusinfodstru.bcalibrating?"border-image:url(:/resouse/Image/green.png)":"border-image:url(:/resouse/Image/grey.png)");


    this->resize(550,PAD_Y);
//    if(KDeviceSingleton::getInstance()->m_DeviceMap.contains(c.deviceIp))
//    {
//        KDeviceSingleton::getInstance()->m_DeviceMap[c.deviceIp]->registObserver(this);
//    }
//    foreach (QPushButton *btn, this) {
//        btn->setStyleSheet("border:5fix");
//    }
    //connect(TCommtransceivermanager::GetInstance(),&TCommtransceivermanager::SignalCarStatusUpdate,this,&CarStatusFrom::updateStatusOnBase);
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&CarStatusFrom::updateStatusOnBase);
    timer->start(300);
}

void CarStatusFrom::fromClose()
{
    if(KDeviceSingleton::getInstance()->m_DeviceMap.contains("m_id"))
    {
        KDeviceSingleton::getInstance()->m_DeviceMap["m_ip"]->removeObserver(this);
    }
    this->close();
}

void CarStatusFrom::relative_move_x()
{
    int value = m_pLineEdit_x->value();
    AbstructInstruction *c = new CarInstruction();
    OrderStru o;
    o.order = X;
    o.value = value;
    c->setParameter(o,m_id);
    c->runInstruction();
}

void CarStatusFrom::relative_move_y()
{
    int value = m_pLineEdit_y->value();
    AbstructInstruction *c = new CarInstruction();
    OrderStru o;
    o.order = Y;
    o.value = value;
    c->setParameter(o,m_id);
    c->runInstruction();
}
// batter status enable online? position
void CarStatusFrom::updateStatusOnBase()
{
    if(Myconfig::GetInstance()->m_CarMap.contains(m_id))
    {
         online_image->setStyleSheet(Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.isOnline?"border-image:url(:/resouse/Image/green.png)":"border-image:url(:/resouse/Image/grey.png)");
         online_lab->setText(Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.isOnline?"在线":"离线");
         battery_lab->setText(Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.statusinfodstru.belectricity? "20%" : "100%");
         QTableWidgetItem *item = new QTableWidgetItem (Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.isLocking == true? "待命中" : "工作中");
         table->setItem(0, 3, item);
         item = new QTableWidgetItem (Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.enable? "enable" : "disable");
         table->setItem(3, 1, item);

         m_crunt_item->setText(QString("%1,%2").arg(Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.carCurrentPosion.x).arg(Myconfig::GetInstance()->m_CarMap[m_carNum].deveceStatus.carCurrentPosion.y));
         err_lab->setStyleSheet(Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.statusinfodstru.berror?"border-image:url(:/resouse/Image/green.png)":"border-image:url(:/resouse/Image/grey.png)");
         ready_lab->setStyleSheet(Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.statusinfodstru.bready?"border-image:url(:/resouse/Image/green.png)":"border-image:url(:/resouse/Image/grey.png)");
         working_lab->setStyleSheet(Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.statusinfodstru.bruning?"border-image:url(:/resouse/Image/green.png)":"border-image:url(:/resouse/Image/grey.png)");
         notReady_lab->setStyleSheet(Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.statusinfodstru.bunready?"border-image:url(:/resouse/Image/green.png)":"border-image:url(:/resouse/Image/grey.png)");
         autoCalibration->setStyleSheet(Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.statusinfodstru.bcalibrating?"border-image:url(:/resouse/Image/green.png)":"border-image:url(:/resouse/Image/grey.png)");
         m_pLeft_haveBox->setStyleSheet(Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.senorgoodsstru.bLhavegoods?"border-image:url(:/resouse/Image/green.png)":"border-image:url(:/resouse/Image/grey.png)");
         m_pRight_haveBox->setStyleSheet(Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.senorgoodsstru.bRhavegoods?"border-image:url(:/resouse/Image/green.png)":"border-image:url(:/resouse/Image/grey.png)");
         m_pTop_haveBox->setStyleSheet(Myconfig::GetInstance()->m_CarMap[m_id].deveceStatus.senorgoodsstru.bloadhavegoods?"border-image:url(:/resouse/Image/green.png)":"border-image:url(:/resouse/Image/grey.png)");

    }
}








