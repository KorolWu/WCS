#ifndef CARLISTFORM_H
#define CARLISTFORM_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QLine>
#include <datastructure.h>
#include <Myconfig.h>
#include <QPoint>
#include <QMouseEvent>
#include <QPointer>
#include <QRect>
#include <QApplication>
#include "CarStatusFrom.h"
/**
 * @brief The CarListForm class
 * show list of car
 */
class CarListForm : public QWidget
{
    Q_OBJECT
public:
    explicit CarListForm(int width,int height,QWidget *parent = 0);
    void initUi();

private:
    QWidget *m_pMainWidget;
    QLabel *m_pHeadLabel;
    QLabel *m_pInfoLabel;
    QVector<QLabel *> m_InfoVec;
    int m_width;
    int m_height;
    bool m_pressflag;
    QPoint m_beginP;
    QPoint m_windowP;
signals:

public slots:

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};
class CarStatusWidget : public QWidget
{
public:
    CarStatusWidget(int width, CarInfoStru c, QWidget *parent =0);
private:
    CarInfoStru m_car;
    CarStatusFrom *m_pCar;
    //QPointer<QWidget> m_pParent;

    // QWidget interface
protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
};
#endif // CARLISTFORM_H
