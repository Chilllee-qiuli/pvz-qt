#ifndef THORN_H
#define THORN_H

#include "plant.h"

class thorn : public plant {
public:
    thorn();
    QRectF boundingRect() const override; // 碰撞范围（覆盖地面区域）
    void advance(int phase) override;     // 处理伤害逻辑和自身状态
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override; // 检测僵尸碰撞
    QString getInfo() const override;     // 植物描述
private:
    int damageInterval; // 伤害间隔（帧数）
    int damageCounter;  // 伤害计时器
};

#endif // THORN_H
