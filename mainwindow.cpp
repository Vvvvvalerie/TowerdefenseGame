#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include <QIcon.h>
#include <QPainter>
#include <QMouseEvent>
#include<QPushButton>
#include"towerposition.h"
#include"tower.h"
#include"bullet.h"
#include"enemy.h"
#include"waypoint.h"
#include"audioplayer.h"
#include"mybutton.h"
#include<QPoint>
#include<QTimer>

static const int TowerCost=300;//建一座塔花费的金币
static const int UpdateTowerCost = 400;//升级炮塔花费400金
static const int TowerSlowingAttackCost=500;//冰冻炮塔花费500金
static const int TowerStrongAttackCost=500;//加强塔花费500金
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    the_waves=0;
    m_playerHp=5;
    m_playerGold=10000;
    m_myGameEnded=false;
    m_myGameWin_1=false;
    m_myGameWin_2=false;
    m_stopgame=false;
    m_DestroyTowerMode=false;
    m_audioplayer=new AudioPlayer(this);
    m_audioplayer->startBGM();
    ui->setupUi(this);
    //调用初始化场景
    initScene();


//DestroyTower按钮
    MyButton *btn= new MyButton(":/new/prefix1/res/Destroy1.png");
     btn->setParent(this);
     btn->move(290,600);
     connect(btn,&QPushButton::clicked,this,[=](){
         btn->zoomdown();
         btn->zoomup();
         QTimer::singleShot(500,this,[=](){
          ChangeDestroyTowerMode();
         });
     });
 //stopgame按钮
 MyButton *stopBtn= new MyButton(":/new/prefix1/res/stopButton.png");
  stopBtn->setParent(this);
  stopBtn->move(500,600);
  connect(stopBtn,&QPushButton::clicked,this,[=](){
    stopBtn->zoomdown();
    stopBtn->zoomup();
    if(!m_stopgame)   //这里判断语句的作用是用同一个按钮完成暂停和继续。
    {
  QTimer::singleShot(500,this,[=](){
   stop_clicked();
 });}
    else{
        QTimer::singleShot(500,this,[=](){
         continue_clicked();
       });
    }
});
//塔1按钮
   MyButton *btn1= new MyButton(":/new/prefix1/res/tower1.Png");
    btn1->setParent(this);
    btn1->move(5,600);
    connect(btn1,&QPushButton::clicked,this,[=](){
        btn1->zoomdown();
        btn1->zoomup();
        QTimer::singleShot(500,this,[=](){
         Changetype1Clicked();
        });

    });
//塔2按钮
    MyButton *btn2= new MyButton(":/new/prefix1/res/SlowingTower.png");
     btn2->setParent(this);
     btn2->move(90,580);
     connect(btn2,&QPushButton::clicked,this,[=](){
         btn2->zoomdown();
         btn2->zoomup();
         QTimer::singleShot(500,this,[=](){
          Changetype2Clicked();
         });

     });
//塔3按钮
    MyButton *btn3= new MyButton(":/new/prefix1/res/StrongTower.png");
    btn3->setParent(this);
    btn3->move(190,580);
    connect(btn3,&QPushButton::clicked,this,[=](){
        btn3->zoomdown();
        btn3->zoomup();
        QTimer::singleShot(500,this,[=](){
         Changetype3Clicked();
        });

    });

   // setStyleSheet("border-image:url(:/new/prefix1/背景1.webp);");
   showtowerposition();
   addWayPoint();

   loadWave();

   QTimer *timer=new QTimer(this);
   connect(timer,SIGNAL(timeout()),this,SLOT(updateMap()));
   timer->start(30);



}
void MainWindow::showtowerposition()
{
    QPoint pos[]={
        QPoint(230,180),
        QPoint(230,260),
        QPoint(100,470),
        QPoint(210,470),
        QPoint(320,470),
        QPoint(450,350),
        QPoint(590,350),
        QPoint(730,350),
        QPoint(380,150),
        QPoint(630,150),
        QPoint(780,150),

    };
    len=sizeof(pos)/sizeof(pos[0]);
    for(int i=0;i<len;i++){
        list.push_back(pos[i]);
    }
}

