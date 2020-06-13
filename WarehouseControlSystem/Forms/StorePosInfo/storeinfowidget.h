#ifndef STOREINFOWIDGET_H
#define STOREINFOWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include "datastructure.h"
#include "Forms/StorePosInfo/storenbrtableview.h"
#include <QStringList>
#include "watingdialogwg.h"
#include <MysqlDataBase/readtabledata.h>

class StoreInfoWidget  : public QWidget
{
    Q_OBJECT
public:
    explicit StoreInfoWidget(QWidget *parent = 0);
    ~StoreInfoWidget();
private:
    QPushButton *m_pAddBtn;
    QPushButton *m_pBatchDelBtn;
    QLineEdit *m_pnbrlineEdit;
    QPushButton *m_pquenbrBtn;
    QPushButton *m_pImportBtn;
    QPushButton *m_pExportBtn;
private slots:
    void slotaddnbrinfo();
    void  slotBatchDelnbrinfo();
    void  slotquenbrinfo();
    void slotImportnbrinfo();
    void slotExportnbrinfo();
private:
    void  Dataselectfromdatabase();
    void  DelDataBaseInfo(  QList<QVariant> nbrlist);
     QList<QStringList> GetdatalistFromstru( QMap<QString,StorePosInfoStru> infoMap);
public slots:
    void  SlotDelSinglerow(QString nbrinfo );
    void  SlotBatchDelData(  QList<QVariant> nbrlist);
signals:
    void signalfindinfo(QString nbrinfo,int clomun);
    void signalBatchDel();
private:
    MapStorePosInfoStru m_stroreposmap; //数据信息
    StorenbrTableView *m_ptableview;
    ReadTableData m_databaseopob;

};

#endif // STOREINFOWIDGET_H
