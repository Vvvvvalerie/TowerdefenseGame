#ifndef WAYPOINT_H
#define WAYPOINT_H
#include<QPoint>
#include<QPainter>

class WayPoint
{
public:
    WayPoint(QPoint pos) ;
    void setNext(WayPoint *nextpoint);
    WayPoint* nextWayPoint() const;
    const QPoint pos() const;
    void draw(QPainter *painter) const;
private:
    QPoint wp_pos;
    WayPoint *wp_next;
};

#endif // WAYPOINT_H
