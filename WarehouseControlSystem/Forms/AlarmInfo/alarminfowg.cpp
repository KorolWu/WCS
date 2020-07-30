#include "alarminfowg.h"
#include<QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QStringList>
#include <QSplitter>
#include <QHeaderView>

AlarmInfoWg::AlarmInfoWg(QWidget *parent):BaseFrom(parent)
{
    this->resize(parent->width(),parent->height());
    QVBoxLayout *mainlay = new QVBoxLayout;

    QGroupBox *btnbox  = new QGroupBox(this);
    //  btnbox->setStyleSheet("QGroupBox{background:grey}");
    QHBoxLayout *btnlay = new QHBoxLayout; //
    btnbox->setLayout(btnlay);

    QGridLayout *slectinfogrid = new QGridLayout;
    QLabel *idlabel = new QLabel("设备ID:");
    slectinfogrid->addWidget(idlabel,0,0,1,1);
    m_devicelineEdit = new QLineEdit(btnbox);
    slectinfogrid->addWidget(m_devicelineEdit,0,1,1,1);

    QLabel *opstatlabel = new QLabel("操作状态:");
    slectinfogrid->addWidget(opstatlabel,1,0,1,1);
    m_statcombox = new QComboBox(btnbox);
    m_statelist.clear();
    m_statelist <<"全部"<<"自动"<<"手动";
    m_statcombox->addItems(m_statelist);
    slectinfogrid->addWidget(m_statcombox,1,1,1,1);

    QLabel *levellabel = new QLabel("报警等级:");
    slectinfogrid->addWidget(levellabel,0,2,1,1);
    m_levelcombox = new QComboBox(btnbox);
    m_levellist.clear();
    m_levellist <<"全部"<<"特别严重Ⅰ级"<<"严重Ⅱ级"<<"较重Ⅲ级"<<"一般Ⅳ级";
    m_levelcombox->addItems(m_levellist);
    slectinfogrid->addWidget(m_levelcombox,0,3,1,1);

    QLabel *errotypelabel = new QLabel("故障类型:");
    slectinfogrid->addWidget(errotypelabel,1,2,1,1);
    m_errortypecombox = new QComboBox(btnbox);
    m_errottypelist.clear();
    m_errottypelist <<"全部"<<"通迅故障"<<"硬件故障";
    m_errortypecombox->addItems(m_errottypelist);
    slectinfogrid->addWidget(m_errortypecombox,1,3,1,1);

    slectinfogrid->setColumnStretch(0,1);
    slectinfogrid->setColumnStretch(1,2);
    slectinfogrid->setColumnStretch(2,1);
    slectinfogrid->setColumnStretch(3,2);
    btnlay->addLayout(slectinfogrid);
    QSplitter *spil = new QSplitter;
    // spil->setStyleSheet("{background:grey}");
    btnlay->addWidget(spil);


    m_slectbtn = new QPushButton("查询");
    m_slectbtn->setIcon(QIcon(":/resouse/Image/search.png"));
    connect(m_slectbtn,&QPushButton::clicked,this,&AlarmInfoWg::slotSlectTableInfo);
    btnlay->addWidget(m_slectbtn);
    m_refreshbtn = new QPushButton("刷新");
    m_refreshbtn->setIcon(QIcon(":/resouse/Image/Refresh.png"));
    connect(m_refreshbtn,&QPushButton::clicked,this,&AlarmInfoWg::slotRefreshTableInfo);

    btnlay->addWidget(m_refreshbtn);
    mainlay->addWidget(btnbox);
    //表格信息
    InitTableViewUI();
    mainlay->setSpacing(15);
    mainlay->addWidget(m_sqltableview);
    mainlay->addWidget(m_pagewg);
    this->setLayout(mainlay);
}

