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
#include <QTimer>
#include <QList>
#include "ControlClass/observerbase.h"
#include "ControlClass/basedevice.h"
#include "KDeviceSingleton.h"
/**
 * @brief The CarListForm class
 * show list of car
 */
class CarStatusWidget : public QWidget,ObserverBase
{
public:
    CarStatusWidget(int width, CarInfoStru c,BaseDevice *o, QWidget *parent =0);
private:
    CarStatusFrom *m_pCar;
    CarInfoStru m_car;
    QString m_ip;
    QLabel *numLab;
    QLabel *staLab;
    QLabel *taskLab;
    QLabel *workLab;
    QLabel *beterLab;
    // QWidget interface
protected:
    void mouseDoubleClickEvent(QMouseEvent *event);

    // ObserverBase interface
public:
    void updateStatusOnBase();
};
class CarListForm : public QWidget
{
    Q_OBJECT
public:
    explicit CarListForm(int width,int height,QWidget *parent = 0);
    void initUi();
    void updateUI();

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
    QTimer *m_pTimer;
    void initStatusForms();
   QList<CarStatusWidget *> list;
signals:
    void updateList();
public slots:

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);



};
#endif // CARLISTFORM_H
