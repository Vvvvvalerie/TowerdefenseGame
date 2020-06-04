#ifndef COLLISION_H
#define COLLISION_H
#include<QPoint>
#include<qmath.h>
//判断是否碰撞，会被多次调用所以另写在一个头文件中
inline bool IfCollision(QPoint point1, int radius1, QPoint point2, int radius2)
{
    const int xdist = point1.x() - point2.x();
    const int ydist = point1.y() - point2.y();
    const int distance = qSqrt(xdist*xdist+ydist*ydist);
    if (distance <= radius1+radius2)
        return true;
    return false;
}
//即求两个圆是否相交

#endif // COLLISION_H
