#include "dialogabstractclass.h"

DialogAbstractClass::DialogAbstractClass(const QStringList &widget_name_list,QString flag, QWidget *parent):QWidget(parent)
{
    m_vbox = new QVBoxLayout();
    m_list = widget_name_list;
    m_sql_flag = flag;
    CreatUi();
}

QStringList DialogAbstractClass::getContent()
{
    QStringList result;
    foreach (QLineEdit *edit, m_edit_list) {
        result<<edit->text();
    }
    return result;
}

void DialogAbstractClass::setContent(const QStringList &list)
{
    if((m_edit_list.size() != list.size()) || list.size() == 0)
        return;
    for(int i = 0; i< list.size();i++)
    {
        m_edit_list[i]->setText(list[i]);
    }
}

void DialogAbstractClass::CreatUi()
{
    if(m_list.size() == 0)
        return;
    w = new QWidget(this);
    w->setObjectName("mainWidget");
    this->resize(500,300);
    w->resize(500,300);
    m_vbox->addSpacing(10);
    for(int i = 0;i < m_list.size();i++)
    {
        m_hbox = new QHBoxLayout();
        m_hbox->addSpacing(50);
        m_info_lab = new QLabel(m_list[i]+":  ");
        m_info_lab->resize(50,20);
        m_hbox->addWidget(m_info_lab,1);
        QLineEdit *edit = new QLineEdit();
        m_hbox->addWidget(edit,2);
        m_hbox->addSpacing(50);
        m_edit_list.append(edit);
        m_vbox->addItem(m_hbox);
    }
    m_err_lab = new QLabel();
    m_hbox = new QHBoxLayout();
    m_hbox->addSpacing(50);
    m_err_lab->setStyleSheet("color:red");
    m_hbox->addWidget(m_err_lab);
    m_vbox->addItem(m_hbox);
    m_hbox = new QHBoxLayout();
    m_hbox->addSpacing(50);
    m_yesbtn = new QPushButton("Ok");
    connect(m_yesbtn,&QPushButton::clicked,this,&DialogAbstractClass::onYesBtnClicked);
    m_hbox->addWidget(m_yesbtn);
    m_hbox->addSpacing(70);
    m_cleanbtn = new QPushButton("Clean");
    connect(m_cleanbtn,&QPushButton::clicked,this,&DialogAbstractClass::onCleanBtnClicked);
    m_hbox->addWidget(m_cleanbtn);
    m_hbox->addSpacing(50);
    m_vbox->addItem(m_hbox);
    m_vbox->addSpacing(10);
    w->setLayout(m_vbox);
    this->setStyleSheet("#mainWidget{border-image:url(:/resouse/Image/grey2.png);border-radius: 15px 15px}"
                        "QLabel{background:transparent;color:white}");
}

void DialogAbstractClass::mouseMoveEvent(QMouseEvent *event)
{
    if(mouse_press){
        move(event->globalPos() - mousePoint);
    }
}

void DialogAbstractClass::mousePressEvent(QMouseEvent *event)
{
    if( (event->button() == Qt::LeftButton) ){
        mouse_press = true;
        mousePoint = event->globalPos() - this->pos();
        //        event->accept();
    }
    else if(event->button() == Qt::RightButton){
        //如果是右键
        this->close();

    }
}

void DialogAbstractClass::mouseReleaseEvent(QMouseEvent *event)
{
    mouse_press = false;
}

void DialogAbstractClass::onYesBtnClicked()
{
    QStringList result = getContent();
    foreach (QString str, result) {
        qDebug()<<str;
    }
}

void DialogAbstractClass::onCleanBtnClicked()
{
    this->hide();
//    foreach (QLineEdit *edit, m_edit_list) {
//        edit->deleteLater();
//    }
    this->deleteLater();
}
