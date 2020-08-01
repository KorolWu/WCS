#ifndef WATINGDIALOGWG_H
#define WATINGDIALOGWG_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QMovie>
#include <QTimer>


class WatingDialogWg :public QDialog
{
    Q_OBJECT
public:
    explicit  WatingDialogWg(QWidget *parent = 0);
    ~WatingDialogWg();

private:
    QMovie *m_pmovie;
    QLabel *m_plabel;
    QTimer  *m_pTimer;

public slots:
    void CloseDialag();
};

#endif // WATINGDIALOGWG_H
