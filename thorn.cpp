#include "thorn.h"
#include "zombie.h"
#include <QPainter>

thorn::thorn() {
    hp = 10000; // 地刺应该是没有血量这个概念的，但为了兼容现有系统保留
    atk = 20;               // 每次伤害值（原版游戏中地刺每次造成20点伤害）
    damageInterval = 30;    // 伤害间隔（约1秒，33ms/帧 × 30 ≈ 1秒）
    damageCounter = 0;
    setMovie(":/new/prefix1/Thorn.png"); // 使用PNG格式的地刺图片
}

// 地刺碰撞范围（覆盖一格地面）
QRectF thorn::boundingRect() const {
    // 地刺应该贴地显示，占据整个格子的底部区域
    // 格子大小约为85x95像素，地刺应该在底部，高度约为20像素
    return QRectF(-40, 15, 80, 20); // 宽度80像素，高度20像素，位于格子底部
}

// 自定义绘制函数，确保地刺正确显示在格子底部
void thorn::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    
    if (mQMovie && !mQMovie->currentImage().isNull()) {
        // 将地刺绘制在格子底部中央
        QImage image = mQMovie->currentImage();
        QRectF targetRect = boundingRect();
        painter->drawImage(targetRect, image);
    }
}

// 每帧更新逻辑
void thorn::advance(int phase) {
    if (!phase) return;
    update();

    // 伤害计时器累加，达到间隔则触发伤害
    if (++damageCounter >= damageInterval) {
        damageCounter = 0;
        // 检测碰撞的僵尸
        QList<QGraphicsItem*> collidingItems = scene()->collidingItems(this);
        foreach (QGraphicsItem* item, collidingItems) {
            zombie* z = qgraphicsitem_cast<zombie*>(item);
            if (z) {
                z->hp -= atk; // 对僵尸造成伤害
            }
        }
    }
}

// 碰撞检测：只与僵尸碰撞
bool thorn::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const {
    Q_UNUSED(mode);
    // 仅检测僵尸，且严格匹配「同一行 + 僵尸在格子范围内」
    const zombie* z = qgraphicsitem_cast<const zombie*>(other);
    if (!z) return false;

    // 同一行（Y轴误差±10像素，适配不同僵尸高度）
    bool sameRow = qAbs(z->y() - y()) < 10;
    // 僵尸X轴覆盖地刺格子（地刺格子宽度80像素）
    bool inXRange = (z->x() >= x() - 40) && (z->x() <= x() + 40);

    return sameRow && inXRange;
}

// 植物信息描述
QString thorn::getInfo() const {
    return QString("地刺：对经过的僵尸造成持续伤害，每次伤害%1").arg(atk);
}
