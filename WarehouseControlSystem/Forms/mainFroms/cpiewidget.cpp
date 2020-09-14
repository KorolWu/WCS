#include "cpiewidget.h"
#include <QDebug>

CPieWidget::CPieWidget(int w, int h, QWidget *parent)
	: QWidget(parent)
{
	
    //resize(600,500);
   this->w = w;
    this->h = h;
	init();
}

CPieWidget::~CPieWidget()
{

}
void CPieWidget::setData( QHash<QString,float> datamap )
{
	m_datamap.clear();
	m_datamap = datamap;
}

void CPieWidget::addData( QString title,float value )
{
	m_datamap.insert(title,value);
}

void CPieWidget::removeData( QString title )
{
	m_datamap.remove(title);
}

void CPieWidget::removeAll()
{
	m_datamap.clear();
}


QHash<QString,float> CPieWidget::getDataMap()
{
	return m_datamap;

}

void CPieWidget::setColors( QList<QColor> colorlist )
{
	for (int i = colorlist.count()-1; i > -1; --i)
	{
		m_colorlist.push_front(colorlist.at(i));
	}
}


void CPieWidget::setPieStyleSheet( PieStyle piestyle /*= Default*/ )
{
	m_piestyle = piestyle;
}

void CPieWidget::setExplodedAll( bool isExploded /*= true*/ )
{
	m_isexploded = isExploded;
}

void CPieWidget::setExplodedIndex( int index )
{
	m_explodedindex = index;
}


void CPieWidget::init()
{
	setPieStyleSheet(RingShadingDount);
	m_explodedindex = -1;
	m_isexploded = false;
	
    m_colorlist << QColor(168,209,207);
    //m_colorlist << QColor(238,187,34);
//	m_colorlist << QColor(102,170,238);
//	m_colorlist << QColor(136,68,255);
	m_colorlist << QColor(116,169,26);
	m_colorlist << QColor(201,64,73);
    m_colorlist << QColor(210,151,153);
    m_colorlist << QColor(77,82,175);
    m_colorlist << QColor(158,102,155);
    m_colorlist << QColor(172,126,126);
    m_colorlist << QColor(90,179,86);


    m_datamap.insert("Empty:",3);
    m_datamap.insert("Full:",8);
    m_datamap.insert("Err:",2);


    int interval = w/13;int i = 0;
    for(auto it = m_datamap.begin();it != m_datamap.end();it++)
    {
        QFont font("??",14);
        QLabel *l = new QLabel(this);
        l->setText(it.key());
        l->setFont(font);
        l->move(interval*i,10);
        l->setAttribute(Qt::WA_TranslucentBackground, true);
        i++;
    }
    i = 0;
    QLabel *r = new QLabel(this);
    interval = interval *0.6;
    r->move(interval*(i+1),10);
    i++;
    r->setStyleSheet("background-color: rgb(18, 62, 111);");
    QLabel *g = new QLabel(this);
    g->move(interval*(i+1.7),10);
    i++;
    g->setStyleSheet("background-color: rgb(201,64,73);");
    QLabel *b = new QLabel(this);
    b->move(interval*(i+2.5),10);
    i++;
    b->setStyleSheet("background-color: rgb(90,179,86);");
    interval = w/50;
    r->resize(interval,interval);
    g->resize(interval,interval);
    b->resize(interval,interval);
}


void CPieWidget::paintEvent( QPaintEvent *e )
{
	QPainter *painter = new QPainter(this);
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setRenderHint(QPainter::SmoothPixmapTransform);
	
	drawEllipse(painter);

	
}

void CPieWidget::drawEllipse( QPainter *painter )
{
	switch (m_piestyle)
	{
		case DefaultPie: drawDefaultPie(painter); break;
		case ConcaveShading:drawConcaveShading(painter);break;
		case RadialGradient:drawRadialGradient(painter);break;
		case DountDefault: drawDountDefault(painter);break;
		case RingShadingDount: drawRingShadingDount(painter);break;
		case ConcaveShadingDount: drawConcaveShadingDount(painter);break;
		//case ExplodedDount: drawExplodedDount(painter);break;
        default:drawDefaultPie(painter);break;
	}
}

