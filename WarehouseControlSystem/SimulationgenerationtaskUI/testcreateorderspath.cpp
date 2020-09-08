#include "testcreateorderspath.h"
#include <QTableWidgetItem>
#include <QLabel>
#include <QComboBox>
#include <QHeaderView>
#include "ControlClass/WarehousingIn/generateinputwarehousingorders.h"
#include "ControlClass/WarehousingIn/getouttrajectory.h"
#include <QGroupBox>


TestcreateOrdersPath::TestcreateOrdersPath(QWidget *parent):QWidget(parent)
{
    this->resize(parent->width(),parent->height());

    QVBoxLayout *blay= new QVBoxLayout;
    m_configTable = new QTableWidget(this);

    blay->addWidget(m_configTable,4);
    // 设置列宽
    m_configTable->setColumnCount(6); //设置列数
    for(int i =0; i < 6;++i)
    {
        m_configTable->setColumnWidth(i,(parent->width()-60)/6);
    }
    QStringList sListHeader;
    sListHeader << "配置名称"<<"X" << "Y" << "Z" << "方向状态"<<"备注";
    m_configTable->setHorizontalHeaderLabels(sListHeader);
    m_configTable->setEditTriggers(QAbstractItemView::DoubleClicked); //设置双击可编辑
    m_configTable->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
    m_configTable->verticalHeader()->resizeSections(QHeaderView::ResizeToContents);//设置表格内容自动适应宽度
    m_configTable->verticalHeader()->setDefaultSectionSize(30); //设置行高
    m_configTable->setFrameShape(QFrame::NoFrame); //设置无边框
    m_configTable->setShowGrid(false); //设置不显示格子线
    m_configTable->verticalHeader()->setVisible(false); //设置垂直头不可见

    m_configTable->setStyleSheet("selection-background-color:lightgray;"); //设置选中背景色
    m_configTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:gray;}"); //设置表头背景色
    m_configTable->setRowCount(6);
    m_configTable->setShowGrid(true);
    m_configTable->verticalHeader()->setVisible(false);
    m_configTable->setSelectionBehavior(QAbstractItemView::SelectRows);//选择一行
    for(int i = 0; i < 6;++i)
    {
        for(int j = 0; j < 6; ++j)
        {
            QTableWidgetItem *item = new QTableWidgetItem("");

            if(j == 0)
            {
                item->setFlags(item->flags() &= (~Qt::ItemIsEditable));
            }
            m_configTable->setItem(i,j,item); //添加到界面
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        }
    }
    m_configTable->item(0,0)->setText("入库电梯等待点信息");
    m_configTable->item(1,0)->setText("出库电梯等待点信息");
    m_configTable->item(2,0)->setText("小车等待电梯点信息");
    m_configTable->item(3,0)->setText("小车进电梯点信息");
    m_configTable->item(4,0)->setText("流道配置信息");
    m_configTable->item(5,0)->setText("换向坐标配置信息");
    m_configTable->item(0,1)->setText("0.0");
    m_configTable->item(0,2)->setText("2430");
    m_configTable->item(1,1)->setText("26");
    m_configTable->item(1,2)->setText("2");
    m_configTable->item(2,1)->setText("0");
    m_configTable->item(2,2)->setText("1423");
    m_configTable->item(3,1)->setText("0");
    m_configTable->item(3,2)->setText("3330");
    m_configTable->item(4,1)->setText("4");
    m_configTable->item(5,1)->setText("0.0");
    //流道缓存区域设置
    QGroupBox *rungroup = new QGroupBox;
    QHBoxLayout *runbox = new  QHBoxLayout();
    rungroup->setLayout(runbox);
    QLabel *inlabel =new QLabel("入库流道缓存区最大容量:");
    runbox->addWidget(inlabel);
    m_InsetValue = new QLineEdit(this);
    runbox->addWidget(m_InsetValue);
    // inlabel =new QLabel("设置参数:");
    //runbox->addWidget(inlabel);
    m_IncurValue = new QLineEdit(this);
    inlabel =new QLabel("当前容量:");
    runbox->addWidget(inlabel);
    runbox->addWidget(m_IncurValue);

    QLabel *outlabel =new QLabel("出库流道缓存区最大容量:");
    runbox->addWidget(outlabel);
    m_OutsetValue = new QLineEdit(this);
    runbox->addWidget(m_OutsetValue);
    outlabel =new QLabel("当前容量:");
    runbox->addWidget(outlabel);
    m_OutcurValue = new QLineEdit(this);


    runbox->addWidget(m_OutcurValue);

    m_ptrigger =  new QPushButton("流道状态改变任务");
    runbox->addWidget(m_ptrigger);

    blay->setSpacing(20);
    blay->addWidget(rungroup,1);


    QHBoxLayout *hbox = new  QHBoxLayout();

    QLabel *label =new QLabel("小车位置坐标:");
    carpos = new QLineEdit(this);

    QLabel *tlabel =new QLabel("目标位置坐标:");
    tpos = new QLineEdit(this);
    carpos->setPlaceholderText(QString::fromUtf8("X:2,Y:3,Z:2")); //QLineEdit设置背景文字
    tpos->setPlaceholderText(QString::fromUtf8("X:2,Y:3,Z:2,D:0"));//设置背景文字

    QStringList list;
    list<<"出库"<<"入库";
    com  = new QComboBox();
    com->addItems(list);
    com->setCurrentIndex(0);
    QPushButton *order = new QPushButton(this);
    order->setText("生成指令");
    QPushButton *clear = new QPushButton("清除");

    hbox->addWidget(label);
    hbox->addWidget(carpos);
    hbox->addWidget(tlabel);
    hbox->addWidget(tpos);
    hbox->addWidget(com);
    hbox->addWidget(order);
    hbox->addWidget(clear);
    blay->addLayout(hbox,2);
    m_ordersedit = new QTextEdit(this);
    blay->addWidget(m_ordersedit,4);
    this->setLayout(blay);
    connect(order,&QPushButton::clicked,this,&TestcreateOrdersPath::Createorderslot);
    connect(clear,&QPushButton::clicked,this,&TestcreateOrdersPath::Cleartextdata);

}

