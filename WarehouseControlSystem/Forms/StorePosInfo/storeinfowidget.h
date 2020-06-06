#ifndef STOREINFOWIDGET_H
#define STOREINFOWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include "datastructure.h"
#include "Forms/StorePosInfo/storenbrtableview.h"

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
private slots:
    void slotaddnbrinfo();
    void  slotBatchDelnbrinfo();
    void  slotquenbrinfo();
    void slotImportnbrinfo();
private:
    MapStorePosInfoStru m_stroreposmap; //数据信息
    StorenbrTableView *m_ptableview;
};

#endif // STOREINFOWIDGET_H
