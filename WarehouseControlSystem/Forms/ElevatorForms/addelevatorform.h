#ifndef ADDELEVATORFORM_H
#define ADDELEVATORFORM_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QApplication>
#include <QDesktopWidget>
#include <QIcon>
#include "../dialogabstractclass.h"
#include "datastructure.h"
#include "Myconfig.h"
#include "MysqlDataBase/crudbaseoperation.h"
/**
 *
 * @author korol
 * @email wuwenpeng@cowain.com.cn
 * @date 2020-06-08 16:02:59
 * use 增加硬件（电梯）交互页面
 */
class AddElevatorForm : public DialogAbstractClass
{
    Q_OBJECT
public:
    explicit AddElevatorForm(const QStringList &list,QString flag,QWidget *parent = 0);

signals:
    void insert_emit();
public slots:

    // DialogAbstractClass interface
public:
    void onYesBtnClicked();
    void onCleanBtnClicked();
};

#endif // ADDELEVATORFORM_H
