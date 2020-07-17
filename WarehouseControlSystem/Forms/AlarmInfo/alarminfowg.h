#ifndef ALARMINFOWG_H
#define ALARMINFOWG_H

#include <QObject>
#include <QWidget>
#include <QSqlTableModel>
#include <QComboBox>
#include <QPushButton>
#include <QDateEdit>
#include <QTableView>
#include "UnitClass/TablepageWgClass/spiltpagesbyqsqltablemodel.h"
#include <QLineEdit>
#include "Forms/basefrom.h"
#include <QSqlTableModel>
#include<QDebug>
#include "datastructure.h"

class MySqlTableModel : public QSqlTableModel
{
     Q_OBJECT
public:
    MySqlTableModel(QObject * parent = 0, QSqlDatabase db = QSqlDatabase())
        : QSqlTableModel(parent,db) {;}
    QVariant GetAlarmLevelStr(int  level) const{
        switch (level) {
        case ALARMLEVEL::ESPSERIOUS:
            return "特别严重Ⅰ级";
            break;
        case ALARMLEVEL::SERIOUS:
            return "严重Ⅱ级";
            break;
        case ALARMLEVEL::MORSERIOUS:
            return "较重Ⅲ级";
            break;
        case ALARMLEVEL::COMSERIOUS:
            return "一般Ⅳ级";
            break;
        default:
            return "未定义";
            break;
        }
    }
    QVariant SetbackColor(QString str)const{
        if(str == "特别严重Ⅰ级")
        {
            return QVariant(QColor(Qt::red));
        }
        else if(str == "严重Ⅱ级")
        {
            return QVariant(QColor(255, 165, 0));
        }
        else if(str == "较重Ⅲ级")
        {
            return QVariant(QColor(Qt::yellow));
        }
        else if(str == "一般Ⅳ级")
        {
            return QVariant(QColor(Qt::blue));
        }
        return QVariant(QColor(Qt::cyan));
    }
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const
    {
        if (role == Qt::TextAlignmentRole)
        {
            return int(Qt::AlignHCenter | Qt::AlignVCenter);
        }
        if (role == Qt::DisplayRole)// 展示文本
        {
            int colum = index.column();
            QVariant test = QSqlTableModel::data(index,role);
            if(test.type() ==QVariant::DateTime ) //日期类型显示格式
          {
                QDateTime time  = test.toDateTime();
            return time.toString("yyyy-MM-dd ddd hh:mm:ss.zzz");
            }
            switch (colum) {
            case 1://报警等级
            {
                return GetAlarmLevelStr(test.toInt());
                break;
            }
            case 3://故障类型
            {
                switch (test.toInt()) {
                case ERRORTYPE::COMM:
                    return "通迅类";
                    break;
                case ERRORTYPE::HARDWARE:
                    return "硬件类型";
                    break;
                default:
                    return "未定义";
                    break;
                }
                break;
            }
            case  5://操作状态
            {
                switch (test.toInt()) {
                case AUTO:
                    return "自动";
                    break;
                case MANUAL:
                    return "手动";
                    break;
                default:
                    return "未定义";
                    break;
                }
            }
            default:
                break;
            }
        }
        if(role==Qt::BackgroundColorRole) //背景色显示
        {
            const  QVariant value(data(index,Qt::DisplayRole));
            int colum = index.column();
            QString str = value.toString();
            switch (colum) {
            case 1://报警等级
            {
                return  SetbackColor(str);
            }
            case 3://故障类型
                break;
            case  5://操作状态
                if(str== "自动")
                {
                    return QVariant(QColor(Qt::green));
                }
                else if(str== "手动"){
                    return QVariant(QColor(Qt::gray));
                }
                break;
            default:
                break;
            }
        }
        return QSqlTableModel::data(index,role);
    }
};
class AlarmInfoWg:public BaseFrom
{
    Q_OBJECT
public:
    AlarmInfoWg(QWidget *parent = 0);
private:
    QComboBox   *m_statcombox;//操作状态combox
    QLineEdit *m_devicelineEdit;//设备ID信息输入框
    QComboBox *m_levelcombox;//报警等级
    QComboBox *m_errortypecombox;//故障类型
    QPushButton *m_slectbtn;//查询按钮
    QPushButton *m_refreshbtn;//刷新按钮
    QTableView  *m_sqltableview;
    MySqlTableModel *m_sqltablemodel;
    SpiltPagesByQSqlTableModel *m_pagewg;
    QStringList m_levellist;
    QStringList m_errottypelist;
    QStringList m_statelist;
private:
    void InitTableViewUI();
    QString GetSelectSqlStr();
    uint8_t GetValue(QString str,int role);
private slots:
    void slotSlectTableInfo();
    void slotRefreshTableInfo();
};

#endif // ALARMINFOWG_H
