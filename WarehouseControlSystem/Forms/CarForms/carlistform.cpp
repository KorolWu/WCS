#include "carlistform.h"

CarListForm::CarListForm(int width, int height, QWidget *parent):QWidget(parent)
{
    this->m_width = width;
    this->m_height = height;
    m_pressflag = false;
    m_InfoVec.clear();
    initUi();

}

void CarListForm::initUi()
{
    m_pMainWidget = new QWidget(this);
    m_pMainWidget->setObjectName("KWidget");
    m_pMainWidget->resize(m_width,m_height);
    QFont m_font ("Times", 20);
    m_pHeadLabel = new QLabel(m_pMainWidget);
    m_pHeadLabel->resize(m_width,m_height/7);
    m_pHeadLabel->setStyleSheet("background-color:rgb(24, 24, 72)");
    m_pInfoLabel = new QLabel("设备列表",m_pMainWidget);
    m_pInfoLabel->setObjectName("headLabel");
    m_pInfoLabel->setStyleSheet("color:white");
    m_pInfoLabel->setFont(m_font);
    m_pInfoLabel->setAttribute(Qt::WA_TranslucentBackground, true);
    m_pInfoLabel->move(10,10);
     QStringList list;
     list<<"全部"<<"在线"<<"离线"<<"异常"<<"维修";
    int interval = 65;
    QFont m_font_l ("Times", 12);
    for(int i = 0;i< 5;i++)
    {
         QLabel *l = new QLabel("asd",m_pMainWidget);
         l->setStyleSheet("color:white");
         l->setText(list[i]);
         l->move(interval*i+interval-20, m_height/7*0.6);
         l->setAttribute(Qt::WA_TranslucentBackground, true);
         l->setFont(m_font_l);
    }

    for(int i = 0;i < 5;i ++)
    {
        QLabel *b = new QLabel(m_pMainWidget);
        b->setStyleSheet("color:white");
        b->setAttribute(Qt::WA_TranslucentBackground, true);
        b->move(interval*i+interval-10,m_height/7*0.8);
        b->setText("0");
        b->setFont(m_font_l);
        m_InfoVec.append(b);
    }
    QStringList list_h;
    list_h<<"设备编号"<<"状态"<<"设备任务"<<"执行状态"<<"电量";
    interval = 70;
    QFont m_font_s ("Times", 10);
    for(int i = 0;i <5;i++)
    {
        QLabel *e = new QLabel(m_pMainWidget);
        e->setAttribute(Qt::WA_TranslucentBackground, true);
        if(i == 0)
            e->move(10,m_height/7*1.1);
        else if(i == 2)
            e->move(interval*i+10,m_height/7*1.1);
        else if(i == 4)
            e->move(interval*i+40,m_height/7*1.1);
        else
            e->move(interval*i+30,m_height/7*1.1);
        e->setStyleSheet("color:black");
        e->setFont(m_font_s);
        e->setText(list_h[i]);

    }
    auto it = Myconfig::GetInstance()->m_CarMap.begin();
    for(int i = 0;i < Myconfig::GetInstance()->m_CarMap.size();i++)
    {
        //createListWidget(it.value())->move(5,m_height/5+i*60);
        CarStatusWidget *f = new CarStatusWidget(m_width,it.value(),m_pMainWidget);
        f->move(5,m_height/5+i*60);
        it++;
    }
    this->setStyleSheet("#KWidget{background-color:rgb(210, 210, 210)}");
}

void CarListForm::mousePressEvent(QMouseEvent *event)
{
    m_pressflag = true;
    m_beginP = event->globalPos();
    m_windowP = this->frameGeometry().topLeft();
    QWidget::mousePressEvent(event);
}

void CarListForm::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressflag = true;
    QWidget::mouseReleaseEvent(event);
}

void CarListForm::mouseMoveEvent(QMouseEvent *event)
{
    if(m_pressflag)
    {
        QPoint relativePos = event->globalPos() - m_beginP;
        this->move(m_windowP + relativePos );
    }
    QWidget::mouseMoveEvent(event);
}


CarStatusWidget::CarStatusWidget(int width, CarInfoStru c, QWidget *parent) :QWidget(parent)
{
    m_pCar = nullptr;
    //m_pParent = parent;
    QWidget *w = new QWidget(this);
    this->m_car = c;
    int interval = 50;
    int y = 10;
    w->resize(width-10,40);
    QFont font("Times", 9 ,QFont::Bold);
    QLabel *numLab = new QLabel(c.deviceNum,w);
    numLab->setAttribute(Qt::WA_TranslucentBackground, true);
    numLab->setFont(font);
    numLab->move(10,y);

    QLabel *staLab = new QLabel(c.deveceStatus.isOnline? "在线":"离线",w);
    staLab->setAttribute(Qt::WA_TranslucentBackground, true);
    staLab->move(interval*2,y);
    QLabel *taskLab = new QLabel("---",w);
    taskLab->setAttribute(Qt::WA_TranslucentBackground, true);
    taskLab->move(interval*3+10,y);
    QString status = "";
    if(c.deveceStatus.status == 0)
        status = " 待命中";
    else if(c.deveceStatus.status == 1)
        status  = "工作中";
    else
        status  = " 故障";
    QLabel *workLab = new QLabel(status,w);
    workLab->setAttribute(Qt::WA_TranslucentBackground, true);
    workLab->move(interval*5-10,y);
    QString batter = QString("%1%").arg(c.deveceStatus.batter);
    QLabel *beterLab = new QLabel(batter,w);
    beterLab->setAttribute(Qt::WA_TranslucentBackground, true);
    beterLab->move(interval*6+20,y);
    w->setStyleSheet("QWidget:hover{background-color:white; color: black;}QWidget:pressed{background-color:rgb(85, 170, 255);}");
}

void CarStatusWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    //QWidget *w = qobject_cast<QWidget *>(m_pParent);
    m_pCar = new CarStatusFrom(m_car);
    QRect  desktop =  QApplication::desktop()->availableGeometry();
    m_pCar->move(desktop.width()/2,desktop.height()/2);
    m_pCar->show();
    QWidget::mouseDoubleClickEvent(event);
}
