#ifndef DISPATCHWIDGET_H
#define DISPATCHWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include "Myconfig.h"
#include <QDateTime>

class DispatchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DispatchWidget(int width,int height,QWidget *parent = 0);

signals:

public slots:
    void onBoxClicked();
    void onGetBoxClicked();
    void onScanCode();
private:
    void initUI();
    int m_width;
    int m_height;
    void initRightW();
    QWidget *m_prightW;
    QPushButton* m_box_list[8];
    QPushButton *m_pScan_1;
    QPushButton *m_pScan_2;
    QVBoxLayout *m_pvbox_rightw;
    QWidget *m_poutWidget;
    QPushButton *m_poutButton;
    QLineEdit *m_plineBoxNum;
    QLineEdit *m_plineCacheIn;
    QLineEdit *m_plineCacheOut;
    QTextEdit *m_ptextLine_log;
    void appendInfo(QString str);
};

#endif // DISPATCHWIDGET_H
