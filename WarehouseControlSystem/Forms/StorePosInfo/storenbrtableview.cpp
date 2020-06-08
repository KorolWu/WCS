#include "storenbrtableview.h"
#include "buttondelegate.h"
#include <QMessageBox>
StorenbrTableView::StorenbrTableView(QWidget *parent):QTableView(parent)
{
    m_ptablemodel = new StorenbrInfoTablemodel();
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->verticalHeader()->hide();
    this->horizontalHeader()->setStretchLastSection(true); // 设置最后一列填充
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setFrameShape(QFrame::NoFrame);
    this->setStyleSheet("QTableView {alternate-background-color: rgb(230, 230, 230);}");//设置交替颜色样式
    this->setAlternatingRowColors(true);
    connect(m_ptablemodel,&StorenbrInfoTablemodel::signalCheckDatachanged,this,&StorenbrTableView::SlotCheckstatChanged);
}
///
/// \brief StorenbrTableView::~StorenbrTableView
///
StorenbrTableView::~StorenbrTableView()
{

}
///
/// \brief StorenbrTableView::SetTableHeaderData
/// \param datalist
/// \param columncnt
///
void StorenbrTableView::SetTableHeaderData(QStringList datalist, int columncnt)
{
       m_ptablemodel->SetTableHeader(datalist);
       m_ptablemodel->SetColumncnt(datalist.size());
       this->setModel(m_ptablemodel);
       int nColumWidth = this->width() / columncnt;
       for(int i = 0; i < datalist.count(); i++)
       {
           this->setColumnWidth(i,nColumWidth);
       }
       ButtonDelegate* opbtsBoxDelegate = new ButtonDelegate(this);
       connect(opbtsBoxDelegate,&ButtonDelegate::signalEditButtonClicked,this,&StorenbrTableView::SlotEditBtnClicked);
       connect(opbtsBoxDelegate,&ButtonDelegate::signalDeleteButtonClicked,this,&StorenbrTableView::SlotDelBtnClicked);
       //在第二列，第四列，添加combobox代理
       this->setItemDelegateForColumn(columncnt-1, opbtsBoxDelegate);
}
///
/// \brief StorenbrTableView::setModeldatalist
/// \param list
///
void StorenbrTableView::setModeldatalist(QList<QStringList> &list)
{
   m_nbrList = list;
   m_ptablemodel->setModelDatas(&m_nbrList);
   m_ptablemodel->refrush();
}
///
/// \brief StorenbrTableView::SlotCheckstatChanged
/// \param row
/// \param check
///记录选择状态的索引号
void StorenbrTableView::SlotCheckstatChanged(int row, bool check)
{
    int index = row;
    if(check)
    {
        // list 做改变

    }
    else {

    }

}
///
/// \brief StorenbrTableView::SlotEditBtnClicked
/// \param row
/// \param column
///
void StorenbrTableView::SlotEditBtnClicked(int row, int column)
{
  QString nbrinfo = m_nbrList[row].at(column);
    emit signalEditRowData(nbrinfo);
}
///
/// \brief StorenbrTableView::SlotDelBtnClicked
/// \param row
/// \param column
/// 单项 删除信息 此行列表信息
void StorenbrTableView::SlotDelBtnClicked(int row, int column)
{
    int ret = QMessageBox::warning(NULL, tr("提示"),
                                   tr("删除后,不可恢复,请谨慎操作!"),
                                   QMessageBox::Yes | QMessageBox::No,QMessageBox::No);
    if(ret == QMessageBox::No)
        return;
    //Qtring 需要删除当前信息
    m_nbrList.removeAt(row);
    QString nbrinfo = m_nbrList[row].at(column);
    emit signalDelRowData(nbrinfo);
     m_ptablemodel->refrush();
}

///
/// \brief StorenbrTableView::SlotFindNbrinfo
/// \param info
///实现查询功能方式
void StorenbrTableView::SlotFindNbrinfo(QString info,int column )
{
    if( info == "")
    {
        for(int i = 0 ; i < m_nbrList.size();++i)
        {
            this->setRowHidden(i,false);
        }
        return;
    }
    for(int i = 0; i < m_nbrList.size(); ++i)
    {
        QStringList rowlist=m_nbrList[i];
        if((column+1)<= rowlist.size())
        {
            QString columninfo = rowlist[column] ;
            if(columninfo.contains(info))
            {
                this->setRowHidden(i,false);
            }
            else{
                this->setRowHidden(i,true);
            }
        }
    }
}
///
/// \brief StorenbrTableView::SlotBatchDelInfo
/// 记录批量删除状态进行删除表格中的数据
void StorenbrTableView::SlotBatchDeltableInfo()
{
    QStringList delnbrlist;
    foreach(auto item,m_nbrList)
    {
        if (item[0] == "1")
        {
            delnbrlist.append(item[2] );
            m_nbrList.removeOne(item);
        }
    }
    // 记录批量删除编号信息
    if(delnbrlist.size() > 0)
    {
         //发送批量删除信号
            emit SignalBatchDel(delnbrlist);
            m_ptablemodel->refrush();
    }
 }


