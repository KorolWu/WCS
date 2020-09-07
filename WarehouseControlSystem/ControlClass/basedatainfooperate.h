#ifndef BASEDATAINFOOPERATE_H
#define BASEDATAINFOOPERATE_H

#include <QObject>
#include<Myconfig.h>
#include <datastructure.h>
#include <QList>
using namespace std;
///
///出库入库信息 出库的时候需要找到料箱所在的位置
///主要关于基础信息的操作，包含从内存数据中提取各种信息
/// StoreInfo空间主要是此数据库内存的信息
namespace StoreInfo {
class BaseDataInfoOperate
{
public:
    BaseDataInfoOperate();
    //获得数据信息函数 ReadData
    ///out 出库
    /// \brief GetWarehouselocationInfo根据需要料箱编号获得仓位编号函数
    /// \param boxinfo 料箱信息编号
    ///获得仓位编号信息
    /// 返回数据结构体，X Y Z位置，若信息的结果为空，说明无料箱的存在
    static  QString GetWarehouselocationInfoForOut(QString boxinfo,KPosition &posstru)
    {
        QString WlocInfo = "";
        QMutexLocker locker(&Myconfig::GetInstance()->m_rmutex);
        auto it = Myconfig::GetInstance()->m_storeinfoMap.begin();
        for(;it !=Myconfig::GetInstance()->m_storeinfoMap.end(); ++it)
        {
            QString str = QString::fromUtf8(it.value().boxnbr);
            if(str ==boxinfo )
            {
                posstru.x = it.value().coordx;
                posstru.y = it.value().coordy;
                posstru.z = it.value().coordz;
                posstru.state = it.value().directionstate;
                WlocInfo = it.key();
                break;
            }
        }
        return WlocInfo;
    }
    ///
    /// \brief GetBoxinfo
    /// \param WarehouselocationInfo
    /// \return
    ///根据仓位信息获得对应料箱编号
    /// 返回为空，那么仓位无料箱处于空闲状态
    static QString  GetBoxinfo(QString Whloctioninfo)
    {
        QString boxnfo = "";
        QMutexLocker locker(&Myconfig::GetInstance()->m_rmutex);
        if(Myconfig::GetInstance()->m_storeinfoMap.contains(Whloctioninfo))
        {
            boxnfo = QString::fromUtf8(Myconfig::GetInstance()->m_storeinfoMap[Whloctioninfo].boxnbr);
        }
        return boxnfo;
    }
    ////
    /// \brief GetStorePosInfoMapByLayer
    /// \param layer 层数的值
    /// \return  对应层数的所有MAPDATA
    ///得到对应层数的数据
    static QMap<QString, StorePosInfoStru>GetStorePosInfoMapByLayer(double layer,QMap<QString, StorePosInfoStru> datamap)
    {
        QMap<QString, StorePosInfoStru> laymap;
        auto it = datamap.begin();
        for(;it !=datamap.end(); ++it)
        {
            if(it.value().coordz == layer)
            {
                laymap.insert(it.key(),it.value());
            }
        }
        return laymap;
    }
    ///
    /// \brief GetStorePosInfoMapByEnble
    /// \return
    ///筛选出对应状态的数据MAP
    static QMap<QString, StorePosInfoStru>GetStorePosInfoMapByEnble(STORESTATE state,QMap<QString, StorePosInfoStru> datamap)
    {
        QMap<QString, StorePosInfoStru> enblemap;
        auto it = datamap.begin();
        for(;it !=datamap.end(); ++it)
        {
            if(it.value().storestat == state)
            {
                enblemap.insert(it.key(),it.value());
            }
        }
        return enblemap;
    }
    ///
    /// \brief GetStorePosInfoMapBystorpri
    /// \param datamap 传入的数据
    /// \return 返回对应级别高的结构体
    ///
    static StorePosInfoStru GetStorePosInfoMapBystorpri(QMap<QString, StorePosInfoStru> datamap)
    {
        StorePosInfoStru stru;
        auto it = datamap.begin();
        int pri = it.value().storepri;
        stru =  it.value();
        for(;it != datamap.end(); ++it)
        {
            if(it.value() .storepri> pri)
            {
                pri = it.value().storepri;
                stru = it.value();
            }
        }
        return stru;
    }
    ///
    /// \brief GetLayersFromStorePosInfo
    /// \return  返回料箱层数信息
    ///编辑所有的信息获取整个仓库中所有的层数信息
    static QList<double> GetLayersFromStorePosInfo()
    {
        QList<double> layers;
        QMutexLocker locker(&Myconfig::GetInstance()->m_rmutex);
        auto it = Myconfig::GetInstance()->m_storeinfoMap.begin();
        for(;it !=  Myconfig::GetInstance()->m_storeinfoMap.end(); ++it)
        {
            if(!layers.contains( it.value().coordz))
            {
                layers.append(it.value().coordz);
            }
        }
        return layers;
    }
    ///
    /// \brief GetXMaxValue
    /// \return
    ///
    static double GetXMaxValue(){
        QMutexLocker locker(&Myconfig::GetInstance()->m_rmutex);
        auto it = Myconfig::GetInstance()->m_storeinfoMap.begin();
        double x = it.value().coordx;
        for(;it != Myconfig::GetInstance()->m_storeinfoMap.end(); ++it)
        {
            if(it.value().coordx > x)
            {
                x= it.value().coordx;
            }
        }
        return x;
    }
    static double GetXMinValue(){
        QMutexLocker locker(&Myconfig::GetInstance()->m_rmutex);
        auto it = Myconfig::GetInstance()->m_storeinfoMap.begin();
        double x = it.value().coordx;
        for(;it != Myconfig::GetInstance()->m_storeinfoMap.end(); ++it)
        {
            if(it.value().coordx < x)
            {
                x = it.value().coordx;
            }
        }
        return x;
    }

