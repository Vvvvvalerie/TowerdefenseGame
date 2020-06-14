#ifndef ENEMY_H
#define ENEMY_H
#include<QPoint>
#include<QPixmap>
#include<QPainter>
#include<QObject>
#include"waypoint.h"
#include"mainwindow.h"
class MainWindow;
class Enemy:public QObject
{
    Q_OBJECT
public:
    Enemy(WayPoint *startPoint, MainWindow *game,const QPixmap &sprite=QPixmap(":/new/prefix1/res/保卫萝卜资源-宠物主题03-HD(PetsTheme03-h_爱给网_aigei_com (1).png"));
    void draw(QPainter *painter);
    void move();
    void getAttacked();
    void gotLostSight();
    QPoint pos();
    void getDamage(int damage);
    void getremoved();
private:
    int e_Hpmax;
    int e_Hpcurrent;
    double e_walkingspeed;
    bool e_active;
    QPoint e_pos;
    QPixmap e_sprite;
    WayPoint *e_destinationWayPoint;
    MainWindow* e_game;
    double e_rotationsprite;
    QSize e_size;
public slots:
    void doActive();

};

#endif // ENEMY_H
