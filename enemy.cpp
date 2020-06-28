#include "enemy.h"
#include"mainwindow.h"
#include"audioplayer.h"
#include<QObject>
#include<QPainter>
#include<QPoint>
#include"collision.h"
#include<QVector2D>
#include<QtMath>
#include<QMatrix>
Enemy::Enemy(WayPoint *startPoint, MainWindow *game, int level, const QPixmap &sprite):
    QObject(0),
    e_Hpmax(40),
    e_Hpcurrent(40),
    e_level(level),
    e_walkingspeed(2.0),
    e_active(false),
    e_isSlowed(false),
    e_pos(startPoint->pos()),
    e_sprite(sprite),
    e_destinationWayPoint(startPoint->nextWayPoint()),
    e_game(game),
    e_rotationsprite(0.0),
    e_size(e_sprite.width(),e_sprite.height())


{
    setLevel(e_level);
}
Enemy::~Enemy()
{
    e_attackedTowerList.clear();
    e_destinationWayPoint=NULL;
    e_game=NULL;
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
        e_game->getHpLose();// 敌人到达终点，引起减少玩家血量的函数
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

void Enemy::getAttacked(Tower *attacker)
{
 e_attackedTowerList.push_back(attacker);
}

void Enemy::gotLostSight(Tower *attacker)
{
    e_attackedTowerList.removeOne(attacker);
}

QPoint Enemy::pos()
{
    return e_pos;
}



void Enemy::getDamage(int damage)
{
    // e_game->audioplayer()->playSound(EnemyDestorySound);
    e_game->audioplayer()->playSound(LaserShootSound);
    e_Hpcurrent=e_Hpcurrent-damage;

    if(e_Hpcurrent<=0)
    {
        e_game->audioplayer()->playSound(EnemyDestorySound);
        e_game->awardGold(200);// 得到奖励
        getremoved();
    }
}

void Enemy::getremoved()
{
    if(e_attackedTowerList.empty())
        return;
    foreach (Tower* attacker,e_attackedTowerList)
        attacker->targetKilled();//通知每一个正在攻击这个敌人的塔，目标清除
    e_game->removeEnemy(this);
}

void Enemy::slowDown()
{
    if(!e_isSlowed)
    {
        e_walkingspeed=1;
        e_isSlowed=true;
    }
    else return;
}

void Enemy::setLevel(int level)
{
    e_level=level;
    e_Hpmax=35+5*level; //level=1:HP=40,随level上升血量增加
    e_Hpcurrent=e_Hpmax;
}

void Enemy::doActive()
{
    e_active=true;
}
//Enemy2


Enemy2::Enemy2(WayPoint *startPoint, MainWindow *game, int level, const QPixmap &sprite):
    Enemy(startPoint,game,level,sprite)

{
    m_speedUp=false;
}

Enemy2::~Enemy2()
{
    e_attackedTowerList.clear();
    e_destinationWayPoint=NULL;
    e_game=NULL;
}


void Enemy2::getDamage(int damage)
{
    Enemy::getDamage(damage);//首先像普通敌人一样正常受伤
    if(!m_speedUp){  //只能加一次速
        m_speedUp=true;
        e_walkingspeed=2+e_walkingspeed; //受伤后加速
    }
}
//EnemyStrong
/*EnemyStrong::EnemyStrong(WayPoint *startPoint, MainWindow *game, int level, const QPixmap &sprite):
    Enemy(startPoint,game,level,sprite)
{
}

EnemyStrong::~EnemyStrong()
{
    e_attackedTowerList.clear();
    e_destinationWayPoint=NULL;
    e_game=NULL;
}

void EnemyStrong::SpecialgetDamage(int damage)
{
    Enemy::getDamage(damage/2);
}*/
Enemy3::Enemy3(WayPoint *startPoint, MainWindow *game, int level, const QPixmap &sprite):
    Enemy(startPoint,game,level,sprite)

{
   // m_speedUp=false;
}

Enemy3::~Enemy3()
{
    e_attackedTowerList.clear();
    e_destinationWayPoint=NULL;
    e_game=NULL;
}


void Enemy3::getDamage(int damage)
{
    Enemy::getDamage(damage/2);//首先像普通敌人一样正常受伤

}
