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
#include <MysqlDataBase/crudbaseoperation.h>
#include <QFileDialog>
#include "UnitClass/ImportExportFile/localfileoperate.h"
#include "editstorenbrinfodialog.h"
const QString stylestr =  "QPushButton{font:12px;}"
                     "QLabel{font:12px;}"
                    "QPushButton:hover{background-color:rgba(255,255,255,110);}"
                    "QPushButton:pressed{background-color:rgba(255,255,255,150);}"
                    "QHeaderView{height:60px;font:12px;border:none;alternate-background-color: rgb(220, 220, 220);}"
                    "QTableView{font:12px;selection-background-color:rgba(0,191,255,255);}"
                    "QMenu::item:selected {background-color:rgba(0,190,230,100);}";
StoreInfoWidget::StoreInfoWidget(QWidget *parent):QWidget(parent)
{
    //Init data
    m_stroreposmap.storeposInfoMap.clear();
    m_editrow = -1;
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

    m_pExportBtn = new QPushButton(tr("导出"),this);
    m_pExportBtn->setIcon(QIcon(":/resouse/Image/exportfile.png"));
    pbtnLayout->addWidget(m_pExportBtn);
    connect(m_pExportBtn,&QPushButton::clicked,this,&StoreInfoWidget::slotExportnbrinfo);
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
    connect(this,&StoreInfoWidget::signalUpdatetable,m_ptableview,&StorenbrTableView::SlotEditInfo);
    connect(m_ptableview,&StorenbrTableView::signalEditRowData,this,&StoreInfoWidget::slottableeditbtn);
    //数据假测试进行测试r
    QStringList strTypeList;
    strTypeList<<tr("选择")<</*tr("序号")<<*/tr("仓位编号")
              <<tr("类型")<<tr("X坐标")<<tr("Y坐标")<<tr("Z坐标")<<tr("料箱编号")<<tr("仓位状态")<<tr("优先级")<<tr("操作");
    m_ptableview->SetTableHeaderData(strTypeList,strTypeList.size());
    Dataselectfromdatabase();
    this->resize(parent->size());
    this->setStyleSheet(stylestr);
}
///
/// \brief StoreInfoWidget::~StoreInfoWidget
///
StoreInfoWidget::~StoreInfoWidget()
{
    if(m_ptableview)
    {
        delete m_pAddBtn;
        delete m_pBatchDelBtn;
        delete m_pnbrlineEdit;
        delete m_pquenbrBtn;
        delete m_pImportBtn;
        delete m_pExportBtn;
        delete m_ptableview;
    }
}
///
/// \brief StoreInfoWidget::slotaddnbrinfo
/// 添加编号信息数据框
void StoreInfoWidget::slotaddnbrinfo()
{
    DelDialogBaseob();
    QStringList strTypeList;
    strTypeList<<tr("仓位编号")
              <<tr("类型")<<tr("X坐标")<<tr("Y坐标")<<tr("Z坐标")<<tr("料箱编号")<<tr("仓位状态")<<tr("优先级");
    QString flag;
    flag = "add";
    EditStorenbrinfoDialog *adddialog = new EditStorenbrinfoDialog (strTypeList,flag,this);
    adddialog->show();
    connect(adddialog,&EditStorenbrinfoDialog::signalAckBtn,this,&StoreInfoWidget::slotEditData);
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
    //获取表格选中状态
    QList<QVariant> list =   m_ptableview->GetBatchDellist();
    if(list.size() > 0 )
    {
        if(DelDataBaseInfo(list))
        {
            m_ptableview->BatchDeltableInfo();
        }
    }
}
///
/// \brief StoreInfoWidget::slotquenbrinfo
///查询 编号的信息进行显示
void StoreInfoWidget::slotquenbrinfo()
{
    QString text  = m_pnbrlineEdit->text();
    emit signalfindinfo(text,1);
}
///
/// \brief StoreInfoWidget::slotImportnbrinfo
///导入csv 或者EXCEL进行处理表格进行数据库的读写
void StoreInfoWidget::slotImportnbrinfo()
{
    ///1.读取数据进行插入
    /// 2.保存到数据库 内存数据与数据库保持 一致
    /// 3.改变内存的方式
    QMessageBox::information(this, tr("导入数据"),tr("会覆盖原有数据"), tr("确定"));
    QFileDialog* fd = new QFileDialog(this);
    QString fileName = fd->getOpenFileName(this,tr("Open File"),"/home",tr("Excel(*.csv)"));
    if(fileName == "")
        return;
    LocalFileOperate fileob;
    QList<QStringList> listdata;
    listdata =  fileob.ReadFileData(fileName);
    if(listdata.size() <= 1)
    {
        QMessageBox::warning(this, tr("数据警告"),tr("导入数据失败，请检查"), tr("确定"));
        return ;
    }
    QMap<QString,StorePosInfoStru> datamap;
    QStringList boxnbr;
    bool datatype = true;
    for(int i = 1; i < listdata.size(); ++i) //从第二行开始屏蔽头数据
    {
        QStringList listrow =listdata[i] ;
        if(listrow.size() >= 8)
        {
            if(boxnbr.contains(listrow[5]))
            {
                datatype = false;
                break;
            }
            boxnbr.append(listrow[5]);
            StorePosInfoStru stru;
            strncpy(stru.boxnbr,listrow[5].toStdString().c_str(),64);
            strncpy(stru.idnbr,listrow[0].toStdString().c_str(),64);
            stru.coordx = listrow[2].toDouble();
            stru.coordy =listrow[3].toDouble();
            stru.coordz = listrow[4].toDouble();
            stru.storestat = listrow[6].toInt();
            stru.storepri = listrow[7].toInt();
            if(!datamap.contains(listrow[0]))
            {
                datamap.insert(listrow[0],stru);
            }
            else{
                datamap[listrow[0]] = stru;
            }
        }
    }
    if(datamap.size() > 0 && datatype)
    {
        //数据写入数据库
        QString msg;
        if(!m_databaseopob.WriteStoreposinfotoDataBase(datamap,msg))
        {
            QMessageBox::warning(this, tr("数据警告"),msg, tr("确定"));
            return ;
        }
        else{ //更新成功
            Dataselectfromdatabase();
        }
    }
    else {
        QMessageBox::warning(this, tr("数据警告"),tr("导入数据失败, 数组的箱子编号不可重复或者数据不能为空"), tr("确定"));
        return ;
    }
}
///
/// \brief StoreInfoWidget::slotExportnbrinfo
/// 数据库表格的数据进行导出操作
void StoreInfoWidget::slotExportnbrinfo()
{
    QString exportfileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                          tr("Files (*.csv)"));
    if (exportfileName.isEmpty())
        return;
    QList<QStringList> datalist;
    //结构体数据相互转化
    for(auto it = m_stroreposmap.storeposInfoMap.begin(); it !=m_stroreposmap.storeposInfoMap.end(); ++it )
    {
        QStringList listinfo ;
        listinfo<<QString::fromUtf8(it.value().idnbr)<<QString::number(it.value().type)<<QString::number(it.value().coordx)\
               <<QString::number(it.value().coordy) <<QString::number(it.value().coordz) <<QString::fromUtf8(it.value().boxnbr) \
              <<QString::number(it.value().storestat) <<QString::number(it.value().storepri);
        datalist.append(listinfo);
    }
    //+
    QStringList tableheadlist;
    tableheadlist<<tr("仓位编号")<<tr("类型")<<tr("x坐标")<<tr("y坐标")<<tr("z坐标")<<tr("箱子编号")<<tr("仓位状态")<<tr("仓位优先级");
    LocalFileOperate fileob;
    if(fileob.WriteFileData(datalist,exportfileName,tableheadlist))
    {
        QMessageBox::information(this, tr("导出数据成功"), tr("信息已保存在%1！").arg(exportfileName), tr("确定"));
    }
}
///
/// \brief StoreInfoWidget::slotEditData
/// \param datalist
/// update 表格
void StoreInfoWidget::slotEditData(QStringList datalist)
{
    emit signalUpdatetable(datalist ,m_editrow);
}
///
/// \brief StoreInfoWidget::slottableeditbtn
/// 表格编辑按钮传输过来slot函数
void StoreInfoWidget::slottableeditbtn(QString nbrinfo ,int row)
{
      DelDialogBaseob();
    m_editrow = row;
    QList<QStringList> list;
    if(m_stroreposmap.storeposInfoMap.contains(nbrinfo))
    {
        QMap<QString,StorePosInfoStru> storeposInfoMap;
        storeposInfoMap.insert(nbrinfo,m_stroreposmap.storeposInfoMap[nbrinfo]);
        list =  GetdatalistFromstru(storeposInfoMap);
    }
    if(list.size() !=1)
        return;
    QStringList strTypeList;
    strTypeList<<tr("仓位编号")
              <<tr("类型")<<tr("X坐标")<<tr("Y坐标")<<tr("Z坐标")<<tr("料箱编号")<<tr("仓位状态")<<tr("优先级");
    QString flag = "update";
    //测试数据
    QStringList TEST;
    TEST.clear();
    TEST << "nbr005"<<"L"<<"234"<<"456"<<"789"<<"box005"<<"1"<<"5";
    //测试
  TEST = list[0];
   list[0].removeFirst();
    EditStorenbrinfoDialog *adddialog = new EditStorenbrinfoDialog (strTypeList,flag,this);
    adddialog->move(m_ptableview->pos().x() +m_ptableview->width()/2 - adddialog->width()/2,m_ptableview->pos().y() + m_ptableview->height()/2-adddialog->height()/2);
    adddialog->setContent( list[0]);
    adddialog->show();
    connect(adddialog,&EditStorenbrinfoDialog::signalAckBtn,this,&StoreInfoWidget::slotEditData);
}
///
/// \brief StoreInfoWidget::Dataselectfromdatabase
///查询数据库的内容，得到信息 映射到表格中
void StoreInfoWidget::Dataselectfromdatabase()
{
    //读数据库表格
    m_stroreposmap.storeposInfoMap.clear();//添加 数据库的内容映射到结构体中
    m_databaseopob.ReadStoreposinfoDataBase();
    QList<QStringList> list;
    m_stroreposmap.storeposInfoMap =  Myconfig::GetInstance()->m_storeinfoMap;
    list =  GetdatalistFromstru(m_stroreposmap.storeposInfoMap);
    QStringList rowlist;
    rowlist<<"0"<<"nbr001"<<"1"<<"345"<<"678.0"<<"444"<<"1"<<"2"<<"5";
    list.append(rowlist);
    rowlist.clear();
    rowlist<<"1"<<"10"<<"1"<<"345"<<"678.0"<<"boxnbr"<<"1"<<"1"<<"5";
    list.append(rowlist);
    rowlist.clear();
    rowlist<<"0"<<"11"<<"1"<<"345"<<"678.0"<<"boxnbr"<<"1"<<"0"<<"5";
    if(list.size() == 0)
    {
        //若数据库打不开则插入测试数据
        list.append(rowlist);
    }
    m_ptableview->setModeldatalist(list);
}

