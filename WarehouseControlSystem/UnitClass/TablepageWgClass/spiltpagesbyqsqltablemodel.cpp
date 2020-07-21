#include "spiltpagesbyqsqltablemodel.h"
#include <QHBoxLayout>
#include <QSplitter>
#include<QSqlQuery>
#include <QDebug>
#include <QMessageBox>


SpiltPagesByQSqlTableModel::SpiltPagesByQSqlTableModel(QWidget *parent):QWidget(parent)
{
    m_sqltableMode = NULL;
    m_currentPage = 1;
    m_totalPage = 1;
    m_totalRecrodCount = -1;
    m_PageRecordCount =-1;
    m_sqlstr = "";
}

SpiltPagesByQSqlTableModel::~SpiltPagesByQSqlTableModel()
{

}

void SpiltPagesByQSqlTableModel::SetParam(QSqlQueryModel *p, QString name, int PageRecordCount)
{
    m_sqltableMode = p;
    m_PageRecordCount = PageRecordCount;
    tablename = name;
}
///
/// \brief SpiltPagesByQSqlTableModel::updateParam
///  //重新查询进行更新 表格或者总的行数
void SpiltPagesByQSqlTableModel::updateParam(int totalRecrodCount,QString sql) //进行数据变换
{
    m_sqlstr = sql;
    m_totalRecrodCount = totalRecrodCount;
    //得到总页数
    m_totalPage = GetTablePageCount();
    m_currentPage = 1;
   // qDebug()<<" 总条数"<<m_totalRecrodCount<<m_totalPage<<m_currentPage;
    //得到总的表格行数
    UpdateUIStatus();
    //设置总的页数
    SetTableTotalPageLabel();
    SetShowTableRecord(0);
}

void SpiltPagesByQSqlTableModel::InitpagefunWg()
{
    QHBoxLayout *hbox = new QHBoxLayout;
    this->setLayout(hbox);
    hbox->addWidget(new QSplitter());
    m_prevButton = new QPushButton(this);
    //  m_prevButton->setText("前一页");:/resouse/Image/left.png
    m_prevButton->setIcon(QIcon(":/resouse/Image/left.png"));
    m_prevButton->setLayoutDirection(Qt::LayoutDirectionAuto);
    m_prevButton->setFlat(true);
    hbox->addWidget(m_prevButton);
    m_switchPageLineEdit = new QLineEdit(this);
    m_switchPageLineEdit->setFixedHeight(20);
    m_switchPageLineEdit->setFixedWidth(60);
    m_switchPageLineEdit->setText("1");
    connect(m_switchPageLineEdit,&QLineEdit::returnPressed,this,&SpiltPagesByQSqlTableModel::slotToPage);

    m_swtoButton = new QPushButton(this);
    m_swtoButton->setText("go");
    m_swtoButton->setFixedWidth(40);
    m_swtoButton->setIcon(QIcon(":/resouse/Image/go.png"));
    m_swtoButton->setLayoutDirection(Qt::LayoutDirectionAuto);
    m_swtoButton->setFlat(true);

    m_nextButton = new QPushButton(this);
    //  m_nextButton->setText("后一页");
    m_nextButton->setIcon(QIcon(":/resouse/Image/right.png"));
    m_nextButton->setLayoutDirection(Qt::LayoutDirectionAuto);
    m_nextButton->setFlat(true);
    m_nextButton->setStyleSheet("color: rgb(0, 0, 0);");
    QString str = QString("共%1").arg(m_currentPage);
    m_currentPageLabel = new QLabel(str);
    hbox->addWidget(m_currentPageLabel);
    str = QString("/%1页").arg(m_totalPage);
    m_totalPageLabel = new QLabel(str);
    hbox->setSpacing(0);
    hbox->addWidget(m_totalPageLabel);
    hbox->addWidget(m_nextButton);

    hbox->addWidget(m_switchPageLineEdit);
    hbox->addWidget(m_swtoButton);

    hbox->addWidget(new QSplitter());
    connect(m_prevButton,&QPushButton::clicked,this,&SpiltPagesByQSqlTableModel::slotprepage);
    connect(m_nextButton,&QPushButton::clicked,this,&SpiltPagesByQSqlTableModel::slotNextpage);
    connect(m_swtoButton,&QPushButton::clicked,this,&SpiltPagesByQSqlTableModel::slotToPage);
    //得到总的表格行数
    m_totalRecrodCount = GetTableTotalRecordCount();
    //得到总页数
    m_totalPage = GetTablePageCount();
    UpdateUIStatus();
    //设置总的页数
    SetTableTotalPageLabel();
    SetShowTableRecord(0);
}
///
/// \brief SpiltPagesByQSqlTableModel::GetTableTotalRecordCount
/// \return
///   // 功能: 得到记录数
int SpiltPagesByQSqlTableModel::GetTableTotalRecordCount()
{
    QString slecttstr =QString("select * from %1").arg(tablename);
    QSqlQuery sql ;
    sql.exec(slecttstr);
    int num = sql.size();
    // qDebug()<<"num"<<num;
    return num /*m_sqltableMode->rowCount()*/;
}
///
/// \brief SpiltPagesByQSqlTableModel::GetTablePageCount
/// \return
///得到总的页数
int SpiltPagesByQSqlTableModel::GetTablePageCount()
{
    if(m_totalRecrodCount == 0)
    {
        m_totalPage = 1;
        return 1;
    }
    return  (m_totalRecrodCount % m_PageRecordCount == 0) ? (m_totalRecrodCount / m_PageRecordCount) : (m_totalRecrodCount / m_PageRecordCount + 1);
}
///
/// \brief SpiltPagesByQSqlTableModel::SetShowTableRecord
/// \param limitdex
///展示显示的页面信息记录,通过sql语句查询的方式实现
void SpiltPagesByQSqlTableModel::SetShowTableRecord(int limitdex)
{
    //可以过滤器的方式实现或者直接查询基类的query语句
    //    QString str = QString("1=1 limit %1,%2").arg(limitdex) .arg(m_PageRecordCount) ;
    //    m_sqltableMode->setFilter(str);
     QString szQuery;
     if(m_sqlstr == "")
     {
         szQuery =  QString("select * from (%1) limit %2,%3").arg(tablename).arg(limitdex).arg(m_PageRecordCount);
     }
     else{
         szQuery =  QString("select * from (%1) as a_table limit %2,%3").arg(m_sqlstr).arg(limitdex).arg(m_PageRecordCount);
     }
     //qDebug()<<"szQuery"<<szQuery;
    // szQuery =  "select * from (select * from t_alarmInfo where DeviceID LIKE '%' AND Operatestate = '1' AND Alarmlevel LIKE '%' AND ErrorType LIKE '%') as a_table limit 0,25";
    m_sqltableMode->setQuery(szQuery);
}

