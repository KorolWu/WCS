#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <From/CarStatusFrom.h>
#include <QRect>
#include <QLabel>
#include <QPushButton>
#include <QTreeView>
#include <From/adddevice.h>

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
    QPushButton *exit_btn;
    QPushButton *user_btn;
    void closeWms();
};

#endif // MAINWINDOW_H
