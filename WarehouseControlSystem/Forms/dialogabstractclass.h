#ifndef DIALOGABSTRACTCLASS_H
#define DIALOGABSTRACTCLASS_H

#include <QObject>
#include <QWidget>
#include <QStringList>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QApplication>
#include <QDesktopWidget>
#include <QIcon>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QList>
#include <QDebug>

/**
 * @author korol
 * @email wuwenpeng@cowain.com.cn
 * @date 2020-06-01 16:02:59
 * use 对话弹窗的基类
 */
class DialogAbstractClass : public QWidget
{
    Q_OBJECT
public:
    explicit DialogAbstractClass(const QStringList &widget_name_list,QWidget *parent = 0);
    //explicit DialogAbstractClass(const QStringList &widget_name_list,const QStringList &value_list,QWidget *parent = 0);
    QStringList getContent();
    void setContent(const QStringList &list);
    QStringList m_list;
    //yes_btn info for user
    QLabel *m_err_lab;

signals:

public slots:
private:
    void CreatUi();
    QWidget *w;
    QList<QLineEdit*> m_edit_list;
    QLabel *m_info_lab;
    QHBoxLayout *m_hbox;
    QVBoxLayout *m_vbox;
    QPushButton *m_yesbtn;
    QPushButton *m_cleanbtn;
public:
    virtual void onYesBtnClicked();
    virtual void onCleanBtnClicked();
};

#endif // DIALOGABSTRACTCLASS_H
