#include "CarStatusFrom.h"
#include <QDebug>
CarStatusFrom::CarStatusFrom(CarInfoStru carStatus,QWidget *parent) : QWidget(parent)
{
    desktop =  QApplication::desktop()->availableGeometry();
    this->setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    this->setStyleSheet("QLabel{background:transparent}QPushButton{border:1px gray;background-color:gray;color:white;border-radius:3px;width:70px;height:25;} QPushButton:hover{background-color:white; color: black;}QPushButton:pressed{background-color:rgb(85, 170, 255);}");
    QFont font("宋体",14);
    QLabel *back_lab = new QLabel(this);
    back_lab->resize(PAD_X,PAD_Y);
    back_lab->setStyleSheet("background-color:rgb(198,198,198)");

    header_lab = new QLabel(this);
    header_lab->resize(PAD_X,100);
    header_lab->setStyleSheet("background-color:rgb(24, 24, 72)");

    online_image = new QLabel(this);
    online_image->resize(15,15);
    online_image->setStyleSheet(carStatus.deveceStatus.isOnline?"border-image:url(:/resouse/Image/green.png)":"border-image:url(:/resouse/Image/grey.png)");
    online_image->move(30,10);
    online_lab = new QLabel(carStatus.deveceStatus.isOnline? "在线":"离线",this);
    online_lab->move (60,10);
    online_lab->setStyleSheet("color:white");

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
    car_number->setText(carStatus.deviceNum);
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
    battery_lab->setText(QString::number(carStatus.deveceStatus.batter)+"%");
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
    item = new QTableWidgetItem (carStatus.deviceIp);
    table->setItem(0, 1, item);
    item = new QTableWidgetItem ("执行状态");
    table->setItem(0, 2, item);
    item = new QTableWidgetItem (carStatus.deveceStatus.enable? "enable" : "disable");
    table->setItem(0, 3, item);
    item = new QTableWidgetItem ("设备名称");
    table->setItem(1, 0, item);
    item = new QTableWidgetItem (carStatus.deviceNum);
    table->setItem(1, 1, item);
    item = new QTableWidgetItem ("货架名称");
    table->setItem(1, 2, item);
    item = new QTableWidgetItem ("");
    table->setItem(1, 3, item);

    item = new QTableWidgetItem ("当前位置");
    table->setItem(2, 0, item);
    item = new QTableWidgetItem (QString("%1,%2").arg(carStatus.deveceStatus.x).arg(carStatus.deveceStatus.y));
    table->setItem(2, 1, item);
    item = new QTableWidgetItem ("目标位置");
    table->setItem(2, 2, item);
    item = new QTableWidgetItem (QString("%1,%2").arg(carStatus.deveceStatus.x_end).arg(carStatus.deveceStatus.y_end));
    table->setItem(2, 3, item);

    item = new QTableWidgetItem ("是否可用");
    table->setItem(3, 0, item);
    item = new QTableWidgetItem (carStatus.deveceStatus.enable? "enable" : "disable");
    table->setItem(3, 1, item);
    item = new QTableWidgetItem ("任务编号");
    table->setItem(3, 2, item);
    item = new QTableWidgetItem ("---");
    table->setItem(3, 3, item);
    table->setStyleSheet("background:#FFFFFF;border:none;font-size:14px;font-family:Microsoft YaHei;color:#666666;");
    int interval = 90;
    delete_btn = new QPushButton("排除",this);
    delete_btn->move(10,242);
    canlen_btn = new QPushButton("取消任务",this);
    canlen_btn->move(10+interval*1,242);
    up_btn = new QPushButton("举起",this);
    up_btn->move(10+interval*2,242);
    down_btn = new QPushButton("放下",this);
    down_btn->move(10+interval*3,242);
    pause_btn = new QPushButton("暂停",this);
    pause_btn->move(10+interval*4,242);
    continue_btn = new QPushButton("继续",this);
    continue_btn->move(10+interval*5,242);
    int interval_y = 280;
    add_battery_btn = new QPushButton("去充电",this);
    add_battery_btn->move(10,interval_y);

    creat_fix_btn = new QPushButton("创建维修",this);
    creat_fix_btn->move(10+interval,interval_y);
    sleep_btn = new QPushButton("休眠",this);
    sleep_btn->move(10+interval*2,interval_y);
    position = new QLineEdit(this);
    position->move(10+interval*3,interval_y);
    position->setText("156212,85694");
    move_btn = new QPushButton("移动",this);
    move_btn->move(10+interval*5-70,interval_y);

    this->resize(550,PAD_Y);
//    foreach (QPushButton *btn, this) {
//        btn->setStyleSheet("border:5fix");
//    }
}

void CarStatusFrom::fromClose()
{
 this->close();
}

