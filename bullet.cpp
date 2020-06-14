#include "bullet.h"
#include"enemy.h"
#include<QPainter>
#include<QPropertyAnimation>

Bullet::Bullet(QPoint currentPos, QPoint targetPos, int damage, Enemy *enemy, MainWindow *game)
    :b_startPoint(currentPos),
     b_targetPoint(targetPos),
     b_target(enemy),
     b_game(game)
{

}

void Bullet::move()
{
static const int duration=100;
QPropertyAnimation *animation =new QPropertyAnimation(this, "b_currentPosition");
animation->setDuration(duration);
animation->setStartValue((b_startPoint));
animation->setEndValue((b_targetPoint));
connect(animation,SIGNAL(finished()),this,SLOT(hitTarget()));
animation->start();
}

void Bullet::setCurrentPosition(QPoint pos)
{

}

QPoint Bullet::currentPosition()
{

}

void Bullet::draw(QPainter *painter)
{

}

void Bullet::hitTarget()
{
    //先判断敌人是否有效
    if(b_game->enemylist().indexOf(b_target)!= -1)
        b_target->getDamage(b_damage);
   // b_game->
}
