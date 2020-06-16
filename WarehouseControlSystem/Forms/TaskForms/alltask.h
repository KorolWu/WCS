#ifndef ALLTASK_H
#define ALLTASK_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include <QLabel>
#include <QHeaderView>
#include <QTableView>
#include <QStandardItemModel>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include "../basefrom.h"

class AllTask : public BaseFrom
{
    Q_OBJECT
public:
    AllTask(int width,int height,QWidget *parent);
    QPushButton *m_in_btn;
    QPushButton *m_out_btn;
    QPushButton *m_all_btn;
    QDateEdit   *m_start_date;
    QDateEdit   *m_end_date;
    QPushButton *m_query_btn;
    QTableView  *m_table_view;
    QSqlTableModel *model;

    void initTableView();
    int width;
    int height;
};

#endif // ALLTASK_H