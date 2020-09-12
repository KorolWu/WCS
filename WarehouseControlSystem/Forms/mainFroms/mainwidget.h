#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include "cpiewidget.h"
/**
 * @brief The MainWidget class
 * show main info widget
 */
class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(int width, int height, QWidget *parent = 0);

signals:
private:
    int m_width;
    int m_height;
    QGridLayout *m_pgridlayout;
    QPushButton *m_ptest;
    QWidget     *m_pmain;
    CPieWidget  *m_piew;
    void initUI();

public slots:
};

#endif // MAINWIDGET_H
