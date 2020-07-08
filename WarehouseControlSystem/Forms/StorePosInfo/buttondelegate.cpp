#include "buttondelegate.h"
#include <QMouseEvent>
#include <QMessageBox>
#include <QPainter>
#include <QStyleOption>
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>

ButtonDelegate::ButtonDelegate(QObject *parent) :QItemDelegate(parent)
{

}
///
/// \brief ButtonDelegate::paint
/// \param painter
/// \param option
/// \param index
///
void ButtonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPair<QStyleOptionButton*, QStyleOptionButton*>* buttons = m_opbtns.value(index);
    if (!buttons) {
        QStyleOptionButton* editbutton = new QStyleOptionButton();
       // editbutton->text = "编辑";
        editbutton->icon = QIcon(":/resouse/Image/Edit.png");
        editbutton->iconSize= QSize(16,16);
        QColor veryLightBlue(230, 230, 230,0);
        QPalette palette = editbutton->palette;     
        palette.setBrush(QPalette::Window,veryLightBlue);//窗口背景颜色
        // palette.setBrush(QPalette::Base, Qt::red);
        palette.setBrush(QPalette::Button,veryLightBlue);//按钮颜色
        editbutton->state |= QStyle::State_Enabled;
        editbutton->palette = palette;
        QStyleOptionButton* delbutton = new QStyleOptionButton();
        //button2->rect = option.rect.adjusted(button1->rect.width() + 4, 4, -4, -4);
       // delbutton->text = "删除";
        delbutton->state |= QStyle::State_Enabled;
        delbutton->icon = QIcon(":/resouse/Image/deleterow.png");
        delbutton->iconSize= QSize(16,16);
        delbutton->palette = palette;
        buttons =new  QPair<QStyleOptionButton*, QStyleOptionButton*>(editbutton, delbutton);
        (const_cast<ButtonDelegate *>(this))->m_opbtns.insert(index, buttons);
    }
    buttons->first->rect = option.rect.adjusted(4, 4, -(option.rect.width() / 2 + 4) , -4); //
    buttons->second->rect = option.rect.adjusted(buttons->first->rect.width() + 4, 4, -4, -4);
   painter->save();
    painter->setRenderHint(QPainter::Antialiasing);//开启边缘反锯齿
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
    }
    painter->restore();
    QApplication::style()->drawControl(QStyle::CE_PushButton, buttons->first, painter);
    QApplication::style()->drawControl(QStyle::CE_PushButton, buttons->second, painter);
}

//QWidget *ButtonDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    Q_UNUSED(editor);
//    Q_UNUSED(index);
//}

//void ButtonDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
//{
//    Q_UNUSED(editor);
//    Q_UNUSED(index);

//}
///
/// \brief ButtonDelegate::editorEvent
/// \param event
/// \param model
/// \param option
/// \param index
/// \return
///
bool ButtonDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
      Q_UNUSED(model);
          Q_UNUSED(option);
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* e =(QMouseEvent*)event;
        if (m_opbtns.contains(index)) {
            QPair<QStyleOptionButton*, QStyleOptionButton*>* btns = m_opbtns.value(index);
            if (btns->first->rect.contains(e->x(), e->y())) {
                btns->first->state |= QStyle::State_Sunken;
            }
            else if(btns->second->rect.contains(e->x(), e->y())) {
                btns->second->state |= QStyle::State_Sunken;
            }
        }
    }
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent* e =(QMouseEvent*)event;
        if (m_opbtns.contains(index)) {
            QPair<QStyleOptionButton*, QStyleOptionButton*>* btns = m_opbtns.value(index);
            if (btns->first->rect.contains(e->x(), e->y())) {
                btns->first->state &= (~QStyle::State_Sunken);
                 //  qDebug()<<"编辑按钮  btn clicked " <<index.row()<<index.column() ;
                   emit signalEditButtonClicked(index.row(),index.column());
            } else if(btns->second->rect.contains(e->x(), e->y())) {
                btns->second->state &= (~QStyle::State_Sunken);
                //  qDebug()<<"删除按钮  btn clicked "<<index.row()<<index.column();
                 emit signalDeleteButtonClicked(index.row(),index.column());
            }
        }
    }
    return true;
}
