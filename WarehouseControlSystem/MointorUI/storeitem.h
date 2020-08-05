#ifndef STOREITEM_H
#define STOREITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPen>
#include <QFont>
#include <QTextBlockFormat>
#include <QTextCursor>
#include<QStyleOptionGraphicsItem>
#include <QPainter>
#include <QTimer>

class StoreItem: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    StoreItem(double StartX = 0, double StartY = 0, double StopX = 0, double StopY = 0,
              const Qt::PenStyle &LineStyle = Qt::SolidLine, const int LineWidth = 1,
              const QColor &LineColor = Qt::white, const QColor &BackColor = Qt::black);
    ~StoreItem();
    void AddTextItem(QString text);
    void SetText(QString text);
    void SetStoreSate(char state);
    void SetIndexID(QString ID);
    QString GetIndexID();
    QString GetText();
    char GetState();
private:
    QString m_ID;
    double m_StartX;
    double m_StartY;
    double m_StopX;
    double m_StopY;
    QColor m_BackGroundColor;
    QColor m_FontColor;
    //    QColor m_LineColor;
    //   Qt::PenStyle  m_LineStyle;
    int m_LineWidth;
    QString m_text;
    char m_state;
    QGraphicsTextItem *textItem;
    QPen p;
    QFont m_font;
    QTimer *m_Timer;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
private slots:
    void  UpdateState();
    //添加阴影
    //    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    //    shadow_effect->setOffset(0, 0);  //阴影偏移
    //    shadow_effect->setColor(Qt::black); //隐隐颜色
    //    shadow_effect->setBlurRadius(20); //阴影半径
    //    item->setGraphicsEffect(shadow_effect); //给item设置阴影
    //    item->setGraphicsEffect(NULL); //去除item设置阴影
private:
    QColor GetNewColor(const QColor &Source, int Value);
//protected:
    //    bool event(QEvent *event);
    // QGraphicsItem interface
//protected:
    //    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    //    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

#endif // STOREITEM_H
