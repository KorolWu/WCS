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
    m_ptest = new QPushButton(m_pmain);
    m_ptest->setText("----");
    m_ptest->resize(50,80);
    m_pmain->setStyleSheet("background-color: rgb(18, 62, 111, 40);");
}