bool StoreInfoWidget::DelDataBaseInfo(QList<QVariant> nbrlist)
{
    QString tablename = "t_storeposinfo";
    QString msg;
    QString id = "idNbr";
    if(!CRUDBaseOperation::getInstance()->ExcBatchDeleteDB(tablename,id,nbrlist,msg))
    {
        QMessageBox::warning(this, tr("数据警告"),msg, tr("确定"));
        return false;
    }
    else{
        for(int i = 0 ; i < nbrlist.size(); ++i)
        {
            QString key = nbrlist[i].toString();
            if(m_stroreposmap.storeposInfoMap.contains(key))
            {
                m_stroreposmap.storeposInfoMap.remove(key);
            }
            //调用数据库进行删除操作 ，删除的操作语句
        }
        return true;
    }
}
///
/// \brief StoreInfoWidget::GetdatalistFromstru
/// \param infoMap
/// \return
///
QList<QStringList> StoreInfoWidget::GetdatalistFromstru(QMap<QString, StorePosInfoStru> infoMap)
{
    QList<QStringList> list;
    for(auto it = infoMap.begin(); it!= infoMap.end(); ++it )
    {
        QStringList columnlist;
        columnlist.append("0");
        columnlist.append(QString::fromUtf8(it.value().idnbr));
        columnlist.append(QString::number(it.value().type));
        columnlist.append(QString::number(it.value().coordx));
        columnlist.append(QString::number(it.value().coordy));
        columnlist.append(QString::number(it.value().coordz));
        columnlist.append(QString::fromUtf8(it.value().boxnbr));
        columnlist.append(QString::number(it.value().storestat));
        columnlist.append(QString::number(it.value().storepri));
        list.append(columnlist);
    }
    return list;
}
///
/// \brief StoreInfoWidget::CheckBoxNbrInfo
/// \param boxnbr
/// \return
///检查是否有重复的boxnbrInfo
bool StoreInfoWidget::CheckBoxNbrInfo(QString boxnbr)
{
    for(auto it = m_stroreposmap.storeposInfoMap.begin(); it !=  m_stroreposmap.storeposInfoMap.end();++it)
    {
        if(QString::fromUtf8(it.value().boxnbr) ==boxnbr )
        {
            return  false;;
        }
    }
    return true;
}
///
/// \brief StoreInfoWidget::SlotDelSinglerow
/// \param nbrinfo
///表格中删除按钮
void StoreInfoWidget::SlotDelSinglerow(QString nbrinfo,int row)
{
    QList<QVariant> list;
    list.append(nbrinfo);
    if(DelDataBaseInfo(list))
    {
        m_ptableview->Delsinglerow(row);
    }
}
///
/// \brief StoreInfoWidget::SlotBatchDelData
/// \param nbrlist
///批量删除数据库中编号信息
void StoreInfoWidget::SlotBatchDelData(  QList<QVariant> nbrlist)
{
    DelDataBaseInfo(nbrlist);

}
///
/// \brief StoreInfoWidget::DelDialogBaseob
///
void StoreInfoWidget::DelDialogBaseob()
{
    QList<EditStorenbrinfoDialog *> list = this->findChildren<EditStorenbrinfoDialog*>();
    if(list.size() == 0)
        return;
    foreach (EditStorenbrinfoDialog* w, list) {
        w->hide();
        w->deleteLater();
    }
}

