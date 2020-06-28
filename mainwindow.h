#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QList>
#include"towerposition.h"
#include"tower.h"
#include"mybutton.h"
#include<QMouseEvent>
//#include"waypoint.h"
//#include"enemy.h"
//#include"bullet.h"
namespace Ui {
class MainWindow;
}
class Enemy;
class WayPoint;
class Bullet;
class AudioPlayer;
class MyButton;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initScene();//初始化场景
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);//用于鼠标点击——>建塔

    void getHpLose(int damage=1);
    void removeEnemy(Enemy *enemy);
    void removeBullet(Bullet *bullet);
    void removeTower(Tower *tower);
    void addBullet(Bullet* bullet);
    void awardGold(int gold);
    AudioPlayer* audioplayer() const;
    QList<Enemy *> enemylist() const;

    void addWayPoint();
    void addWayPoint2();
    void showtowerposition();
    void showtowerposition2();
    void doGameOver();
    //打印一些基本信息
    void drawWave(QPainter *painter);
    void drawHP(QPainter *painter);
    void drawPlayerGold(QPainter *painter);

    bool loadWave();
    bool canBuyTower();
    bool canUpgradeTower();
    bool canBuySlowingAttackTower();
private:
    Ui::MainWindow *ui;

    QList<TowerPosition>list;//塔座的list
    QList<Tower*> t_towersList;//塔的list
    QList<WayPoint *>wp_waypointList; //位点的list
    QList<Enemy *>e_enemylist;
    QList<Bullet*> b_bulletlist;
    QList<MyButton*>m_buttopn;

    int len;   //有多少个塔
    int the_waves;
    int m_playerHp;
    int m_playerGold;
    int TowerMode=1;

    bool m_myGameWin_1;
    bool m_myGameWin_2;
    bool m_myGameEnded;
    bool m_stopgame;
    bool m_DestroyTowerMode;

    AudioPlayer* m_audioplayer;
public slots:
    void updateMap();
    void stop_clicked();
    void continue_clicked();
    void Changetype1Clicked();
    void Changetype2Clicked();
    void Changetype3Clicked();
    void ChangeDestroyTowerMode();
signals:
    void chooseBack();
};

#endif // MAINWINDOW_H
