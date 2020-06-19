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
    else
        painter->setBrush(QColor(200,200,200));
    painter->setPen(Qt::white);
    painter->drawRect( option.rect.x()+2, option.rect.y()+2, option.rect.width()-4, option.rect.height()-4 );
    painter->setFont(QFont("Arial", 10));
    painter->drawText(option.rect.x()+2, option.rect.y()+2, option.rect.width()-4, option.rect.height()-4, Qt::AlignCenter, str);
}