TestcreateOrdersPath::~TestcreateOrdersPath()
{

}

void TestcreateOrdersPath::Createorderslot()
{
    //获取各个表格及其他配置数据信息
    SetHWConfigData();
    KPosition task_P;
    KPosition carPosion;
    GetSetDataValue(task_P, carPosion);
    QQueue<OrderStru> taskQueue;
    if(com->currentText() == "入库")
    {
        GenerateInputWarehousingOrders inob;
        inob.SetPathParam(task_P,carPosion);
        inob.SetHWConfigData(m_configTable->item(0,1)->text().toDouble(),m_configTable->item(0,2)->text().toDouble(),\
                             m_configTable->item(5,1)->text().toDouble(),m_configTable->item(2,1)->text().toDouble(),\
                             m_configTable->item(2,2)->text().toDouble(),m_configTable->item(3,1)->text().toDouble(),\
                             m_configTable->item(3,2)->text().toDouble(),m_configTable->item(0,3)->text().toDouble());
        taskQueue = inob.GetInputWarehousingOrders();
    }
    else{
        //出库
        //GetOutTrajectory outob(task_P,);

    }
    for(int i = 0; i < taskQueue.size();++i)
    {
        QString str = com->currentText()+"-----指令名字:"+ GetorderNameByValue(taskQueue.at(i).order) +"指令参数:"+QString::number(taskQueue.at(i).value);
        m_ordersedit->append(str);
    }

}

void TestcreateOrdersPath::Cleartextdata()
{
    m_ordersedit->clear();
}

void TestcreateOrdersPath::SimulaRunnerBtn()
{

}

QString TestcreateOrdersPath::GetorderNameByValue(Order value)
{
    QString name;
    switch (value) {
    case X:
        name = "X方向移动";
        break;
    case Y:
        name = "Y方向移动";
        break;
    case ChangeWhell:
        name = "ChangeWhell";
        break;
    case Left_Pickup:
        name = "取仓位左边的箱子状态为0";
        break;
    case Right_Pickup:
        name = "取仓位右边的箱子状态为1";
        break;
    case Call:
        name = "呼叫小车电梯到指定层数";
        break;
    case Elevator_Near:
        name = "到达小车电梯临近点";
        break;
    case Elevator_In:
        name = "呼叫小车进电梯";
        break;
    case Elevator_Out:
        name = "呼叫小车出电梯";
        break;

    case Left_WorkBin:
        name = "放入出库电梯的货物";
        break;
    case Right_WorkBin:
        name = "取入库电梯的货物";
        break;
    case  Call_WorkBin_Out:
        name = "呼叫出库电梯到达指定层数";
        break;
    case Call_WorkBin_In:
        name = "呼叫入库电梯到达指定层数";
        break;
    case call_Runner_Putbox:
        name = "呼叫流道把箱子放入电梯";
        break;
    case Left_Putinto:
        name = "把箱子放入左边仓位状态为0";
        break;
    case Right_Putinto:
        name = "把箱子放入右边的仓位状态为1";
        break;
    default:
        break;
    }
    return name;
}

void TestcreateOrdersPath::GetSetDataValue(KPosition &task_P, KPosition &carPosion)
{
    //小车位置
    //目标位置
    QString carstr =  carpos->text();
    QStringList list = carstr.split(",");
    if(list.size() == 3)
    {
        QString xstr = list[0];
        QStringList listvalue =  xstr.split(":");
        if(listvalue.size() == 2)
        {
            carPosion .x = QString(listvalue[1]).toDouble();
        }
        QString ystr = list[1];
        listvalue =  ystr.split(":");
        if(listvalue.size() == 2)
        {
            carPosion .y = QString(listvalue[1]).toDouble();
        }
        QString zstr = list[2];
        listvalue =  zstr.split(":");
        if(listvalue.size() == 2)
        {
            carPosion .z = QString(listvalue[1]).toDouble();
        }
    }
    QString trastr =  tpos->text();
    list = trastr.split(",");
    if(list.size() == 4)
    {
        QString xstr = list[0];
        QStringList listvalue =  xstr.split(":");
        if(listvalue.size() == 2)
        {
            task_P .x = QString(listvalue[1]).toDouble();
        }
        QString ystr = list[1];
        listvalue =  ystr.split(":");
        if(listvalue.size() == 2)
        {
            task_P .y = QString(listvalue[1]).toDouble();
        }
        QString zstr = list[2];
        listvalue =  zstr.split(":");
        if(listvalue.size() == 2)
        {
            task_P .z = QString(listvalue[1]).toDouble();
        }
        QString statstr = list[3];
        listvalue =  statstr.split(":");
        if(listvalue.size() == 2)
        {
            task_P .state = QString(listvalue[1]).toInt();
        }
    }


}
///
/// \brief TestcreateOrdersPath::SetHWConfigData
///从表格信息获取流道 电梯  信息 内容
void TestcreateOrdersPath::SetHWConfigData()
{
    //入库电梯
    //小车电梯
    //流道信息



}
