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
#include <QLineEdit>
class CarStatusFrom : public QWidget
{
    Q_OBJECT
public:
    explicit CarStatusFrom(_Car_status carStatus, QWidget *parent = 0);

public slots:
    void fromClose();

private:
     int PAD_X = 550;
     int PAD_Y = 320;
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

    QPushButton *add_battery_btn;
    QPushButton *creat_fix_btn;
    QPushButton *sleep_btn;
    QLineEdit *position;
    QPushButton *move_btn;


    QPushButton *closeBtn;
    //QTimer* timer;
};

#endif // CarStatusFrom_H
