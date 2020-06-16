#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <datastructure.h>
#include <QDesktopWidget>
#include <QIcon>
#include "UnitClass/logininfowg.h"
#include "UnitClass/myIniconfig.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    initUI();
    _Car_status s;
    s.batter = 70;
    s.carNum = "ABS-002";
    f = new CarStatusFrom(s,this);
    f->move(desk_rect.width()-600,desk_rect.height()-350);
    getConfigParameter();
    CRUDBaseOperation::getInstance()->openDB();
    getParameterFromDB();
    GetSystemLogObj()->writeLog("电梯管理",0);
    GetSystemLogObj()->writeLog("电梯管理",0);
    GetSystemLogObj()->writeLog("电梯管理",1);
    GetSystemLogObj()->writeLog("电梯管理",2);
    LogManager *l = new LogManager(this);
    l->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeWcs()
{
    //DataBaseUnit::GetInstance()->closeDb();
    this->close();
}

void MainWindow::initUI()
{
    desk_rect = QApplication::desktop()->availableGeometry();
    this->resize(desk_rect.width(),desk_rect.height());


    QLabel *head_lab = new QLabel(this);
    head_lab->resize(desk_rect.width(),desk_rect.height()/10);
    head_lab->setStyleSheet("background-color:rgb(198,198,198)");
    QLabel *log_lab = new QLabel(this);
    log_lab->move(55,15);
    log_lab->resize(desk_rect.height()/10,desk_rect.height()/10-30);
    log_lab->setStyleSheet("border-image:url(:/resouse/Image/mt.png);");
    QLabel *info_lab =new QLabel(this);
    info_lab->setText("Warehouse Control System");
    info_lab->setFont(QFont("宋体",20));
    info_lab->move(160,70);
    info_lab->resize(600,30);
    treewidget = new QWidget(this);
    treewidget->setStyleSheet("background-color:rgb(150,150,150)");
    treewidget->resize(desk_rect.width()/7,desk_rect.height()/10*9);
    treewidget->move(0,desk_rect.height()/10);
    p_main_widget = new QWidget(this);
    p_main_widget->resize(desk_rect.width()/7*6-5,desk_rect.height()/10*9-5);
    p_main_widget->move(desk_rect.width()/7+3,desk_rect.height()/10+3);
    p_main_widget->setStyleSheet("background-color:rgb(230,230,230)");

    p_treeView = new QTreeView(treewidget);
    p_treeView->setStyleSheet("QTreeView{border: 1px solid lightgray;}"
                                                                     "QTreeView::item {height: 40px;border-radius: 2px;"
                                                                     "border: 1px solid transparent;background: transparent;color: black;}"
                                                                     "QTreeView::item:has-children {border: none;border-bottom: 1px solid lightgray;}"
                                                                     "QTreeView::item:hover {border: 1px solid rgb(170, 190, 230);"
                                                                     "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(230, 240, 250),"
                                                                     "stop: 0.5 rgb(220, 235, 255), stop: 1.0 rgb(210, 230, 255));}"
                                                                     "QTreeView::item:selected {border: 1px solid rgb(230, 240, 250);"
                                                                     "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(230, 240, 250),"
                                                                     "stop: 0.5 rgb(220, 235, 255), stop: 1.0 rgb(210, 230, 255));});)");
    connect(p_treeView,&QTreeView::clicked,this,&MainWindow::onTreeviewClicked);
    p_treeView->setFixedSize(desk_rect.width()/7-5,desk_rect.height()/10*9-5);
    p_treeStandarModel = new QStandardItemModel(p_treeView);
    p_treeView->setModel(p_treeStandarModel);
    p_treeView->setFont(QFont("宋体",12));
    p_treeView->header()->hide();
    p_treeView->setEditTriggers(0);
    p_standarItem = new QStandardItem("用户管理");
    p_standarItem->setIcon(QIcon(":/resouse/Image/user.png"));
    p_userItem = new QStandardItem("权限管理");
    p_standarItem->appendRow(p_userItem);
    p_treeStandarModel->appendRow(p_standarItem);
    p_standarItem = new QStandardItem("设备管理");
    p_standarItem->setIcon(QIcon(":/resouse/Image/devices.png"));
    p_agvItem = new QStandardItem("小车管理");
    p_agvItem->setIcon(QIcon(":/resouse/Image/car.png"));
    p_standarItem->appendRow(p_agvItem);
    p_elevator = new QStandardItem("电梯管理");
    p_elevator->setIcon(QIcon(":/resouse/Image/elevator.png"));
    p_standarItem->appendRow(p_elevator);

    p_treeStandarModel->appendRow(p_standarItem);
    p_standarItem = new QStandardItem("货架管理");
    p_standarItem->setIcon(QIcon(":/resouse/Image/warehouset.png"));
    p_treeStandarModel->appendRow(p_standarItem);
    p_standarItem = new QStandardItem("报警管理");
    p_standarItem->setIcon(QIcon(":/resouse/Image/alarm_bell.png"));
    p_treeStandarModel->appendRow(p_standarItem);
    p_standarItem = new QStandardItem("日志管理");
    p_standarItem->setIcon(QIcon(":/resouse/Image/log.png"));
    p_treeStandarModel->appendRow(p_standarItem);

    p_standarItem = new QStandardItem("任务管理");
    p_standarItem->setIcon(QIcon(":/resouse/Image/tasks.png"));
    p_all_tasks = new QStandardItem("已完成任务");
    p_all_tasks->setIcon(QIcon(":/resouse/Image/all_tasks.png"));
    p_standarItem->appendRow(p_all_tasks);

    p_current_tasks = new QStandardItem("当前任务");
    p_current_tasks->setIcon(QIcon(":/resouse/Image/current_tasks.png"));
    p_standarItem->appendRow(p_current_tasks);
    p_treeStandarModel->appendRow(p_standarItem);


    user_btn = new QPushButton("用户",this);
    user_btn->setIcon(QIcon(":/resouse/Image/user.png"));
    user_btn->move(desk_rect.width()*0.85,desk_rect.height()/20);
   connect(user_btn,&QPushButton::clicked,this,&MainWindow::slotlogin);
    exit_btn = new QPushButton("安全退出",this);
    connect(exit_btn,&QPushButton::clicked,this,&MainWindow::closeWcs);
    exit_btn->setIcon(QIcon(":/resouse/Image/shutdown.png"));
    exit_btn->move(desk_rect.width()*0.9+20,desk_rect.height()/20);
    m_pstoreWg = nullptr;
}