    ///
    /// \brief GetYMaxValue
    /// \return
    ///
    static double GetYMaxValue(){
        QMutexLocker locker(&Myconfig::GetInstance()->m_rmutex);
        auto it = Myconfig::GetInstance()->m_storeinfoMap.begin();
        double y = it.value().coordy;
        for(;it != Myconfig::GetInstance()->m_storeinfoMap.end(); ++it)
        {
            if(it.value().coordy > y)
            {
                y= it.value().coordy;
            }
        }
        return y;
    }
    static double GetYMinValue(){
        QMutexLocker locker(&Myconfig::GetInstance()->m_rmutex);
        auto it = Myconfig::GetInstance()->m_storeinfoMap.begin();
        double y = it.value().coordy;
        for(;it != Myconfig::GetInstance()->m_storeinfoMap.end(); ++it)
        {
            if(it.value().coordy < y)
            {
                y= it.value().coordy;
            }
        }
        return y;
    }

    ///
    /// \brief GetWarehouselocationInfoForIn
    /// \param boxinfo 料箱信息
    /// \param posstru 返回最终得到数据坐标
    /// \return
    ///实现入库动作选仓位算法目地
    /// 1.筛选出每层的仓位
    /// 2.筛选出空的仓位
    /// 3.筛选出优先级别最高的
    static bool  GetWarehouselocationInfoForIn(QString boxinfo,KPosition &posstru,QList<double> layers,QString &id)
    {
        id = "";
        if(BaseDataInfoOperate::CheckBoxnbronWarehouselocation(boxinfo))
            return false;
        //从低层筛选层数取值范围
        std::sort(layers.begin(), layers.end());
        for(int i = 0; i < layers.size(); ++i)
        {
            QMutexLocker locker(&Myconfig::GetInstance()->m_rmutex);
            QMap<QString, StorePosInfoStru> laymap= BaseDataInfoOperate::GetStorePosInfoMapByLayer\
                    (layers[i],Myconfig::GetInstance()->m_storeinfoMap);
            if(laymap.size() > 0)
            {
                QMap<QString, StorePosInfoStru> enblemap = BaseDataInfoOperate::GetStorePosInfoMapByEnble\
                        (ENBLED,laymap);
                if(enblemap.size() > 0)
                {
                    StorePosInfoStru  pristru = BaseDataInfoOperate::GetStorePosInfoMapBystorpri(enblemap);
                    posstru.x = pristru.coordx;
                    posstru.y = pristru.coordy;
                    posstru.z = pristru.coordz;
                    posstru.state = pristru.directionstate;
                    id = pristru.idnbr;
                    break;
                }
            }
        }
        return true;
    }
    ///
    /// \brief GetWarehouselocationInfoForIn
    /// \param boxinfo
    /// \param posstru
    /// \param id
    /// \return
    ///
    static bool GetWarehouselocationInfoForIn(QString boxinfo,KPosition &posstru,QString &id)
    {
        QList<double> layers = BaseDataInfoOperate::GetLayersFromStorePosInfo();
        return BaseDataInfoOperate::GetWarehouselocationInfoForIn(boxinfo,posstru,layers,id);
    }
    ///
    /// \brief GetWarehouselocationInfoForIn_V1
    /// \param boxinfo
    /// \param posstru
    /// \param id
    /// \return
    ///测试部分的代码根据箱子号得到货架号码
    static bool GetWarehouselocationInfoForIn_V1(QString boxinfo,KPosition &posstru,QString &id)
    {

        QMutexLocker locker(&Myconfig::GetInstance()->m_rmutex);
        auto it = Myconfig::GetInstance()->m_storeinfoMap.begin();
        for(;it !=Myconfig::GetInstance()->m_storeinfoMap.end(); ++it)
        {
            QString str = QString::fromUtf8(it.value().boxnbr);
            if(str ==boxinfo )
            {
                posstru.x = it.value().coordx;
                posstru.y = it.value().coordy;
                posstru.z = it.value().coordz;

                QStringList keylist = it.key().split("-");
                if(keylist.size() == 5)
                {
                    QString dirstateinfo = keylist[2];
                    dirstateinfo  =   dirstateinfo.right(dirstateinfo.size()-1);
                    if(dirstateinfo.toInt()%2 == 0) //左边是x值小的
                    {
                       posstru.state = 1;
                    }
                    else{
                        posstru.state = 0; //A1 x坐标系左边
                    }
                }
                id = it.key();
                return true;
            }
        }
        return false;
    }

    ///
    /// \brief CheckBoxnbronWarehouselocation
    /// \param boxinfo 料箱号
    /// \return true 已有料箱 false 无料箱在仓库
    ///
    static bool CheckBoxnbronWarehouselocation(QString boxinfo)
    {
         QMutexLocker locker(&Myconfig::GetInstance()->m_rmutex);

         auto it = Myconfig::GetInstance()->m_storeinfoMap.begin();
         for(;it !=Myconfig::GetInstance()->m_storeinfoMap.end(); ++it)
         {
             QString str = QString::fromUtf8(it.value().boxnbr);
             if(str ==boxinfo )
             {
                return true;
             }
         }
         return false;
    }
};
}


#endif // BASEDATAINFOOPERATE_H
