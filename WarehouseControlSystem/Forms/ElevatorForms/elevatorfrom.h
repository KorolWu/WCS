#ifndef ELEVATORFROM_H
#define ELEVATORFROM_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QSqlQueryModel>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <Forms/basefrom.h>
#include <QDebug>
#include <QSpinBox>
#include "Forms/ElevatorForms/addelevatorform.h"
/**
 *
 * @author korol
 * @email wuwenpeng@cowain.com.cn
 * @date 2020-06-01 16:02:59
 * use 小车硬件信息显示
 */
class ElevatorFrom : public BaseFrom
{
    Q_OBJECT
public:
    explicit ElevatorFrom(int width, int height,QWidget *parent = 0);

signals:

public slots:
    void onAddClicked();
private:
    QTableView *p_table_view;
    QPushButton *p_add_btn;
    QPushButton *p_delete_btn;
    QPushButton *p_export_btn;
    QPushButton *p_query_btn;
    QLineEdit *p_input_text;
};

#endif // ELEVATORFROM_H
