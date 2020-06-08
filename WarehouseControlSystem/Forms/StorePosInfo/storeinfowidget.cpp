#include "storeinfowidget.h"
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QAction>
#include <QLabel>
#include <QGroupBox>
#include <QDebug>
#include <QMessageBox>
#include <QEventLoop>
#include <QTimer>



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
    connect(m_pnbrlineEdit,&QLineEdit::returnPressed,this,&StoreInfoWidget::slotquenbrinfo);

    m_pquenbrBtn = new QPushButton(tr("查询仓位编号"),this);
    m_pquenbrBtn->setIcon(QIcon(":/resouse/Image/Search.png"));
    pbtnLayout->addWidget(m_pquenbrBtn);
    connect(m_pquenbrBtn,&QPushButton::clicked,this,&StoreInfoWidget::slotquenbrinfo);
    //m_pquenbrBtn->setShortcut(Qt::Key_Enter);//将字母区回车键查询按钮绑定在一起
   // m_pquenbrBtn->setShortcut(Qt::Key_Return);//将小键盘回车键与查询按钮按钮绑定在一起

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

    connect(this,&StoreInfoWidget::signalfindinfo,m_ptableview,&StorenbrTableView::SlotFindNbrinfo);
    connect(m_ptableview,&StorenbrTableView::signalDelRowData,this,&StoreInfoWidget::SlotDelSinglerow);//表格中的单行操作
    connect(this,&StoreInfoWidget::signalBatchDel,m_ptableview,&StorenbrTableView::SlotBatchDeltableInfo);
    connect(m_ptableview,&StorenbrTableView::SignalBatchDel,this,&StoreInfoWidget::SlotBatchDelData);
    //数据假测试进行测试
    QStringList strTypeList;
    strTypeList<<tr("选择")<<tr("序号")<<tr("仓位编号")
              <<tr("类型")<<tr("X坐标")<<tr("Y坐标")<<tr("Z坐标")<<tr("料箱编号")<<tr("仓位状态")<<tr("优先级")<<tr("操作");
    m_ptableview->SetTableHeaderData(strTypeList,strTypeList.size());
    //数据测试时效果图
    QStringList strlist;
    strlist<<tr("0")<<tr("0")<<tr("abcdef")
                  <<tr("大")<<tr("3456")<<tr("789")<<tr("8999")<<tr("cdfh")<<tr("占用")<<tr("9")<<tr("操作");
    QStringList strlist1;
    strlist1<<tr("0")<<tr("0")<<tr("abc")
                  <<tr("大")<<tr("3456")<<tr("789")<<tr("8999")<<tr("cdfh")<<tr("占用")<<tr("9")<<tr("操作");
    QStringList strlist2;
    strlist2<<tr("0")<<tr("0")<<tr("2333")
                  <<tr("大")<<tr("3456")<<tr("789")<<tr("8999")<<tr("cdfh")<<tr("占用")<<tr("9")<<tr("操作");
    QList<QStringList> list;
    list.append(strlist);
    list.append(strlist1);
    list.append(strlist);
    list.append(strlist2);
    m_ptableview->setModeldatalist(list);
    this->resize(parent->size());
}
///
/// \brief StoreInfoWidget::~StoreInfoWidget
///
StoreInfoWidget::~StoreInfoWidget()
{
    if(m_ptableview)
    {
        delete m_ptableview;
    }
}
///
/// \brief StoreInfoWidget::slotaddnbrinfo
///
void StoreInfoWidget::slotaddnbrinfo()
{

}
///
/// \brief StoreInfoWidget::slotBatchDelnbrinfo
/// 批量删除数据库内容根据编号信息进行删除，不可退回
void StoreInfoWidget::slotBatchDelnbrinfo()
{
    int ret = QMessageBox::warning(NULL, tr("提示"),
                                   tr("删除后,不可恢复,请谨慎操作!"),
                                   QMessageBox::Yes | QMessageBox::No,QMessageBox::No);
    if(ret == QMessageBox::No)
        return;
    //先进行表格数据，查看checkbox的状态
    emit signalBatchDel();
}
///
/// \brief StoreInfoWidget::slotquenbrinfo
///查询 编号的信息进行显示
void StoreInfoWidget::slotquenbrinfo()
{
    QString text  = m_pnbrlineEdit->text();
    emit signalfindinfo(text,2);
}
///
/// \brief StoreInfoWidget::slotImportnbrinfo
///导入csv 或者EXCEL进行处理表格进行数据库的读写
void StoreInfoWidget::slotImportnbrinfo()
{
    ///1.读取数据进行插入
    /// 2.保存到数据库 内存数据与数据库保持 一致
    /// 3.改变内存的方式
     //ESC
    WatingDialogWg dialogwg;
     dialogwg.exec(); //加载3s结束
}
///
/// \brief StoreInfoWidget::SlotDelSinglerow
/// \param nbrinfo
///表格中删除按钮
void StoreInfoWidget::SlotDelSinglerow(QString nbrinfo)
{
    if(m_stroreposmap.storeposInfoMap.contains(nbrinfo))
    {
        m_stroreposmap.storeposInfoMap.remove(nbrinfo);
    }
    //更新数据库内容进行删除操作
}
///
/// \brief StoreInfoWidget::SlotBatchDelData
/// \param nbrlist
///批量删除数据库中编号信息
void StoreInfoWidget::SlotBatchDelData(QStringList nbrlist)
{
    for(int i = 0 ; i < nbrlist.size(); ++i)
    {
        if(m_stroreposmap.storeposInfoMap.contains(nbrlist[i]))
        {
            m_stroreposmap.storeposInfoMap.remove(nbrlist[i]);
        }
    }
    //调用数据库进行删除操作 ，删除的操作语句

}

