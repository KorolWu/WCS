#ifndef EDITSTORENBRINFODIALOG_H
#define EDITSTORENBRINFODIALOG_H

#include <QObject>
#include <QWidget>
#include  "Forms/dialogabstractclass.h"
#include "datastructure.h"
#include "Myconfig.h"
#include <MysqlDataBase/readtabledata.h>
#include <QMouseEvent>
#include <QButtonGroup>
class EditStorenbrinfoDialog:public DialogAbstractClass
{
    Q_OBJECT
public:
    explicit   EditStorenbrinfoDialog(const QStringList &list,QString flag ,QWidget *parent);
public:
    void onYesBtnClicked();
signals:
    void signalAckBtn(QStringList datalist);
    void signalAckAdd(QStringList datalist);
private:
    QString m_idnbr;
//private:
//    QButtonGroup *Getradiogroup(QString list);
//    QButtonGroup *m_pButtonGroup;
//protected:
//    void mouseMoveEvent(QMouseEvent *event);
//    void mousePressEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);
//private:
//    QPoint mousePoint;
//    bool mouse_press;

};

#endif // EDITSTORENBRINFODIALOG_H
