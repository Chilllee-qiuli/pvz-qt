#include "thorn.h"
#include "zombie.h"

thorn::thorn() {
    hp = 300;               // 地刺生命值（可被僵尸攻击摧毁）
    atk = 10;               // 每次伤害值
    damageInterval = 30;    // 伤害间隔（约1秒，33ms/帧 × 30 ≈ 1秒）
    damageCounter = 0;
    setMovie(":/new/prefix1/thorn.gif"); // 地刺图片（需准备素材），这里素材准备一下，先挂起
    // 但是要注意是不是也要找攻击的gif
}

// 地刺碰撞范围（覆盖一格地面）
QRectF thorn::boundingRect() const {
    return QRectF(-40, -20, 80, 40); // 横向范围稍大，确保僵尸经过时触发
}

// 每帧更新逻辑
void thorn::advance(int phase) {
    if (!phase) return;
    update();

    // 自身生命值耗尽则消失
    if (hp <= 0) {
        delete this;
        return;
    }

    // 伤害计时器累加，达到间隔则触发伤害
    if (++damageCounter >= damageInterval) {
        damageCounter = 0;
        // 检测碰撞的僵尸
        QList<QGraphicsItem*> collidingItems = scene()->collidingItems(this);
        foreach (QGraphicsItem* item, collidingItems) {
            zombie* z = qgraphicsitem_cast<zombie*>(item);
            if (z) {
                z->hp -= atk; // 对僵尸造成伤害
                // 同时地刺会被僵尸反击（模拟被踩坏的逻辑）
                hp -= z->atk / 5; // 僵尸攻击力的1/5（地刺较耐踩）
            }
        }
    }
}

// 碰撞检测：只与僵尸碰撞
bool thorn::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const {
    Q_UNUSED(mode);
    return other->type() == zombie::Type && qFuzzyCompare(other->y(), y()); // 同一行的僵尸
}

// 植物信息描述
QString thorn::getInfo() const {
    return QString("地刺：对经过的僵尸造成持续伤害，生命值%1，每次伤害%2").arg(hp).arg(atk);
}
