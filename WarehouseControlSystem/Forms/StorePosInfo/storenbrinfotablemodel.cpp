#include "storenbrinfotablemodel.h"
#include <QDebug>

//QSqlTableModel
//QAbstractTableModel
StorenbrInfoTablemodel::StorenbrInfoTablemodel(QObject *parent) :QSqlQueryModel(parent)
{
    m_columncount = 0 ;
    m_headerlist.clear();
    m_storenbrList = NULL;
    m_setpagerowsize = 20;
}
///
/// \brief StorenbrInfoTablemodel::~StorenbrInfoTablemodel
///
StorenbrInfoTablemodel::~StorenbrInfoTablemodel()
{

}

void StorenbrInfoTablemodel::SetTableHeader(QStringList list)
{
    m_headerlist = list;
}
///
/// \brief StorenbrInfoTablemodel::SetColumncnt
/// \param colcnt
/// 设置表格的列数目
void StorenbrInfoTablemodel::SetColumncnt(int colcnt)
{
    m_columncount =  colcnt;
}

void StorenbrInfoTablemodel::setModelDatas(QList<QStringList> *list)
{
    m_storenbrList = list;
 //  m_curpageDatalist = list;
    m_setpagerowsize =20;
    m_totalrecord = m_storenbrList->size();
    SetCurPage(0);
}

int StorenbrInfoTablemodel::GetRowCount()
{
        m_totalrecord = m_storenbrList->size();
    return m_totalrecord;
}

int StorenbrInfoTablemodel::GetPageSize()
{
    int size = (GetRowCount() % m_setpagerowsize == 0)
            ? (GetRowCount() / m_setpagerowsize)
            : (GetRowCount() / m_setpagerowsize + 1);
    if(size == 0)
        size = 1;
    return size;
}

void StorenbrInfoTablemodel::SetCurPage(int iPage)
{
    //当前页必须小于总页数
    if(iPage < 0)
        return;
    if (iPage < GetPageSize())
    {
        m_iCurPage = iPage;
        //查询起始索引1
        int iStart = m_setpagerowsize * m_iCurPage;
        //查询结束索引
        int iend = 0;
        //如果本页可以填满
        if (iStart + m_setpagerowsize < GetRowCount())
        {
            iend = iStart + m_setpagerowsize-1;
        }
        //本页没有被填满
        else
        {
            iend = GetRowCount() - 1;
        }
        //填充当前页数据
        m_curpageDatalist.clear();
        for (int i = iStart; i <= iend; ++i)
        {
            if(i < m_storenbrList->size())
           {
                m_curpageDatalist.append(m_storenbrList->at(i));
            }
        }
        refrush();
    }
    return;
}
///
/// \brief StorenbrInfoTablemodel::rowCount
/// \param parent
/// \return
///
int StorenbrInfoTablemodel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    if(NULL == m_storenbrList)
        return 0;
    else
        return m_curpageDatalist.size(); //有争议
}
///
/// \brief StorenbrInfoTablemodel::columnCount
/// \param parent
/// \return
/// 设置列的数目
int StorenbrInfoTablemodel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_columncount;
}

QVariant StorenbrInfoTablemodel::data(const QModelIndex &index, int role) const
{
    //表格数据
    if (!index.isValid())
        return QVariant();
    if (role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    else if (role == Qt::DisplayRole)
    {
        int row = index.row();
        int column = index.column();
        if(row >=  m_curpageDatalist.size())
            return QVariant();
      // QString str = m_storenbrList->at(row).at(column);//原来旧
       QString str = m_curpageDatalist.at(row).at(column);  //变更增加
        switch (column) {
        case 0:
              return "";
        case 7://仓位状态文字显示
            if(str == "0")
            {
                return "空闲";
            }
            else if(str == "1")
            {
                  return "占用";
            }
            else if(str == "2")
            {
                  return "锁定";
            }
        default:
          return m_curpageDatalist.at(row).at(column);
        }
    }
    else if (role == Qt::CheckStateRole) //第一列选中状态编辑
    {
        int row = index.row();
        int column = index.column();
        if(column == 0)
        {
          QString checkstr = m_curpageDatalist.at(row).at(column);
            bool check = false;
            if(checkstr == "1")
            {
                check = true;
            }
            return check ? Qt::Checked:Qt::Unchecked;
        }
    }
    else if(role == Qt::BackgroundRole)
    {
        int row = index.row();
        int column = index.column();
        QString str = m_curpageDatalist.at(row).at(column);
        switch (index.column()) {
        case 7://仓位状态设置样式
        {
            if(str == "1")
              return QVariant(QColor(Qt::red));
            else if(str == "2"){
                     return QVariant(QColor(Qt::yellow));
            }
            else{
                  return QVariant(QColor(Qt::green));
            }
        }
        default:
         return QVariant();
        }
    }
    return QVariant();
}

bool StorenbrInfoTablemodel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //表格数据变化
    if (data(index, role) != value)
    {
        // FIXME: Implement me!
        int row = index.row();
        int column = index.column();
        QVariant vatemp = value;
        QString strcurrenttext = vatemp.toString();
        if(strcurrenttext.isEmpty())
        {
            return false;
        }
        //计算实际数据的下标
        int dataindex = index.row() + m_iCurPage * m_setpagerowsize; //获得实际显示数据记录的索引编号
        if(column == 0) //索引号变化变更 被选中
        {
            //记录索引号对应的 料箱编号信息
            if((role == Qt::CheckStateRole))
            {
                if(value == Qt::Checked)
                {
                    QString stat = "1";
                    if(m_storenbrList)
                    {
                        QStringList list =  m_storenbrList->at(dataindex);
                        list[0] = stat;
                        m_storenbrList->replace(dataindex,list); //改变总的数据
                        m_curpageDatalist.replace(row,list);
                        QString nbr = list[1];
                      emit  signalCheckDatachanged (dataindex, true,nbr);
                    }
                }
                else{
                    QStringList list =  m_storenbrList->at(dataindex);
                    list[0] = "0";
                    m_storenbrList->replace(dataindex,list);
                      m_curpageDatalist.replace(row,list);
                          QString nbr = list[1];
                      emit  signalCheckDatachanged (dataindex, false,nbr);
                }
            }
        }
        return true;
    }
    return false;
}
/////
///// \brief StorenbrInfoTablemodel::headerData
///// \param section
/// \param orientation 表格 横向  纵向
/// \param role 角色
/// \return
///DisplayRole //代表文本
QVariant StorenbrInfoTablemodel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        return m_headerlist[section];
    }
    return QAbstractTableModel::headerData(section,orientation,role);
}

Qt::ItemFlags StorenbrInfoTablemodel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index);

  if( index.column() == 0 ) //第一列可编辑
  {
      return (Qt::ItemIsEnabled|Qt::ItemIsSelectable |Qt::ItemIsUserCheckable );
  }
  Qt::ItemFlags  flag = Qt::ItemIsEnabled | Qt::ItemIsSelectable  ;
    return flag;
}

void StorenbrInfoTablemodel::refrush()
{
    beginResetModel();
    endResetModel();
}


