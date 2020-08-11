#ifndef TESTCREATEORDERSPATH_H
#define TESTCREATEORDERSPATH_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <datastructure.h>
#include <QComboBox>

class TestcreateOrdersPath:public QWidget
{
    Q_OBJECT
public:
    TestcreateOrdersPath(QWidget *parent = 0);
    ~TestcreateOrdersPath();
private:
    QTableWidget *m_configTable;
    QTextEdit *m_ordersedit;
    QComboBox *com ;
    QLineEdit *carpos;
    QLineEdit *tpos;

    QLineEdit *m_InsetValue;
    QLineEdit *m_IncurValue;
    QLineEdit *m_OutsetValue;
    QLineEdit *m_OutcurValue;
    QPushButton *m_ptrigger;
public slots:
    void Createorderslot();
    void Cleartextdata();
    void SimulaRunnerBtn();
private:
    QString GetorderNameByValue(Order value);

    void GetSetDataValue( KPosition &task_P, KPosition &carPosion);
    void SetHWConfigData();

};

#endif // TESTCREATEORDERSPATH_H
