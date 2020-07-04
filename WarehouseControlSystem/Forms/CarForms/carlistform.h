#ifndef CARLISTFORM_H
#define CARLISTFORM_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QLine>
#include <datastructure.h>
#include <Myconfig.h>
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
    QWidget *createListWidget(CarInfoStru c);
    int m_width;
    int m_height;


signals:

public slots:
};

#endif // CARLISTFORM_H
