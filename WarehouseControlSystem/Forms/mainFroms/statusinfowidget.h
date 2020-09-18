#ifndef STATUSINFOWIDGET_H
#define STATUSINFOWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QTimer>
#include <QDateTime>
#include "Myconfig.h"
class StatusInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StatusInfoWidget(int width, int height, QWidget *parent = 0);
    void appendLog(QString &str);

signals:

public slots:
private:
    void init();
    int m_width;
    int m_height;
    void changeStatus();
    QWidget *m_mainWidget;
    QHBoxLayout *m_hbox;
    QVBoxLayout *m_vbox;
    QLabel *m_wmsLabel;
    QLabel *m_elevatorLabel;
    QLabel *m_runner;
    QLabel *m_agvLabel;
    QLabel *m_mysqlLabel;
    QTimer *m_timer;

    QTextEdit *m_textEdit;
};

#endif // STATUSINFOWIDGET_H
