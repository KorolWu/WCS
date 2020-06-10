#include "elevatorfrom.h"
#include <QHeaderView>
#include <QIcon>
#include <Forms/CarForms/labeldelegate.h>
#include <QStandardItemModel>
#include "Forms/StorePosInfo/buttondelegate.h"
ElevatorFrom::ElevatorFrom(int width, int height,QWidget *parent) : BaseFrom(parent)
{
    p_add_btn = new QPushButton("添加",this);
    p_add_btn->setIcon(QIcon(":/resouse/Image/add.png"));
    connect(p_add_btn,&QPushButton::clicked,this,&ElevatorFrom::onAddClicked);
    p_add_btn->move(5,10);
    p_delete_btn= new QPushButton("删除",this);
    p_delete_btn->setIcon(QIcon(":/resouse/Image/delete.png"));
    p_delete_btn->move(100,10);
    p_export_btn= new QPushButton("导出",this);
    p_export_btn->move(200,10);
    p_export_btn->setIcon(QIcon(":/resouse/Image/download.png"));

    QLabel *text_lable = new QLabel("设备编号:",this);
    text_lable->move(350,12);
    text_lable->setAlignment(Qt::AlignBottom);
    p_input_text = new QLineEdit(this);
    p_input_text->resize(150,30);
    p_input_text->move(440,10);
    p_query_btn = new QPushButton("查询",this);
    p_query_btn->move(610,10);
    p_query_btn->setStyleSheet("background-color:rgb(0,170,255)");


    p_table_view = new QTableView(this);
    p_table_view->move(5,60);
    p_table_view->verticalHeader()->hide();
    p_table_view->resize(width,height);
    QStandardItemModel *model = new QStandardItemModel(10,9);
    p_table_view->setModel(model);


    p_table_view->setEditTriggers(QAbstractItemView::AllEditTriggers);
    LabelDelegate *delegate = new LabelDelegate();
    p_table_view->setItemDelegateForColumn(8,delegate);
    QStringList header;
    header<<"编号"<<"类型"<<"通讯地址"<<"端口"<<"靠近点位置"<<"当前层"<<"目标层"<<"位置"<<"状态"<<"操作按钮";
    //p_table_view->setHorizontalHeaderLabels(header);
    for(int i = 0 ;i <header.size();i++)
    {
        model->setHeaderData(i, Qt::Horizontal, header.at(i));
    }

    p_table_view->setColumnWidth(0,width/20*1);
    p_table_view->setColumnWidth(1,width/20*2);
    p_table_view->setColumnWidth(2,width/20*3);
    p_table_view->setColumnWidth(3,width/20*3);

    p_table_view->setColumnWidth(4,width/20*2);
    p_table_view->setColumnWidth(5,width/20*2);
    p_table_view->setColumnWidth(6,width/20*2);
    p_table_view->horizontalHeader()->setMinimumHeight(40);
    // is online and status is a part of struct elevator
    for(int i = 0;i < 9; i++)
    {

    }
    int row_count = model->rowCount();
    //table row count is up to elevator count
    for (int j = 0; j < row_count; j++)
    {
        QSpinBox *spinBox = new QSpinBox();
        spinBox->setMinimum(0);
        spinBox->setMaximum(12);
        spinBox->setValue(0);
        p_table_view->setIndexWidget(model->index(j,5), spinBox);
    }
    qDebug()<<"the model count :"<<row_count;


   //p_table_view->setFont(QFont("宋体",26)); //设置字体
    this->setStyleSheet("QPushButton{font: 14px;width:70px;height:25;}QLabel{font: 16px}");

}

void ElevatorFrom::onAddClicked()
{
    QStringList list;
    list<<"编号"<<"类型"<<"通讯地址"<<"端口"<<"靠近点位置";
    AddElevatorForm *elevator = new AddElevatorForm(list,this);
    elevator->setContent(list);
    QRect r = QApplication::desktop()->availableGeometry();
    elevator->move(r.width()/2-elevator->width(),r.height()/2-elevator->height());
    elevator->show();
}
