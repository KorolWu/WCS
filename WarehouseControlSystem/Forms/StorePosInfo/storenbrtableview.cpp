#include "storenbrtableview.h"
#include "buttondelegate.h"
#include <QMessageBox>
StorenbrTableView::StorenbrTableView(QWidget *parent):QTableView(parent)
{
    m_ptablemodel = new StorenbrInfoTablemodel();
    //    m_ptablemodel->setTable("t_storeposinfo");
    //    m_ptablemodel->select();
    //    m_ptablemodel->insertColumn(0);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->verticalHeader()->hide();
    this->horizontalHeader()->setStretchLastSection(true); // 设置最后一列填充
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setFrameShape(QFrame::NoFrame);
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
    Q_UNUSED(row)
    //  int index = row;
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
    Q_UNUSED(column)
    QString nbrinfo = m_nbrList[row].at(1);
    emit signalEditRowData(nbrinfo,row);
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
    QString nbrinfo = m_nbrList[row].at(column);
    emit signalDelRowData(nbrinfo,row);
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
/// \brief StorenbrTableView::SlotaddNbrInfo
/// \param list
///新增插入
void StorenbrTableView::SlotaddNbrInfo(QStringList list)
{
    int sizerow = m_nbrList.size();
    m_nbrList.append(list);
    m_ptablemodel->refrush();
    this->selectRow(sizerow);
}
///
/// \brief StorenbrTableView::SlotEditInfo
/// \param newlist
/// \param row
///编辑数据进行替换
void StorenbrTableView::SlotEditInfo(QStringList newlist, int row)
{
    //替换
    if(m_nbrList.size() > row )
    {
        m_nbrList.replace(row,newlist);
          m_ptablemodel->refrush();
    }
}

QList<QVariant> StorenbrTableView::GetBatchDellist()
{
    QList<QVariant> delnbrlist;
    foreach(auto item,m_nbrList)
    {
        if (item[0] == "1")
        {
            delnbrlist.append(item[1] );
        }
    }
    return delnbrlist;
}
///
/// \brief StorenbrTableView::BatchDeltableInfo
///批量删除表格中的数据
void StorenbrTableView::BatchDeltableInfo()
{
    QList<QVariant> delnbrlist;
    foreach(auto item,m_nbrList)
    {
        if (item[0] == "1")
        {
            delnbrlist.append(item[1] );
            m_nbrList.removeOne(item);
        }
    }
    // 记录批量删除编号信息
    if(delnbrlist.size() > 0)
    {
        //发送批量删除信号
        m_ptablemodel->refrush();
    }
}
///
/// \brief StorenbrTableView::Delsinglerow
/// \param row
///更新表格中的数据
void StorenbrTableView::Delsinglerow(int row)
{
    //Qtring 需要删除当前信息
    m_nbrList.removeAt(row);
    m_ptablemodel->refrush();
}


