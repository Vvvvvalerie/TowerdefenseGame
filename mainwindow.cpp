#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include <QIcon.h>
#include <QPainter>
#include <QMouseEvent>
#include"towerposition.h"
#include"tower.h"
#include<QPoint>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //调用初始化场景
    initScene();
   // setStyleSheet("border-image:url(:/new/prefix1/背景1.webp);");
   showtowerposition();

}
void MainWindow::showtowerposition()
{
    QPoint pos[]={
        QPoint(230,180),
        QPoint(230,260),
      //  QPoint(280,260),
        QPoint(100,470),
        QPoint(210,470),
        QPoint(320,470),
        QPoint(450,350),
        QPoint(590,350),
        QPoint(730,350),
        QPoint(380,150),
        QPoint(630,150),
        QPoint(780,150),
//QPoint(100,100),
    };
    len=sizeof(pos)/sizeof(pos[0]);
    for(int i=0;i<len;i++){
        list.push_back(pos[i]);
    }
}



void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint Mousepoint =event->pos();//找到鼠标点击的点
    //怎么确定这个点击是否有效？即怎么确定这个点击处落在塔座上而且这里没有塔?
    QList<TowerPosition>::iterator it=list.begin();//循环，从塔座list第一个开始,其中begin和end返回类似指针（iterator迭代器）
    while(it!=list.end()){
        if(it->containPoint(Mousepoint)&&!it->hastower()&&canBuyTower()){
            it->sethasTower();//此处从此设为有塔
            Tower *temp=new Tower(it->centerPos());
            t_towersList.push_back(temp);//建塔
            update();
            break;//只要在塔座list中找到某一个点符合就好，break
        }
        ++it;
    }
}


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/new/prefix1/背景1.webp"));

    foreach (TowerPosition tp, list)
      tp.draw(&painter);

    foreach(Tower* temp,t_towersList)
        temp->draw(&painter);


        // QPoint a(100,100);
   // painter.drawPixmap(a,QPixmap(":/new/prefix1/res/spot2.png"));

}



bool MainWindow::canBuyTower()
{
    return true;
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initScene()
{
    //设置窗口固定尺寸
    setFixedSize(GAME_WIDTH,GAME_HEIGHTH);
    //设置标题
    setWindowTitle(GAME_TITLE);
    //窗口左上角的小图标
    setWindowIcon(QIcon(":/new/prefix1/右上角图标.png"));
}
