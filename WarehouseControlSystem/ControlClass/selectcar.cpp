#include "selectcar.h"

SelectCar::SelectCar(QObject *parent) : QObject(parent)
{

}
/**
 * @brief SelectCar::getCarIp_out
 * @param p 料箱的库位坐标
 *        出库时根据料箱号来选择小车
 * @return 返回小车的ip NoCarUse:表示所有的小车都在做任务
 */
QString SelectCar::getCarIp_out(const KPosition &p)
{
    QMap<int,QString> socker_map;
    socker_map.clear();
    for(auto it= Myconfig::GetInstance()->m_CarMap.begin();it != Myconfig::GetInstance()->m_CarMap.end();it++)
    {
        //小车的状态由自己来做标记，同一个任务需要多次向小车发送命令,在未完成之前都是doing状态
        if(it.value().deveceStatus.isLocking == false && it.value().deveceStatus.status == 1 && it.value().deveceStatus.isOnline)
        {
            if(it.value().deveceStatus.carCurrentPosion.z == p.z)
            {
                change_status(it.value().deviceIp);
                return it.value().deviceIp;
            }
            else if(qAbs(it.value().deveceStatus.carCurrentPosion.z - p.z) == 1)
            {
                change_status(it.value().deviceIp);
                return it.value().deviceIp;
            }
            socker_map.insert(qAbs(it.value().deveceStatus.carCurrentPosion.z-p.z),it.value().deviceIp);
        }
    }
    if(socker_map.size() == 0)
        return "NoCarUse";
    else
    {
        int key = 99;
        for(auto it = socker_map.begin();it != socker_map.end();it++)
        {
            if(it.key() <key)
                key = it.key();
        }
        change_status(socker_map[key]);
        return socker_map[key];
    }
}
/**
 * @brief SelectCar::getCarIp_in
 * @param p 入库时料想的坐标
 * @return 返回小车的ip
 */
QString SelectCar::getCarIp_in(const KPosition &p)
{
    //小车Z的差值，小车的ip
    QMap<int,QString> socker_map;
    socker_map.clear();
    for(auto it= Myconfig::GetInstance()->m_CarMap.begin();it != Myconfig::GetInstance()->m_CarMap.end();it++)
    {
        //小车的状态由自己来做标记，同一个任务需要多次向小车发送命令,在未完成之前都是doing状态
        if(it.value().deveceStatus.isLocking = false && it.value().deveceStatus.status == 1&& it.value().deveceStatus.isOnline)
        {
            if(it.value().deveceStatus.carCurrentPosion.z == p.z)
            {
                return it.value().deviceIp;
            }
            else if(qAbs(it.value().deveceStatus.carCurrentPosion.z - p.z) == 1)
            {
                return it.value().deviceIp;
            }
            socker_map.insert(qAbs(it.value().deveceStatus.carCurrentPosion.z-p.z),it.value().deviceIp);
        }
    }
    int key = 99;
    // sort about z
    for(auto it = socker_map.begin();it != socker_map.end();it++)
    {
        if(it.key() < key)
            key = it.key();
    }
    Myconfig::GetInstance()->m_CarMap[socker_map[key]].deveceStatus.isLocking = true;
    return socker_map[key];

}

void SelectCar::change_status(QString carIp)
{
    Myconfig::GetInstance()->m_CarMap[carIp].deveceStatus.isLocking = true;
    Myconfig::GetInstance()->m_CarMap[carIp].deveceStatus.status = 2;
    //qDebug()<<"select car change car status"+carIp;
}
///
/// \brief SelectCar::hasUseCar
/// 选车调车由主线程分配，不用加锁
/// \return true = haveCar false = noCarUse
///
bool SelectCar::hasUseCar()
{
    for(auto it= Myconfig::GetInstance()->m_CarMap.begin();it != Myconfig::GetInstance()->m_CarMap.end();it++)
    {
        if(it.value().deveceStatus.isLocking == false && it.value().deveceStatus.status == 1 && it.value().deveceStatus.isOnline)
            return true;
    }
    return false;
}
