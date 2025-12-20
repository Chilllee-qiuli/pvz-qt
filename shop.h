#ifndef SHOP_H
#define SHOP_H

#include "other.h"
#include "plant.h"

#include "sun.h"
#include "sunflower.h"
#include "pea.h"
#include "cherry.h"
#include "wallnut.h"
#include "snowpea.h"
#include "potato.h"
#include "repeater.h"
#include "chomper.h"
#include "chilipepper.h"
#include "thorn.h"
#include <QString>

class shop : public other
{
public:
    int sunnum;
    shop();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;

    // 旧接口（仍可被拖拽/其它逻辑调用）
    void addPlant(const QString& s, const QPointF& pos);

    // 新接口：用于“点卡片选中 → 点草坪种植”，返回是否种植成功
    bool tryAddPlant(const QString& s, const QPointF& pos);
    // 选中态（点击卡片后进入）
    void selectPlant(const QString& name);
    void clearSelection();
    bool hasSelection() const;
    QString selectedPlant() const;

private:
    int counter;
    int time;
    // ✅新增：当前选中的植物卡片
    QString mSelectedPlant;
};


#endif // SHOP_H
