#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <datastructure.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1500,1000);
    _Car_status s;
    s.batter = 70;
    s.carNum = "ABS-002";
    f = new CarStatusFrom(s,this);
    f->move(10,10);

}

MainWindow::~MainWindow()
{
    delete ui;
}
