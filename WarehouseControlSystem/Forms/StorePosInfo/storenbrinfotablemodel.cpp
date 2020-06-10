#include "storenbrinfotablemodel.h"
#include <QDebug>


StorenbrInfoTablemodel::StorenbrInfoTablemodel(QObject *parent) :QSqlTableModel(parent)
{
    m_columncount = 0 ;
    m_headerlist.clear();
    m_storenbrList = NULL;
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
        return m_storenbrList->size();

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
        if(column == 0 )
            return "";
       return m_storenbrList->at(row).at(column);;
    }
    else if (role == Qt::CheckStateRole)
    {
        int row = index.row();
        int column = index.column();
        if(column == 0)
        {
          QString checkstr = m_storenbrList->at(row).at(column);
            bool check = false;
            if(checkstr == "1")
            {
                check = true;
            }
            return check ? Qt::Checked:Qt::Unchecked;
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
                        QStringList list =  m_storenbrList->at(row);
                        list[0] = stat;
                        m_storenbrList->replace(row,list);
                      emit  signalCheckDatachanged (row, true);
                    }
                }
                else{
                    QStringList list =  m_storenbrList->at(row);
                    list[0] = "0";
                    m_storenbrList->replace(row,list);
                      emit  signalCheckDatachanged (row, false);
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


