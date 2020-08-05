#include "monitorui.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QGridLayout>
#include <QScrollBar>
#include <QLabel>
#define ROADWIDTH 30
using namespace std;

MonitorUI::MonitorUI(QWidget *parent):QWidget(parent)
{
    this->resize(parent->width(),parent->height());
    this->setStyleSheet("QLabel{font:13px;}");
    m_cursceneMap.clear();
    m_sizeW = 5;
    m_sizeH = 5;
    m_laycombox = new  QComboBox(this);
    m_laycombox->setFixedHeight(28);
    QObject::connect(m_laycombox,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&MonitorUI::SetCurLayUI);
    m_refreshbtn = new QPushButton("刷新",this);
    // m_refreshbtn->setIcon(QIcon(":/resouse/Image/Refresh.png"));
    m_refreshbtn->setStyleSheet("QPushButton{font:12px;background-color: rgba(18, 80, 155, 255);color:rgb(230, 230, 230);}");
    m_laycombox->setStyleSheet("QComboBox{font:12px;}");
    connect(m_refreshbtn,&QPushButton::clicked,this,&MonitorUI::updateUIbyData);
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(m_laycombox);
    hbox->setSpacing(20);
    hbox->addWidget(m_refreshbtn);
    // hbox->addWidget(new QSplitter);

    // QHBoxLayout *hlabel = new QHBoxLayout();

    QLabel *label= new QLabel(tr("仓位状态空:"));
    QLabel *emptylabel= new QLabel();

    label->setFixedSize(70,15);
    emptylabel->setObjectName("emptyrect");
    emptylabel->setFixedSize(15,15);
    emptylabel->setStyleSheet("#emptyrect{font:12px;background-color: rgb(164, 160, 160);}");

    hbox->addWidget(label,Qt::AlignLeft);
    hbox->addWidget(emptylabel,Qt::AlignLeft);

    QLabel *labelf= new QLabel(tr("仓位状态满:"));
    labelf->setFixedSize(70,15);
    QLabel *fulllabel= new QLabel();
    fulllabel->setObjectName("fullrect");
    fulllabel->setFixedSize(15,15);
    fulllabel->setStyleSheet("#fullrect{font:12px;background-color: rgb(0, 160, 0);}");

    hbox->addWidget(labelf,Qt::AlignLeft);
    hbox->addWidget(fulllabel,Qt::AlignLeft);

    QLabel *labellock= new QLabel(tr("仓位状态锁定:"));
    labellock->setFixedSize(80,15);
    QLabel *locklabel= new QLabel();
    locklabel->setObjectName("lockrect");
    locklabel->setFixedSize(15,15);
    locklabel->setStyleSheet("#lockrect{font:12px;background-color: rgb(200, 0, 0);}");

    hbox->addWidget(labellock,Qt::AlignLeft);
    hbox->addWidget(locklabel,Qt::AlignLeft);


    QLabel *labelun= new QLabel(tr("仓位状态未定义:"));
    labelun->setFixedSize(100,15);
    QLabel *unlabel= new QLabel();
    unlabel->setObjectName("unrect");
    unlabel->setFixedSize(15,15);
    unlabel->setStyleSheet("#unrect{font:12px;background-color: rgb(34, 180, 180);}");

    hbox->addWidget(labelun,Qt::AlignLeft);
    hbox->addWidget(unlabel,Qt::AlignLeft);



    //QSplitter *spil = new QSplitter;
    // hlabel->addWidget(spil);
    hbox->addWidget(new QSplitter);


    QVBoxLayout *vboxlay = new QVBoxLayout;
    vboxlay->addLayout(hbox);

    vboxlay->setSpacing(20);

    //  vboxlay->addLayout(hlabel);
    //显示当前的界面数据信息
    m_pview = new MonitorView(this);
    m_pview->setFixedSize(parent->width()-40,parent->height()-60);
    m_curscene = new QGraphicsScene;
    SetUIDataItem();
    m_laycombox->setCurrentIndex(0);
    if(m_cursceneMap.size() > 0)
    {
        SetCurLayUI(0);
    }
    // m_pview->setScene(m_curscene);
    vboxlay->addWidget(m_pview);
    this->setLayout(vboxlay);
    //增加刷新当前数据的timer
    m_timer = new QTimer();
    connect(m_timer,&QTimer::timeout,this,&MonitorUI::updateCurSceneData);
    m_timer->start(200);
}

MonitorUI::~MonitorUI()
{
    if(m_timer)
    {
        m_timer->stop();
        delete m_timer;
    }
    m_cursceneMap.clear();
    if(m_pview)
    {
        delete m_pview;
    }
}

