#include "tower.h"
#include<QPainter>
#include<QTimer>
#include"bullet.h"
#include"mainwindow.h"
#include"enemy.h"
#include"collision.h"
#include<QList>


Tower::Tower(QPoint pos,MainWindow* game, const QPixmap &sprite):
m_attacking(false),t_pos(pos),t_sprite(sprite),t_damage(10),t_rate(1000),
t_attackRange(100),t_chosenEnemy(NULL),t_game(game)
{
    m_towerType=1;
    t_rateTimer=new QTimer(this);
    connect(t_rateTimer,SIGNAL(timeout()),this,SLOT(shootWeapon())); //随时间变化打炮，还需设置频率
    t_size=QSize(t_sprite.width(),t_sprite.height());
}
Tower::~Tower()
{
    delete t_rateTimer;
    t_rateTimer= NULL;
}
void Tower::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::black);//设置笔：黑色
    painter->drawEllipse(t_pos,t_attackRange,t_attackRange);//通过圆心、半径画攻击范围的圆
    //接下来画塔，而t_pos是指塔的图片的中心点，所以说画塔时的坐标要偏移一下
    QPoint pianyi(t_size.width()/2,t_size.height());
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
    t_chosenEnemy->getAttacked(this);


}

void Tower::checkEnemyinRange()
{
    if(t_chosenEnemy)
    {
        if(!IfCollision(t_pos,t_attackRange,t_chosenEnemy->pos(),1))
            LostSight();
    }
    else{
        QList<Enemy *>enemylist=t_game->enemylist();
        foreach (Enemy *enemy,enemylist)
        {
            if(IfCollision(t_pos,t_attackRange,enemy->pos(),1))
            {
                chooseOnetoAttack(enemy);
                break;
            }
        }
    }
}

void Tower::setTowerLevel(int level)
{
    m_towerLevel=level;
    if(level==1)
    {
        m_towerType=1;
        t_attackRange=100;
        t_damage=10;
        t_rate=1000;
    }
    if(level==2)
    {
        t_attackRange=120;
        t_damage=12;
        t_rate=800;
    }

}

int Tower::getTowerLevel()
{
    return m_towerLevel;
}

QPoint Tower::getPosition()
{
    return t_pos;
}

void Tower::removebullet()
{

}

void Tower::damageEnemy()
{

}

void Tower::LostSight()
{
    t_chosenEnemy->gotLostSight(this);
    if(t_chosenEnemy)
        t_chosenEnemy=NULL;
    t_rateTimer->stop();
    //没有rotation
}

int Tower::getTowerType()
{
    return m_towerType;
}

void Tower::shootWeapon()
{
    Bullet* bullet=new Bullet(t_pos,t_chosenEnemy->pos(),t_damage,t_chosenEnemy,t_game);
    bullet->move();
    t_game->addBullet(bullet);

}

//升级塔实现
Tower2::Tower2(QPoint pos, MainWindow *game, const QPixmap &sprite/* = QPixmap(":/image/tower.png"*/)
    : Tower(pos,game,sprite)
{
    t_attackRange=120;
    t_damage=12;
    t_rate=800;
    t_rateTimer = new QTimer(this);
    connect(t_rateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

Tower2::~Tower2()
{
    delete t_rateTimer;
    t_rateTimer = NULL;
}

//冰冻塔实现
TowerSlowingAttack::TowerSlowingAttack(QPoint pos, MainWindow *game, const QPixmap &sprite)
    : Tower(pos,game,sprite)
{
    m_towerType=2;//第二种塔
    t_attackRange=100;
    t_damage=5;
    t_rate=1000;
    t_rateTimer = new QTimer(this);
    connect(t_rateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

TowerSlowingAttack::~TowerSlowingAttack()
{
    delete t_rateTimer;
    t_rateTimer = NULL;
}

void TowerSlowingAttack::shootWeapon()
{
    Bullet* bullet=new BulletSlowingAttack(t_pos,t_chosenEnemy->pos(),t_damage,t_chosenEnemy,t_game);
    bullet->move();
    t_game->addBullet(bullet);
}

//强力塔实现
TowerStrongAttack::TowerStrongAttack(QPoint pos, MainWindow *game, const QPixmap &sprite)
    : Tower(pos,game,sprite)
{
    m_towerType=3;//第三种塔
    t_attackRange=100;
    t_damage=25;
    t_rate=2000;
    t_rateTimer = new QTimer(this);
    connect(t_rateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

TowerStrongAttack::~TowerStrongAttack()
{
    delete t_rateTimer;
    t_rateTimer = NULL;
}

void TowerStrongAttack::shootWeapon()
{
    Bullet* bullet=new BulletStrongAttack(t_pos,t_chosenEnemy->pos(),t_damage,t_chosenEnemy,t_game);
    bullet->move();
    t_game->addBullet(bullet);
}
//void Tower::shoot(){}



//void Tower::setposition(int x, int y){}



