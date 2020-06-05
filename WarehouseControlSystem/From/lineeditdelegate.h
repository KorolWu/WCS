#ifndef LINEEDITDELEGATE_H
#define LINEEDITDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QSpinBox>
/**
 *
 * @author korol
 * @email wuwenpeng@cowain.com.cn
 * @date 2020-06-01 16:02:59
 * use 用来限制文本输入,只能输入数字
 */
class LineEditDelegate : public QItemDelegate
{
public:
    LineEditDelegate(QWidget *parent);

    // QAbstractItemDelegate interface
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // LINEEDITDELEGATE_H
