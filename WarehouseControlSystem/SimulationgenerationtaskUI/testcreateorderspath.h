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

class TestcreateOrdersPath:public QWidget
{
    Q_OBJECT
public:
    TestcreateOrdersPath(QWidget *parent = 0);
    ~TestcreateOrdersPath();
private:
    QTableWidget *m_configTable;
    QTextEdit *m_ordersedit;
public slots:
    void Createorderslot();
    void Cleartextdata();

};

#endif // TESTCREATEORDERSPATH_H
