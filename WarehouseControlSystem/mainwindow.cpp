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

    p_treeView = new QTreeView(treewidget);
    connect(p_treeView,&QTreeView::clicked,this,&MainWindow::onTreeviewClicked);
    p_treeView->setFixedSize(desk_rect.width()/7-5,desk_rect.height()/10*9-5);
    p_treeStandarModel = new QStandardItemModel(p_treeView);
    p_treeView->setModel(p_treeStandarModel);
    p_treeView->setFont(QFont("宋体",16));
    p_treeView->header()->hide();
    p_treeView->setEditTriggers(0);
    p_standarItem = new QStandardItem("用户管理");
    p_userItem = new QStandardItem("权限管理");
    p_standarItem->appendRow(p_userItem);
    p_treeStandarModel->appendRow(p_standarItem);
    p_standarItem = new QStandardItem("设备管理");
    p_agvItem = new QStandardItem("小车管理");
    p_elevator = new QStandardItem("电梯管理");
    p_standarItem->appendRow(p_agvItem);
    p_standarItem->appendRow(p_elevator);

    p_treeStandarModel->appendRow(p_standarItem);
    p_standarItem = new QStandardItem("货架管理");
    p_treeStandarModel->appendRow(p_standarItem);
    p_standarItem = new QStandardItem("报警管理");
    p_treeStandarModel->appendRow(p_standarItem);
    p_standarItem = new QStandardItem("日志管理");
    p_treeStandarModel->appendRow(p_standarItem);


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

    DataBaseUnit::GetInstance()->openDB();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeWms()
{
    this->close();
}

void MainWindow::onTreeviewClicked(const QModelIndex &index)
{
    int row_index = index.row();
    QString row_name = index.data().toString();
    if(row_name == "权限管理")
    {
        qDebug()<<"handle 权限管理...";
    }
    else if(row_name == "小车管理")
    {
        qDebug()<<"handle 小车管理...";
    }
    else if(row_name == "电梯管理")
    {
        qDebug()<<"handle 电梯管理...";
    }
}
