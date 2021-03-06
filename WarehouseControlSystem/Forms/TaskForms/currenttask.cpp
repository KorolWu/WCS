#include "currenttask.h"

CurrentTask::CurrentTask(int width,int height,QWidget *parent):BaseFrom(parent)
{
    this->width = width;
    this->height = height;
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
                model->setItem(i,j,new QStandardItem(it.value().creatTime.toString("yyyy-MM-dd hh:mm:ss")));
            it ++;
        }
    }
}

void CurrentTask::refreshTable()
{
    setTableViewValue();
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
//save to crruntTask table
bool CurrentTask::saveTaskToDB(TaskInfoStru taskStru)
{
    QString err = "";
    if(!CRUDBaseOperation::getInstance()->saveCrruntTask(taskStru,err))
    {
        GetSystemLogObj()->writeLog(err,3);
        return false;
    }
    return true;

}

void CurrentTask::handelHttpTask(QString reply)
{
    //taskNum=00263&status=Wait&boxNum=Box-0900&pripty=1&from=wms&end=5-58-1&carNum=3&creatTime=2020-06-1715%3A40%3A09
    QStringList list = reply.split("&");
    for(int i = 0 ;i <list.size();i++)
    {
        list[i] = QString(list[i]).mid(QString(list[i]).indexOf("=")+1);
    }
    //qDebug()<<list;
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
    //saveTaskToDB(t);
    if(t.taskNum.contains("O"))
    {
        QMutexLocker locker(&Myconfig::GetInstance()->m_task_mutex);
        Myconfig::GetInstance()->m_taskQueue.enqueue(t);
    }
    else
    {
         QMutexLocker(&Myconfig::GetInstance()->m_in_task_mutex);
         Myconfig::GetInstance()->m_in_taskMap.insert(t.boxNum,t);
         qDebug()<<"添加入库任务";
    }
    QMutexLocker(&Myconfig::GetInstance()->m_mutex_taskMap);
    Myconfig::GetInstance()->m_taskMap.insert(t.taskNum,t);
    QString errMsg = "";
//    if(!CRUDBaseOperation::getInstance()->saveKBaseStruct("t_crrunt_task",t,errMsg))
//        GetSystemLogObj()->writeLog("save current to dbbase failed! ->"+errMsg,2);
    setTableViewValue();
    qDebug()<<reply;

}
