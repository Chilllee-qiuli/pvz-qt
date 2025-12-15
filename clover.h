#ifndef CLOVER_H
#define CLOVER_H


#include "plant.h"

class clover : public plant {
public:
    clover();
    void advance(int phase) override; // 处理清除僵尸逻辑
    QString getInfo() const override; // 植物描述
    QRectF boundingRect() const override; // 碰撞范围
};

#endif // CLOVER_H
