#include "testcreateorderspath.h"
#include <QTableWidgetItem>
#include <QLabel>
#include <QComboBox>
#include <QHeaderView>


TestcreateOrdersPath::TestcreateOrdersPath(QWidget *parent):QWidget(parent)
{
    this->resize(parent->width(),parent->height());

    QVBoxLayout *blay= new QVBoxLayout;
    m_configTable = new QTableWidget(this);

    blay->addWidget(m_configTable);
   // 设置列宽
    m_configTable->setColumnCount(5); //设置列数
    for(int i =0; i < 5;++i)
    {
        m_configTable->setColumnWidth(i,(parent->width()-60)/5);
    }
    QStringList sListHeader;
    sListHeader << "X" << "Y" << "Z" << "方向状态"<<"备注";
    m_configTable->setHorizontalHeaderLabels(sListHeader);
    m_configTable->setEditTriggers(QAbstractItemView::DoubleClicked); //设置双击可编辑
    m_configTable->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
     m_configTable->verticalHeader()->resizeSections(QHeaderView::ResizeToContents);//设置表格内容自动适应宽度
     m_configTable->verticalHeader()->setDefaultSectionSize(30); //设置行高
     m_configTable->setFrameShape(QFrame::NoFrame); //设置无边框
     m_configTable->setShowGrid(false); //设置不显示格子线
     m_configTable->verticalHeader()->setVisible(false); //设置垂直头不可见

     m_configTable->setStyleSheet("selection-background-color:lightblue;"); //设置选中背景色
     m_configTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
     m_configTable->setRowCount(4);
     m_configTable->setShowGrid(true);
     //m_configTable->verticalHeader()->setVisible(false);
     m_configTable->setSelectionBehavior(QAbstractItemView::SelectRows);//选择一行
    for(int i = 0; i < 4;++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            QTableWidgetItem *item = new QTableWidgetItem("");
            m_configTable->setItem(i, j, item); //添加到界面
        }
    }
    m_configTable->item(0,0)->setText("入库电梯信息");
    m_configTable->item(1,0)->setText("出库电梯信息");
    m_configTable->item(2,0)->setText("小车电梯信息");
    m_configTable->item(3,0)->setText("流道信息");

    QHBoxLayout *hbox = new  QHBoxLayout();

    QLabel *label =new QLabel("小车位置坐标:");
    QLineEdit *carpos = new QLineEdit(this);

    QLabel *tlabel =new QLabel("目标位置坐标:");
    QLineEdit *tpos = new QLineEdit(this);

   QStringList list;
   list<<"出库"<<"入库";
   QComboBox *com  = new QComboBox();
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
   blay->addLayout(hbox);
    m_ordersedit = new QTextEdit(this);
    blay->addWidget(m_ordersedit);
    this->setLayout(blay);

}

TestcreateOrdersPath::~TestcreateOrdersPath()
{

}

void TestcreateOrdersPath::Createorderslot()
{

    //获取各个表格及其他配置数据信息



}

void TestcreateOrdersPath::Cleartextdata()
{

}
