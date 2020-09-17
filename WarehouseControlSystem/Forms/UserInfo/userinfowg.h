#ifndef USERINFOWG_H
#define USERINFOWG_H

#include <QObject>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QString>
#include <QSqlTableModel>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QHeaderView>
#include "Forms/basefrom.h"

class UserInfoWg:public BaseFrom
{
    Q_OBJECT

public:
    UserInfoWg(QWidget *parent = 0);
    ~UserInfoWg();
private:
    QPushButton *m_pAddBtn;
    QPushButton *m_PdelBtn;
    QPushButton *m_pRefreshBtn;
    QPushButton *m_pSaveBtn;
    QPushButton *m_pRevokeBtn;
    QTableView  *m_sqltableview;
    QSqlTableModel *m_sqltablemodel;
private slots:
    void slotaddnbrinfo();
    void  slotDelnbrinfo();
    void slotRefreshDataBase();
    void slotSavenbrinfo();
    void slotRevokeInfo();
};

#endif // USERINFOWG_H
