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
    m_pview->setFixedSize(this->width()-60,this->height()-40);
    //-5000,-60000,5000,60000
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
    m_carpos.state = 0;
    m_carpos.x = 0;
    m_carpos.y = 0;
    m_carpos.z = 1;
    //增加刷新当前数据的timer
    m_timer = new QTimer();
    connect(m_timer,&QTimer::timeout,this,&MonitorUI::updateCurSceneData);
    m_scanPathtimer = new QTimer();
    connect(m_scanPathtimer,&QTimer::timeout,this,&MonitorUI::slotCarPathsimulation);
    //test car pos
    m_carpos = GetCarPos(99); //默认ID等于99
    m_caritem = new StoreItem(m_carpos.x/k-10,m_carpos.y/k-10,m_carpos.x/k+10,m_carpos.y/k+10);
    qDebug()<<"x:"<<m_carpos.x/k<<" y:"<<m_carpos.y/k;
    m_caritem->SetText("car");
    m_caritem->SetIndexID("99");
    if(m_cursceneMap.size()> 0 &&m_cursceneMap.contains(1) )
    {
        m_cursceneMap[1]->addItem(m_caritem);
    }
    m_caritem->SetStoreSate(9);
    m_xpathppos.clear();
    m_ypathppos.clear();
    qDebug()<<"befor"<<m_caritem->pos().x()<<","<<m_caritem->pos().y();
    //m_caritem->setPos(100,100);
    qDebug()<<"after"<<m_caritem->pos().x()<<","<<m_caritem->pos().y();
    m_coefficient = 1;
    m_running = false;
    m_timer->start(100);

}

MonitorUI::~MonitorUI()
{
    if(m_timer)
    {
        m_timer->stop();
        delete m_timer;
    }
    m_scanPathtimer->stop();
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
double movvalue = 0;
bool maxflag = false;
bool minflag = false;
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
                    if(text.size()>3)
                    {
                        text = text.right(text.size()-3);
                    }
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
    if(z != 1)
        return;
    UpdateCarPosPathVec(); //添加了刷新的内容
//    if(!minflag && !maxflag)
//    {
//        movvalue--;
//    }
//    if(movvalue < m_minY/k )
//    {
//        minflag = true;
//        maxflag = false;
//    }
//    if(minflag&& !maxflag)
//    {
//        movvalue ++;
//    }
//    if(movvalue > (m_Y-m_minY)/k )
//    {
//        maxflag = true;
//        minflag = false;
//    }
//    if(maxflag&& !minflag)
//    {
//        movvalue--;
//    }
//    m_caritem->setPos(0,movvalue);
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
                if(text.size()>3)
                {

                    text = text.right(text.size()-3);
                }
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
    GetstoreposSize();
    double roadwidth = 640/k; //预留过道的高度 实际距离640 缩小30系数之后尺寸
    double layh = (this->height()-60-40-(2*m_Y*m_sizeH+ m_Y*roadwidth))/2 ;
    layh = layh+(2*m_Y*m_sizeH+ m_Y*roadwidth)/2;
    m_sizeW = 640/k;
    m_sizeH = 450/k;
    qDebug()<<"value:"<<roadwidth<<m_sizeW<<m_sizeH <<k;
    // roadwidth = 30;
    for(int i =0; i < m_laylist.size(); ++i )
    {
        QString str = m_laylist[i].mid(1,m_laylist[i].size()-6);
        //得到当前层数
        double z = str.toDouble() ;
        //获得本层数据结构体
        QMap<QString, StorePosInfoStru>  laymap = BaseDataInfoOperate::GetStorePosInfoMapByLayer\
                (z,Myconfig::GetInstance()->m_storeinfoMap);
        QGraphicsScene *curlay = new QGraphicsScene;
        // curlay->setSceneRect(-30,-60,this->width()-40,this->height()-60);
        //curlay->setSceneRect(-100,-500,800,1000);
        curlay->setSceneRect(m_minX/k-50,m_minY/k-50,(m_X-m_minX)/k+100,(m_Y-m_minY)/k+100);
        curlay->setItemIndexMethod(QGraphicsScene::NoIndex);

        for(auto it = laymap.begin(); it != laymap.end();++it)
        {

            //            double startx= it.value().coordx*m_sizeW;
            //            double starty = layh-(it.value().coordy*m_sizeH*2+roadwidth*it.value().coordy);
            //            double stopx =it.value().coordx*m_sizeW+m_sizeW;
            //            double stopy = starty-m_sizeH;
            double startx = it.value().coordx/k-0.5*roadwidth-m_sizeW;
            double starty = it.value().coordy/k;
            double stopx = startx+m_sizeW;
            double stopy = starty+m_sizeH;



            QStringList keylist = it.key().split("-");
            if(keylist.size() == 5)
            {
                QString dirstateinfo = keylist[2];
                dirstateinfo  =   dirstateinfo.right(dirstateinfo.size()-1);
                // qDebug()<<"str:"<<dirstateinfo<<dirstateinfo.toInt() << dirstateinfo.toInt()%2;
                if(dirstateinfo.toInt()%2 == 0)
                {
                    startx = stopx+roadwidth;
                    stopx =  stopx+roadwidth+m_sizeW;
                    // if(it.value().coordz == 1)
                    {
                        // qDebug()<<"坐标位置:"<<startx<< starty  << stopx<< stopy <<laymap.size() << dirstateinfo<<it.key();
                    }
                }
            }
            StoreItem *item = new StoreItem(startx,starty ,stopx,stopy);

            item->SetIndexID(QString(it.value().idnbr));
            QString text = QString::fromUtf8(it.value().boxnbr);
            if(text.size()>3)
            {

                text = text.right(text.size()-3);
            }
            // qDebug()<<"坐标位置"<<startx<< starty  << stopx<< stopy <<text <<laymap.size();
            item->SetText(text);
            item->SetStoreSate(it.value().storestat);
            curlay->addItem(item);
        }
        m_cursceneMap.insert(z,curlay);
    }
}
///
/// \brief MonitorUI::UpdateCarPos
///
void MonitorUI::UpdateCarPosPathVec()
{
    if(m_running)
        return;
    //小车结构体更新
    auto it =  Myconfig::GetInstance()->m_CarMap.begin();
    for(;it!= Myconfig::GetInstance()->m_CarMap.end();++it)
    {
        if(m_caritem->GetIndexID() == QString::number(it.key()))
        {
            double xdiffvalue = it.value().deveceStatus.carCurrentPosion.x-m_carpos.x;

            if(xdiffvalue != 0 )
            {
                //生成x计算轨迹
                m_xpathppos.clear();
                int sizecnt =  qAbs(xdiffvalue/k/m_coefficient);
                for(int i = 0; i < sizecnt; ++i)
                {
                    double value;
                    if(xdiffvalue < 0)
                    {
                         value = -1*i*m_coefficient + m_caritem->x();
                    }
                    else
                        value = i*m_coefficient + m_caritem->x();
                    m_xpathppos.append(value);
                }
                m_carpos.x = it.value().deveceStatus.carCurrentPosion.x;
                qDebug()<<xdiffvalue<<"-"<<m_xpathppos;
                break;
            }
            double ydiffvalue = it.value().deveceStatus.carCurrentPosion.y-m_carpos.y;
            //qDebug()<<"update pos y" <<it.value().deveceStatus.carCurrentPosion.y;
            if(ydiffvalue != 0 )
            {
                //生成y计算轨迹
                m_ypathppos.clear();
                int sizecnt =  qAbs(ydiffvalue/k/m_coefficient);
                for(int i = 0; i < sizecnt; ++i)
                {
                    double value;
                    if(ydiffvalue < 0)
                     value = -1*i*m_coefficient + m_caritem->y();
                    else
                        value = i*m_coefficient + m_caritem->y();
                    m_ypathppos.append(value);
                }
                m_carpos.y = it.value().deveceStatus.carCurrentPosion.y;
                qDebug()<<"-"<<ydiffvalue<<m_ypathppos <<m_carpos.x/k << m_coefficient<< k ;
                break;
            }
        }
    }
    if(m_ypathppos.size() > 0 || m_xpathppos.size() > 0 )
    {
          m_running = true;
        if(!m_scanPathtimer->isActive())
        {
            m_scanPathtimer->start(10);
        }
    }
}

