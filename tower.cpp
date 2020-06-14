#include "Tower.h"
#include<QPainter>
#include<QTimer>
#include"bullet.h"
#include"mainwindow.h"
#include"enemy.h"
const QSize Tower::t_size(150,190);


Tower::Tower(QPoint pos,MainWindow* game, const QPixmap &sprite):
t_pos(pos),t_sprite(sprite),t_damage(10),t_rate(1000),
t_attacjRange(100),t_chosenEnemy(NULL),t_game(game)
{
    t_rateTimer=new QTimer(this);
    connect(t_rateTimer,SIGNAL(timeout()),this,SLOT(shootWeapoon())); //随时间变化打炮，还需设置频率
}

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

void Tower::targetKilled()
{
    if(t_chosenEnemy)
        t_chosenEnemy=NULL;
    t_rateTimer->stop();
    //没有 ratation
}

void Tower::attackEnemy()
{
    //承接构造函数中的connect函数而来，设定了打炮的频率
    t_rateTimer->start(t_rate);
}

void Tower::chooseOnetoAttack(Enemy *enemy)
{
    t_chosenEnemy=enemy;//找到了敌人
    attackEnemy();//开始攻击
    t_chosenEnemy->getAttacked();


}

void Tower::LostSight()
{
    t_chosenEnemy->gotLostSight();
    if(t_chosenEnemy)
        t_chosenEnemy=NULL;
    t_rateTimer->stop();
    //没有rotation
}

void Tower::shootWeapoon()
{
    Bullet* bullet=new Bullet(t_pos,t_chosenEnemy->pos(),t_damage,t_chosenEnemy,t_game);
    bullet->move();
    t_game->addBullet(bullet);

}

//void Tower::shoot(){}



//void Tower::setposition(int x, int y){}



