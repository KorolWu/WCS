#ifndef CPIEWIDGET_H
#define CPIEWIDGET_H


#include <QPainter>
#include <QRadialGradient>
#include <QHash>
#include <qmath.h>
#include <QtWidgets>
#include <QCheckBox>
enum PieStyle
{
	DefaultPie=0,
	ConcaveShading,
	RadialGradient,
	DountDefault,
	RingShadingDount,
	ConcaveShadingDount
};
enum LegendPost
{
	LeftPost=0,
	RigthPost,
	TopPost,
	BottomPost
};

class CPieWidget : public QWidget
{
	Q_OBJECT

public:
    CPieWidget(int w, int h, QWidget *parent = 0);
	~CPieWidget();

	void setData(QHash<QString,float> datamap);
	void addData(QString title,float value);
	void removeData(QString title);
	void removeAll();
	QHash<QString,float> getDataMap();
	void setColors(QList<QColor> colorlist);
	//////////////////////////////////////////////////////////////////////////
	void setPieStyleSheet(PieStyle piestyle = DefaultPie);
	void setExplodedAll(bool isExploded = true);
    void setExplodedIndex(int index);
    void setCharTitle(QString title);
	

protected:
	void init();
	void drawEllipse(QPainter *painter);
	void drawDefaultPie(QPainter *painter);
	void drawConcaveShading(QPainter *pianter);
	void drawRadialGradient(QPainter *painter);
	void drawDountDefault(QPainter *painter);
	void drawRingShadingDount(QPainter *painter);
	void drawConcaveShadingDount(QPainter *painter);
	void drawExplodedDount(QPainter *painter);

	void drawLegend(QPainter *painter);
    void onCheckClicked();


	void paintEvent(QPaintEvent *e);
private:
	inline qreal getSumValue();
	inline QPoint getMovePoint(qreal angel);

private:
	QHash<QString,float> m_datamap;
	QList<QColor> m_colorlist;
	QList<QColor> m_defaultcolorlist;
	PieStyle m_piestyle;
	bool m_isexploded;
	int m_explodedindex;
    int w;
    int h;
    QCheckBox *m_pcheckbox;
};

#endif // CPIEWIDGET_H
