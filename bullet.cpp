#include "bullet.h"
#include"enemy.h"
#include"mainwindow.h"
#include<QPainter>
#include<QPropertyAnimation>

Bullet::Bullet(QPoint startP, QPoint targetP, int damage, Enemy *enemy, MainWindow *game,const QPixmap&sprite)
    :b_startPoint(startP),
     b_targetPoint(targetP),
     b_currentPosition(startP),
     b_sprite(sprite),
     b_target(enemy),
     b_game(game),
     b_damage(damage)
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
 b_currentPosition=pos;
}

QPoint Bullet::currentPosition()
{
   return b_currentPosition;
}

void Bullet::draw(QPainter *painter)
{
    painter->drawPixmap(b_currentPosition,b_sprite);
}

void Bullet::hitTarget()
{
    //先判断敌人是否有效
    if(b_game->enemylist().indexOf(b_target)!= -1)
        b_target->getDamage(b_damage);
     b_game->removeBullet(this);
}

//冰冻类子弹实现
BulletSlowingAttack::BulletSlowingAttack(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
                                     MainWindow *game, const QPixmap &sprite)
    : Bullet(startPos,targetPoint,damage,target,game,sprite)
{}

BulletSlowingAttack::~BulletSlowingAttack()
{}
void BulletSlowingAttack::hitTarget()
{
    // 这样处理的原因是:
    // 可能多个炮弹击中敌人,而其中一个将其消灭,导致敌人delete
    // 后续炮弹再攻击到的敌人就是无效内存区域
    // 因此先判断下敌人是否还有效
    if (b_game->enemylist().indexOf(b_target) != -1)
    {
        b_target->slowDown();     //多了一个slowdown功能，于是这个继承类要重写一遍hittarget
        b_target->getDamage(b_damage);
    }
    b_game->removeBullet(this);
}

//强化类子弹实现
BulletStrongAttack::BulletStrongAttack(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
                                     MainWindow *game, const QPixmap &sprite)
    : Bullet(startPos,targetPoint,damage,target,game,sprite)
{}

BulletStrongAttack::~BulletStrongAttack()
{}

