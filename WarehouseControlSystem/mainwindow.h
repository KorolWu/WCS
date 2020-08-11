#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Forms/CarForms/CarStatusFrom.h>
#include <QRect>
#include <QLabel>
#include <QPushButton>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <Forms/CarForms/adddevice.h>
#include <Forms/CarForms/agvform.h>
#include <Forms/ElevatorForms/elevatorfrom.h>
#include "Forms/TaskForms/currenttask.h"
#include "Forms/TaskForms/alltask.h"
#include "Forms/TaskForms/subtask.h"
#include <Forms/basefrom.h>
#include "Forms/StorePosInfo/storeinfowidget.h"
#include "Forms/LogForms/logforms.h"
#include <QTimer>
#include <QEventLoop>
#include <MysqlDataBase/readtabledata.h>
#include <MysqlDataBase/crudbaseoperation.h>
#include <QCoreApplication>
#include <QDir>
#include "UnitClass/c_systemlogmng.h"
#include "UnitClass/logmanager.h"
#include "UnitClass/khttpserver.h"
#include "JQHttpServer.h"
#include "ControlClass/basedevice.h"
#include "KDeviceSingleton.h"
#include "datastructure.h"
#include "Forms/CarForms/carlistform.h"
#include "Forms/AlarmInfo/alarminfowg.h"
#include "Forms/Runner/runerform.h"
#include "ControlClass/dispatchcenter.h"
#include "MointorUI/monitorui.h"
#include"SimulationgenerationtaskUI/testcreateorderspath.h"
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QRect desk_rect;
    QWidget *treewidget;
    QStandardItemModel *p_treeStandarModel;
    QStandardItem *p_standarItem;
    QStandardItem *p_userItem;
    QStandardItem *p_ordersItem;
    QStandardItem *p_agvItem;
    QStandardItem *p_elevator;
    QStandardItem *p_runer;
    QStandardItem *p_all_tasks;
    QStandardItem *p_current_tasks;
    QStandardItem *p_sub_tasks;
    QTreeView     *p_treeView;
    QPushButton   *exit_btn;
    QPushButton   *user_btn;
    QWidget       *p_main_widget;
    CurrentTask   *t;
    AlarmInfoWg *m_palarmWg;
    LogForms      *m_pLog;
    AgvForm       *car_from;
    AllTask       *m_pTaskAll;
    SubTask       *m_pSubTask;
    ElevatorFrom  *p_mElevator;
    RunerForm     *p_mRunerForm;
    CarListForm   *p_mCarList;
    QThread       *p_mDispatchThread;
    JQHttpServer::TcpServerManage *m_pHttpServer;

    void closeWcs();
    void initUI();
    void initDeviceClient();
    void deleteChildrenList();
    void getParameterFromDB();
    void getConfigParameter();
    void delay_msc(int msc);
private slots:
    void onTreeviewClicked(const QModelIndex &index);
    void slotlogin();
    void onReplyReady(QString str);


private:
    StoreInfoWidget *m_pstoreWg;
    MonitorUI *m_pmonitorui;
    //test
    TestcreateOrdersPath *m_testorders;
signals:
    void httpRedReady(QString str);
    void dispatched();
};

#endif // MAINWINDOW_H