void AlarmInfoWg::InitTableViewUI()
{
    m_sqltableview = new QTableView(this);
    m_sqltableview->resize(this->width(),this->height()*9/10);
    m_sqltableview->horizontalHeader()->setStyleSheet(headstlye);
    m_sqltableview->verticalHeader()->hide();
    m_sqltableview->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_sqltableview->verticalHeader()->hide();
    m_sqltableview->horizontalHeader()->setStretchLastSection(true); // 设置最后一列填充
    m_sqltableview->setSelectionMode(QAbstractItemView::SingleSelection);
    m_sqltableview->setFrameShape(QFrame::NoFrame);
    m_sqltableview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_sqltableview->setAlternatingRowColors(true);

    m_sqltablemodel = new MySqlTableModel();
    m_sqltablemodel->setTable("t_alarmInfo");
     m_sqltablemodel->insertColumn(0);
      m_sqltablemodel->setSort(0,Qt ::AscendingOrder);
    m_sqltableview->setModel(m_sqltablemodel);

    m_sqltablemodel->select();

    //page ob 功能实现方式
    m_pagewg = new SpiltPagesByQSqlTableModel(this);
    m_pagewg->SetParam(m_sqltablemodel,"t_alarmInfo",25);
    m_pagewg->InitpagefunWg();

    QStringList headerlist;
    headerlist<<"ID"<<" 报警等级"<<"设备编号ID"<<"故障类型"<<"故障代码"<<"操作状态"<<"小车子任务ID"<<\
                "WMS任务ID"<<"库箱编号"<<"报警信息"<<"小车坐标X"<<"小车坐标Y"<<"小车坐标Z"<<"更新时间"<<"备注";
    for(int i = 0 ;i <headerlist.size();i++)
    {
        m_sqltablemodel->setHeaderData(i, Qt::Horizontal, headerlist.at(i));
    }
    for(int i =1; i< headerlist.size(); ++i )
    {
        if(i !=9)
        {
            m_sqltableview->setColumnWidth(i,this->width()*2/3/14);
        }
    }
    m_sqltableview->setColumnWidth(0,40);
    m_sqltableview->setColumnWidth(9,this->width()/3);
    m_sqltableview->horizontalHeader()->setMinimumHeight(40);
    //m_sqltableview->s
}
///
/// \brief AlarmInfoWg::GetSelectSqlStr
/// \return
///根据条件得到组成过滤器的字符串
QString AlarmInfoWg::GetSelectSqlStr()
{
    QString deciveid = m_devicelineEdit->text();
    QString stat = m_statcombox->currentText();
    QString level = m_levelcombox->currentText();
    QString errortype = m_errortypecombox->currentText();
    if(deciveid == "")
    {
       // deciveid = QString("DeviceID LIKE '%'");
    }
    else{
        deciveid = QString("DeviceID = '%1' AND ").arg(deciveid);
    }
    uint8_t value = GetValue(stat,0);
    if(value == 0)
    {
        stat = QString("Operatestate LIKE '%' ");
    }
    else{
        stat = QString("Operatestate = '%1'").arg(value);
    }
    value = GetValue(errortype,1);
    if(value == 0)
    {
        errortype = QString("ErrorType LIKE '%'");
    }
    else{
        errortype = QString("ErrorType = '%1'").arg(value);
    }
    value = GetValue(level,2);
    if(value == 0)
    {
        level = QString("Alarmlevel LIKE '%'");
    }
    else{
        level = QString("Alarmlevel = '%1'").arg(value);
    }
    //注意：过滤器使用查询方式区别查询语句 针对字符类型或者 数值类型不需要加’  ‘
    //QString sqlstr = QString("SELECT * FROM t_alarmInfo WHERE %1 AND %2 AND %3 AND %4;").arg(deciveid).arg(stat).arg(level).arg(errortype);
    QString sqlstr = QString("%1  %2 AND %3 AND %4;").arg(deciveid).arg(stat).arg(level).arg(errortype);
    return sqlstr;
}

uint8_t AlarmInfoWg::GetValue(QString str,int role)
{
    uint8_t value = -1;
    switch (role) {
    case 0: // 状态
        value = m_statelist.indexOf(str);
        break;
    case 1: // 类型
        value = m_errottypelist.indexOf(str);
        break;
    case 2: // 报警等级
        value = m_levellist.indexOf(str);
        break;
    default:
        break;
    }
    return value;
}
///
/// \brief AlarmInfoWg::slotSlectTableInfo
///根据查询条件查询符合条件的数据的信息显示在表格中
void AlarmInfoWg::slotSlectTableInfo()
{
    //根据条件查询选择
    //获得查询条件  设备id 状态  报警等级  故障类型
    QString  sql = GetSelectSqlStr();
     //select * from t_alarmInfo where DeviceID like '%' and ErrorType like '%' and Operatestate like '1' and Alarmlevel like '%'
    m_sqltablemodel->setFilter(sql);
    int total =  m_sqltablemodel->rowCount();
     sql= "select * from t_alarmInfo where "+sql;
     sql.chop(1);
  //   qDebug()<<"sql "<<sql << total;
    m_pagewg->updateParam(total,sql);
}
///
/// \brief AlarmInfoWg::slotRefreshTableInfo
///刷新数据中的数据，重新读取数据中的信息
void AlarmInfoWg::slotRefreshTableInfo()
{
    m_sqltablemodel->setFilter("");
    if(m_sqltablemodel != NULL)
    {
        m_sqltablemodel->select();
    }
    //分页变化
    int total =  m_sqltablemodel->rowCount();
    m_pagewg->updateParam(total,"");
}

