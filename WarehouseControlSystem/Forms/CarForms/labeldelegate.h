#ifndef LABELDELEGATE_H
#define LABELDELEGATE_H

#include <QObject>
#include <QLabel>
#include <QItemDelegate>
#include <QLineEdit>
#include <QPushButton>
#include <QStyledItemDelegate>

class LabelDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
     LabelDelegate(QObject *parent = nullptr);

    // QAbstractItemDelegate interface
public:
   virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  virtual  void setEditorData(QWidget *editor, const QModelIndex &index) const;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

     // QAbstractItemDelegate interface
public:
     void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // LABELDELEGATE_H
