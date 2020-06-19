#include "currenttask.h"

CurrentTask::CurrentTask(int width,int height,QWidget *parent):BaseFrom(parent)
{
    this->width = width;
    this->height = height;
//    m_in_btn = new QPushButton("只看入库",this);
//    m_in_btn->setIcon(QIcon(":/resouse/Image/in.png"));
//    //connect(m_in_btn,&QPushButton::clicked,this,&CurrentTask::onAddClicked);
//    m_in_btn->move(5,10);
//    m_out_btn= new QPushButton("只看出库",this);
//    //connect(m_out_btn,&QPushButton::clicked,this,&CurrentTask::onDeleteClicked);
//    m_out_btn->setIcon(QIcon(":/resouse/Image/out.png"));
//    m_out_btn->move(150,10);
//    m_all_btn= new QPushButton("查看全部",this);
//    m_all_btn->move(300,10);
//    m_all_btn->setIcon(QIcon(":/resouse/Image/all.png"));

//    m_start_date = new QDateEdit(this);
//    m_start_date->setCalendarPopup(true);
//    m_start_date->move(450,10);
//    QLabel *l = new QLabel(this);
//    l->setText("-");
//    l->move(580,10);
//    m_end_date = new QDateEdit(this);
//    m_end_date->setCalendarPopup(true);
//    m_end_date->move(600,10);

//    m_query_btn = new QPushButton("查询",this);
//    m_query_btn->move(750,10);
//    m_query_btn->setStyleSheet("background-color:rgb(0,170,255)");
//    this->setStyleSheet("QPushButton{font: 14px;width:100px;height:25;}QLabel{font: 16px}QDateEdit{width:100px;height:25px}");
    initTableView();
}

void CurrentTask::setTableViewValue()
{
    int row_count = Myconfig::GetInstance()->m_taskMap.size();
    for(int j = 0; j< 8 ;j++)
    {
        auto it = Myconfig::GetInstance()->m_taskMap.begin();
        for(int i = 0;i<row_count;i++)
        {
            if(j == 111)
                model->setItem(i,j,new QStandardItem(QString("%1").arg(i)));
            else if(j == 0)
                model->setItem(i,j,new QStandardItem(it.value().taskNum));
            else if(j == 1)
                model->setItem(i,j,new QStandardItem(it.value().status));
            else if(j == 2)
                model->setItem(i,j,new QStandardItem(it.value().boxNum));
            else if(j == 3)
                model->setItem(i,j,new QStandardItem(QString("%1").arg(it.value().pripty)));
            else if(j == 4)
                model->setItem(i,j,new QStandardItem(it.value().from));
            else if(j == 5)
                model->setItem(i,j,new QStandardItem(it.value().end));
            else if(j == 6)
                model->setItem(i,j,new QStandardItem(it.value().carNum));
            else if(j == 7)
                model->setItem(i,j,new QStandardItem(it.value().creatTime.toString()));
            it ++;
        }
    }
}

void CurrentTask::initTableView()
{
    m_table_view = new QTableView(this);
    m_table_view->horizontalHeader()->setStyleSheet(headstlye);
    m_table_view->move(5,10);
    m_table_view->verticalHeader()->hide();
    m_table_view->resize(width,height);

    model = new QStandardItemModel(10,8);
    m_table_view->setModel(model);

    m_table_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table_view->setEditTriggers(QAbstractItemView::AllEditTriggers);

    QStringList header;
    header<<"任务号"<<"任务状态"<<"料箱号"<<"优先级"<<"来源"<<"目标"<<"穿梭车号"<<"创建时间";
    for(int i = 0 ;i <header.size();i++)
    {
        model->setHeaderData(i, Qt::Horizontal, header.at(i));
    }
    m_table_view->setColumnWidth(0,width/20*1);
    m_table_view->setColumnWidth(1,width/20*2);
    m_table_view->setColumnWidth(2,width/20*3);
    m_table_view->setColumnWidth(3,width/20*2);

    m_table_view->setColumnWidth(4,width/20*2);
    m_table_view->setColumnWidth(5,width/20*2);
    m_table_view->setColumnWidth(6,width/20*2);
    m_table_view->setColumnWidth(7,width/20*3);
    m_table_view->horizontalHeader()->setMinimumHeight(40);
    m_table_view->setFont(QFont("宋体",12)); //设置字体
}

void CurrentTask::handelHttpTask(QString reply)
{
    //taskNum=00263&status=Wait&boxNum=Box-0900&pripty=1&from=wms&end=5-58-1&carNum=3&creatTime=2020-06-1715%3A40%3A09
    QStringList list = reply.split("&");
    for(int i = 0 ;i <list.size();i++)
    {
        list[i] = QString(list[i]).mid(QString(list[i]).indexOf("=")+1);
    }
    qDebug()<<list;
    TaskInfoStru t;
    if(list.size() != 8)
        return;
    t.taskNum  = list[0];
    t.status  = list[1];
    t.boxNum = list[2];
    t.pripty = QString(list[3]).toInt();
    t.from = list[4];
    t.end = list[5];
    t.carNum = list[6];
    t.creatTime = QDateTime::currentDateTime();
    Myconfig::GetInstance()->m_taskMap.insert(t.taskNum,t);
    setTableViewValue();

}
