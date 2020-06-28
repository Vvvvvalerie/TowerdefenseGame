#ifndef TOWER_H
#define TOWER_H
#include <QPixmap>
#include <QRect>
#include<QObject>

class MainWindow;
class Enemy;
class Tower:public QObject
{
   Q_OBJECT
public:
    Tower( QPoint pos,MainWindow *game,const QPixmap &sprite= QPixmap(":/new/prefix1/res/tower1.Png"));
    ~Tower();
    //void shoot();
    //发射子弹
  //  void setposition(int x,int y);
    //设置位置
    virtual void draw(QPainter *painter) const;//画图
    virtual void targetKilled();
    virtual void attackEnemy();
    virtual void checkEnemyinRange();
    virtual void setTowerLevel(int level);
    virtual int getTowerLevel();
    QPoint getPosition();

    void chooseOnetoAttack(Enemy *enemy);
    void removebullet();
    void damageEnemy();
    void LostSight();
    int getTowerType();


    int m_towerType=1;
    int m_towerLevel;
    bool m_attacking;

    QPoint t_pos; //坐标：塔的圆心坐标（为了方便画圆）
    QPixmap t_sprite;//塔的图像
    int t_damage;//伤害（不同的等级伤害不同）
    int t_rate;//攻击的频率
    int t_attackRange;//攻击范围：射程半径
    QSize t_size;//这是图标的大小 用static const（恒定不变）
    Enemy* t_chosenEnemy;
    QTimer* t_rateTimer;
    MainWindow* t_game;
public slots:
    void shootWeapon();

};
class Tower2:public Tower{
   Q_OBJECT
public:
    Tower2(QPoint pos, MainWindow *game,const QPixmap &sprite = QPixmap(":/new/prefix1/res/tower1.Png"));
    ~Tower2();


};
class TowerSlowingAttack:public Tower   //冰冻塔
{
    Q_OBJECT//所有应用QT槽的类都需要声明
public:
    TowerSlowingAttack(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/new/prefix1/res/SlowingTower.png"));
    ~TowerSlowingAttack();
    void chooseEnemyForAttack(Enemy *enemy);
    int m_towerType=2;
public slots:
    void shootWeapon();

};
class TowerStrongAttack:public Tower    //强力塔
{
    Q_OBJECT
public:
    TowerStrongAttack(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/new/prefix1/res/StrongTower.png"));
    ~TowerStrongAttack();
    int  m_towerType=3;
public slots:
    void shootWeapon();
};


#endif // TOWER_H
