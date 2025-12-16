#include "thorn.h"
#include "zombie.h"

thorn::thorn() {
    hp = 10000; // 注意地刺应该是没有血量这个概念的
    atk = 10;               // 每次伤害值
    damageInterval = 30;    // 伤害间隔（约1秒，33ms/帧 × 30 ≈ 1秒）
    damageCounter = 0;
    setMovie(":/new/prefix1/thorn.gif"); // 地刺图片（需准备素材），这里素材准备一下，先挂起
    // 但是要注意是不是也要找攻击的gif

    // 关键：设置锚点为图片底部中心（让地刺贴格子下部显示）
    //setTransformOriginPoint(boundingRect().width()/2, boundingRect().height());
    // 微调Y轴位置（根据素材大小调整，示例向下偏移20像素）
    //setPos(x(), y() + 20);
}

// 地刺碰撞范围（覆盖一格地面）
// QRectF thorn::boundingRect() const {
//     //  return QRectF(-40, 10, 80, 40); // 向下移动30像素（Y轴从-20→10）
//     return QRectF(0, 10, 60, 90); // 横向范围稍大，确保僵尸经过时触发
// }

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
            if (z) z->hp -= atk; // 对僵尸造成伤害

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
    return QString("地刺：对经过的僵尸造成持续伤害，生命值%1，每次伤害%2").arg(hp).arg(atk);
}
