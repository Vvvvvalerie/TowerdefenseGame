#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H
#include <QPoint>
#include <QPixmap>
class TowerPosition
{
public:
    TowerPosition(QPoint pos,const QPixmap &sprite= QPixmap(":/new/prefix1/res/spot2.png") );
    void sethasTower(bool hastower=true);   //放上塔之后， s_hastower就该变为ture
    bool hastower() const;       //给出是否有塔：有的话就有升级操作
    const QPoint centerPos() const;  //找到一个基座的中心点
    bool containPoint(const QPoint &pos) const;   //鼠标点击的点是否在基座spot上
    void draw(QPainter *painter) const;          //画图



private:
        QPoint  s_pos;     //安放塔的位置
        bool s_hastower;   //是否有塔
        QPixmap s_sprite;  //塔的图片
        static const QSize s_size;//这是图标的大小 用static const（恒定不变）

};

#endif // TOWERPOSITION_H
