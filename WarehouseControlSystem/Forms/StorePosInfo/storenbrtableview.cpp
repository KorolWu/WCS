#include "storenbrtableview.h"
#include "buttondelegate.h"
#include <QMessageBox>
const  QString   headstlye ="QHeaderView:section{height:32px;font:12px;border:3;color: rgb(250, 250, 250);background-color: rgba(68, 69, 71,200);}";
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
    this->horizontalHeader()->setStyleSheet(headstlye);
    this->verticalHeader()->setStyleSheet(headstlye);
    m_findflag = true;
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
///
void StorenbrTableView::SlotCheckstatChanged(int row, bool check,QString nbr)
{
    Q_UNUSED(row)
    //  int index = row;
    if(!m_findflag)//查询状态中数据发生了变化
    {
        foreach(auto item,m_findbeforenbrList)
        {
            if (item[1] == nbr)
            {
                int index= m_findbeforenbrList.indexOf(item);
                if(check)
                {
                    // list 做改变
                    item[0] = "1";
                }
                else {
                    item[0] = "0";
                }
                m_findbeforenbrList.replace(index,item);
                break;
            }
        }
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
    // QString nbrinfo = m_nbrList[row].at(1);
    QString nbrinfo = m_ptablemodel->m_curpageDatalist[row].at(1);
    emit signalEditRowData(nbrinfo,row);
}
///
/// \brief StorenbrTableView::SlotDelBtnClicked
/// \param row
/// \param column
/// 单项 删除信息 此行列表信息
void StorenbrTableView::SlotDelBtnClicked(int row, int column)
{
    Q_UNUSED(column)
    int ret = QMessageBox::warning(NULL, tr("提示"),
                                   tr("删除后,不可恢复,请谨慎操作!"),
                                   QMessageBox::Yes | QMessageBox::No,QMessageBox::No);
    if(ret == QMessageBox::No)
        return;
    //QString nbrinfo = m_nbrList[row].at(column);
    QString nbrinfo = m_ptablemodel->m_curpageDatalist[row].at(1);
    emit signalDelRowData(nbrinfo,row);
}

///
/// \brief StorenbrTableView::SlotFindNbrinfo
/// \param info
///实现查询功能方式

void StorenbrTableView::SlotFindNbrinfo(QString info,int column )
{  
    //查询逻辑是重新进行数据分页计算
    //更新widget按钮总页数目更新当前
    QList<QStringList> tempdatalist;
    if( info == "") //所有条件符合显示当前页更新
    {
        m_nbrList = m_findbeforenbrList;
        m_findflag = true;
        SetTableshowRowsSize();
        m_ptablemodel->refrush();
        //        for(int i = 0 ; i < m_nbrList.size();++i)
        //        {
        //           // this->setRowHidden(i,false);
        //        }
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
                tempdatalist.append(rowlist);
                //this->setRowHidden(i,false);
            }
            else{
                //  this->setRowHidden(i,true);
            }
        }
    }
    if(tempdatalist.size() > 0)
    {
        m_findtotalnum = tempdatalist.size();
        if(m_findflag)
        {
            m_findbeforenbrList = m_nbrList;
            m_findflag = false;
        }
        m_nbrList = tempdatalist; //数据重新更新
        m_ptablemodel->m_totalrecord =m_findtotalnum;
        if(m_ptablemodel->m_iCurPage>= m_ptablemodel->GetPageSize())
        {
            m_ptablemodel->m_iCurPage = 0;
        }
        m_ptablemodel->SetCurPage(m_ptablemodel->m_iCurPage);
        emit signalTableDataSizechange(m_nbrList.size());
        m_ptablemodel->refrush();
    }
    else{ //没有查询到相关的信息内容

    }
}
///
/// \brief StorenbrTableView::SlotaddNbrInfo
/// \param list
///新增插入
void StorenbrTableView::SlotaddNbrInfo(QStringList list)
{
    QModelIndex index = this->selectionModel()->currentIndex();
    int iSel = index.row();
    if(iSel < 0)
    {
        iSel = 0;
    }
    int  curstateiSel = GetDataIndex(iSel);
    int sizerow = m_nbrList.size();
    QString nbr = m_nbrList[iSel].at(1);
    m_nbrList.insert(curstateiSel,list);
    //若为查询状态，则要更新原有的总数据--------------------
    if(!m_findflag)
    {
        //找到编号对应的索引信息
        int allindex = GetIndexByNbrinfo(nbr);
        if(allindex>=0 && allindex<m_findbeforenbrList.size())
        {
            m_findbeforenbrList.insert(allindex,list);
        }
    }
    //若为查询状态，则要更新原有的总数据-------------------
    //更新页的状态
    SetTableshowRowsSize();
    m_ptablemodel->refrush();
    //新增
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
    if(row < 0)
        return;
    int dataindex = GetDataIndex( row); //获得实际显示数据记录的索引编
    if(m_nbrList.size() > dataindex&&dataindex>=0  )
    {
        //若为查询状态，则要更新原有的总数据--------------------
        if(!m_findflag)
        {
            QString nbr = m_nbrList[dataindex].at(1);
            //找到编号对应的索引信息
            int allindex = GetIndexByNbrinfo(nbr);
            if(allindex>=0 && allindex<m_findbeforenbrList.size())
            {
                m_findbeforenbrList.replace(allindex,newlist);
            }
        }
        //若为查询状态，则要更新原有的总数据--------------------
        m_nbrList.replace(dataindex,newlist);
        m_ptablemodel->m_curpageDatalist.replace(row,newlist);//编辑过程不涉及到页码的变化
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
    //    foreach(auto item,m_ptablemodel->m_curpageDatalist)
    //    {
    //        if (item[0] == "1")
    //        {
    //            delnbrlist.append(item[1] );
    //            m_ptablemodel->m_curpageDatalist.removeOne(item);
    //        }
    //    }
    //若为查询状态，则要更新原有的总数据--------------------
    if(!m_findflag)
    {
        //找到编号对应的索引信息
        foreach(auto item,m_findbeforenbrList)
        {
            if (item[0] == "1")
            {
                m_findbeforenbrList.removeOne(item);
            }
        }
    }
    //若为查询状态，则要更新原有的总数据--------------------
    // 记录批量删除编号信息
    if(delnbrlist.size() > 0)
    {
        //发送批量删除信号 //更新页的状态
        SetTableshowRowsSize();
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
    int dataindex = GetDataIndex( row); //获得实际显示数据记录的索引编
    if(dataindex>=0&& dataindex<m_nbrList.size())
    {
        //若为查询状态，则要更新原有的总数据--------------------
        if(!m_findflag)//如果是查询状态
        {
            QString nbr = m_nbrList[dataindex].at(1);
            int allindex = GetIndexByNbrinfo(nbr);
            if(allindex>=0&& allindex<m_findbeforenbrList.size())
            {
                m_findbeforenbrList.removeAt(dataindex);
            }
        }
        //若为查询状态，则要更新原有的总数据--------------------
        m_nbrList.removeAt(dataindex);
        // m_ptablemodel->m_curpageDatalist.removeAt(row);//代表的是表格中显示的数据，页面表格会更新
        SetTableshowRowsSize();
        m_ptablemodel->refrush();
    }
}

int StorenbrTableView::GetDataIndex(int row)
{
    return row + m_ptablemodel->m_iCurPage*m_ptablemodel->m_setpagerowsize; //获得实际显示数据记录的索引编
}

void StorenbrTableView::SetTableshowRowsSize()
{
    m_ptablemodel->m_totalrecord = m_nbrList.size();
    if(m_ptablemodel->m_iCurPage >= m_ptablemodel->GetPageSize())
    {
        m_ptablemodel->m_iCurPage = 0;
    }
    m_ptablemodel->SetCurPage(m_ptablemodel->m_iCurPage);//显示数据进行改变的方式
    emit signalTableDataSizechange(m_nbrList.size());
}

int StorenbrTableView::GetIndexByNbrinfo(QString nbr)
{
    int allindex = -1;
    foreach(auto item,m_nbrList)
    {
        if (item[1] ==nbr)
        {
            allindex = m_nbrList.indexOf(item);
            break;
        }
    }
    return allindex;
}


