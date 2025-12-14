#ifndef MOWER_H
#define MOWER_H

#include "other.h"
#include "zombie.h"

// 重新定义 Mower 类，继承自 other
class Mower : public other
{
public:
    // 构造函数
    Mower();
    // 重写 boundingRect 函数，用于定义图形项的边界矩形
    QRectF boundingRect() const override;
    // 重写 paint 函数，用于绘制图形项
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    // 重写 collidesWithItem 函数，用于检测图形项之间的碰撞
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    // 重写 advance 函数，用于更新图形项的状态
    void advance(int phase) override;

private:
    // 标志位，用于判断割草机是否启动
    bool isActivated;
    // 割草机的移动速度
    qreal movementSpeed;
};

#endif
