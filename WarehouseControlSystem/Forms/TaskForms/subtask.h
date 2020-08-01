#ifndef SUBTASK_H
#define SUBTASK_H

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
#include <QSqlQuery>
#include <QSqlTableModel>
#include "labeldelegateV1.h"
#include "../basefrom.h"
#include "UnitClass/TablepageWgClass/spiltpagesbyqsqltablemodel.h"
/**
 * @brief The SubTask class
 * @date  2020/7/25
 * @title 用来显示任务生成的子任务
 */
class SubTask : public BaseFrom
{
    Q_OBJECT
public:
    SubTask(int width, int height, QWidget *parent = 0);
    QPushButton *m_in_btn;
    QPushButton *m_out_btn;
    QPushButton *m_all_btn;
    QLineEdit   *m_task_edit;
    QPushButton *m_query_btn;
    QTableView  *m_table_view;
    QSqlQueryModel *model;
    SpiltPagesByQSqlTableModel *m_pagewg;

    void initTableView();
    int m_width;
    int m_height;
signals:

public slots:
    void selectTask();
};

#endif // SUBTASK_H
