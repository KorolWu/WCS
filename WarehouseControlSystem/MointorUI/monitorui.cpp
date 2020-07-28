#include "monitorui.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QGridLayout>
#include <QScrollBar>

MonitorUI::MonitorUI(QWidget *parent):QWidget(parent)
{
   this->resize(parent->width(),parent->height());
    m_cursceneMap.clear();
    m_sizeW = 5;
    m_sizeH = 5;
    m_laycombox = new  QComboBox();
   // GetAllLayers();
  //
    m_refreshbtn = new QPushButton("刷新",this);
    connect(m_refreshbtn,&QPushButton::clicked,this,&MonitorUI::updateUIbyData);
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(m_laycombox);
    hbox->addWidget(m_refreshbtn);
    hbox->addWidget(new QSplitter);
    QVBoxLayout *vboxlay = new QVBoxLayout;
    vboxlay->addLayout(hbox);
    //显示当前的界面数据信息
    m_pview = new MonitorView(this);
    m_pview->setFixedSize(parent->width()-40,parent->height()-60);
    m_curscene = new QGraphicsScene;
    //    int sizew = 60;
    //    int sizeh = 30;
    //    m_curscene->setSceneRect(-30,-30,parent->width()-40,parent->height()-60);
    //    m_curscene->setItemIndexMethod(QGraphicsScene::NoIndex);
    //    StoreItem *item = new StoreItem(0,0,0+sizew,0+sizeh);
    //    item->SetText(tr("仓位编号00"));
    //    m_curscene->addItem(item);
    //    item = new StoreItem(sizew+10,0,sizew*2+10,sizeh);
    //    item->SetText(tr("仓位编号01"));
    //    m_curscene->addItem(item);
    //    for(int i = 3; i < 26;++i)
    //    {
    //        StoreItem *  itemtest = new StoreItem(sizew*(i-1)+10,0,sizew*i+10,sizeh);
    //        itemtest->SetText(QString(tr("仓位编号%1").arg(i)));
    //        m_curscene->addItem(itemtest);
    //    }
    //获取场景map的数据信息
    SetSceneMapData();
    m_laycombox->setCurrentIndex(0);
    if(m_cursceneMap.size() > 0)
    {
        SetCurLayUI();
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

void MonitorUI::SetCurLayUI()
{
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
    qSort(layvalues.begin(), layvalues.end());
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
    int roadwidth = 30; //预留过道的高度
    GetstoreposSize();
    for(int i =0; i <m_laylist.size(); ++i )
    {
        QString str = m_laylist[i].mid(1,m_laylist[i].size()-6);
        //得到当前层数
        double z = str.toDouble() ;
        //获得本层数据结构体
        QMap<QString, StorePosInfoStru>  laymap = BaseDataInfoOperate::GetStorePosInfoMapByLayer\
                (z,Myconfig::GetInstance()->m_storeinfoMap);
        QGraphicsScene *curlay = new QGraphicsScene;
        curlay->setSceneRect(-30,-30,this->width()-40,this->height()-60);
        curlay->setItemIndexMethod(QGraphicsScene::NoIndex);
        for(double y = 0; y <= m_Y; ++y)
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
                double starty = y*m_sizeH*2+roadwidth*y;
                double stopx =x*m_sizeW+m_sizeW;
                double stopy =y*m_sizeH*2+roadwidth*y+m_sizeH;
                StoreItem *item = new StoreItem(startx,starty ,stopx,stopy);
              //  qDebug()<<"0pos坐标位置"<<z<<startx<< starty<<stopx<<stopy;
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
    if(x > 0 && y > 0)
    {
        double w  =(this->size().width() -40)/x/2;//同一个坐标对应两个仓位编号
        double h = (this->size().width() -60)/y/3;//同一个坐标对应两个仓位编号 小车过道的位置预留出
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
