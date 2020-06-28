#ifndef BULLET_H
#define BULLET_H
#include<QPoint>
#include<QPixmap>
#include<QObject>
#include<QPainter>
#include"enemy.h"
//#include
class MainWindow;
class Enemy;
class Bullet:public QObject
{
    Q_OBJECT
   Q_PROPERTY(QPoint b_currentPosition READ currentPosition WRITE setCurrentPosition)


public:
    Bullet(QPoint startP,QPoint targetP,int damage,Enemy* enemy,MainWindow* game,const QPixmap&sprite=QPixmap(":/new/prefix1/res/bullet1.png"));
    void move();
    void setCurrentPosition(QPoint pos);
    QPoint currentPosition();
    void draw(QPainter *painter);

   const QPoint b_startPoint;
   const QPoint b_targetPoint;
   QPoint b_currentPosition;
   QPixmap b_sprite;
   Enemy* b_target;
   MainWindow* b_game;
   int b_damage;
public slots:
   virtual void hitTarget();
};
class BulletSlowingAttack:public Bullet   //冰冻塔的子弹
{
     Q_OBJECT
    Q_PROPERTY(QPoint b_currentPosition READ currentPosition WRITE setCurrentPosition)

public:
    BulletSlowingAttack(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
           MainWindow *game, const QPixmap &sprite = QPixmap(":/new/prefix1/res/SlowingBullet_1.png"));
    ~BulletSlowingAttack();

public slots:
    virtual void hitTarget();

};

class BulletStrongAttack:public Bullet  //强力塔的子弹
{
    Q_OBJECT//所有应用QT槽的类都需要声明
    Q_PROPERTY(QPoint b_currentPosition READ currentPosition WRITE setCurrentPosition)

public:
    BulletStrongAttack(QPoint startPos, QPoint targetPoint, int damage, Enemy *target,
           MainWindow *game, const QPixmap &sprite = QPixmap(":/new/prefix1/res/StrongBullet.png"));
    ~BulletStrongAttack();

};

#endif // BULLET_H
