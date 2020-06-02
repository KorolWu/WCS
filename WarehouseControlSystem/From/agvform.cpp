#include "agvform.h"
#include <QHeaderView>
#include <QIcon>
#include <QDesktopWidget>
#include <QApplication>
AgvForm::AgvForm(int width, int height, QWidget *parent) : QWidget(parent)
{
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
    p_query_btn->setStyleSheet("background-color:rgb(0,170,255)");


    p_table_widget = new QTableView(this);//18,7,
    p_table_widget->move(5,60);
    p_table_widget->verticalHeader()->hide();
    p_table_widget->resize(width,height);
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("select *from t_device_info;");
    model->query();
    p_table_widget->setModel(model);
    QStringList header;
    header<<"ID"<<"穿梭车编号"<<"通讯地址"<<"端口号"<<"类型"<<"状态"<<"位置"<<"电量"<<"工作模式"<<"运行操作";
    //p_table_widget->setHorizontalHeaderLabels(header);
    for(int i = 0 ;i <header.size();i++)
    {
        model->setHeaderData(i, Qt::Horizontal, header.at(i));
    }

    p_table_widget->setColumnWidth(0,width/20*2);
    p_table_widget->setColumnWidth(1,width/20*3);
    p_table_widget->setColumnWidth(2,width/20*2.5);
    p_table_widget->setColumnWidth(3,width/20*4);

    p_table_widget->setColumnWidth(4,width/20*2);
    p_table_widget->setColumnWidth(5,width/20*3);
    p_table_widget->setColumnWidth(6,width/20*3);
    p_table_widget->horizontalHeader()->setMinimumHeight(40);
    p_table_widget->setFont(QFont("宋体",12)); //设置字体
    this->setStyleSheet("QPushButton{font: 14px;width:70px;height:25;}QLabel{font: 16px}");
}

void AgvForm::onAddClicked()
{
    QRect r = QApplication::desktop()->availableGeometry();
    AddDevice * d = new AddDevice();
    d->move(r.width()/2-d->width()/2,(r.height()-d->height())/2);
    qDebug()<<r.width()/2-d->width()/2<<","<<(r.height()-d->height()/2)<<"main-width:"<<r.height()<<"d-width"<<d->height();
    d->show();

}
