#ifndef BUTTONDELEGATE_H
#define BUTTONDELEGATE_H

#include <QObject>
#include <QWidget>
#include <QItemDelegate>
class ButtonDelegate :public  QItemDelegate
{
    Q_OBJECT
public:
explicit ButtonDelegate(QObject *parent = 0);
    // QAbstractItemDelegate interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
//    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
//    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    // QAbstractItemDelegate interface
public:
    virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
private:
    typedef QMap<QModelIndex, QPair<QStyleOptionButton*, QStyleOptionButton*>* >  m_opcollButtons;
       m_opcollButtons m_opbtns;
signals:
       void signalEditButtonClicked(int indexrow,int indexcol);
       void signalDeleteButtonClicked(int indexrow,int indexcol);
};

#endif // BUTTONDELEGATE_H
