#include "waypoint.h"
#include<QPainter>
#include<QPoint>
#include<QColor>
#include<QPen>

WayPoint::WayPoint(QPoint pos):
    wp_pos(pos),wp_next(NULL)  //构造函数中下一个点设为null
{

}

void WayPoint::setNext(WayPoint *nextpoint)
{
    wp_next=nextpoint;
}

WayPoint* WayPoint::nextWayPoint() const
{
    return wp_next;
}

const QPoint WayPoint::pos() const
{
    return wp_pos;
}

void WayPoint::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(QColor(28, 134, 238));  //挑选了一个喜欢的颜色的rgb嘿嘿
   // painter.setPen(QPen(Qt::red, 2);
    painter->drawEllipse(wp_pos,6,6);
    painter->drawEllipse(wp_pos,2,2);//画个同心圆

    if(wp_next){
        painter->drawLine(wp_pos,wp_next->wp_pos);
    }
    painter->restore();
}

