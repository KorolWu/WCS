#include "storeinfowidget.h"
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QAction>
#include <QLabel>
#include <QGroupBox>
#include <QDebug>


StoreInfoWidget::StoreInfoWidget(QWidget *parent):QWidget(parent)
{
    //Init data
    m_stroreposmap.storeposInfoMap.clear();
    //读取数据库的内容映射到内存中
    //Init UI
    QVBoxLayout *pmainlayout = new QVBoxLayout;
    setLayout(pmainlayout);
    QLabel *pshowlabeltitle = new QLabel(tr("当前位置：WCS系统<<货架管理..."));
    pmainlayout->addWidget(pshowlabeltitle);
    pmainlayout->setSpacing(25);
    QHBoxLayout *pbtnLayout = new QHBoxLayout();
    m_pAddBtn = new QPushButton(tr("添加"),this);
    m_pAddBtn->setIcon(QIcon(":/resouse/Image/add.png"));
    m_pAddBtn->setLayoutDirection(Qt::LayoutDirectionAuto);
    pbtnLayout->addWidget(m_pAddBtn);
    connect(m_pAddBtn,&QPushButton::clicked,this,&StoreInfoWidget::slotaddnbrinfo);

    m_pBatchDelBtn = new QPushButton(tr("批量删除"),this);
    m_pBatchDelBtn->setIcon(QIcon(":/resouse/Image/delete.png"));
    pbtnLayout->addWidget(m_pBatchDelBtn);
     connect(m_pBatchDelBtn,&QPushButton::clicked,this,&StoreInfoWidget::slotBatchDelnbrinfo);

    m_pnbrlineEdit = new QLineEdit(this);
    QAction *pnbrAction = new QAction( m_pnbrlineEdit);
    pnbrAction->setIcon(QIcon(":/resouse/Image/Search.png"));
    m_pnbrlineEdit->addAction(pnbrAction,QLineEdit::LeadingPosition);
    m_pnbrlineEdit->setMaxLength(64);
    pbtnLayout->addWidget(m_pnbrlineEdit);

    m_pquenbrBtn = new QPushButton(tr("查询仓位编号"),this);
    m_pquenbrBtn->setIcon(QIcon(":/resouse/Image/Search.png"));
    m_pquenbrBtn->setStyleSheet("background-color:rgba(150,255,150,255);");
    pbtnLayout->addWidget(m_pquenbrBtn);
    connect(m_pquenbrBtn,&QPushButton::clicked,this,&StoreInfoWidget::slotquenbrinfo);



    m_pImportBtn = new QPushButton(tr("导入"),this);
    m_pImportBtn->setIcon(QIcon(":/resouse/Image/import.png"));
    pbtnLayout->addWidget(m_pImportBtn);
    connect(m_pImportBtn,&QPushButton::clicked,this,&StoreInfoWidget::slotImportnbrinfo);
    pbtnLayout->addStretch();
     //添加table表头
    m_ptableview = new StorenbrTableView();
    m_ptableview->resize(parent->width(),parent->height());

    QVBoxLayout *pBodyLayout = new QVBoxLayout();
    pBodyLayout->addLayout(pbtnLayout);

    QGroupBox *pbtnMainGroup = new QGroupBox();
    pbtnMainGroup->setLayout(pBodyLayout);
    pmainlayout->addWidget(pbtnMainGroup);

    pmainlayout->addWidget(m_ptableview);
//   pmainlayout->setStretchFactor(pshowlabeltitle,1);
//   pmainlayout->setStretchFactor(pbtnLayout,1);
    QStringList strTypeList;
    strTypeList<<tr("选择")<<tr("序号")<<tr("仓位编号")
              <<tr("类型")<<tr("X坐标")<<tr("Y坐标")<<tr("Z坐标")<<tr("料箱编号")<<tr("仓位状态")<<tr("优先级")<<tr("操作");
    m_ptableview->SetTableHeaderData(strTypeList,strTypeList.size());
    //数据测试时效果图
    QStringList strlist;
    strlist<<tr("0")<<tr("0")<<tr("abcdef")
                  <<tr("大")<<tr("3456")<<tr("789")<<tr("8999")<<tr("cdfh")<<tr("占用")<<tr("9")<<tr("操作");
    QList<QStringList> list;
    list.append(strlist);
    list.append(strlist);
    list.append(strlist);
    m_ptableview->setModeldatalist(list);
    this->resize(parent->size());
}
///
/// \brief StoreInfoWidget::~StoreInfoWidget
///
StoreInfoWidget::~StoreInfoWidget()
{

}
///
/// \brief StoreInfoWidget::slotaddnbrinfo
///
void StoreInfoWidget::slotaddnbrinfo()
{

}
///
/// \brief StoreInfoWidget::slotBatchDelnbrinfo
///
void StoreInfoWidget::slotBatchDelnbrinfo()
{

}
///
/// \brief StoreInfoWidget::slotquenbrinfo
///
void StoreInfoWidget::slotquenbrinfo() //查询信息
{
emit signalFindNbrInfo();

}
///
/// \brief StoreInfoWidget::slotImportnbrinfo
///
void StoreInfoWidget::slotImportnbrinfo()
{

}

