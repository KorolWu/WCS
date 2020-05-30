#ifndef ADDDEVICE_H
#define ADDDEVICE_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <datastructure.h>
#include <UnitClass/databaseunit.h>
class AddDevice : public QWidget
{
    Q_OBJECT
public:
    explicit AddDevice(QWidget *parent = 0);

signals:
private:
    QWidget *w;
    QLineEdit *deviceNum;
    QLineEdit *deviceIp;
    QLineEdit *port;
    QLineEdit *deviceType;
    QLineEdit *remarks;
    QPushButton *yesBtn;
    QPushButton *calenBtn;
    QHBoxLayout *hbox;
    QVBoxLayout *vbox;
    AddDeviceStu deviceStruct;
    void addDevices();
};

#endif // ADDDEVICE_H