void CPieWidget::drawDefaultPie( QPainter *painter )
{
	qreal sum = getSumValue();
//	int w = width();
//	int h = height();
	int radius = qMin(w,h)*0.8; //直径
	QRect rect(w/2-radius/2,h/2-radius/2,radius,radius);

	painter->save();
	painter->setPen(Qt::NoPen);
	QHashIterator<QString, float> i(m_datamap);
	
	qreal index = 30;  //启始位置
	int colorindex=0;
	QStringList keylist = m_datamap.keys();
	for (int i = 0; i < keylist.count(); ++i)
	{
		qreal v = m_datamap.value(keylist.at(i));
		v =v/sum*(360);
		QRect newrect = rect;
		if (m_explodedindex == i || m_isexploded)
		{
			QPoint newcenter = newrect.center();
			int midangel = index+v/2;
			QPoint tp = getMovePoint(midangel);
			newcenter += tp;
			newrect.moveCenter(newcenter);
		}

		QPoint centerPoint = newrect.center();
	 	QColor firstColor = m_colorlist.at(colorindex);
	 	QRadialGradient firstGradient(centerPoint, radius/2);
 	 	firstGradient.setColorAt(0, firstColor.lighter(80));
	 	firstGradient.setColorAt(1.0, firstColor.darker(80));
	 	painter->setBrush(firstGradient);
		painter->drawPie(newrect, index * 16, v * 16);
		index+=v;
		colorindex++;
		if (colorindex==m_colorlist.count())
		{
			colorindex = 0;
		}
	}
	painter->restore();
}


void CPieWidget::drawConcaveShading( QPainter *painter )
{
	qreal sum = getSumValue();
//	int w = width();
//	int h = height();
	int radius = qMin(w,h)*0.8; //直径
	QRect rect(w/2-radius/2,h/2-radius/2,radius,radius);

	painter->save();
	painter->setPen(Qt::NoPen);
	QHashIterator<QString, float> i(m_datamap);

	qreal index = 30;  //启始位置
	int colorindex=0;
	QStringList keylist = m_datamap.keys();
	for (int i = 0; i < keylist.count(); ++i)
	{
		qreal v = m_datamap.value(keylist.at(i));
		v =v/sum*(360);
		QRect newrect = rect;
		if (m_explodedindex == i || m_isexploded)
		{
			QPoint newcenter = newrect.center();
			int midangel = index+v/2;
			QPoint tp = getMovePoint(midangel);
			newcenter += tp;
			newrect.moveCenter(newcenter);
		}

		QPoint centerPoint = newrect.center();
		QColor firstColor = m_colorlist.at(colorindex);
		QRadialGradient firstGradient(centerPoint, radius/2);
		firstGradient.setColorAt(0, firstColor.darker(80));
	 	firstGradient.setColorAt(0.90, firstColor.lighter(100));
	 	firstGradient.setColorAt(1.0, firstColor.darker(150));
		painter->setBrush(firstGradient);
		painter->drawPie(newrect, index * 16, v * 16);
		index+=v;
		colorindex++;
		if (colorindex==m_colorlist.count())
		{
			colorindex = 0;
		}
	}
	painter->restore();
}

void CPieWidget::drawRadialGradient( QPainter *painter )
{
	qreal sum = getSumValue();
//	int w = width();
//	int h = height();
	int radius = qMin(w,h)*0.8; //直径
	QRect rect(w/2-radius/2,h/2-radius/2,radius,radius);

	painter->save();
	painter->setPen(Qt::NoPen);
	QHashIterator<QString, float> i(m_datamap);

	qreal index = 30;  //启始位置
	int colorindex=0;
	QStringList keylist = m_datamap.keys();
	for (int i = 0; i < keylist.count(); ++i)
	{
		qreal v = m_datamap.value(keylist.at(i));
		v =v/sum*(360);
		QRect newrect = rect;
		if (m_explodedindex == i || m_isexploded)
		{
			QPoint newcenter = newrect.center();
			int midangel = index+v/2;
			QPoint tp = getMovePoint(midangel);
			newcenter += tp;
			newrect.moveCenter(newcenter);
		}

		QPoint centerPoint = newrect.center();
		QColor firstColor = m_colorlist.at(colorindex);
		QRadialGradient firstGradient(centerPoint, radius/2);
		firstGradient.setColorAt(0, firstColor.lighter(80));
		firstGradient.setColorAt(0.61, firstColor.lighter(90));
		firstGradient.setColorAt(0.80, firstColor.lighter(100));
		firstGradient.setColorAt(1.0, firstColor.darker(150));
		painter->setBrush(firstGradient);
		painter->drawPie(newrect, index * 16, v * 16);
		index+=v;
		colorindex++;
		if (colorindex==m_colorlist.count())
		{
			colorindex = 0;
		}
	}
	painter->restore();
}