void MonitorUI::SetCurLayUI(int index)
{
    Q_UNUSED(index)
    //当前层数显示
    QString indexstr = m_laycombox->currentText();
    QString str = indexstr.mid(1,indexstr.size()-6);
    //得到当前层数的值
    double z = str.toDouble() ;
    if(m_cursceneMap.contains(z))
    {
        m_pview->setScene(m_cursceneMap[z]);
        m_curscene = m_cursceneMap[z];
    }
}
///
/// \brief MonitorUI::updateUIbyData
///刷新数据库的地图数据进行重建
void MonitorUI::updateUIbyData()
{
    //内存数据进行重新分配item 计算画布数量 和 插入对应的画布场景
    //显示画布首页的状态
    SetUIDataItem();
}
///
/// \brief MonitorUI::updateCurSceneData
///得到当前的场景，对场景中的数据进行更新
void MonitorUI::updateCurSceneData()
{
    //当前层数显示
    QString indexstr = m_laycombox->currentText();
    QString str = indexstr.mid(1,indexstr.length()-6);
    //得到当前层数的值
    double z = str.toDouble() ;
    if(m_cursceneMap.contains(z))
    {
        QGraphicsScene *Scene =  m_cursceneMap[z];
        if(Scene)
        {
            foreach(QGraphicsItem *mGraphicsItem, Scene-> items())
            {
                StoreItem *FindItem = dynamic_cast<StoreItem *>(mGraphicsItem);
                if(!FindItem)
                    continue;
                QString id = FindItem->GetIndexID();
                //  qDebug()<<"idnbr"<<id;
                if( Myconfig::GetInstance()->m_storeinfoMap.contains(id)&& id != "")
                {
                    QString text = "";
                    char state = 3;
                    state = Myconfig::GetInstance()->m_storeinfoMap[id].storestat;
                    text =  QString::fromUtf8(Myconfig::GetInstance()->m_storeinfoMap[id].boxnbr);
                    if(FindItem->GetText()!= text)//料箱信息更新
                    {
                        FindItem->SetText(text);
                    }
                    if(FindItem->GetState() !=state )//料箱状态更新
                    {
                        FindItem->SetStoreSate(state);
                    }
                }
            }
        }
    }
}
///
/// \brief MonitorUI::GetAllLayers
/// \return
///得到所有的层数的结构体
void  MonitorUI::GetAllLayers()
{
    m_laylist.clear();
    QList<double> layvalues = BaseDataInfoOperate::GetLayersFromStorePosInfo();
    std::sort(layvalues.begin(), layvalues.end());
    for(int i = 0; i < layvalues.size();++i)
    {
        m_laylist.append(QString("第%1层区域画面").arg(layvalues[i]));
    }
    m_laycombox->clear();
    m_laycombox->addItems(m_laylist);
}

