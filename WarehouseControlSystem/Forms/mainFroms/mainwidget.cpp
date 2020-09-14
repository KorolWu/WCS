#include "mainwidget.h"

MainWidget::MainWidget(int width, int height, QWidget *parent) : QWidget(parent)
{
    this->m_width = width;
    this->m_height = height;
    initUI();

}

void MainWidget::initUI()
{
    m_pmain = new QWidget(this);
    m_pmain->resize(m_width,m_height);
    qDebug()<<m_width<<"**"<<m_height;
    m_pgridlayout = new QGridLayout();
    m_piew = new CPieWidget(m_width/2,m_height/2);
    m_piew->setPieStyleSheet((PieStyle)8);
    m_piew->update();
    m_pgridlayout->addWidget(m_piew,0,0,1,1);
    m_tchar = new TorqueChart(m_width/2,m_height/2);
    m_pgridlayout->addWidget(m_tchar,0,1,1,1);

    m_perrwidget = new CPieWidget(m_width/2,m_height/2);
    SetErrwidgetInfo();
    m_perrwidget->setPieStyleSheet((PieStyle)3);
    m_perrwidget->update();
    m_pgridlayout->addWidget(m_perrwidget,1,1,1,1);

    m_profileWidget = new WarehouseprofileInfoShowWg(m_width/2,m_height/2);
    m_pgridlayout->addWidget(m_profileWidget,1,0,1,1);



    m_pmain->setLayout(m_pgridlayout);
    m_pmain->setStyleSheet("background-color: rgb(18, 62, 111, 40);");
}

void MainWidget::SetErrwidgetInfo()
{
    m_colorlist << QColor(116,169,26);
    m_colorlist << QColor(201,64,73);
    m_colorlist << QColor(210,151,153);
    m_colorlist << QColor(77,82,175);
    m_colorlist << QColor(158,102,155);
    m_colorlist << QColor(172,126,126);
    m_colorlist << QColor(90,179,86);
    QHash<QString,float> data;
    data.insert("car",6);
    data.insert("logic",3);
    data.insert("elevator",2);
    data.insert("runner",5);
    data.insert("wms",1);
    m_perrwidget->setColors(m_colorlist);
    m_perrwidget->setData(data);
}
