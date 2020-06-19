#ifndef LABELDELEGATE_H
#define LABELDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QLabel>
#include <QItemDelegate>
#include <QLineEdit>
#include <QPushButton>
class LabelDelegateV1 : public QStyledItemDelegate
{
public:
    LabelDelegateV1();

    // QAbstractItemDelegate interface
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // LABELDELEGATE_H
