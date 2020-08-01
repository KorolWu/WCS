#include "watingdialogwg.h"

WatingDialogWg::WatingDialogWg(QWidget *parent):QDialog(parent)
{
    //    Q_IMPORT_PLUGIN(qgif)
    m_plabel = new QLabel(this);
    this->setFixedSize(300,300);
    //  setWindowOpacity(0.5);  //设置透明用；
    this->setWindowFlags(Qt::Dialog|Qt::CustomizeWindowHint);
    //取消对话框标题
    //this->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
    //取消对话框标题和边框
    //this->setAutoFillBackground(true);
    this->setContentsMargins(0,0,0,0);
    m_plabel->setContentsMargins(0,0,0,0);
    /*QPalettepalette;palette.setBrush(QPalette::Background,QBrush(QPixmap("E:/qml/imgdialog/loading.gif")));
        this->setPalette(palette)*/;///root/WcsProject/WCS/WarehouseControlSystem/Image
    m_pmovie = new QMovie(":/resouse/Image/wainting2.gif");
    m_plabel->setMovie(m_pmovie);
    m_pmovie->start();
    m_plabel->show();
    m_pTimer = new QTimer(this);
    m_pTimer->setSingleShot(true);
    connect(m_pTimer, &QTimer::timeout, this, [=](){this->close();});
    m_pTimer->start(10000);
}

WatingDialogWg::~WatingDialogWg()
{
    delete m_plabel;
    delete  m_pmovie;
}

void WatingDialogWg::CloseDialag()
{
    this->close();

}
