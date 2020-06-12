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
    void SlotCheckstatChanged(int row, bool check);
    void SlotEditBtnClicked(int row,int column);
    void SlotDelBtnClicked(int row,int column);
    void SlotFindNbrinfo(QString info , int column = 2);
    void SlotBatchDeltableInfo();
signals:
    void signalEditRowData(QString nbrinfo);
     void signalDelRowData(QString nbrinfo);
     void SignalBatchDel(  QList<QVariant> datalist);
private:
    StorenbrInfoTablemodel *m_ptablemodel;
   QList<QStringList> m_nbrList;
   // QWidget interface
   //public slots:
   // virtual void setVisible(bool visible);
   //public:
   // virtual QSize sizeHint() const;
   // virtual QSize minimumSizeHint() const;
};

#endif // STORENBRTABLEVIEW_H
