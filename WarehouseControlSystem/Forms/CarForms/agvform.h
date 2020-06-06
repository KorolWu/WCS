#ifndef AGVFORM_H
#define AGVFORM_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QSqlQueryModel>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <Forms/CarForms/adddevice.h>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <Forms/CarForms/CarStatusFrom.h>
#include <Forms/CarForms/labeldelegate.h>
#include <Forms/CarForms/progressbardelegate.h>
#include <Forms/basefrom.h>
#include <QTableView>
#include <QSqlTableModel>
/**
 *
 * @author korol
 * @email wuwenpeng@cowain.com.cn
 * @date 2020-06-01 16:02:59
 * use 小车硬件信息显示
 */
class AgvForm : public BaseFrom
{
    Q_OBJECT
public:
    explicit AgvForm(int width,int height,QWidget *parent = 0);

signals:

public slots:
    void onAddClicked();
    void tableRowClicked();
    void refreshTable();
private:
    QTableView *p_table_view;
    QPushButton *p_add_btn;
    QPushButton *p_delete_btn;
    QPushButton *p_export_btn;
    QPushButton *p_query_btn;
    QLineEdit *p_input_text;
    CarStatusFrom *p_car_info;
    QSqlTableModel *model;
};

#endif // AGVFORM_H
