#include "storenbrtableview.h"
#include "buttondelegate.h"
#include "From/labeldelegate.h"
StorenbrTableView::StorenbrTableView(QWidget *parent):QTableView(parent)
{
      m_ptablemodel = new StorenbrInfoTablemodel();
     this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->verticalHeader()->hide();
    this->horizontalHeader()->setStretchLastSection(true); // 设置最后一列填充
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setFrameShape(QFrame::NoFrame);
    this->setStyleSheet("QTableView {alternate-background-color: rgb(200,200, 200);}");//设置交替颜色样式
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
       //在最后一列添加操作按钮
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
    emit signalEditRowData(row);
}
///
/// \brief StorenbrTableView::SlotDelBtnClicked
/// \param row
/// \param column
///
void StorenbrTableView::SlotDelBtnClicked(int row, int column)
{
 emit signalDelRowData(row);
}


