#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QList>
#include"towerposition.h"
#include"tower.h"
#include<QMouseEvent>
namespace Ui {
class MainWindow;
}

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
private:
    Ui::MainWindow *ui;
    QList<TowerPosition>list;//塔座的list
    QList<Tower*> t_towersList;//塔的list
    void showtowerposition();
    int len;   //有多少个塔
};

#endif // MAINWINDOW_H