void SpiltPagesByQSqlTableModel::UpdateUIStatus()
{
    //设置当前页文本
    QString szCurrentText = QString("共%1").arg(QString::number(m_currentPage));
    //   szCurrentText = QString("<font color=\"#00FF00\">%1</font> ").arg(szCurrentText);
    m_currentPageLabel->setText(szCurrentText);
    //设置按钮是否可用
    if(m_currentPage ==1&& m_totalPage == 1) //    //当前第一页，且总共只有一页
    {
        m_prevButton->setEnabled(false);
        m_nextButton->setEnabled(false);
    }
    else if(m_currentPage == 1&& m_totalPage > 1) //当前是第一页且数据大于1
    {
        m_prevButton->setEnabled(false);
        m_nextButton->setEnabled(true);
    }
    else if(m_currentPage == (m_totalPage))
    {
        m_prevButton->setEnabled(true);
        m_nextButton->setEnabled(false);
    }
    else{
        m_prevButton->setEnabled(true);
        m_nextButton->setEnabled(true);
    }
}
///设置总页数变化
void SpiltPagesByQSqlTableModel::SetTableTotalPageLabel()
{
    QString szPageCountText = QString("/%1页").arg(QString::number(m_totalPage));
    //szPageCountText = QString("<font color=\"#0000FF\">%1</font> ").arg(szPageCountText);
    m_totalPageLabel->setText(szPageCountText);
}
///
/// \brief SpiltPagesByQSqlTableModel::slotprepage
///前一页
void SpiltPagesByQSqlTableModel::slotprepage()
{
    int limitIndex = (m_currentPage - 2) * m_PageRecordCount;
    SetShowTableRecord(limitIndex);
    m_currentPage -= 1;
    UpdateUIStatus();
}
///
/// \brief SpiltPagesByQSqlTableModel::slotNextpage
///  后一页
void SpiltPagesByQSqlTableModel::slotNextpage()
{
    int limitIndex = m_currentPage * m_PageRecordCount;
    SetShowTableRecord(limitIndex);
    m_currentPage += 1;
    UpdateUIStatus();
}
///
/// \brief SpiltPagesByQSqlTableModel::slotToPage
///转到制定页面
void SpiltPagesByQSqlTableModel::slotToPage()
{
    //得到输入字符串
    QString szText = m_switchPageLineEdit->text();
    //数字正则表达式
    QRegExp regExp("-?[0-9]*");
    //判断是否为数字
    if(!regExp.exactMatch(szText))
    {
        QMessageBox::information(this, tr("提示"), tr("请输入数字"));
        return;
    }
    //是否为空
    if(szText.isEmpty())
    {
        QMessageBox::information(this, tr("提示"), tr("请输入跳转页面"));
        return;
    }
    //得到页数
    int pageIndex = szText.toInt();
    //判断是否有指定页
    if(pageIndex > m_totalPage || pageIndex < 1)
    {
        QMessageBox::information(this, tr("提示"), tr("没有指定的页面，请重新输入"));
        return;
    }
    //得到查询起始行号
    int limitIndex = (pageIndex-1) * m_PageRecordCount;
    //记录查询
    SetShowTableRecord(limitIndex);
    //设置当前页
    m_currentPage = pageIndex;
    //刷新状态
    UpdateUIStatus();
}
