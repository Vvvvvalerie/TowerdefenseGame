#ifndef TOWER_H
#define TOWER_H
#include <QPixmap>
#include <QRect>
#include<QObject>
#include"enemy.h"
#include"mainwindow.h"
class MainWindow;
class Enemy;
class Tower:public QObject
{
    Q_OBJECT
public:
    Tower( QPoint pos,MainWindow *game,const QPixmap &sprite= QPixmap(":/new/prefix1/res/塔1.png"));

    //void shoot();
    //发射子弹
  //  void setposition(int x,int y);
    //设置位置
    void draw(QPainter *painter) const;//画图
    void targetKilled();
    void attackEnemy();
    void chooseOnetoAttack(Enemy *enemy);//待实现

private:
    QPoint t_pos; //坐标：塔的圆心坐标（为了方便画圆）
    QPixmap t_sprite;//塔的图像
    int t_damage;//伤害（不同的等级伤害不同）
    int t_rate;//攻击的频率
    int t_attacjRange;//攻击范围：射程半径
    static const QSize t_size;//这是图标的大小 用static const（恒定不变）
    Enemy* t_chosenEnemy;
    QTimer* t_rateTimer;
    MainWindow* t_game;
    void removebullet();
    void LostSight();
private slots:
    void shootWeapoon();

 //   QRect m_Rect;
    //矩阵边框
};

#endif // TOWER_H
