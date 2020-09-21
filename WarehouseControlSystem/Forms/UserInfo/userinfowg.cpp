#include "userinfowg.h"
#include <QGroupBox>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QCryptographicHash>

UserInfoWg::UserInfoWg( QWidget *parent):BaseFrom(parent)
{
    m_pRevokeBtn = NULL;
    this->resize(parent->width(),parent->height());
    // 删除 按钮  刷新按钮
    //Init UI
    QVBoxLayout *pmainlayout = new QVBoxLayout;
    setLayout(pmainlayout);
    QLabel *pshowlabeltitle = new QLabel(tr("当前位置：WCS系统<<登录管理"));
    pmainlayout->addWidget(pshowlabeltitle);
    // pmainlayout->setSpacing(10);
    QHBoxLayout *pbtnLayout = new QHBoxLayout();

    //增加用户名字 密码 等级编辑框
    QLabel *userlabel = new QLabel(tr("用户名:"));
    m_usernameEdit = new QLineEdit(this);
    QLabel *pwdlabel = new QLabel(tr("密码:"));

    m_passwdEdit = new QLineEdit(this);
    QLabel *levellabel = new QLabel(tr("用户等级:"));
    m_plevelcombox = new QComboBox(this);
    QStringList levellist;
    levellist<<"1"<<"2"<<"3"<<"4";
    m_plevelcombox->addItems(levellist);


    pbtnLayout->addWidget(userlabel);
    pbtnLayout->addWidget(m_usernameEdit);
    pbtnLayout->addWidget(pwdlabel);
    pbtnLayout->addWidget(m_passwdEdit);
    pbtnLayout->addWidget(levellabel);
    pbtnLayout->addWidget(m_plevelcombox);


    m_pModifyBtn = new QPushButton(tr("修改"),this);
    m_pModifyBtn->setIcon(QIcon(":/resouse/Image/updatepasswd.png"));
    m_pModifyBtn->setLayoutDirection(Qt::LayoutDirectionAuto);
    pbtnLayout->addWidget(m_pModifyBtn);
    connect(m_pModifyBtn,&QPushButton::clicked,this,&UserInfoWg::slotModifyInfo);

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

    //    m_pRevokeBtn = new QPushButton(tr("撤销"),this);
    //    m_pRevokeBtn->setIcon(QIcon(":/resouse/Image/save.png"));
    //    pbtnLayout->addWidget(m_pRevokeBtn);
    //    connect(m_pRevokeBtn,&QPushButton::clicked,this,&UserInfoWg::slotRevokeInfo);

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
    m_sqltableview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_sqltableview->setAlternatingRowColors(true);

    m_sqltablemodel = new QSqlTableModel();
    m_sqltablemodel->setTable("t_userinfo");
    m_sqltablemodel->insertColumn(0);
    m_sqltablemodel->setSort(0,Qt ::AscendingOrder);
    m_sqltablemodel->setEditStrategy(QSqlTableModel::OnManualSubmit);// 设置提交修改才有效
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

    connect(m_sqltableview,&QTableView::doubleClicked,this,&UserInfoWg::slotRowDataEdit);
}
//model->revertAll();
UserInfoWg::~UserInfoWg()
{

}
///
/// \brief UserInfoWg::GetMd5CryptographicHashStr
/// \param passwd
/// \return
///加密字符数据
QString UserInfoWg::GetMd5CryptographicHashStr(QString passwd)
{
    //加密过程
    QCryptographicHash hash(QCryptographicHash::Md5);
    //放入原始数据
    hash.addData(passwd.toUtf8());
    //取出加密后的数据
    QByteArray arr = hash.result();
    //重新复制给passwd
    passwd = arr.toHex();
    //看一下加密后的数据
   // qDebug()<<"passwd"<<passwd;
    return passwd;
}
///
/// \brief UserInfoWg::slotaddnbrinfo
///
void UserInfoWg::slotaddnbrinfo()
{
   // m_sqltablemodel->insertRow(m_sqltablemodel->rowCount());
    //QSqlRecord record = m_sqltablemodel->record();
    //m_sqltablemodel->insertRecord(m_sqltablemodel->rowCount(),record);
    if(m_passwdEdit->text() != "" && m_usernameEdit->text() != "")
    {
        int row = m_sqltablemodel->rowCount();
        m_sqltablemodel->insertRow(m_sqltablemodel->rowCount());
        m_sqltablemodel->setData(m_sqltablemodel->index(row,1),m_usernameEdit->text());
        m_sqltablemodel->setData(m_sqltablemodel->index(row,2),m_plevelcombox->currentIndex()+1);
        m_sqltablemodel->setData(m_sqltablemodel->index(row,3),GetMd5CryptographicHashStr(m_passwdEdit->text()));
        slotSavenbrinfo();
    }
    else
    {
       QMessageBox::warning(this,tr("tableModel"),tr("请检查等级取值范围，用户名和密码不超过11位,密码和用户名字不为空"),QMessageBox::Ok);
    }
}
///
/// \brief UserInfoWg::slotDelnbrinfo
///
void UserInfoWg::slotDelnbrinfo()
{
    int row = m_sqltableview->currentIndex().row();//记录当前选择行
    if(QMessageBox::Yes == QMessageBox::question(this,"Make Sure","确定删除第"+QString::number(row+1)+"行吗？",QMessageBox::Yes | QMessageBox::No , QMessageBox::Yes))
    {
        //提示框，防止误操作，是/否，按下是的操作后
        m_sqltablemodel->removeRow(row);//删除当前行
        m_sqltablemodel->submitAll();//提交修改的数据
        m_sqltablemodel->select();//显示修改后的数据
    }
}
///
/// \brief UserInfoWg::slotRefreshDataBase
///
void UserInfoWg::slotRefreshDataBase()
{
    m_sqltablemodel->select();
}
///
/// \brief UserInfoWg::slotSavenbrinfo
///
void UserInfoWg::slotSavenbrinfo()
{
    //  m_sqltablemodel->database().transaction();//开始事务操作
    if(m_sqltablemodel->submitAll())
    {
        //        if(m_sqltablemodel->database().commit())//提交
        //        {
        QMessageBox::information(this,tr("tableModel"),tr("数据库修改成功！"));
        m_sqltablemodel->select();
        //  }
        //        else
        //        {
        //            m_sqltablemodel->database().rollback();//回滚
        //            m_sqltablemodel->select();//显示修改后的数据
        //            QMessageBox::warning(this,tr("tableModel"),tr("数据库错误：%1").arg(m_sqltablemodel->lastError().text()),QMessageBox::Ok);
        //        }
    }
    else{
        QMessageBox::warning(this,tr("tableModel"),tr("数据库错误：%1，请检查等级取值范围，用户名和密码不超过11位").arg(m_sqltablemodel->lastError().text()),QMessageBox::Ok);
        //QMessageBox::about(this,"Warning","请确认数据不可以为空");
    }
}
///
/// \brief UserInfoWg::slotRevokeInfo
///撤销按钮
void UserInfoWg::slotRevokeInfo()
{
    m_sqltablemodel->revertAll();
    m_sqltablemodel->select();
}
///
/// \brief UserInfoWg::slotModifyInfo
///  修改当前行数据进行替换
void UserInfoWg::slotModifyInfo()
{
    //索引号
    QModelIndex index = m_sqltableview->currentIndex();
    int row = index.row();
    if(row < 0)
        return ;
    //int id = m_sqltablemodel->index(row,0).data().toInt();
    m_sqltablemodel->setData(m_sqltablemodel->index(row,1),m_usernameEdit->text());
    m_sqltablemodel->setData(m_sqltablemodel->index(row,2),m_plevelcombox->currentIndex()+1);
    m_sqltablemodel->setData(m_sqltablemodel->index(row,3),GetMd5CryptographicHashStr(m_passwdEdit->text()));
    slotSavenbrinfo();
    m_sqltablemodel->select();
}
///
/// \brief UserInfoWg::slotRowDataEdit
/// 双击获取用户信息和数据进行编辑
void UserInfoWg::slotRowDataEdit()
{
    //获得当前行数据
    QModelIndex index = m_sqltableview->currentIndex();
    int row = index.row();
    m_usernameEdit->setText(m_sqltablemodel->index(row,1).data().toString());
    m_passwdEdit->setText("");
    m_plevelcombox->setCurrentText(m_sqltablemodel->index(row,2).data().toString());
}
