#ifndef RUNERFORM_H
#define RUNERFORM_H

#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFont>
#include "datastructure.h"
class RunerForm : public QWidget
{
    Q_OBJECT
public:
    explicit RunerForm(int width, int height, QWidget *parent = 0);
    void setParameter(RunerStru s);

signals:

public slots:
    void yesBtnClicked();
private:
    QGroupBox *m_pgboxSocketInfo;
    QLineEdit *m_pIp;
    QLineEdit *m_pPort;
    QLineEdit *m_prunerName;
    QGroupBox *m_prunerInfo;
    QLineEdit *m_pinCache;
    QLineEdit *m_poutCache;
    QGroupBox *m_preplyInfo;
    QLineEdit *m_porderIn;
    QLineEdit *m_preplyin;
    QLineEdit *m_porderOut;
    QLineEdit *m_preplyOut;
    QVBoxLayout *m_pvBox;
    QPushButton *m_pYesBtn;
    QPushButton *m_pNoBtn;
    int m_width;
    int m_height;
    void initUi();
};

#endif // RUNERFORM_H
