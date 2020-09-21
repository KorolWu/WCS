#include "logininfowg.h"
#include <QMessageBox>
#include <QAction>
#include <QGraphicsDropShadowEffect>
#include "datastructure.h"
#include <QBitmap>
#include <QPainter>
#include <QCryptographicHash>
#include <MysqlDataBase/readtabledata.h>

LoginInfoWg::LoginInfoWg(QWidget *parent) :QDialog(parent)
{
    this->setFixedSize(300,280);
   // this-> setWindowFlags (Qt::FramelessWindowHint);
 //   setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    //this->setAttribute(Qt::WA_TranslucentBackground);
   //this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor("#444444"));
    shadow->setBlurRadius(10);
    this->setGraphicsEffect(shadow);
  //  this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    this->setObjectName("myloginWidget");//border-radius:10px;
   this->setStyleSheet("QWidget#myloginWidget { background-image : url(:/resouse/Image/addDevice.png); }");
    //登录系统界面文字信息
    QLabel *wcsloginlabel = new QLabel(this);
    wcsloginlabel->move(90,35);
    wcsloginlabel->setText(tr("WCS用户登录系统"));
    wcsloginlabel->setObjectName("loginlabelob");
    wcsloginlabel->setStyleSheet("color: rgba(255, 255, 240,70%);font: 13pt;");
    //用户名输入框
    m_puserNameLEd = new QLineEdit(this);
    m_puserNameLEd->move(90,80);
    m_puserNameLEd->setPlaceholderText(tr("Username"));//占位符
    QAction *nameAction = new QAction( m_puserNameLEd);
    nameAction->setIcon(QIcon(":/resouse/Image/loginyusername.png"));
    m_puserNameLEd->addAction(nameAction,QLineEdit::LeadingPosition);
    m_puserNameLEd->setStyleSheet("background-color: rgba(255, 255, 224, 60%);border-radius:2px;border: 0px;font: 75 11pt \"宋体\";");
    m_puserNameLEd->setMaxLength(32);
    //密码输入框
    m_pwdLEd = new QLineEdit(this);
    m_pwdLEd->move(90,130);
    m_pwdLEd->setPlaceholderText("Password");
    m_pwdLEd->setEchoMode(QLineEdit::Password);//输入的密码以圆点显示
    QAction *passwdAction = new QAction( m_pwdLEd);
    passwdAction->setIcon(QIcon(":/resouse/Image/loginpasswd.png"));
    m_pwdLEd->addAction(passwdAction,QLineEdit::LeadingPosition);
    m_pwdLEd->setStyleSheet("background-color: rgba(255, 255, 224, 60%);border-radius:2px;border: 0px;font: 75 11pt \"宋体\";");
    m_pwdLEd->setMaxLength(32);
    //登录按钮
    m_loginBtn = new QPushButton(this);
    m_loginBtn->move(60,200);
    m_loginBtn->setText(tr("Login"));
    //m_loginBtn->setFlat(true);
    //退出按钮
    m_exitBtn = new QPushButton(this);
    m_exitBtn->move(180,200);
    m_exitBtn->setText(tr("Exit"));
    m_username = "user";
    //m_exitBtn->setFlat(true);
    //单击登录按钮时 执行 LoginForm::login 槽函数(自定义)；单击退出按钮时 执行 LoginForm::close 槽函数(窗体的关闭函数)
    connect(m_loginBtn,&QPushButton::clicked,this,&LoginInfoWg::login);
    connect(m_exitBtn,&QPushButton::clicked,this,&LoginInfoWg::close);
    QWidget::setTabOrder(m_puserNameLEd,m_pwdLEd);
    QWidget::setTabOrder(m_pwdLEd, m_loginBtn);
    m_loginBtn->setShortcut(QKeySequence::InsertParagraphSeparator);//将小键盘回车键与登录按钮绑定在一起
    m_loginBtn->setShortcut(Qt::Key_Enter);//将字母区回车键与登录按钮绑定在一起
    m_loginBtn->setShortcut(Qt::Key_Return);//将小键盘回车键与登录按钮绑定在一起
}

LoginInfoWg::~LoginInfoWg()
{

}

void LoginInfoWg::login()
{
    //获得m_puserNameLEd输入框的文本：m_puserNameLEd->text()；
    //trimmed()去掉前后空格
    //tr()函数，防止设置中文时乱码
    QString username = m_puserNameLEd->text().trimmed() ;
    QString passwd =  m_pwdLEd->text();
  //  MapLoginInfoStru userinfoMap;
   // bool usercheck = false;
    //直接查询数据库内容
//    for(auto it = userinfoMap.loginInfoMap.begin(); it !=  userinfoMap.loginInfoMap.end(); ++it)
//    {
//        if(username == it.key() )
//        {
//            QString passstr ;
//            passstr = QString(it.value().passwd) ;
//            if(passwd == passstr )
//            {
//                usercheck = true;
//               // if()

//                accept();//关闭窗体，并设置返回值为Accepted
//            }
//            break;
//        }
//    }
    ReadTableData databaseopob;
    char level = -1;
    //加密过程
    QCryptographicHash hash(QCryptographicHash::Md5);
    //放入原始数据
    hash.addData(passwd.toUtf8());
    //取出加密后的数据
    QByteArray arr = hash.result();
    //重新复制给passwd
    passwd = arr.toHex();
    //看一下加密后的数据
   // qDebug()<<"passwd"<<passwd;
    if(databaseopob.CheckUserInfo(level,username,passwd))
    {
        Myconfig::GetInstance()->m_curLoginlevel = level;
        m_username = username;
        accept();//关闭窗体，并设置返回值为Accepted
    }
    else
    {
        QMessageBox::warning(this, tr("警告！"),tr("用户名或密码错误！"),QMessageBox::Yes);
        // 清空输入框内容
        m_puserNameLEd->clear();
        m_pwdLEd->clear();
        //光标定位
        m_puserNameLEd->setFocus();
    }
}

void LoginInfoWg::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),15,15);
    setMask(bmp);
}

void LoginInfoWg::mouseMoveEvent(QMouseEvent *event)
{
    if(mouse_press){
        move(event->globalPos() - mousePoint);
    }
}

void LoginInfoWg::mousePressEvent(QMouseEvent *event)
{
    if( (event->button() == Qt::LeftButton) ){
        mouse_press = true;
        mousePoint = event->globalPos() - this->pos();
        //        event->accept();
    }
    else if(event->button() == Qt::RightButton){
        //如果是右键
        this->close();

    }
}

void LoginInfoWg::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    mouse_press = false;
}


