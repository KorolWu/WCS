#ifndef STORENBRINFOTABLEMODEL_H
#define STORENBRINFOTABLEMODEL_H

#include <QObject>
#include <QWidget>
#include <QTableView>
#include <QAbstractTableModel>
#include <QStringList>
#include <QHeaderView>
#include <QStyledItemDelegate>
#include <QSqlTableModel>

class StorenbrInfoTablemodel : public  QSqlQueryModel  /*QSqlTableModelQSqlQueryModel*/
{
    Q_OBJECT
public:
    explicit  StorenbrInfoTablemodel(QObject *parent = 0);
    ~StorenbrInfoTablemodel();
public:
    void SetTableHeader(QStringList list);
    void SetColumncnt(int colcnt);
    void setModelDatas(QList<QStringList> *list);
    //分页的数据说明
    int GetRowCount(); //得到总的记录数目
    int m_setpagerowsize;//设置每页显示的记录数目
    int  GetPageSize();//得到本页的数量
    void SetCurPage(int page);//设置本页的数据
    void SetPageSize(int size);//设置页码数量
    QList<QStringList>m_curpageDatalist; //平均分配每一页的数据情况，代表显示的当前的数据
    int m_iCurPage;
    int m_totalrecord;
public:
    //    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    // data
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    // headerdata
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    //    QMap<int, QVariant> itemData(const QModelIndex &index) const;
    //    bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles);

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    void refrush();
signals:
    void signalCheckDatachanged(int rowindex,bool check,QString nbr);
private:
    QStringList m_headerlist;
    int m_columncount;
    QList<QStringList>* m_storenbrList;

    enum storepostype{
        Large  = '1',
        Middle = '2',
        Small  = '3',
        Other = '4' ,
        Undefined =99
    };
};



#endif // STORENBRINFOTABLEMODEL_H
