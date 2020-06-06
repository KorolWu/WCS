#include "progressbardelegate.h"
#include <QPainter>
#include <QApplication>
ProgressBarDelegate::ProgressBarDelegate(QObject *parent):QItemDelegate(parent)
{

}

void ProgressBarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    int value = index.model()->data(index).toInt();
    double factor = double(value)/100.0; // 计算比例因子
    //    QStyleOptionProgressBarV2 progressBarOption;
    //    progressBarOption.rect = option.rect.adjusted(4, 4, -4, -4);
    //    progressBarOption.minimum = 0;
    //    progressBarOption.maximum = 100;
    //    progressBarOption.textAlignment = Qt::AlignRight;
    //    progressBarOption.textVisible = true;
    //    progressBarOption.progress = value;
    //    progressBarOption.text = tr("%1%").arg(progressBarOption.progress);
    //    painter->save();
    painter->setPen(Qt::white);
    if(factor > 0.3)
        painter->setBrush(QColor(71,214,105));
    else
        painter->setBrush(QColor(255,205,88));
    //    if (option.state & QStyle::State_Selected) {
    //        painter->fillRect(option.rect, option.palette.highlight());
    //        painter->setBrush(option.palette.highlightedText());
    //    }
    //    QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);
    painter->drawRect( option.rect.x()+2, option.rect.y()+2, int(factor*(option.rect.width()-5)), option.rect.height()-5 );

    painter->setFont(QFont("Arial", 10));
    painter->drawText(option.rect.x()+2, option.rect.y()+2, int(factor*(option.rect.width()-5)), option.rect.height()-5, Qt::AlignCenter, tr("%1%").arg(value));
    //painter->restore();


    // return QItemDelegate::paint (painter, option, index);

}