void MainWindow::deleteChildrenList()
{
    QList<BaseFrom *> list = p_main_widget->findChildren<BaseFrom*>();
    if(list.size() == 0)
        return;
    foreach (BaseFrom* w, list) {
        w->hide();
        w->deleteLater();
    }
}

void MainWindow::getParameterFromDB()
{
    ReadTableData r;
    r.readt_device_info();
    r.readt_elevator();
    qDebug()<<Myconfig::GetInstance()->m_CarMap.size();
}

void MainWindow::getConfigParameter()
{
    QString currPath = QCoreApplication::applicationDirPath();
    QStringList list = currPath.split("/");
    if(list.size() > 1)
        list.removeAt(list.size()-1);
    QString absPath = list.join("/");
    MyIniConfig f;
    f.Config(absPath+"/config.ini");
    //QMutexLocker locker(&Myconfig::GetInstance()->m_mutex);
    Myconfig::GetInstance()->m_databaseInfo.databaseName = f.Get("DataBase","databaseName").toString();
    Myconfig::GetInstance()->m_databaseInfo.ip = f.Get("DataBase","ip").toString();
    Myconfig::GetInstance()->m_databaseInfo.passWord = f.Get("DataBase","passWord").toString();
    Myconfig::GetInstance()->m_databaseInfo.port = f.Get("DataBase","port").toInt();
    Myconfig::GetInstance()->m_databaseInfo.sqlName = f.Get("DataBase","sqlName").toString();
    Myconfig::GetInstance()->m_databaseInfo.userName = f.Get("DataBase","userName").toString();
    qDebug()<<"Myconfig::GetInstance()->m_databaseInfo";
}

void MainWindow::delay_msc(int msc)
{
    QEventLoop loop;
    QTimer::singleShot(msc,&loop,SLOT(quit()));
    loop.exec();
}

void MainWindow::onTreeviewClicked(const QModelIndex &index)
{
    deleteChildrenList();
    QString row_name = index.data().toString();
    if(row_name == "权限管理")
    {
        //qDebug()<<"handle 权限管理...";
        Myconfig::GetInstance()->InsertLog(0,"mainwindow","This test message is from MainWindow form");
    }
    else if(row_name == "小车管理")
    {
        AgvForm *car_from = new AgvForm(desk_rect.width()/7*6-5,desk_rect.height()/10*9-5,p_main_widget);
        car_from->resize(desk_rect.width()/7*6-5,desk_rect.height()/10*9-5);
        car_from->show();
    }
    else if(row_name == "货架管理")
    {
        //增加货架管理信息的界面
        m_pstoreWg = new StoreInfoWidget(p_main_widget);
        m_pstoreWg->show();
    }
    else if(row_name == "电梯管理")
    {
        ElevatorFrom *elevator = new ElevatorFrom(desk_rect.width()/7*6-5,desk_rect.height()/10*9-5,p_main_widget);
        elevator->resize(desk_rect.width()/7*6-5,desk_rect.height()/10*9-5);
        elevator->show();
    }
    else if(row_name == "当前任务")
    {
        CurrentTask *t = new CurrentTask(desk_rect.width()/7*6-5,desk_rect.height()/10*9-5,p_main_widget);
        t->resize(desk_rect.width()/7*6-5,desk_rect.height()/10*9-5);
        t->show();
    }
    else if(row_name == "已完成任务")
    {
        AllTask *t = new AllTask(desk_rect.width()/7*6-5,desk_rect.height()/10*9-5,p_main_widget);
        t->resize(desk_rect.width()/7*6-5,desk_rect.height()/10*9-5);
        t->show();
    }
}

void MainWindow::slotlogin()
{
    LoginInfoWg login;
    if (login.exec() == QDialog::Accepted)//调用login.exec()，阻塞主控制流，直到完成返回，继续执行主控制流
    {
        //获取当前用户信息和级别
        user_btn->setText(tr("admin"));
    }
}
