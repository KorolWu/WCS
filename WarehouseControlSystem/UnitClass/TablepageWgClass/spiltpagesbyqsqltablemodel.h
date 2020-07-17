#ifndef SPILTPAGESBYQSQLTABLEMODEL_H
#define SPILTPAGESBYQSQLTABLEMODEL_H

#include <QObject>
#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSqlQuery>

class SpiltPagesByQSqlTableModel:public  QWidget
{
    Q_OBJECT
public:
    SpiltPagesByQSqlTableModel(QWidget *parent =0);
    ~SpiltPagesByQSqlTableModel();
    void SetParam(QSqlQueryModel *p,QString name,int  PageRecordCount =25);//先设置 参数
    void InitpagefunWg();//初始化界面
    void updateParam(int totalRecrodCount,QString sql);//表格数据变化的时候重新计算表格总的数量，直接查询表格更新参数
private:
    QSqlQueryModel *m_sqltableMode;
    int       m_currentPage;      //当前页
    int       m_totalPage; //总页数
    int       m_totalRecrodCount;     //总记录数
    int      m_PageRecordCount;//每页显示的行数目
    QString tablename;
    QString m_sqlstr;
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
    void SetShowTableRecord(int limitdex);
    void UpdateUIStatus();
    // 功能: 设置总数页文本
    void SetTableTotalPageLabel();
private slots:
    void  slotprepage();
    void  slotNextpage();
    void  slotToPage();
};

#endif // SPILTPAGESBYQSQLTABLEMODEL_H
