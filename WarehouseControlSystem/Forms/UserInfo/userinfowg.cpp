#include "userinfowg.h"
#include <QGroupBox>

UserInfoWg::UserInfoWg( QWidget *parent):BaseFrom(parent)
{
    this->resize(parent->width(),parent->height());
    // 删除 按钮  刷新按钮
    //Init UI
    QVBoxLayout *pmainlayout = new QVBoxLayout;
    setLayout(pmainlayout);
    QLabel *pshowlabeltitle = new QLabel(tr("当前位置：WCS系统<<用户管理..."));
    pmainlayout->addWidget(pshowlabeltitle);
    // pmainlayout->setSpacing(10);
    QHBoxLayout *pbtnLayout = new QHBoxLayout();

    m_pAddBtn = new QPushButton(tr("添加"),this);
    m_pAddBtn->setIcon(QIcon(":/resouse/Image/add.png"));
    m_pAddBtn->setLayoutDirection(Qt::LayoutDirectionAuto);
    pbtnLayout->addWidget(m_pAddBtn);
    connect(m_pAddBtn,&QPushButton::clicked,this,&UserInfoWg::slotaddnbrinfo);
    m_PdelBtn = new QPushButton(tr("删除"),this);
    m_PdelBtn->setIcon(QIcon(":/resouse/Image/delete.png"));
    pbtnLayout->addWidget(m_PdelBtn);
    connect(m_PdelBtn,&QPushButton::clicked,this,&UserInfoWg::slotDelnbrinfo);

    m_pSaveBtn = new QPushButton(tr("保存"),this);
    m_pSaveBtn->setIcon(QIcon(":/resouse/Image/save.png"));
    pbtnLayout->addWidget(m_pSaveBtn);
    connect(m_pSaveBtn,&QPushButton::clicked,this,&UserInfoWg::slotSavenbrinfo);

    m_pRefreshBtn = new QPushButton(tr("刷新"),this);
    m_pRefreshBtn->setIcon(QIcon(":/resouse/Image/Refresh.png"));
    pbtnLayout->addWidget(m_pRefreshBtn);
    connect(m_pRefreshBtn,&QPushButton::clicked,this,&UserInfoWg::slotRefreshDataBase);
    pbtnLayout->addStretch();

    //添加table表头
    m_sqltableview = new QTableView(this);
    m_sqltableview->resize(this->width(),this->height()*9/10);
    m_sqltableview->horizontalHeader()->setStyleSheet(headstlye);
    m_sqltableview->verticalHeader()->hide();
    m_sqltableview->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_sqltableview->verticalHeader()->hide();
    m_sqltableview->horizontalHeader()->setStretchLastSection(true); // 设置最后一列填充
    m_sqltableview->setSelectionMode(QAbstractItemView::SingleSelection);
    m_sqltableview->setFrameShape(QFrame::NoFrame);
    m_sqltableview->setEditTriggers(QAbstractItemView::SelectedClicked);
    m_sqltableview->setAlternatingRowColors(true);

    m_sqltablemodel = new QSqlTableModel();
    m_sqltablemodel->setTable("t_userinfo");
    m_sqltablemodel->insertColumn(0);
    m_sqltablemodel->setSort(0,Qt ::AscendingOrder);
    m_sqltableview->setModel(m_sqltablemodel);

    m_sqltablemodel->select();

    QStringList headerlist;
    headerlist<<"ID"<<"用户名字"<<"等级"<<"密码"<<"备注";
    for(int i = 0 ;i <headerlist.size();i++)
    {
        m_sqltablemodel->setHeaderData(i, Qt::Horizontal, headerlist.at(i));
    }
    for(int i = 0; i< headerlist.size(); ++i )
    {
        m_sqltableview->setColumnWidth(i,this->width()/5);
    }
    QGroupBox *pbtnMainGroup = new QGroupBox();
    pbtnMainGroup->setLayout(pbtnLayout);;
    pmainlayout->addWidget(pbtnMainGroup);
    pmainlayout->setSpacing(10);
    pmainlayout->addWidget(m_sqltableview);

}

UserInfoWg::~UserInfoWg()
{

}
///
/// \brief UserInfoWg::slotaddnbrinfo
///
void UserInfoWg::slotaddnbrinfo()
{
    m_sqltablemodel->insertRow(m_sqltablemodel->rowCount());
}
///
/// \brief UserInfoWg::slotDelnbrinfo
///
void UserInfoWg::slotDelnbrinfo()
{

}
///
/// \brief UserInfoWg::slotRefreshDataBase
///
void UserInfoWg::slotRefreshDataBase()
{

}
///
/// \brief UserInfoWg::slotSavenbrinfo
///
void UserInfoWg::slotSavenbrinfo()
{

}
