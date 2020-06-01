#ifndef AGVFORM_H
#define AGVFORM_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QSqlQueryModel>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <From/adddevice.h>
/**
 *
 * @author korol
 * @email wuwenpeng@cowain.com.cn
 * @date 2020-06-01 16:02:59
 * use 小车硬件信息显示
 */
class AgvForm : public QWidget
{
    Q_OBJECT
public:
    explicit AgvForm(int width,int height,QWidget *parent = 0);

signals:

public slots:
    void onAddClicked();
private:
    QTableWidget *p_table_widget;
    QPushButton *p_add_btn;
    QPushButton *p_delete_btn;
    QPushButton *p_export_btn;
    QPushButton *p_query_btn;
    QLineEdit *p_input_text;
};

#endif // AGVFORM_H
