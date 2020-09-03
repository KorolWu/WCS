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
#include <QTimer>
#include <QSpinBox>
#include "datastructure.h"
#include "MysqlDataBase/crudbaseoperation.h"
#include "../../ControlClass/Instructions/abstructinstruction.h"
#include "../../ControlClass/Instructions/carelevatorinstruction.h"
class RunerForm : public QWidget
{
    Q_OBJECT
public:
    explicit RunerForm(int width, int height, QWidget *parent = 0);
    void setParameter(RunerStru s);

signals:

public slots:
    void yesBtnClicked();
    void updateUI();
    void onClicked();
private:
    QGroupBox *m_pgboxSocketInfo;
    QLineEdit *m_pIp;
    QSpinBox *m_pPort;
    QSpinBox *m_prunerName;
    QSpinBox *m_pvalue;
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
    QLabel *m_pickupImage;
    QLabel *m_putupImage;
    QLabel *m_pscanImage1;
    QLabel *m_pscanImage2;
    QLabel *m_pbackupImage;
    QTimer *m_timer;
    QSpinBox *m_paddress;
    QPushButton *m_psendBtn;
    QPushButton *m_pStartBtn;
    void initUi();
};

#endif // RUNERFORM_H
