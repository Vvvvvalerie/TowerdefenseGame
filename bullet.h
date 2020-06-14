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
    Q_OBJECT//所有应用QT槽的类都需要声明
    Q_PROPERTY(QPoint b_currentPosition READ currentPosition WRITE setCurrentPosition)


public:
    Bullet(QPoint currentPos,QPoint targetPos,int damage,Enemy* enemy,MainWindow* game);
    void move();
    void setCurrentPosition(QPoint pos);
    QPoint currentPosition();
    void draw(QPainter *painter);
private:
   const QPoint b_startPoint;
   const QPoint b_targetPoint;
   QPoint b_currentPosition;
   QPixmap b_sprite;
   Enemy* b_target;
   MainWindow* b_game;
   int b_damage;
private slots:
   virtual void hitTarget();
};

#endif // BULLET_H
