#include "warehouseprofileinfoshowwg.h"

WarehouseprofileInfoShowWg::WarehouseprofileInfoShowWg(int w, int h, QWidget *parent): QWidget(parent)
{
    this->resize(w,h);


}

void WarehouseprofileInfoShowWg::paintEvent(QPaintEvent *e)
{
    //绘制边框
    QPainter painter(this);
    painter.setPen(QColor(139, 139, 139));
    painter.drawLine(0, 0, this->width() - 1, 0);
    painter.drawLine(0, 0, 0, this->height() - 1);
    painter.drawLine(this->width()-1 , 0, this->width() - 1, this->height()-1 );
    painter.drawLine(0, this->height()-1 , this->width() - 1, this->height()-1 );
    painter.setBrush(Qt::white);
    painter.drawRect(0,0,this->width() - 1,this->height()-1);
    //绘制标题文字
    painter.setPen(QColor(0, 70, 200));
    QFont font;
    font.setFamily("Microsoft YaHei");
    // 大小
    font.setPointSize(16);
    // 斜体
    // font.setItalic(true);
    // 设置下划线
    font.setUnderline(true);
    // 设置上划线
    // font.setOverline(true);
    // 设置字母大小写
    font.setCapitalization(QFont::SmallCaps);
    // 设置字符间距
    font.setLetterSpacing(QFont::AbsoluteSpacing, 5);
    //使用字体
    painter.setFont(font);
    //绘制区域从x坐标100，y坐标100处开始
    painter.drawText(20, 30, QStringLiteral(">>仓库概览信息"));
    //绘制库位配置数据显示
    font.setPointSize(12);
    font.setUnderline(false);
    painter.setPen(QColor(80, 80, 80,200));
    font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
    painter.setFont(font);
    painter.drawText(this->width()/4+10, this->height()/5 , QStringLiteral("总库位"));
    painter.drawText(this->width()/4, this->height()/5*2 , QStringLiteral("仓库地点"));
    painter.drawText(this->width()/4, this->height()/5*3 , QStringLiteral("仓库类型"));
    painter.drawText(this->width()/4,  this->height()/5*4 , QStringLiteral("仓库状态"));
    //仓位配置数据的显示
     painter.setPen(QColor(0, 40, 90));
    font.setPointSize(28);
     painter.setFont(font);
      painter.drawText(this->width()*2/3,  this->height()/5 , QStringLiteral("13490"));

}
