#include "Tower.h"
#include<QPainter>

const QSize Tower::t_size(150,190);


Tower::Tower(QPoint pos, const QPixmap &sprite):
t_pos(pos),t_sprite(sprite),t_damage(10),t_rate(1000),t_attacjRange(100)
{}

void Tower::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::black);//设置笔：黑色
    painter->drawEllipse(t_pos,t_attacjRange,t_attacjRange);//通过圆心、半径画攻击范围的圆
    //接下来画塔，而t_pos是指塔的图片的中心点，所以说画塔时的坐标要偏移一下
    QPoint pianyi(t_size.width()/2,t_size.height()/2);
    QPoint trueposition=t_pos-pianyi;
    painter->drawPixmap(trueposition,t_sprite);
    painter->restore();

}

//void Tower::shoot(){}



//void Tower::setposition(int x, int y){}



