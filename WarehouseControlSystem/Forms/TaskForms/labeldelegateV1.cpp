#include "labeldelegateV1.h"
#include <QDebug>
#include <QApplication>
#include <QPainter>
LabelDelegateV1::LabelDelegateV1()
{

}

void LabelDelegateV1::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QString str = index.model()->data(index).toString();
    if(str == "已完成")
        painter->setBrush(QColor(71,214,105));
    else if(str == "取消")
        painter->setBrush(QColor(200,200,200));
    else if(str == "出库")
        painter->setBrush(QColor(170,255,255));
    else if(str == "入库")
         painter->setBrush(QColor(170,255,127));
    else if(str == "未执行")
         painter->setBrush(QColor(190,190,190));
    else if(str == "执行成功")
        painter->setBrush(QColor(152,251,152));
    else if(str == "执行失败")
        painter->setBrush(QColor(205,92,92));
    else
        painter->setBrush(QColor(255,0,0));
    painter->setPen(Qt::white);
    painter->drawRect( option.rect.x()+2, option.rect.y()+2, option.rect.width()-4, option.rect.height()-4 );
    painter->setFont(QFont("Arial", 10));
    painter->drawText(option.rect.x()+2, option.rect.y()+2, option.rect.width()-4, option.rect.height()-4, Qt::AlignCenter, str);
}


