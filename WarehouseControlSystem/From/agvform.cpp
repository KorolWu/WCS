#include "agvform.h"
#include <QHeaderView>
#include <QIcon>
#include <QDesktopWidget>
#include <QApplication>
#include <QModelIndex>
#include <QProgressBar>
AgvForm::AgvForm(int width, int height, QWidget *parent) : BaseFrom(parent)
{
    p_car_info = nullptr;
    p_add_btn = new QPushButton("添加",this);
    p_add_btn->setIcon(QIcon(":/resouse/Image/add.png"));
    connect(p_add_btn,&QPushButton::clicked,this,&AgvForm::onAddClicked);
    p_add_btn->move(5,15);
    p_delete_btn= new QPushButton("删除",this);
    p_delete_btn->setIcon(QIcon(":/resouse/Image/delete.png"));
    p_delete_btn->move(100,15);
    p_export_btn= new QPushButton("导出",this);
    p_export_btn->move(200,15);
    p_export_btn->setIcon(QIcon(":/resouse/Image/download.png"));

    QLabel *text_lable = new QLabel("设备编号:",this);
    text_lable->move(350,15);
    text_lable->setAlignment(Qt::AlignBottom);
    p_input_text = new QLineEdit(this);
    p_input_text->resize(150,30);
    p_input_text->move(440,15);
    p_query_btn = new QPushButton("查询",this);
    p_query_btn->move(610,15);
    p_query_btn->setStyleSheet("background-color:rgb(80,133,212)");


    p_table_view = new QTableView(this);//18,7,
    connect(p_table_view,&QTableView::clicked,this,&AgvForm::tableRowClicked);
    p_table_view->move(5,60);
    p_table_view->verticalHeader()->hide();
    p_table_view->resize(width,height);
    // set tableWidget no edit
   p_table_view->setEditTriggers(QAbstractItemView::AllEditTriggers);
   p_table_view->setSelectionBehavior(QAbstractItemView::SelectRows);

//    QSqlQueryModel *model = new QSqlQueryModel;
//    model->setQuery("select *from t_device_info;");
//    model->query();
//    p_table_view->setModel(model);
    model = new QSqlTableModel();
    model->setTable("t_device_info");
    model->select();
    p_table_view->setModel(model);
    p_table_view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    LabelDelegate *delegate_lab = new LabelDelegate();
    p_table_view->setItemDelegateForColumn(6,delegate_lab);
    ProgressBarDelegate *delegate_progressBar = new ProgressBarDelegate(this);
    p_table_view->setItemDelegateForColumn(5,delegate_progressBar);

    QStringList header;
    header<<"ID"<<"穿梭车编号"<<"通讯地址"<<"端口号"<<"类型"<<"电量"<<"状态"<<"位置"<<"工作模式"<<"运行操作";
    for(int i = 0 ;i <header.size();i++)
    {
        model->setHeaderData(i, Qt::Horizontal, header.at(i));
    }

    p_table_view->setColumnWidth(0,width/20*2);
    p_table_view->setColumnWidth(1,width/20*3);
    p_table_view->setColumnWidth(2,width/20*2.5);
    p_table_view->setColumnWidth(3,width/20*4);

    p_table_view->setColumnWidth(4,width/20*2);
    p_table_view->setColumnWidth(5,width/20*3);
    p_table_view->setColumnWidth(6,width/20*3);
    p_table_view->horizontalHeader()->setMinimumHeight(40);
    p_table_view->setFont(QFont("宋体",12)); //设置字体
    this->setStyleSheet("QPushButton{font: 14px;width:70px;height:25;}QLabel{font: 16px}QProgressBar{color:red}");
//    int row_count = model->rowCount();
//    for (int i = 0;i < row_count;i++)
//    {

//    }
}

void AgvForm::onAddClicked()
{
    QRect r = QApplication::desktop()->availableGeometry();
    AddDevice * d = new AddDevice();
    connect(d,&AddDevice::insert_emit,this,&AgvForm::refreshTable);
    d->move(r.width()/2-d->width()/2,(r.height()-d->height())/2);
    //qDebug()<<r.width()/2-d->width()/2<<","<<(r.height()-d->height()/2)<<"main-width:"<<r.height()<<"d-width"<<d->height();
    d->show();

}

void AgvForm::tableRowClicked()
{
    if(p_car_info!= nullptr)
    {
        p_car_info->hide();
        p_car_info->deleteLater();
        p_car_info = nullptr;
    }
    _Car_status device_stru;
    int row_index = p_table_view->currentIndex().row();
    QAbstractItemModel *model = p_table_view->model ();

    QModelIndex index = model->index(row_index,0);//选中行第一列的内容
    QVariant data = model->data(index);
    index = model->index(row_index,1);
    data = model->data(index);
    device_stru.carNum = data.toString();
    index = model->index(row_index,2);
    data = model->data(index);
    device_stru.carIp = data.toString();
    index = model->index(row_index,5);
    data = model->data(index);
    device_stru.status = data.toString();
    //base information to get other status of agv
     p_car_info = new CarStatusFrom(device_stru,this);
     QRect r = QApplication::desktop()->availableGeometry();
     p_car_info->move(r.width()/2-p_car_info->width(),(r.height()-p_car_info->height())/2);

     p_car_info->show();

}

void AgvForm::refreshTable()
{
    //model->database().commit();
    //model->setTable("t_device_info");
    //model->submitAll();
    model->select();
}
