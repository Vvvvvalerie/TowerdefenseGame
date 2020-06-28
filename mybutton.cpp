#include "mybutton.h"
#include<QPixmap>
#include<QPropertyAnimation>
MyButton::MyButton(QString pix):QPushButton(0)
{
       QPixmap pixmap(pix);
       this->setFixedSize(pixmap.width(),pixmap.height());
       this->setStyleSheet("QPushButton{border:Opx;}");
       this->setIcon(pixmap);
       this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}

void MyButton::zoomup()
{
    QPropertyAnimation* animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->start();
}

void MyButton::zoomdown()
{
    QPropertyAnimation* animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->start();
}