void MainWindow::showtowerposition2()
{
    QPoint pos[]={

        QPoint(80,300),
        QPoint(180,300),
        QPoint(200,110),
        QPoint(390,260),
        QPoint(300,470),
        QPoint(450,470),
        QPoint(640,300),
        QPoint(550,110),
        QPoint(750,110)


    };
    len=sizeof(pos)/sizeof(pos[0]);
    for(int i=0;i<len;i++){
        list.push_back(pos[i]);
    }
}

bool MainWindow::loadWave()
{
    //加一个判断第一关的if
    if(the_waves==0)
    {
        WayPoint *startWayPoint=wp_waypointList.back();
        int enemyInterval[]={10,29000,28000,36000,45000,57000};//每波出现六个敌人
        for(int i=0;i<6;++i)
        {
            if(i%3==0)
            {
                Enemy *enemy=new Enemy(startWayPoint,this);
                e_enemylist.push_back(enemy);
                QTimer::singleShot(enemyInterval[i],enemy,SLOT(doActive()));
            }
            if(i%3==1)
            {
                Enemy *enemy2=new Enemy2(startWayPoint,this);
                e_enemylist.push_back(enemy2);
                QTimer::singleShot(enemyInterval[i],enemy2,SLOT(doActive()));
            }
            if(i%3==2)
            {
                Enemy *enemy3=new Enemy3(startWayPoint,this);
                e_enemylist.push_back(enemy3);
                QTimer::singleShot(enemyInterval[i],enemy3,SLOT(doActive()));
            }
        }
        return true;
    }
    if(the_waves==1)
    {
        WayPoint *startWayPoint=wp_waypointList.back();
        int enemyInterval[]={1000,10000,19000,28000,36000,45000,54000,63000,71000,79000};//每波出现六个敌人
        for(int i=0;i<10;++i)
        {
            if(i%3==0)
            {
                Enemy *enemy=new Enemy(startWayPoint,this);
                e_enemylist.push_back(enemy);
                QTimer::singleShot(enemyInterval[i],enemy,SLOT(doActive()));
            }
            if(i%3==1)
            {
                Enemy *enemy2=new Enemy2(startWayPoint,this);
                e_enemylist.push_back(enemy2);
                QTimer::singleShot(enemyInterval[i],enemy2,SLOT(doActive()));
            }
            if(i%3==2)
            {
                Enemy *enemy3=new Enemy3(startWayPoint,this);
                e_enemylist.push_back(enemy3);
                QTimer::singleShot(enemyInterval[i],enemy3,SLOT(doActive()));
            }
        }
        return true;
    }
    if(the_waves>=2)
        return false;
}

void MainWindow::doGameOver()
{
    if(!m_myGameEnded)
    {
        m_myGameEnded=true;
    }
}

void MainWindow::drawWave(QPainter *painter)
{
    QFont font = painter->font();
      font.setPixelSize(24);
      painter->setFont(font);
    painter->setPen(QPen(Qt::blue));
    painter->drawText(QRect(700, 5, 100, 25), QString("WAVE : %1").arg(the_waves + 1));
}

void MainWindow::drawHP(QPainter *painter)
{
    QFont font = painter->font();
      font.setPixelSize(24);
      painter->setFont(font);
    painter->setPen(QPen(Qt::blue));
    painter->drawText(QRect(30, 5, 100, 25), QString("HP : %1").arg(m_playerHp));
}

void MainWindow::drawPlayerGold(QPainter *painter)
{
    QFont font = painter->font();
      font.setPixelSize(24);
      painter->setFont(font);
    painter->setPen(QPen(Qt::blue));
    painter->drawText(QRect(400, 5, 200, 25), QString("GOLD : %1").arg(m_playerGold));
}

