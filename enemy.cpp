#include "enemy.h"
#include"mainwindow.h"
#include<QObject>
#include<QPainter>
#include<QPoint>
#include"collision.h"
#include<QVector2D>
#include<QtMath>
#include<QMatrix>
Enemy::Enemy(WayPoint *startPoint, MainWindow *game, const QPixmap &sprite):
    QObject(0),
    e_Hpmax(40),
    e_Hpcurrent(40),
    e_walkingspeed(1.0),
    e_active(false),
    e_pos(startPoint->pos()),
    e_sprite(sprite),
    e_destinationWayPoint(startPoint->nextWayPoint()),
    e_game(game),
    e_rotationsprite(0.0),
    e_size(e_sprite.width(),e_sprite.height())


{

}

void Enemy::draw(QPainter *painter)
{
    if(!e_active)
        return;
    //画头顶的血条
    static const int Blood_Bar_Length=80;
    painter->save();
    QPoint BloodBar_Pos=e_pos+QPoint(-Blood_Bar_Length/2 -5,-e_size.height()/2);
    painter->setPen((Qt::NoPen));
    painter->setBrush(Qt::red);
    QRect wholeblodRect(BloodBar_Pos,QSize(Blood_Bar_Length,2));
 //   QRect a(QPoint(20,20),QSize(20,2));
 //   painter->drawRect(a);
    painter->drawRect(wholeblodRect);//一整个条
    painter->setBrush(Qt::green);  //调整颜色
    QRect bloodbarRect(BloodBar_Pos,QSize((double)e_Hpcurrent/e_Hpmax*Blood_Bar_Length,2));
    painter->drawRect(bloodbarRect);   //绘制出了剩余血量的矩形条


    //绘制敌人
    QPoint pianyi(-e_size.width()/2,-e_size.height()/2);//pianyi偏移坐标
    painter->translate(e_pos);  //平移，每次都画在敌人中心坐标的panyi处
  //  painter->rotate((e_rotationsprite));//不用rotate比较好看喔
    painter->drawPixmap(pianyi,e_sprite);
    painter->restore();


}

void Enemy::move()
{
    if(!e_active)
        return;
    if(IfCollision(e_pos,1,e_destinationWayPoint->pos(),1))//敌人已经与航点足够近啦！
 {
    if(e_destinationWayPoint->nextWayPoint())  //下一个航点不为空
    {
        e_pos=e_destinationWayPoint->pos();
        e_destinationWayPoint=e_destinationWayPoint->nextWayPoint();//沿着航线前进了

    }
    else{
        e_game->causeHpLose();// 敌人到达终点，引起减少玩家血量的函数
        e_game->removeEnemy(this);// 敌人达到终点，把敌人移走
        return;
    }
 }
    //还未接近下一个航点，继续前进
    QPoint targetpoint=e_destinationWayPoint->pos();
    double movementSpeed=e_walkingspeed;   //行进路中可以修改速度？？？？弱AI？？？？？
    QVector2D normalized(targetpoint - e_pos);
    normalized.normalize();
    e_pos = e_pos + normalized.toPoint() * movementSpeed;
    e_rotationsprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) + 180;//转换方向
}

void Enemy::getAttacked()
{

}

void Enemy::gotLostSight()
{

}

QPoint Enemy::pos()
{
    return e_pos;
}

void Enemy::getDamage(int damage)
{
    e_Hpcurrent=e_Hpcurrent-damage;

    if(e_Hpcurrent<=0)
    {
        getremoved();
    }
}

void Enemy::getremoved()
{

}

void Enemy::doActive()
{
    e_active=true;
}
