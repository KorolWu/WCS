#include "editstorenbrinfodialog.h"
#include <QDoubleValidator>
#include <QCompleter>
#include <QRadioButton>

EditStorenbrinfoDialog::EditStorenbrinfoDialog(const QStringList &list, QString flag, QWidget *parent):DialogAbstractClass(list,flag,parent)
{
    if(m_edit_list.size() == 8)
    {
        m_edit_list[0]->setMaxLength(64);
        QStringList list;
        list<<"L"<<"M"<<"S";
        QCompleter *completer = new QCompleter(list,this);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
        m_edit_list[1]->setCompleter(completer);
         m_edit_list[1]->setMaxLength(1);
        for(int i = 2; i< 5;++i)
        {
            QDoubleValidator *pIntValidator = new QDoubleValidator(this);
            m_edit_list[i]->setValidator(pIntValidator);
        }
        m_edit_list[5]->setMaxLength(64);
        m_edit_list[6]->setMaxLength(1);
        m_edit_list[7]->setMaxLength(1);
    }
}
///
/// \brief EditStorenbrinfoDialog::onYesBtnClicked
///
void EditStorenbrinfoDialog::onYesBtnClicked()
{
    QStringList list =  getContent();
    if(list.size()!= 8)
    {
        m_err_lab->setText(tr("添加数据失败,获取内容数量"));
        return;
    }
    for(int i = 0; i <list.size() ; ++i )
    {
        if(list[i]=="")
        {
            m_err_lab->setText(tr("数据内容不可为空"));
            return;
        }
    }
    StorePosInfoStru storestru;
    list.insert(0,"0");
    strncpy(storestru.idnbr, list[1].toStdString().c_str(),64);
    storestru.type = QString(list[2]).toInt();
    storestru.coordx = QString(list[3]).toDouble();
    storestru.coordy = QString(list[4]).toDouble();
    storestru.coordz = QString(list[5]).toDouble();
    strncpy(storestru.boxnbr, list[6].toStdString().c_str(),64);
    storestru.storestat = QString(list[7]).toInt();
    storestru.storepri =   QString(list[8]).toInt();
    ReadTableData rwdb;
    QMap<QString,StorePosInfoStru> infoMap;
    infoMap.insert( list[0],storestru);
    QString msg;
  //  if( rwdb.WriteStoreposinfotoDataBase(infoMap,msg))
    {
//        Myconfig::GetInstance()->m_storeinfoMap.insert(list[0],storestru);
        emit signalAckBtn(list);
        this->hide();
        this->deleteLater();
    }
//    else
//    {
//        if(msg == " ")
//        {
//            msg = "数据库打开失败";
//        }
//        m_err_lab->setText(QString("编辑失败请检查，信息内容：%1").arg(msg));
//    }
}

//QButtonGroup *EditStorenbrinfoDialog::Getradiogroup(QString list)
//{
//     m_pButtonGroup=new QButtonGroup(this);
//    QRadioButton  *frbtn= QRadioButton(m_pButtonGroup);
//    m_pButtonGroup->addButton(frbtn,0);//一个值为0
//    QRadioButton  *srbtn= QRadioButton(m_pButtonGroup);
//    m_pButtonGroup->addButton(srbtn,1);//一个值为1
//    QRadioButton  *trbtn= QRadioButton(m_pButtonGroup);
//    m_pButtonGroup->addButton(trbtn,2);//一个值为1
//}

//void EditStorenbrinfoDialog::mouseMoveEvent(QMouseEvent *event)
//{

//    //    if(event->buttons() == Qt::LeftButton){  //如果这里写这行代码，拖动会有点问题
//    if(mouse_press){
//        move(event->globalPos() - mousePoint);
//        //        event->accept();
//    }
//}

//void EditStorenbrinfoDialog::mousePressEvent(QMouseEvent *event)
//{
//    if( (event->button() == Qt::LeftButton) ){
//        mouse_press = true;
//        mousePoint = event->globalPos() - this->pos();
//        //        event->accept();
//    }
//    else if(event->button() == Qt::RightButton){
//        //如果是右键
//        this->close();

//    }
//}

//void EditStorenbrinfoDialog::mouseReleaseEvent(QMouseEvent *event)
//{
//    mouse_press = false;
//}


