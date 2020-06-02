#ifndef TOWER_H
#define TOWER_H
#include <QPixmap>
#include <QRect>
class Tower
{
public:
    Tower(QPoint pos,const QPixmap &sprite= QPixmap(":/new/prefix1/res/塔1.png"));
    //void shoot();
    //发射子弹
  //  void setposition(int x,int y);
    //设置位置
    void draw(QPainter *painter) const;//画图
private:
    QPoint t_pos; //坐标：塔的圆心坐标（为了方便画圆）
    QPixmap t_sprite;//塔的图像
    int t_damage;//伤害（不同的等级伤害不同）
    int t_rate;//攻击的频率
    int t_attacjRange;//攻击范围：射程半径
    static const QSize t_size;//这是图标的大小 用static const（恒定不变）

 //   QRect m_Rect;
    //矩阵边框
};

#endif // TOWER_H