///
/// \brief MonitorUI::SetSceneMapData
///设置场景数据map信息
void MonitorUI::SetSceneMapData()
{ 
    GetAllLayers();//得到所有的层数
    m_cursceneMap.clear();//数据删除 重新更
    int roadwidth = ROADWIDTH; //预留过道的高度
    GetstoreposSize();
    for(int i = 0; i <m_laylist.size(); ++i )
    {
        QString str = m_laylist[i].mid(1,m_laylist[i].size()-6);
        //得到当前层数
        double z = str.toDouble() ;
        //获得本层数据结构体
        QMap<QString, StorePosInfoStru>  laymap = BaseDataInfoOperate::GetStorePosInfoMapByLayer\
                (z,Myconfig::GetInstance()->m_storeinfoMap);
        QGraphicsScene *curlay = new QGraphicsScene;
        curlay->setSceneRect(-300,-300,this->width()-40+300,this->height()-60+300);
        curlay->setItemIndexMethod(QGraphicsScene::NoIndex);
        for(double y = 0; y <= 1; ++y)
        {
            for(double x = 0; x <= m_X;++x)
            {
                //先是0,后边是1
                QString text = "";
                char state = 3;
                QString id = "";
                id =  FindStorePos(state,text,laymap,0,x,y);
                if(id == "")
                {
                    continue;
                }
                double startx= x*m_sizeW;
                double starty = this->height()-60-40-(y*m_sizeH*2+roadwidth*y);
                double stopx =x*m_sizeW+m_sizeW;
                double stopy =starty-m_sizeH;
                StoreItem *item = new StoreItem(startx,starty ,stopx,stopy);
                //qDebug()<<"0pos坐标位置"<<z<<startx<< starty<<stopx<<stopy;
                item->SetIndexID(id);
                // text =
                item->SetText(text);
                item->SetStoreSate(state);
                curlay->addItem(item);
                //先是0,后边是1
                id =FindStorePos(state,text,laymap,1,x,y);
                if(id == "")
                {
                    continue;
                }
                item = new StoreItem(startx,stopy+roadwidth ,stopx,stopy+roadwidth+m_sizeH);
                //  qDebug()<<"1pos坐标位置"<<z<<startx <<stopy+roadwidth<<stopx<<stopy+roadwidth+m_sizeH;
                item->SetIndexID(id);
                item->SetText(text);
                item->SetStoreSate(state);
                curlay->addItem(item);
            }
        }
        m_cursceneMap.insert(z,curlay);
    }
}
///
/// \brief MonitorUI::SetUIDataItem
///  seco nd method create  item data 2020/07/29
void MonitorUI::SetUIDataItem()
{

    GetAllLayers();//得到所有的层数
    m_cursceneMap.clear();//数据删除 重新更
    int roadwidth = ROADWIDTH; //预留过道的高度
    GetstoreposSize();
    double layh = (this->height()-60-40-(2*m_Y*m_sizeH+ m_Y*roadwidth))/2 ;
    layh = layh+(2*m_Y*m_sizeH+ m_Y*roadwidth)/2;
    for(int i =0; i < m_laylist.size(); ++i )
    {
        QString str = m_laylist[i].mid(1,m_laylist[i].size()-6);
        //得到当前层数
        double z = str.toDouble() ;
        //获得本层数据结构体
        QMap<QString, StorePosInfoStru>  laymap = BaseDataInfoOperate::GetStorePosInfoMapByLayer\
                (z,Myconfig::GetInstance()->m_storeinfoMap);
        QGraphicsScene *curlay = new QGraphicsScene;
        curlay->setSceneRect(-30,-60,this->width()-40,this->height()-60);

        curlay->setItemIndexMethod(QGraphicsScene::NoIndex);

        for(auto it = laymap.begin(); it != laymap.end();++it)
        {
            double startx= it.value().coordx*m_sizeW;
            double starty = layh-(it.value().coordy*m_sizeH*2+roadwidth*it.value().coordy);
            double stopx =it.value().coordx*m_sizeW+m_sizeW;
            double stopy = starty-m_sizeH;
            if(it.value().directionstate == 1)
            {
                starty = stopy-roadwidth;
                stopy =  stopy-roadwidth-m_sizeH;
            }
            StoreItem *item = new StoreItem(startx,stopy ,stopx,starty);

            item->SetIndexID(QString(it.value().idnbr));
            QString text = QString::fromUtf8(it.value().boxnbr);
            //qDebug()<<"坐标位置"<<stopy<< starty  << startx<< stopx <<text ;
            item->SetText(text);
            item->SetStoreSate(it.value().storestat);
            curlay->addItem(item);
        }
        m_cursceneMap.insert(z,curlay);
    }
}
///
/// \brief MonitorUI::FindStorePos
/// \param state
/// \param text
/// \param laymap
/// \return
///根据本层信息找到对应数据中Xy的坐标和方向状态
QString MonitorUI::FindStorePos(char &state, QString &text, QMap<QString, StorePosInfoStru>  laymap,char direction,double x,double y)
{
    bool find = false;
    QString id = "";
    StorePosInfoStru stru;

    for( auto item =laymap.begin(); item != laymap.end(); ++item )
    {
        if((item.value().coordx == x )&&(item.value().coordy == y)&&(item.value().directionstate ==uint8_t(direction)))
        {
            //状态显示判断
            stru = item.value();
            find = true;
            id = item.key();
            break;
        }
    }
    if(find)
    {
        state = stru.storestat;
        text = QString::fromUtf8(stru.boxnbr);
    }
    else{
        state = 3;
        text = tr("未定义");
    }
    return id;
}
///
/// \brief MonitorUI::GetstoreposSize
///计算得到仓位的显示尺寸信息
void MonitorUI::GetstoreposSize()
{
    double x= BaseDataInfoOperate::GetXMaxValue();
    double y = BaseDataInfoOperate::GetYMaxValue();
    if(x >= 0 && y >= 0)
    {
        double w  =(this->size().width() -40)/(x+1)/2;//同一个坐标对应两个仓位编号
        double h = (this->size().width() -60)/(y+1)/3;//同一个坐标对应两个仓位编号 小车过道的位置预留出
        m_X = x;
        m_Y = y;
        m_sizeW = w;
        m_sizeH = h;
    }
    if(m_sizeW <= 4)
    {
        m_sizeW = 5; //设置最小尺寸5
    }
    if(m_sizeH <= 4)
    {
        m_sizeH = 5;//设置最小尺寸5
    }
    m_sizeH = 20;
    m_sizeW =30;
}