void MainWindow::addBullet(Bullet *bullet)
{
    b_bulletlist.push_back(bullet);
}

void MainWindow::awardGold(int gold)
{
    m_playerGold+=gold;
    update();
}

AudioPlayer *MainWindow::audioplayer() const
{
    return m_audioplayer;
}

QList<Enemy *> MainWindow::enemylist() const
{
    return e_enemylist;
}

void MainWindow::updateMap()
{
    if(!m_stopgame){
    foreach (Enemy *enemy, e_enemylist)
       enemy->move();
    foreach(Tower* tower,t_towersList)
        tower->checkEnemyinRange();
    update();
    }
}

void MainWindow::stop_clicked()
{
       m_stopgame=true;
}

void MainWindow::continue_clicked()
{
      m_stopgame=false;
}

void MainWindow::Changetype1Clicked()
{
    m_DestroyTowerMode=false;
    TowerMode=1;
}

void MainWindow::Changetype2Clicked()
{
    m_DestroyTowerMode=false;
    TowerMode=2;
}

void MainWindow::Changetype3Clicked()
{
    m_DestroyTowerMode=false;
    TowerMode=3;
}

void MainWindow::ChangeDestroyTowerMode()
{
    m_DestroyTowerMode=true;
}

void MainWindow::addWayPoint()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(900, 400));
    wp_waypointList.push_back(wayPoint1);
    WayPoint *wayPoint2 = new WayPoint(QPoint(900, 280));
    wp_waypointList.push_back(wayPoint2);
    wayPoint2->setNext(wayPoint1);
    WayPoint *wayPoint3 = new WayPoint(QPoint(400, 280));
    wp_waypointList.push_back(wayPoint3);
    wayPoint3->setNext(wayPoint2);
    WayPoint *wayPoint4 = new WayPoint(QPoint(400,400));
    wp_waypointList.push_back(wayPoint4);
    wayPoint4->setNext(wayPoint3);
    WayPoint *wayPoint5 = new WayPoint(QPoint(140,400));
    wp_waypointList.push_back(wayPoint5);
    wayPoint5->setNext(wayPoint4);
    WayPoint *wayPoint6 = new WayPoint(QPoint(140,10));
    wp_waypointList.push_back(wayPoint6);
    wayPoint6->setNext(wayPoint5);


}