void CPieWidget::drawDountDefault( QPainter *painter )
{
	qreal sum = getSumValue();
//	int w = width();
//	int h = height();
	int radius = qMin(w,h)*0.8; //直径
	QRect rect(w/2-radius/2,h/2-radius/2,radius,radius);

	painter->save();
	painter->setPen(Qt::NoPen);
	QHashIterator<QString, float> i(m_datamap);

	qreal index = 30;  //启始位置
	int colorindex=0;
	QStringList keylist = m_datamap.keys();
	for (int i = 0; i < keylist.count(); ++i)
	{
		qreal v = m_datamap.value(keylist.at(i));
		v =v/sum*(360);
		QRect newrect = rect;
		if (m_explodedindex == i || m_isexploded)
		{
			QPoint newcenter = newrect.center();
			int midangel = index+v/2;
			QPoint tp = getMovePoint(midangel);
			newcenter += tp;
			newrect.moveCenter(newcenter);
		}
		QPoint centerPoint = newrect.center();
		QColor firstColor = m_colorlist.at(colorindex);
		QRadialGradient firstGradient(centerPoint, radius/2);
		firstGradient.setColorAt(0, Qt::transparent);
		firstGradient.setColorAt(0.6, Qt::transparent);
		firstGradient.setColorAt(0.61, firstColor.lighter(100));
		firstGradient.setColorAt(0.80, firstColor.lighter(100));
		firstGradient.setColorAt(1.0, firstColor.lighter(100));
		painter->setBrush(firstGradient);
		painter->drawPie(newrect, index * 16, v * 16);
		index+=v;
		colorindex++;
		if (colorindex==m_colorlist.count())
		{
			colorindex = 0;
		}
	}
	painter->restore();
}

void CPieWidget::drawRingShadingDount( QPainter *painter )
{
	qreal sum = getSumValue();
//	int w = width();
//	int h = height();
	int radius = qMin(w,h)*0.8; //直径
	QRect rect(w/2-radius/2,h/2-radius/2,radius,radius);

	painter->save();
	painter->setPen(Qt::NoPen);
	QHashIterator<QString, float> i(m_datamap);

	qreal index = 30;  //启始位置
	int colorindex=0;
	QStringList keylist = m_datamap.keys();
	for (int i = 0; i < keylist.count(); ++i)
	{
		qreal v = m_datamap.value(keylist.at(i));
		v =v/sum*(360);
		QRect newrect = rect;
		if (m_explodedindex == i || m_isexploded)
		{
			QPoint newcenter = newrect.center();
			int midangel = index+v/2;
			QPoint tp = getMovePoint(midangel);
			newcenter += tp;
			newrect.moveCenter(newcenter);
		}
		QPoint centerPoint = newrect.center();
		QColor firstColor = m_colorlist.at(colorindex);
		QRadialGradient firstGradient(centerPoint, radius/2);
		firstGradient.setColorAt(0, Qt::transparent);
		firstGradient.setColorAt(0.6, Qt::transparent);
		firstGradient.setColorAt(0.61, firstColor.dark(150));
		firstGradient.setColorAt(0.80, firstColor.lighter(100));
		firstGradient.setColorAt(1.0, firstColor.dark(150));
		painter->setBrush(firstGradient);
		painter->drawPie(newrect, index * 16, v * 16);
		index+=v;
		colorindex++;
		if (colorindex==m_colorlist.count())
		{
			colorindex = 0;
		}
	}
	painter->restore();
}

