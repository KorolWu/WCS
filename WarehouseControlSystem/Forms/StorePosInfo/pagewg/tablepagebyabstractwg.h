#ifndef TABLEPAGEBYABSTRACTWG_H
#define TABLEPAGEBYABSTRACTWG_H

#include <QObject>
#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSqlQuery>
class TablepagebyabstractWg:public  QWidget
{
    Q_OBJECT
public:
    TablepagebyabstractWg(QWidget *parent =0);
    void SetParam(int totalRecrodCount,/*QAbstractItemModel *p,*/QString name,int  PageRecordCount =25);//先设置 参数
    void InitpagefunWg();//初始化界面
    void updateParam();//更新界面参数变化的时候进行界面更新
public:
    // QAbstractItemModel *m_sqltableMode;
    int       m_currentPage;      //当前页
    int       m_totalPage; //总页数
    int       m_totalRecrodCount;     //总记录数
    int      m_PageRecordCount;//每页显示的行数目
    QString tablename;
private:
    QLabel *m_totalPageLabel;//总页文本
    QLabel     *m_currentPageLabel; //当前页文本
    QLineEdit  *m_switchPageLineEdit;//转到页输入框,回车触发跳转功能
    QPushButton   *m_prevButton;      //前一页按钮
    QPushButton   *m_nextButton;      //下一页按钮
    QPushButton *m_swtoButton; //转到指定页面
private:
    int  GetTableTotalRecordCount();
    int GetTablePageCount();
    void UpdateUIStatus();
    void SetTableTotalPageLabel();    // 功能: 设置总数页文本
public  slots:
    void  slotprepage();
    void  slotNextpage();
    void  slotToPage();
signals:
    void SetShowTableRecord(int limitdex); // 发送获得当前页进行展示数据
};

#endif // TABLEPAGEBYABSTRACTWG_H
