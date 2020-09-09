#include "dispatchwidget.h"

DispatchWidget::DispatchWidget(int width, int height, QWidget *parent) : QWidget(parent)
{
    this->m_height = height;
    this->m_width = width;
    initUI();
}

//料箱子进入仓库的唯一入口，从这个地方记录当前等待入库的数量
void DispatchWidget::onBoxClicked()
{
    QPushButton *b = (QPushButton*)sender();
    if(b != nullptr)
    {
        int i = b->objectName().toInt();
        if(Myconfig::GetInstance()->m_cacheRunerMap[i] == true)
        {
            Myconfig::GetInstance()->m_runer.cache_in_current++;
            Myconfig::GetInstance()->m_cacheRunerMap[i] == false;
        }
    }
}

void DispatchWidget::onGetBoxClicked()
{
   if(Myconfig::GetInstance()->m_storeinfoMap.contains(m_plineBoxNum->text()))
   {
      QString box_num = Myconfig::GetInstance()->m_storeinfoMap[m_plineBoxNum->text()].boxnbr;
      TaskInfoStru t;
      t.boxNum = box_num;
      t.taskNum = QString("HK_%1").arg(QDateTime::currentDateTime().toTime_t());
      t.creatTime = QDateTime::currentDateTime();//.toString("yyyy-MM-dd:hh:ss:mm");
      t.from = "Manual";
      t.pripty= 1;
      Myconfig::GetInstance()->m_taskQueue.enqueue(t);
      appendInfo("已插入出库队列");
   }
   else
       appendInfo("We can't find this bin");
}

void DispatchWidget::onScanCode()
{
    QPushButton *b = (QPushButton*)sender();
    if(b->objectName() == "Scan_1")
    {

    }
    else if(b->objectName() == "Scan_2")
    {

    }
    else
        return;

}

void DispatchWidget::initUI()
{
    initRightW();
    m_prightW->move(m_width - 250,10);
    m_poutWidget = new QWidget(this);
    m_poutWidget->setStyleSheet("QWidget{background-color:rgb(190,190,190);border-radius: 6px;}QPushButton{font: 14px;width:100px;height:25;background-color:rgb(150,150,150);}QPushButton:hover{background: rgb(220, 220, 220);}QPushButton:pressed{background-color:rgb(85, 170, 255);}");
    m_poutWidget->resize(1300,m_height-10);
    m_poutWidget->move(10,10);

    QLabel *b = new QLabel(m_poutWidget);
    b->setText("In_Cache:");
    m_plineCacheIn = new QLineEdit(m_poutWidget);
    b->move(20,50);
    m_plineCacheIn->move(90,50);
    QLabel *a = new QLabel(m_poutWidget);
    a->setText("Out_Cache:");
    a->move(230,50);
    m_plineCacheOut = new QLineEdit(m_poutWidget);
    m_plineCacheOut->move(330,50);
    QLabel *e = new QLabel(m_poutWidget);
    e->setText("BoxNumber:");
    e->move(20,100);
    m_poutButton = new QPushButton(m_poutWidget);
    m_poutButton->setText("GetBox");
    connect(m_poutButton,&QPushButton::clicked,this,&DispatchWidget::onGetBoxClicked);
    m_plineBoxNum = new QLineEdit(m_poutWidget);
    m_plineBoxNum->resize(200,30);
    m_plineBoxNum->move(100,100);
    m_poutButton->move(320,100);
   // m_poutButton->setStyleSheet("QPushButton{font: 14px;width:100px;height:25;background-color:rgb(150,150,150);}QPushButton:hover{background: rgb(220, 220, 220);}QPushButton:pressed{background-color:rgb(85, 170, 255);}");
    m_pScan_1 = new QPushButton(m_poutWidget);
    m_pScan_1->setText("Scan_1");
    m_pScan_1->setObjectName("Scan_1");
    m_pScan_2 = new QPushButton(m_poutWidget);
    m_pScan_2->setText("Scan_2");
    m_pScan_2->setObjectName("Scan_2");
    m_pScan_1->move(20,160);
    m_pScan_2->move(320,160);
    connect(m_pScan_1,&QPushButton::clicked,this,&DispatchWidget::onScanCode);
    connect(m_pScan_2,&QPushButton::clicked,this,&DispatchWidget::onScanCode);
    m_ptextLine_log = new QTextEdit(m_poutWidget);
    m_ptextLine_log->move(20,200);
    m_ptextLine_log->resize(400,110);
}

void DispatchWidget::initRightW()
{
    m_prightW = new QWidget(this);
    m_prightW->resize(160,m_height-10);
    m_pvbox_rightw = new QVBoxLayout(m_prightW);
    QFont font("宋体",12);
    for(int i = 0; i < 8; i++)
    {
        m_box_list[i] = new QPushButton();
        m_box_list[i]->setObjectName(QString("%1").arg(i));
        m_box_list[i]->setText(QString("A%1").arg(i));
        m_box_list[i]->setFont(font);
        connect(m_box_list[i],&QPushButton::clicked,this,&DispatchWidget::onBoxClicked);
        m_pvbox_rightw->addWidget(m_box_list[i]);
    }
    m_prightW->setLayout(m_pvbox_rightw);
    m_prightW->setStyleSheet("QPushButton{background-image: url(:/resouse/Image/no_box.png);}"
                             "QPushButton:hover{background-image: url(:/2.bmp);}"
                             "QPushButton:pressed{background-image: url(:/resouse/Image/have_box.png);}"
                             "QPushButton{width:70px;height:70;}"
                             "QWidget{background-color:rgb(190,190,190);border-radius: 5px;}");

}

void DispatchWidget::appendInfo(QString str)
{
    m_ptextLine_log->append(QString(">%1  :"+str).arg(QDateTime::currentDateTime().toString("hh:mm:ss")));
}
