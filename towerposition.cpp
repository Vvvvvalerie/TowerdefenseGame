#include "towerposition.h"
#include <QSize.h>
#include <QPainter>


const QSize TowerPosition::s_size(80,80);


TowerPosition::TowerPosition(QPoint pos, const QPixmap &sprite):
    s_pos(pos),s_hastower(false),s_sprite(sprite){}

void TowerPosition::sethasTower(bool hastower)
{
    s_hastower=hastower;
}

bool TowerPosition::hastower() const
{
    return s_hastower;
}

const QPoint TowerPosition::centerPos() const
{
    QPoint m(s_size.width()/2,s_size.height()/2);   //位移图片长宽的一半，就是中心点
    return s_pos+m;
}

bool TowerPosition::containPoint(const QPoint &pos) const
{
    bool X= s_pos.x() < pos.x() && pos.x() < (s_pos.x() + s_size.width());//判断x是否在基座的图标上
    bool Y= s_pos.y() < pos.y() && pos.y() < (s_pos.y() + s_size.height());//判断y是否在基座的图标上
    return X&&Y;
}

void TowerPosition::draw(QPainter *painter) const
{
    painter->drawPixmap(s_pos.x(),s_pos.y(),s_sprite);
}
//QPoint y(100,100);
//TowerPosition x(y);