KPosition MonitorUI::GetCarPos(int index)
{
    KPosition pos;

    //小车结构体更新
    auto it =  Myconfig::GetInstance()->m_CarMap.begin();
    for(;it!= Myconfig::GetInstance()->m_CarMap.end();++it)
    {
        if(index == it.key())
        {
            pos.state = it.value().task_position.state;
            pos.x = it.value().deveceStatus.carCurrentPosion.x;
            pos.y = it.value().deveceStatus.carCurrentPosion.y;
            pos.z = it.value().deveceStatus.carCurrentPosion.z;
        }
    }
    return pos;
}
///
/// \brief MonitorUI::slotCarPathsimulation
///小车轨迹模拟运行
int cnt = 0;
void MonitorUI::slotCarPathsimulation()
{
    if(m_xpathppos.size() > cnt )
    {
        m_running  = true;
        m_caritem->setPos(m_xpathppos[cnt],m_caritem->y());
        qDebug()<<"x:movvalue"<<m_carpos.x/k<<m_carpos.x/k<<m_xpathppos[cnt];
        cnt++;
    }
    else{
        if(m_running && m_ypathppos.size() <= 0)
        {
            m_running = false;
            m_scanPathtimer->stop();
            cnt = 0;
            m_xpathppos.clear();
        }
    }
    if(m_ypathppos.size() > cnt)
    {
        m_running  = true;
       // m_caritem->setPos(0,m_ypathppos[cnt]);
        m_caritem->setPos(m_caritem->x(),m_ypathppos[cnt]);
        qDebug()<<"y:movvalue"<<m_carpos.x/k<<m_carpos.y/k<<m_ypathppos[cnt];
        cnt++;
    }
    else{
        if(m_running && m_xpathppos.size() <= 0)
        {
            m_running = false;
            m_scanPathtimer->stop();
             cnt = 0;
             m_ypathppos.clear();
        }
         return;
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
    double xmin = BaseDataInfoOperate::GetXMinValue();
    double ymin = BaseDataInfoOperate::GetYMinValue();
    //qDebug()<<"maxbavalue:"<<x<<y<<ymin<<xmin << this->size().width() -40<<this->size();
    double k1  = 0;
    double k2 = 0;
    k1 = (x-xmin)/(this->size().width() -40);
    k2 = (y-ymin)/(this->size().height() -60);
    if(k1 > k2)
    {
        k = k1;
    }
    else{

        k = k2;
    }
    m_X = x;
    m_Y = y;
    m_minY = ymin;
    m_minX = xmin;

}
