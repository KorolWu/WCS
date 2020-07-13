#ifndef BASEDATAINFOOPERATE_H
#define BASEDATAINFOOPERATE_H

#include <QObject>
#include<Myconfig.h>
///
///
///主要关于基础信息的操作，包含从内存数据中提取各种信息
/// StoreInfo空间主要是此数据库内存的信息
namespace StoreInfo {
class BaseDataInfoOperate
{
public:
    BaseDataInfoOperate();
    //获得数据信息函数 ReadData
    ///
    /// \brief GetWarehouselocationInfo根据需要料箱编号获得仓位编号函数
    /// \param boxinfo 料箱信息编号
    ///获得仓位编号信息，第一种找到已经存在
    static  QString GetWarehouselocationInfo(QString boxinfo)
    {
        QString WlocInfo = "";
         QMutexLocker locker(&Myconfig::GetInstance()->m_rmutex);
        auto it = Myconfig::GetInstance()->m_storeinfoMap.begin();
        for(;it !=Myconfig::GetInstance()->m_storeinfoMap.end(); ++it)
        {
            QString str = QString::fromUtf8(it.value().boxnbr);
            if(str ==boxinfo )
            {
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
    ///根据料箱信息获得对应位置的仓位信息
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
    ///
    /// 分配可用的仓位的信息获得返回数据
};
}


#endif // BASEDATAINFOOPERATE_H
