#ifndef USERINFOWG_H
#define USERINFOWG_H

#include <QObject>
#include <QWidget>

class UserInfoWg:public QWidget
{
    Q_OBJECT

public:
    UserInfoWg(int width,int height,QWidget *parent = 0);
    ~UserInfoWg();
private:

};

#endif // USERINFOWG_H
