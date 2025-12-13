#include "mower.h"

// 构造函数实现
Mower::Mower()
{
    // 初始状态下割草机未启动
    isActivated = false;
    // 计算割草机的移动速度
    movementSpeed = 270.0 * 33 / 1000;
}

// 实现 boundingRect 函数
QRectF Mower::boundingRect() const
{
    // 返回割草机的边界矩形
    return QRectF(-30, -30, 60, 60);
}

// 实现 paint 函数
void Mower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 忽略 option 和 widget 参数
    Q_UNUSED(option);
    Q_UNUSED(widget);
    // 在指定矩形区域绘制割草机的图片
    painter->drawPixmap(QRect(-30, -30, 60, 60), QPixmap(":/new/prefix1/LawnMower.png"));
}

// 实现 collidesWithItem 函数
bool Mower::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    // 忽略 mode 参数
    Q_UNUSED(mode);
    // 检查是否与僵尸碰撞，并且在同一行，且水平距离小于 15
    return other->type() == zombie::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 15;
}

// 实现 advance 函数
void Mower::advance(int phase)
{
    // 如果 phase 为 0，直接返回
    if (phase == 0)
        return;
    // 更新图形项
    update();
    // 获取与割草机碰撞的所有图形项
    QList<QGraphicsItem *> collidedItems = collidingItems();
    // 如果有碰撞的图形项
    if (!collidedItems.isEmpty())
    {
        // 启动割草机
        isActivated = true;
        // 遍历所有碰撞的图形项
        for (QGraphicsItem *item : collidedItems)
        {
            // 将图形项转换为僵尸类型
            zombie *zom = qgraphicsitem_cast<zombie *>(item);
            // 如果转换成功，将僵尸的生命值设为 0
            if (zom)
            {
                zom->hp = 0;
            }
        }
    }
    // 如果割草机已启动
    if (isActivated)
    {
        // 更新割草机的 x 坐标
        setX(x() + movementSpeed);
    }
    // 如果割草机超出了指定位置
    if (x() > 1069)
    {
        // 删除割草机对象
        delete this;
    }
}
