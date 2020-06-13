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

class StorenbrInfoTablemodel : public  QAbstractTableModel  /*QSqlTableModel*/
{
    Q_OBJECT
public:
    explicit  StorenbrInfoTablemodel(QObject *parent = 0);
    ~StorenbrInfoTablemodel();
public:
    void SetTableHeader(QStringList list);
    void SetColumncnt(int colcnt);
    void setModelDatas(QList<QStringList> *list);
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
     void signalCheckDatachanged(int rowindex,bool check);
private:
    QStringList m_headerlist;
    int m_columncount;
  QList<QStringList>* m_storenbrList;
};



#endif // STORENBRINFOTABLEMODEL_H
