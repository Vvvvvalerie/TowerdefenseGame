#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QList>
#include"towerposition.h"
#include"tower.h"
#include<QMouseEvent>
#include"waypoint.h"
#include"enemy.h"
#include"bullet.h"
namespace Ui {
class MainWindow;
}
class Enemy;
class Tower;
class Bullet;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initScene();//初始化场景
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);//用于鼠标点击——>建塔
    bool canBuyTower();
    void causeHpLose(int damage=1);
    void removeEnemy(Enemy *enemy);
    void removeBullet(Bullet *bullet);
    void addBullet(Bullet* bullet);
    QList<Enemy *> enemylist() const;
private:
    Ui::MainWindow *ui;
    QList<TowerPosition>list;//塔座的list
    QList<Tower*> t_towersList;//塔的list
    QList<WayPoint *>wp_waypointList; //位点的list
    QList<Enemy *>e_enemylist;
    void addWayPoint();
    void showtowerposition();
    bool loadWave();
    int len;   //有多少个塔
    int the_waves;
public slots:
    void updateMap();
};

#endif // MAINWINDOW_H
