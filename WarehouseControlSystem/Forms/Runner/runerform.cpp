#include "runerform.h"

RunerForm::RunerForm(int width, int height, QWidget *parent) : QWidget(parent)
{
    initUi();
    m_width = width;
    m_height = height;
    this->resize(width/2, height);
}

void RunerForm::setParameter(RunerStru s)
{
    m_pIp->setText(s.deviceIp);
    m_pPort->setText(QString("%1").arg(s.port));
    m_prunerName->setText(s.deviceNum);
    m_pinCache->setText(QString("%1").arg(s.cache_in));
    m_poutCache->setText(QString("%1").arg(s.cache_out));
    m_porderIn->setText(s.request_in);
    m_preplyin->setText(s.response_in);
    m_porderOut->setText(s.request_out);
    m_preplyOut->setText(s.response_out);
}

void RunerForm::initUi()
{
    QFont serifFont("Times", 16);
    m_pvBox = new QVBoxLayout(this);
    QLabel *info = new QLabel("流道参数管理",this);
    m_pvBox->addWidget(info);
    m_pgboxSocketInfo = new QGroupBox("通讯信息", this);
    m_pgboxSocketInfo->resize(600,100);
    QHBoxLayout *hboxSokcet = new QHBoxLayout();
    QLabel *name = new QLabel("名称 :");
    hboxSokcet->addWidget(name);
    m_prunerName = new QLineEdit();
    hboxSokcet->addWidget(m_prunerName);
    QLabel *ip = new QLabel("Ip :");
    hboxSokcet->addWidget(ip);
    m_pIp = new QLineEdit();
    hboxSokcet->addWidget(m_pIp);
    QLabel *port = new QLabel("Port :");
    hboxSokcet->addWidget(port);
    m_pPort = new QLineEdit();
    hboxSokcet->addWidget(m_pPort);
    m_pgboxSocketInfo->setFont(serifFont);
    m_pgboxSocketInfo->setLayout(hboxSokcet);
    hboxSokcet->setSpacing(30);
    m_pvBox->addWidget(m_pgboxSocketInfo);
    //--------------------------------
    m_prunerInfo = new QGroupBox("缓存区信息", this);
    m_prunerInfo->setFont(serifFont);
    m_prunerInfo->resize(600,100);
    QHBoxLayout *hboxRuner = new QHBoxLayout();
    QLabel *incache = new QLabel("入库缓存数量:");
    m_pinCache = new QLineEdit();
    hboxRuner->addWidget(incache);
    hboxRuner->addWidget(m_pinCache);
    QLabel *outcache = new QLabel("出库缓存数量:");
    m_poutCache = new QLineEdit();
    hboxRuner->addWidget(outcache);
    hboxRuner->addWidget(m_poutCache);
    hboxRuner->setSpacing(30);
    m_prunerInfo->setLayout(hboxRuner);
    m_pvBox->addWidget(m_prunerInfo);
    //--------------------------------
    m_preplyInfo = new QGroupBox("响应信息", this);
    m_preplyInfo->setFont(serifFont);
    QLabel *request = new QLabel("request In :");
    m_porderIn = new QLineEdit();

    QHBoxLayout *hboxOrder = new QHBoxLayout();
    hboxOrder->addWidget(request);
    hboxOrder->addWidget(m_porderIn);

    QLabel *reply = new QLabel("reply In :");
    m_preplyin = new QLineEdit();
    hboxOrder->addWidget(reply);
    hboxOrder->addWidget(m_preplyin);
    hboxOrder->setSpacing(30);
    QVBoxLayout *v = new QVBoxLayout();
    v->addLayout(hboxOrder);

    hboxOrder = new QHBoxLayout();
    QLabel *replyOut = new QLabel("request Out :");
    m_porderOut = new QLineEdit();
    hboxOrder->addWidget(replyOut);
    hboxOrder->addWidget(m_porderOut);
    QLabel *replyIn = new QLabel("reply Out :");
    m_preplyOut = new QLineEdit();
    hboxOrder->addWidget(replyIn);
    hboxOrder->addWidget(m_preplyOut);
    //hboxOrder->addStretch();
     hboxOrder->setSpacing(30);
    v->addLayout(hboxOrder);
    m_preplyInfo->setLayout(v);
    m_pvBox->addWidget(m_preplyInfo);

    m_pYesBtn = new QPushButton("确定", this);
    m_pNoBtn = new QPushButton("取消",this);
    QHBoxLayout *h = new QHBoxLayout();
    h->addWidget(m_pYesBtn);
    h->addWidget(m_pNoBtn);
    h->setSpacing(120);
    h->addStretch();
    m_pvBox->addLayout(h);
    m_pvBox->setSpacing(60);
    m_pvBox->addStretch();

    this->setStyleSheet("QLineEdit{font: 14px;width:70px;height:25;}QPushButton{font: 14px;width:100px;height:25;}QLabel{font: 16px}QGroupBox{border: 1px solid white;border-radius:8px;margin-top:6px;}QGroupBox:title{color:rgb(24,24,58);subcontrol-origin: margin;left: 10px;}");
    this->setLayout(m_pvBox);

}
