#ifndef STORENBRTABLEVIEW_H
#define STORENBRTABLEVIEW_H

#include <QObject>
#include <QWidget>
#include <QTableView>
#include "From/StorePosInfo/storenbrinfotablemodel.h"

class StorenbrTableView : public QTableView
{
    Q_OBJECT
public:
 explicit    StorenbrTableView( QWidget *parent= 0);
    ~StorenbrTableView();
public:
    void SetTableHeaderData(QStringList datalist,int columncnt);
    void setModeldatalist(QList<QStringList>& list);
public slots:
    void SlotCheckstatChanged(int row, bool check);
    void SlotEditBtnClicked(int row,int column);
    void SlotDelBtnClicked(int row,int column);
signals:
    void signalEditRowData(int row);
     void signalDelRowData(int row);
private:
     StorenbrInfoTablemodel *m_ptablemodel;
     QList<QStringList> m_nbrList;
     //QWidget interface
     //public slots:
     //virtual void setVisible(bool visible);
     //public:
     // virtual QSize sizeHint() const;
     // virtual QSize minimumSizeHint() const;
};

#endif // STORENBRTABLEVIEW_H
