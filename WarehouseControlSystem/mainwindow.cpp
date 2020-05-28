#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <datastructure.h>
#include <QDesktopWidget>
#include <QIcon>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    desk_rect = QApplication::desktop()->availableGeometry();
    this->resize(desk_rect.width(),desk_rect.height());

    QLabel *head_lab = new QLabel(this);
    head_lab->resize(desk_rect.width(),desk_rect.height()/10);
    head_lab->setStyleSheet("background-color:rgb(198,198,198)");
    treewidget = new QWidget(this);
    treewidget->setStyleSheet("background-color:rgb(150,150,150)");
    treewidget->resize(desk_rect.width()/7,desk_rect.height()/10*9);
    treewidget->move(0,desk_rect.height()/10);
    user_btn = new QPushButton("用户",this);
    user_btn->setIcon(QIcon(":/resouse/Image/user.png"));
    user_btn->move(desk_rect.width()*0.85,desk_rect.height()/20);
    exit_btn = new QPushButton("安全退出",this);
    connect(exit_btn,&QPushButton::clicked,this,&MainWindow::closeWms);
    exit_btn->setIcon(QIcon(":/resouse/Image/shutdown.png"));
    exit_btn->move(desk_rect.width()*0.9+20,desk_rect.height()/20);

    _Car_status s;
    s.batter = 70;
    s.carNum = "ABS-002";
    f = new CarStatusFrom(s,this);
    f->move(desk_rect.width()-600,desk_rect.height()-350);

    AddDevice *device = new AddDevice(this);
    device->move(300,150);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeWms()
{
    this->close();
}
