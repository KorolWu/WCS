#ifndef CURRENTTASK_H
#define CURRENTTASK_H

#include <QObject>
#include <QWidget>
#include "../basefrom.h"
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDateEdit>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
/**
 *
 * @author korol
 * @email wuwenpeng@cowain.com.cn
 * @date 2020-06-12 13:53:59
 * use 显示当前正在执行的任务
 */
class CurrentTask : public BaseFrom
{
public:
    CurrentTask(int width,int height,QWidget *parent);
private:
//    QPushButton *m_in_btn;
//    QPushButton *m_out_btn;
//    QPushButton *m_all_btn;
//    QDateEdit   *m_start_date;
//    QDateEdit   *m_end_date;
//    QPushButton *m_query_btn;
    QTableView  *m_table_view;
    QStandardItemModel *model;

    void initTableView();
    int width;
    int height;
};

#endif // CURRENTTASK_H