void MainWindow::addWayPoint2()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(980, 400));
       wp_waypointList.push_back(wayPoint1);
       WayPoint *wayPoint2 = new WayPoint(QPoint(840, 400));
       wp_waypointList.push_back(wayPoint2);
       wayPoint2->setNext(wayPoint1);
       WayPoint *wayPoint3 = new WayPoint(QPoint(840, 240));
       wp_waypointList.push_back(wayPoint3);
       wayPoint3->setNext(wayPoint2);
       WayPoint *wayPoint4 = new WayPoint(QPoint(550,240));
       wp_waypointList.push_back(wayPoint4);
       wayPoint4->setNext(wayPoint3);
       WayPoint *wayPoint5 = new WayPoint(QPoint(550,400));
       wp_waypointList.push_back(wayPoint5);
       wayPoint5->setNext(wayPoint4);
       WayPoint *wayPoint6 = new WayPoint(QPoint(320,400));
       wp_waypointList.push_back(wayPoint6);
       wayPoint6->setNext(wayPoint5);
       WayPoint *wayPoint7 = new WayPoint(QPoint(320,240));
       wp_waypointList.push_back(wayPoint7);
       wayPoint7->setNext(wayPoint6);
       WayPoint *wayPoint8 = new WayPoint(QPoint(100,240));
       wp_waypointList.push_back(wayPoint8);
       wayPoint8->setNext(wayPoint7);
       WayPoint *wayPoint9 = new WayPoint(QPoint(100,10));
       wp_waypointList.push_back(wayPoint9);
       wayPoint9->setNext(wayPoint8);

}  //把测试出来的一系列位点放入QList中


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint Mousepoint =event->pos();//找到鼠标点击的点
    //怎么确定这个点击是否有效？即怎么确定这个点击处落在塔座上而且这里没有塔?
    auto it=list.begin();
    while(it!=list.end())
    {
//拆除模式
        if(m_DestroyTowerMode&&it->containPoint(Mousepoint)&&it->hastower())
        {
            foreach(Tower* tower,t_towersList)
            {
                if(it->centerPos()==tower->getPosition())
                {
                    this->removeTower(tower);
                    it->s_hastower=false;
                }
            }
           update();
           break;
        }
//塔1
        if(!m_DestroyTowerMode&&it->containPoint(Mousepoint)&&!it->hastower()&&canBuyTower()&&TowerMode==1)
        {
           m_audioplayer->playSound(TowerPlaceSound);
            m_playerGold=m_playerGold-TowerCost;
            it->sethasTower();//此处从此设为有塔

            Tower *temp=new Tower(it->centerPos(),this);
            temp->setTowerLevel(1);//初建时塔为1级
            t_towersList.push_back(temp);//建塔
            update();
            break;//只要在塔座list中找到某一个点符合就好，break
        }
        if(!m_DestroyTowerMode&&it->containPoint(Mousepoint)&&canUpgradeTower()&&TowerMode==1)
        {
            foreach(Tower*attacker,t_towersList)
            {
                if(it->centerPos()==attacker->getPosition()&&attacker->getTowerLevel()==1)//只有原来的塔时1级的时候才能升级
                {
                    attacker->setTowerLevel(2);
                    m_audioplayer->playSound(TowerPlaceSound);//应该用升级的声音
                    m_playerGold-= UpdateTowerCost;
                }
            }
            update();
            break;//只要在塔座list中找到某一个点符合就好，break
        }
//塔2
        if(!m_DestroyTowerMode&&it->containPoint(Mousepoint)&&!it->hastower()&&canBuyTower()&&TowerMode==2)
        {
           m_audioplayer->playSound(TowerPlaceSound);
           m_playerGold=m_playerGold-TowerSlowingAttackCost;
           it->sethasTower();//此处从此设为有塔

            Tower *temp=new TowerSlowingAttack(it->centerPos(),this);
            temp->setTowerLevel(1);//初建
            t_towersList.push_back(temp);//建塔
            update();
            break;//只要在塔座list中找到某一个点符合就好，break
        }
        if(!m_DestroyTowerMode&&it->containPoint(Mousepoint)&&canUpgradeTower()&&TowerMode==2)
        {
            foreach(Tower*attacker,t_towersList)
            {
                if(it->centerPos()==attacker->getPosition()&&attacker->getTowerLevel()==1)//只有原来的塔时1级的时候才能升级
                {
                    attacker->setTowerLevel(2);
                    m_audioplayer->playSound(TowerPlaceSound);//应该用升级的声音
                    m_playerGold-= UpdateTowerCost;
                }
            }
            update();
            break;//只要在塔座list中找到某一个点符合就好，break
        }
//塔3
        if(!m_DestroyTowerMode&&it->containPoint(Mousepoint)&&!it->hastower()&&canBuyTower()&&TowerMode==3)
        {
           m_audioplayer->playSound(TowerPlaceSound);
            m_playerGold=m_playerGold-TowerStrongAttackCost;
            it->sethasTower();//此处从此设为有塔

            Tower *temp=new TowerStrongAttack(it->centerPos(),this);
            temp->setTowerLevel(1);//初建
            t_towersList.push_back(temp);//建塔
            update();
            break;//只要在塔座list中找到某一个点符合就好，break
        }
        if(!m_DestroyTowerMode&&it->containPoint(Mousepoint)&&canUpgradeTower()&&TowerMode==3)
        {
            foreach(Tower*attacker,t_towersList)
            {
                if(it->centerPos()==attacker->getPosition()&&attacker->getTowerLevel()==1)//只有原来的塔时1级的时候才能升级
                {
                    attacker->setTowerLevel(2);
                    m_audioplayer->playSound(TowerPlaceSound);//应该用升级的声音
                    m_playerGold-= UpdateTowerCost;
                }
            }
            update();
            break;//只要在塔座list中找到某一个点符合就好，break
        }

        ++it;
    }
}


