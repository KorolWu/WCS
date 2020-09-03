#include "elevatorstatus.h"
#include <QFile>

ElevatorStatusWidget::ElevatorStatusWidget(int elevatorId, QWidget *parent) : QWidget(parent)
{
    this->m_elevatorId = elevatorId;
    this->resize(400,300);
    //this->setStyleSheet("background-color:white;");

    QFile file(":/resouse/warehouse.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    this->setStyleSheet(stylesheet);
    file.close();
    m_ptimer = new QTimer(this);
    connect(m_ptimer,&QTimer::timeout,this,&ElevatorStatusWidget::updateStatus);
    initUI();
    m_ptimer->start(500);
}

void ElevatorStatusWidget::updateStatus()
{
    Myconfig::GetInstance()->m_elevatorMap[m_elevatorId].status.isOnline? m_pOnline_image->setStyleSheet("border-image:url(:/resouse/Image/green.png)"):m_pOnline_image->setStyleSheet("border-image:url(:/resouse/Image/grey.png)");
    m_pCurrent_layer->setValue(Myconfig::GetInstance()->m_elevatorMap[m_elevatorId].status.curruntLayer);
    m_pcurachelayer->setValue(Myconfig::GetInstance()->m_elevatorMap[m_elevatorId].status.curachelayer);

}

void ElevatorStatusWidget::initUI()
{
    v = new QVBoxLayout(this);
    v->addStretch();
    QHBoxLayout *h = new QHBoxLayout();
    QLabel *l = new QLabel("ID :");
    QLabel *i = new QLabel(QString("%1").arg(m_elevatorId));
    h->addWidget(l);
    h->addStretch();
    h->addWidget(i);
    h->addStretch();
    m_pOnline_image = new QLabel();
    m_pOnline_image->resize(5,5);
    m_pOnline_image->setStyleSheet("border-image:url(:/resouse/Image/grey.png)");
    m_pOnline_lab = new QLabel("在线");
    h->addWidget(m_pOnline_lab);
    h->addStretch();
    h->addWidget(m_pOnline_image);
    h->addStretch();
    v->addLayout(h);
    v->addStretch();
    h = new QHBoxLayout();
    QLabel *c = new QLabel("当前层 :");
    m_pCurrent_layer = new QSpinBox();
    h->addWidget(c);
    h->addWidget(m_pCurrent_layer);
    QLabel *e = new QLabel("缓存层");
    m_pcurachelayer = new QSpinBox();
    h->addWidget(e);
    h->addWidget(m_pcurachelayer);
    v->addLayout(h);
    v->addStretch();

    m_pSelectRadioButton = new QRadioButton("立库");
    m_pSelectRadioButton->resize(50,30);
    m_pMove = new QPushButton("Move");
    connect(m_pMove,&QPushButton::clicked,this,&ElevatorStatusWidget::onMove);
    m_pOrder_layer = new QSpinBox();
    h = new QHBoxLayout();
    h->addWidget(m_pSelectRadioButton);
    h->addWidget(m_pMove);
    h->addWidget(m_pOrder_layer);
    v->addLayout(h);
    v->addStretch();
    this->setLayout(v);

}

void ElevatorStatusWidget::onMove()
{
    OrderStru o;
    o.z = m_pOrder_layer->value();
    o.order = Call;
    if(m_pSelectRadioButton->isChecked())
        o.startaddress = 1;
    else
        o.startaddress = 2;
    o.Datatype = 4;
    o.childtype = 2;
    AbstructInstruction *e = new CarElevatorInstruction();
    e->setParameter(o,21);
    e->runInstruction();
    QString resultMsg ="";
    e->getResult(resultMsg);
    qDebug()<<resultMsg;
}
