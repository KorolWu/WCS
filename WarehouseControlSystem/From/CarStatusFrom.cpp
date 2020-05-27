#include "CarStatusFrom.h"
#include <QDebug>
CarStatusFrom::CarStatusFrom(_Car_status carStatus,QWidget *parent) : QWidget(parent)
{
    desktop =  QApplication::desktop()->availableGeometry();
    qDebug()<<"x "<<desktop.width();
    qDebug()<<"y"<<desktop.height();


   // this->move(desktop.width()-PAD_X-20,desktop.height()-PAD_Y-20);
    QFont font("宋体",14);
    header_lab = new QLabel(this);
    header_lab->resize(PAD_X,100);
    header_lab->setStyleSheet("background-color:rgb(24, 24, 72)");

    online_image = new QLabel(this);
    online_image->resize(15,15);
    online_image->setStyleSheet(carStatus.isOnline?"border-image:url(:/resouse/Image/green.png)":"border-image:url(:/resouse/Image/grey.png)");
    online_image->move(30,10);
    online_lab = new QLabel(carStatus.isOnline? "在线":"离线",this);
    online_lab->move (60,10);
    online_lab->setStyleSheet("color:white");

    closeBtn = new QPushButton(this);
    closeBtn->setStyleSheet("border-image:url(:/resouse/Image/close.png)");
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
    car_number->setText(carStatus.carNum);
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
    battery_lab->setText(QString::number(carStatus.batter)+"%");
    qDebug()<<QString::number(carStatus.batter);
    battery_lab->move(450,line1_y-20);
    battery_lab->setFont(font);
    battery_lab->setStyleSheet("color:white");

    QLabel *b = new QLabel("电池用量",this);
    b->setStyleSheet("color:white");
    b->move(450,line1_y);

    //this->setStyleSheet("#this{color:red}");
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
    item = new QTableWidgetItem (carStatus.carIp);
    table->setItem(0, 1, item);
    item = new QTableWidgetItem ("执行状态");
    table->setItem(0, 2, item);
    item = new QTableWidgetItem (carStatus.status);
    table->setItem(0, 3, item);
    item = new QTableWidgetItem ("设备名称");
    table->setItem(1, 0, item);
    item = new QTableWidgetItem (carStatus.carNum);
    table->setItem(1, 1, item);
    item = new QTableWidgetItem ("货架名称");
    table->setItem(1, 2, item);
    item = new QTableWidgetItem (carStatus.shelves);
    table->setItem(1, 3, item);

    item = new QTableWidgetItem ("当前位置");
    table->setItem(2, 0, item);
    item = new QTableWidgetItem (QString("%1,%2").arg(carStatus.x).arg(carStatus.y));
    table->setItem(2, 1, item);
    item = new QTableWidgetItem ("目标位置");
    table->setItem(2, 2, item);
    item = new QTableWidgetItem (QString("%1,%2").arg(carStatus.x_end).arg(carStatus.y_end));
    table->setItem(2, 3, item);

    item = new QTableWidgetItem ("是否可用");
    table->setItem(3, 0, item);
    item = new QTableWidgetItem (carStatus.enable);
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


    this->resize(600,PAD_Y);


}

void CarStatusFrom::fromClose()
{
 this->close();
}

