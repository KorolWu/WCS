#ifndef MONITORVIEW_H
#define MONITORVIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QMouseEvent>

class QWidget;
class MonitorView: public QGraphicsView
{
        Q_OBJECT
public:
    MonitorView(QWidget *parent = 0);
    void Zoom(double _Multiple);
    void SetZoom(double _Zoom);
    double GetZoom() const;
    void SetRotate(int rotate);
    int GetRotate() const;
signals:
    void MousePress(int x, int y);
protected:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    double m_Zoom;
    int m_Rotate;
protected:
//    void enterEvent(QEvent *event);
//    void leaveEvent(QEvent *event);
};

#endif // MONITORVIEW_H