void CPieWidget::drawConcaveShadingDount( QPainter *painter )
{
	qreal sum = getSumValue();
//	int w = width();
//	int h = height();
	int radius = qMin(w,h)*0.8; //直径
	QRect rect(w/2-radius/2,h/2-radius/2,radius,radius);

	painter->save();
	painter->setPen(Qt::NoPen);
	QHashIterator<QString, float> i(m_datamap);

	qreal index = 30;  //启始位置
	int colorindex=0;
	QStringList keylist = m_datamap.keys();
	for (int i = 0; i < keylist.count(); ++i)
	{
		qreal v = m_datamap.value(keylist.at(i));
		v =v/sum*(360);
		QRect newrect = rect;
		if (m_explodedindex == i || m_isexploded)
		{
			QPoint newcenter = newrect.center();
			int midangel = index+v/2;
			QPoint tp = getMovePoint(midangel);
			newcenter += tp;
			newrect.moveCenter(newcenter);
		}
		QPoint centerPoint = newrect.center();
		QColor firstColor = m_colorlist.at(colorindex);
		QRadialGradient firstGradient(centerPoint, radius/2);
		firstGradient.setColorAt(0, Qt::transparent);
		firstGradient.setColorAt(0.6, Qt::transparent);
		firstGradient.setColorAt(0.61, firstColor.dark(100));
		firstGradient.setColorAt(0.90, firstColor.lighter(100));
		firstGradient.setColorAt(1.0, firstColor.dark(180));
		painter->setBrush(firstGradient);
		painter->drawPie(newrect, index * 16, v * 16);
		index+=v;
		colorindex++;
		if (colorindex==m_colorlist.count())
		{
			colorindex = 0;
		}
	}
	painter->restore();
}

void CPieWidget::drawExplodedDount( QPainter *painter )
{
	qreal sum = getSumValue();
//	int w = width();
//	int h = height();
	int radius = qMin(w,h)*0.8; //直径
	QRect rect(w/2-radius/2,h/2-radius/2,radius,radius);

	painter->save();
	painter->setPen(Qt::NoPen);
	QHashIterator<QString, float> i(m_datamap);
	
	qreal index = 30;  //启始位置
	int colorindex = 0;

	QStringList keylist = m_datamap.keys();
	for (int i = 0; i < keylist.count(); ++i)
	{
		qreal v = m_datamap.value(keylist.at(i));
		v =v/sum*(360);
		QRect newrect = rect;
		if (m_explodedindex == i || m_isexploded)
		{
			QPoint newcenter = newrect.center();
			int midangel = index+v/2;
			QPoint tp = getMovePoint(midangel);
			newcenter += tp;
			newrect.moveCenter(newcenter);
		}

		QPoint centerPoint = newrect.center();
		QColor firstColor = m_colorlist.at(colorindex);
		QRadialGradient firstGradient(centerPoint, radius/2);
		firstGradient.setColorAt(0, Qt::transparent);
		firstGradient.setColorAt(0.6, Qt::transparent);
		firstGradient.setColorAt(0.61, firstColor.dark(150));
		firstGradient.setColorAt(0.80, firstColor.lighter(100));
		firstGradient.setColorAt(1.0, firstColor.dark(150));
		painter->setBrush(firstGradient);
		painter->drawPie(newrect, index * 16, v * 16);
		index+=v;		
		colorindex++;
		if (colorindex==m_colorlist.count())
		{
			colorindex = 0;
		}
	}

	painter->restore();
}

qreal CPieWidget::getSumValue()
{
	qreal sum = 0;
	QHashIterator<QString, float> i(m_datamap);
	while (i.hasNext()) {
		i.next();
		sum+= i.value();
	}
	if (sum == 0.0)
		sum = 1;
	return sum;
}

QPoint CPieWidget::getMovePoint( qreal angel )
{
	int wl = 0;
	int hl = 0;
	qreal ang = (angel)*3.14/180;
	wl = 20*qCos(ang);
	hl = 20*qSin(ang);

	if (angel > 90 && angel < 270)
		wl = qAbs(wl)*-1;
	else
		wl = qAbs(wl);

	if (angel < 180)
		hl = qAbs(hl)*-1;
	else
		hl = qAbs(hl);

	return QPoint(wl,hl);
}







