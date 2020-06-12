#include "labeldelegate.h"
#include <QDebug>
#include <QApplication>
#include <QPainter>
LabelDelegate::LabelDelegate(QObject *parent): QStyledItemDelegate(parent)
{


}

QWidget *LabelDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    QPushButton *lab = new QPushButton(parent);
    return lab;
}

void LabelDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::EditRole).toString();
    QPushButton *lab = static_cast<QPushButton*>(editor);
    lab->setText(text);
}

void LabelDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QPushButton *lineEdit = static_cast<QPushButton*>(editor);
    QString text = lineEdit->text();
    if(text == "在线")
        lineEdit->setStyleSheet("color:green");
    else
        lineEdit->setStyleSheet("font: 46px");
    model->setData(index, text, Qt::EditRole);
    qDebug()<<"setModelData";
}

void LabelDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
    editor->setStyleSheet("color:red");
}

void LabelDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

//    QStyleOptionButton *button = new QStyleOptionButton();
//    button->rect = option.rect.adjusted(4, 4, -4, -4);
//    button->text = index.model()->data(index, Qt::EditRole).toString();
//    button->state |= QStyle::State_Enabled;
//    painter->save();
//    if (option.state & QStyle::State_Selected) {
//        painter->fillRect(option.rect, option.palette.highlight());
//    }
//    painter->setBrush(QColor(255,205,88));
//    painter->restore();
//    QApplication::style()->drawControl(QStyle::CE_PushButton, button, painter);

    QString str = index.model()->data(index).toString();
    if(str == "在线")
        painter->setBrush(QColor(71,214,105));
    else if(str == "离线")
        painter->setBrush(QColor(200,200,200));
    else
        painter->setBrush(QColor(200,200,200));
    painter->setPen(Qt::white);
    painter->drawRect( option.rect.x()+2, option.rect.y()+2, option.rect.width()-4, option.rect.height()-4 );
    painter->setFont(QFont("Arial", 10));
    painter->drawText(option.rect.x()+2, option.rect.y()+2, option.rect.width()-4, option.rect.height()-4, Qt::AlignCenter, str);
}
