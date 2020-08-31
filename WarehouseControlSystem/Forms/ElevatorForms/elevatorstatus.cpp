#include "elevatorstatus.h"

ElevatorStatusWidget::ElevatorStatusWidget(int elevatorId, QWidget *parent) : QWidget(parent)
{
    this->m_elevatorId = elevatorId;
    this->resize(400,300);
    //this->setStyleSheet("background-color:white;");
    initUI();
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
    v->addLayout(h);
    v->addStretch();
    m_pMove = new QPushButton("Move");
    connect(m_pMove,&QPushButton::clicked,this,&ElevatorStatusWidget::onMove);
    m_pOrder_layer = new QSpinBox();
    h = new QHBoxLayout();
    h->addWidget(m_pMove);
    h->addWidget(m_pOrder_layer);
    v->addLayout(h);
    v->addStretch();
    this->setLayout(v);

}

void ElevatorStatusWidget::onMove()
{

}
