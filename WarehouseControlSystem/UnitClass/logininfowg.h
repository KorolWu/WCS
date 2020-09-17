#ifndef LOGININFOWG_H
#define LOGININFOWG_H

#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMouseEvent>

class LoginInfoWg:public QDialog
{
    Q_OBJECT
public:
   explicit  LoginInfoWg(QWidget *parent = 0);
    ~LoginInfoWg();
    //当前用户信息
    QString GetUserName()
    {
        return m_username;
    }

public slots:
    void login();//点击登录按钮是执行的槽函数
protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    QPoint mousePoint;
    bool mouse_press;
private:
    QLabel *m_userNameLbl;         //"用户名"标签
    QLabel *m_pwdLbl;              //"密码"标签
    QLineEdit *m_puserNameLEd;      //用户名编辑行
    QLineEdit *m_pwdLEd;           //密码编辑行
    QPushButton *m_loginBtn;       //登录按钮
    QPushButton *m_exitBtn;        //退出按钮
private:
    QString m_username;
    QString m_passwd;
    };

#endif // LOGININFOWG_H
