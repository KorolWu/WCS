#ifndef CarStatusFrom_H
#define CarStatusFrom_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <QFont>
#include <QPixmap>
#include <QVBoxLayout>
#include <QTimer>
#include <QApplication>
#include <QDesktopWidget>
#include <QTableWidget>
#include <datastructure.h>
#include <QPushButton>
#include <QTableView>
#include <QHeaderView>
#include <QScrollBar>
class CarStatusFrom : public QWidget
{
    Q_OBJECT
public:
    explicit CarStatusFrom(_Car_status carStatus, QWidget *parent = 0);

public slots:
    void fromClose();

private:
//    const int PAD_X = 640;
//    const int PAD_Y = 420;
     int PAD_X = 550;
     int PAD_Y = 600;
    QRect desktop;
    QLabel *header_lab;
    QLabel *car_image;
    QLabel *car_number;
    QLabel *battery_lab;
    QLabel *battery_image;
    QLabel *online_image;
    QLabel *online_lab;
    QLabel *l ;

    QTableWidget *table;
    QPushButton *delete_btn;
    QPushButton *canlen_btn;
    QPushButton *up_btn;
    QPushButton *down_btn;
    QPushButton *pause_btn;
    QPushButton *continue_btn;
    //QPushButton *delete_btn;

    QPushButton *closeBtn;
    //QTimer* timer;
};

#endif // CarStatusFrom_H
