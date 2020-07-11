#ifndef STORENBRTABLEVIEW_H
#define STORENBRTABLEVIEW_H

#include <QObject>
#include <QWidget>
#include <QTableView>
#include "Forms/StorePosInfo/storenbrinfotablemodel.h"

class StorenbrTableView : public QTableView
{
    Q_OBJECT
public:
    explicit    StorenbrTableView( QWidget *parent= 0);
    ~StorenbrTableView();
public:
    void SetTableHeaderData(QStringList datalist,int columncnt);
    void setModeldatalist(QList<QStringList>& list);
    StorenbrInfoTablemodel * GetStoretablemodel(){
        return m_ptablemodel;
    }
public slots:
    void SlotCheckstatChanged(int row, bool check,QString nbr);
    void SlotEditBtnClicked(int row,int column);
    void SlotDelBtnClicked(int row,int column);
    void SlotFindNbrinfo(QString info , int column = 2);
    void SlotaddNbrInfo(QStringList list);
    void SlotEditInfo(QStringList newlist,int row);
public:
    QList<QVariant> GetBatchDellist();
    void BatchDeltableInfo();
    void Delsinglerow(int row);
    int GetDataIndex(int row);
    int m_findtotalnum;
    void SetTableshowRowsSize();
    int  GetIndexByNbrinfo(QString nbr);
signals:
    void signalEditRowData(QString nbrinfo,int row);
    void signalDelRowData(QString nbrinfo,int row);
    void signalTableDataSizechange(int size);
private:
    StorenbrInfoTablemodel *m_ptablemodel;
    QList<QStringList> m_nbrList;
    QList<QStringList> m_findbeforenbrList;
    bool m_findflag ;

    // QWidget interface
    //public slots:
    // virtual void setVisible(bool visible);
    //public:
    // virtual QSize sizeHint() const;
    // virtual QSize minimumSizeHint() const;
};

#endif // STORENBRTABLEVIEW_H
