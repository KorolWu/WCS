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
#include <UnitClass/databaseunit.h>
#include <Forms/CarForms/agvform.h>
#include <Forms/ElevatorForms/elevatorfrom.h>
#include "Forms/TaskForms/currenttask.h"
#include "Forms/TaskForms/alltask.h"
#include <Forms/basefrom.h>
#include "Forms/StorePosInfo/storeinfowidget.h"
#include "Myconfig.h"
#include <../SDK/include/MysqlDataBase/readtabledata.h>
#include <../SDK/include/MysqlDataBase/crudbaseoperation.h>
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
    CarStatusFrom *f;
    QRect desk_rect;

    //treewidget
    QWidget *treewidget;
    QStandardItemModel *p_treeStandarModel;
    QStandardItem *p_standarItem;
    QStandardItem *p_userItem;
    QStandardItem *p_agvItem;
    QStandardItem *p_elevator;
    QStandardItem *p_all_tasks;
    QStandardItem *p_current_tasks;
    QTreeView *p_treeView;
    QPushButton *exit_btn;
    QPushButton *user_btn;
    QWidget *p_main_widget;
    void closeWms();
    void initUI();
    void deleteChildrenList();
    void getParameterFromDB();
private slots:
    void onTreeviewClicked(const QModelIndex &index);
    void  slotlogin();

private:
    StoreInfoWidget *m_pstoreWg;
};

#endif // MAINWINDOW_H
