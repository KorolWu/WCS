#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <From/CarStatusFrom.h>
#include <QRect>
#include <QLabel>
#include <QPushButton>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <From/adddevice.h>
#include <UnitClass/databaseunit.h>
#include <From/agvform.h>
#include <From/elevatorfrom.h>

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
    QTreeView *p_treeView;
    QPushButton *exit_btn;
    QPushButton *user_btn;
    QWidget *p_main_widget;
    void closeWms();
    void initUI();
private slots:
    void onTreeviewClicked(const QModelIndex &index);
};

#endif // MAINWINDOW_H
