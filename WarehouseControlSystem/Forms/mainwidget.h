#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
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
    QPushButton *m_ptest;
    QWidget     *m_pmain;
    void initUI();

public slots:
};

#endif // MAINWIDGET_H
