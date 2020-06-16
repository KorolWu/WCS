#include "alltask.h"

AllTask::AllTask(int width, int height, QWidget *parent):BaseFrom(parent)
{
        this->width = width;
        this->height = height;
        m_in_btn = new QPushButton("只看入库",this);
        m_in_btn->setIcon(QIcon(":/resouse/Image/in.png"));
        //connect(m_in_btn,&QPushButton::clicked,this,&CurrentTask::onAddClicked);
        m_in_btn->move(5,10);
        m_out_btn= new QPushButton("只看出库",this);
        //connect(m_out_btn,&QPushButton::clicked,this,&CurrentTask::onDeleteClicked);
        m_out_btn->setIcon(QIcon(":/resouse/Image/out.png"));
        m_out_btn->move(150,10);
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
        this->setStyleSheet("QPushButton{font: 14px;width:100px;height:25;}QLabel{font: 16px}QDateEdit{width:100px;height:25px}");
        initTableView();
}

void AllTask::initTableView()
{
    m_table_view = new QTableView(this);
    m_table_view->move(5,60);
    m_table_view->verticalHeader()->hide();
    m_table_view->resize(width,height);

    model = new QSqlTableModel();
    model->setTable("t_all_task");
    m_table_view->setModel(model);
    model->select();
    m_table_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table_view->setEditTriggers(QAbstractItemView::AllEditTriggers);


    QStringList header;
    header<<"ID"<<"任务号"<<"任务状态"<<"料箱号"<<"优先级"<<"来源"<<"目标"<<"穿梭车号"<<"创建时间"<<"结束时间";
    for(int i = 0 ;i <header.size();i++)
    {
        model->setHeaderData(i, Qt::Horizontal, header.at(i));
    }
    m_table_view->setColumnWidth(0,width/20*1);
    m_table_view->setColumnWidth(1,width/20*2);
    m_table_view->setColumnWidth(2,width/20*2);
    m_table_view->setColumnWidth(3,width/20*2);

    m_table_view->setColumnWidth(4,width/20*2);
    m_table_view->setColumnWidth(5,width/20*2);
    m_table_view->setColumnWidth(6,width/20*2);
    m_table_view->setColumnWidth(7,width/20*1);
    m_table_view->setColumnWidth(8,width/20*3);
    m_table_view->setColumnWidth(9,width/20*3);
    m_table_view->horizontalHeader()->setMinimumHeight(40);
    m_table_view->setFont(QFont("宋体",13)); //设置字体
}
