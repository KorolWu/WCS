#include "dispatchwidget.h"

DispatchWidget::DispatchWidget(int width, int height, QWidget *parent) : QWidget(parent)
{
    this->m_height = height;
    this->m_width = width;
    initUI();
}

void DispatchWidget::onBoxClicked()
{
    QPushButton *b = (QPushButton*)sender();
}

void DispatchWidget::onGetBoxClicked()
{

}

void DispatchWidget::initUI()
{
    initRightW();
    m_prightW->move(m_width - 250,10);
    m_poutWidget = new QWidget(this);
    m_poutWidget->setStyleSheet("QWidget{background-color:rgb(190,190,190);border-radius: 6px;}");
    m_poutWidget->resize(1300,m_height-10);
    m_poutWidget->move(10,10);
    QLabel *e = new QLabel(m_poutWidget);
    e->setText("BoxNumber:");
    e->move(20,50);
    m_poutButton = new QPushButton(m_poutWidget);
    m_poutButton->setText("GetBox");
    connect(m_poutButton,&QPushButton::clicked,this,&DispatchWidget::onGetBoxClicked);
    m_plineBoxNum = new QLineEdit(m_poutWidget);
    m_plineBoxNum->resize(200,30);
    m_plineBoxNum->move(100,50);
    m_poutButton->move(320,50);
    m_poutButton->setStyleSheet("QPushButton{font: 14px;width:100px;height:25;background-color:rgb(150,150,150);}QPushButton:hover{background: rgb(220, 220, 220);}QPushButton:pressed{background-color:rgb(85, 170, 255);}");

}

void DispatchWidget::initRightW()
{
    m_prightW = new QWidget(this);
    m_prightW->resize(160,m_height-10);
    m_pvbox_rightw = new QVBoxLayout(m_prightW);
    QFont font("宋体",12);
    for(int i = 0; i < 8; i++)
    {
        m_box_list[i] = new QPushButton();
        m_box_list[i]->setObjectName(QString("box_%1").arg(i));
        m_box_list[i]->setText(QString("A%1").arg(i));
        m_box_list[i]->setFont(font);
        connect(m_box_list[i],&QPushButton::clicked,this,&DispatchWidget::onBoxClicked);
        m_pvbox_rightw->addWidget(m_box_list[i]);
    }
    m_prightW->setLayout(m_pvbox_rightw);
    m_prightW->setStyleSheet("QPushButton{background-image: url(:/resouse/Image/no_box.png);}"
                             "QPushButton:hover{background-image: url(:/2.bmp);}"
                             "QPushButton:pressed{background-image: url(:/resouse/Image/have_box.png);}"
                             "QPushButton{width:70px;height:70;}"
                             "QWidget{background-color:rgb(190,190,190);border-radius: 5px;}");

}
