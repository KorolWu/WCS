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
#include "pagewg/tablepagebyabstractwg.h"

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
    QPushButton *m_pRefreshBtn;
private slots:
    void slotaddnbrinfo();
    void  slotBatchDelnbrinfo();
    void  slotquenbrinfo();
    void slotImportnbrinfo();
    void slotExportnbrinfo();
    void slotEditData(QStringList datalist);
    void slottableeditbtn(QString ,int row);
    void  slotSetCurPageData(int ipage);
    void slotRefreshDataBase();
private:
    void  Dataselectfromdatabase();
    bool  DelDataBaseInfo( QList<QVariant> nbrlist);
    QList<QStringList> GetdatalistFromstru( QMap<QString,StorePosInfoStru> infoMap);
    bool CheckBoxNbrInfo(QString boxnbr);
public slots:
    void  SlotDelSinglerow(QString nbrinfo,int row );
    void  SlotBatchDelData(  QList<QVariant> nbrlist);
    void SlotupdatePageUI(int size);
signals:
    void signalfindinfo(QString nbrinfo,int clomun);
    void signalBatchDel();
    void signalUpdatetable(QStringList ,int row) ;

private:
    enum storepostype{
        Large  = '1',
        Middle = '2',
        Small  = '3',
        Other = '4' ,
        Undefined =99
    };
    enum storestat{

    };
private:
    void DelDialogBaseob();
private:
    MapStorePosInfoStru m_stroreposmap; //数据信息
    StorenbrTableView *m_ptableview;
    ReadTableData m_databaseopob;
    int m_editrow ;
    TablepagebyabstractWg *m_pagewg;
    WatingDialogWg m_waitwg;
};



#endif // STOREINFOWIDGET_H
