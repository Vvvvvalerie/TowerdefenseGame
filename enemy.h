#ifndef ENEMY_H
#define ENEMY_H
#include<QPoint>
#include<QPixmap>
#include<QPainter>
#include<QObject>
#include<QList>
#include"waypoint.h"
#include"mainwindow.h"
#include"tower.h"
class MainWindow;
class Tower;
//普通敌人
class Enemy:public QObject
{
    Q_OBJECT
public:
    Enemy(WayPoint *startPoint, MainWindow *game,int level=1,const QPixmap &sprite=QPixmap(":/new/prefix1/res/enemy1.png"));
    virtual void draw(QPainter *painter);
    virtual void move();
    virtual void getAttacked(Tower *attacker);
    virtual void gotLostSight(Tower *attacker);

    virtual void getDamage(int damage);
    virtual void getremoved();
    virtual void slowDown();
    virtual void setLevel(int level);
    QPoint pos();
    ~Enemy();
protected:
    int e_Hpmax;
    int e_Hpcurrent;
    int e_level;
    double e_walkingspeed;
    double e_rotationsprite;
    bool e_active;
    bool e_isSlowed;
    QPoint e_pos;
    QPixmap e_sprite;
    WayPoint *e_destinationWayPoint;
    MainWindow* e_game;

    QSize e_size;
    QList<Tower*> e_attackedTowerList;
public slots:
    void doActive();


};
//受伤后加速的enemy
class Enemy2 : public Enemy
{
   Q_OBJECT//所有应用QT槽的类都需要声明
public:
    Enemy2(WayPoint *startPoint, MainWindow *game,int level=1,const QPixmap &sprite=QPixmap(":/new/prefix1/res/enemy2（active）.gif"));
    ~Enemy2();
    void getDamage(int damage);//受伤后有加速效果
    bool m_speedUp;//判断是否已经加速
};

//耐打怪：每份伤害减半
/*class EnemyStrong : public Enemy
{
    Q_OBJECT//所有应用QT槽的类都需要声明
public:
    EnemySttong(WayPoint *startPoint, MainWindow *game,int level=1,const QPixmap &sprite=QPixmap(":/new/prefix1/res/enemy2（active）.gif"));
    ~EnemyStrong();
    void SpecialgetDamage(int damage);//每次伤害减半
*/
class Enemy3 : public Enemy
{
  Q_OBJECT//所有应用QT槽的类都需要声明
public:
    Enemy3(WayPoint *startPoint, MainWindow *game,int level=1,const QPixmap &sprite=QPixmap(":/new/prefix1/res/enemy3 (2).png"));
    ~Enemy3();
    void getDamage(int damage);//受伤后有加速效果
    //bool m_speedUp;//判断是否已经加速
};

#endif // ENEMY_H
