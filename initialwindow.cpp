#include "initialwindow.h"
#include"config.h"
#include"mainwindow.h"
#include<QPushButton>
#include"mybutton.h"
#include<QPainter>
#include<QTimer>
InitialWindow::InitialWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(GAME_TITLE);
    //窗口左上角的小图标
    setWindowIcon(QIcon(":/new/prefix1/icon.png"));
    this->setFixedSize(1000,700);

    MyButton *btn=new MyButton(":/new/prefix1/res/startButton.png");
    btn->setParent(this);
    btn->move(330,330);

   MainWindow* scene=new MainWindow;
    connect(btn,&MyButton::clicked,this,[=](){
        btn->zoomdown();
        btn->zoomup();
        QTimer::singleShot(500,this,[=](){

            this->close();
            scene->show();
        });
    });


}

void InitialWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/new/prefix1/res/InitialPix.jpg"));
}
