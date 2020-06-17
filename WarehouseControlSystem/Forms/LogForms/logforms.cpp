#include "logforms.h"

LogForms::LogForms(int width, int height,QWidget *parent):BaseFrom(parent)
{
    this->width = width;
    this->height = height;
    QLabel *q = new QLabel("来源",this);
    q->move(5,10);
    m_com_box = new QComboBox(this);
    m_com_box->setToolTip("--select--");
    m_com_box->addItems(QStringList("--select--"));

    m_com_box->move(100,10);
    m_all_btn= new QPushButton("查看全部",this);
    m_all_btn->move(300,10);
    m_all_btn->setIcon(QIcon(":/resouse/Image/all.png"));

    m_start_date = new QDateEdit(this);
    m_start_date->setDateTime(QDateTime::currentDateTime());
    m_start_date->setCalendarPopup(true);
    m_start_date->move(450,10);
    QLabel *l = new QLabel(this);
    l->setText("-");
    l->move(580,10);
    m_end_date = new QDateEdit(this);
    m_end_date->setDateTime(QDateTime::currentDateTime());
    m_end_date->setCalendarPopup(true);
    m_end_date->move(600,10);

    m_query_btn = new QPushButton("查询",this);
    m_query_btn->move(750,10);
    m_query_btn->setStyleSheet("background-color:rgb(0,170,255)");
    this->setStyleSheet("QPushButton{font: 14px;width:100px;height:25;}QLabel{font: 16px}QDateEdit{width:100px;height:25px}QComboBox{width:120px;height:25px}");
    initTableView();
}

void LogForms::initTableView()
{
    m_table_view = new QTableView(this);
    m_table_view->move(5,60);
    m_table_view->verticalHeader()->hide();
    m_table_view->resize(width,height);

    model = new QSqlTableModel();
    model->setTable("t_log");
    m_table_view->setModel(model);
    model->select();
    m_table_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table_view->setEditTriggers(QAbstractItemView::AllEditTriggers);


    QStringList header;
    header<<"ID"<<"等级"<<"来自"<<"信息"<<"时间";
    for(int i = 0 ;i <header.size();i++)
    {
        model->setHeaderData(i, Qt::Horizontal, header.at(i));
    }
    m_table_view->setColumnWidth(0,width/20*2);
    m_table_view->setColumnWidth(1,width/20*2);
    m_table_view->setColumnWidth(2,width/20*3);
    m_table_view->setColumnWidth(3,width/20*8);
    m_table_view->setColumnWidth(4,width/20*4);
    m_table_view->horizontalHeader()->setMinimumHeight(40);
    m_table_view->setFont(QFont("宋体",12)); //设置字体
}