void MainWindow::paintEvent(QPaintEvent *)
{
    if(m_myGameWin_2)
    {
        QPainter painter(this);
        painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/new/prefix1/res/win！.png"));
    }
    if(m_myGameEnded)
    {
        QPainter painter(this);
        painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/new/prefix1/res/lose！.png"));
    }
    if(!m_myGameEnded&&!m_myGameWin_1)//第一局
    {
        QPainter painter(this);
        painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/new/prefix1/背景1.webp"));

        foreach (TowerPosition tp, list)
            tp.draw(&painter);

        foreach(Tower* temp,t_towersList)
            temp->draw(&painter);

        foreach(WayPoint* wp,wp_waypointList )
            wp->draw(&painter);

        foreach(Enemy *en,e_enemylist)
            en->draw(&painter);
        foreach(Bullet* bullet, b_bulletlist)
            bullet->draw(&painter);

        drawWave(&painter);
        drawHP(&painter);
        drawPlayerGold(&painter);
    }
    if(!m_myGameEnded&&m_myGameWin_1)//第二局
    {
        QPainter painter(this);
        painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/new/prefix1/be背景2.webp"));

        foreach (TowerPosition tp, list)
            tp.draw(&painter);

        foreach(Tower* temp,t_towersList)
            temp->draw(&painter);

        foreach(WayPoint* wp,wp_waypointList )
            wp->draw(&painter);
        foreach(Enemy *en,e_enemylist)
            en->draw(&painter);
        foreach(Bullet* bullet, b_bulletlist)
            bullet->draw(&painter);

        drawWave(&painter);
        drawHP(&painter);
        drawPlayerGold(&painter);
    }
}



bool MainWindow::canBuyTower()
{
    if(TowerMode==1)
    {
        if(m_playerGold>=TowerCost)
            return true;
        else return false;
    }
   else  if(TowerMode==2)
    {
        if(m_playerGold>=TowerSlowingAttackCost)
            return true;
        else return false;
    }
    else if(TowerMode==3)
    {
        if(m_playerGold>=TowerStrongAttackCost)
            return true;
        else return false;
    }
    else return false;
}

bool MainWindow::canUpgradeTower()
{
    if(m_playerGold>=UpdateTowerCost)
        return true;
    else return false;
}

bool MainWindow::canBuySlowingAttackTower()
{
    if(m_playerGold >=TowerSlowingAttackCost)
        return true;
    return false;
}

void MainWindow::getHpLose(int damage)
{
    m_audioplayer->playSound(LifeLoseSound);
    m_playerHp=m_playerHp-damage;
    if(m_playerHp<=0)
        doGameOver();
}

void MainWindow::removeEnemy(Enemy *enemy)
{
    e_enemylist.removeOne(enemy);
    delete enemy;
    if(e_enemylist.empty())
    {
        the_waves++;
        if(!loadWave())
        {
            if(!m_myGameWin_1)
            {
                m_myGameWin_1=true;
                t_towersList.clear();
                list.clear();
                wp_waypointList.clear();
                showtowerposition2();
                addWayPoint2();
                the_waves=0;
                loadWave();

            }
            else{
                m_myGameWin_2=true;
            }
        }
    }

}

void MainWindow::removeBullet(Bullet *bullet)
{
    b_bulletlist.removeOne(bullet);
    delete bullet;
}

void MainWindow::removeTower(Tower *tower)
{
    t_towersList.removeOne(tower);
    delete tower;
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
    setWindowIcon(QIcon(":/new/prefix1/icon.png"));
}
