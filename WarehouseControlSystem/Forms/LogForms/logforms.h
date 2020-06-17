#ifndef LOGFORMS_H
#define LOGFORMS_H

#include <QObject>
#include "../basefrom.h"
#include <QPushButton>
#include <QDateEdit>
#include <QTableView>
#include <QSqlTableModel>
#include <QHeaderView>
#include <QLabel>
#include <QComboBox>
/**
 * @author korol
 * @email wuwenpeng@cowain.com.cn
 * @date 2020-06-16 16:02:59
 * use Log日志显示基类
 */
class LogForms : public BaseFrom
{
public:
    LogForms(int width, int height,QWidget *parent);
    QComboBox   *m_com_box;
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

#endif // LOGFORMS_H
