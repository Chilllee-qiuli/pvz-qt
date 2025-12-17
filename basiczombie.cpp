#include "basiczombie.h"
#include "thorn.h"

basiczombie::basiczombie()
{
    // 初始化僵尸属性
    hp = 270;                                  // 基础生命值
    atk = 100 * 33 / 1000;                    // 每秒攻击力转换为每帧伤害
    speed = 30.0 * 33 / 1000;                  // 每秒移动速度转换为每帧像素
    setZValue(2);                              // 设置Z轴层级
    setMovie(":/new/prefix1/ZombieWalk1.gif"); // 设置初始动画
}

void basiczombie::advance(int phase)
{
    if (phase != 1) return;  // 过滤非主更新阶段

    // 更新视觉表现
    update();

    // 状态检查：是否已死亡
    // if (hp <= 0) {
    //     handleDeath();
    //     return;
    // }
    if (hp <= 0) // 如果基础僵尸的生命值小于等于0，表示已经被击败
    {
        if (state < 2) // 如果基础僵尸的状态小于2，表示处于死亡状态
        {
            state = 2; // 将状态设置为2（死亡）
            setMovie(":/new/prefix1/ZombieDie.gif"); // 设置基础僵尸的死亡动画
            setHead(":/new/prefix1/ZombieHead.gif"); // 设置基础僵尸的头部掉落动画
        }
        else if (mQMovie->currentFrameNumber() == mQMovie->frameCount() - 1)
            delete this; // 如果基础僵尸的死亡动画播放完毕，删除基础僵尸对象
        return;
    }





    // 检测前方是否有植物
    if (checkCollisionWithPlant()) {
        attackPlant();
        return;
    }

    // 没有障碍物时继续移动
    if (state != 0) {
        state = 0;  // 切换到行走状态
        setMovie(":/new/prefix1/ZombieWalk1.gif");
    }

    // 更新位置（向左移动）
    moveForward();
}

bool basiczombie::checkCollisionWithPlant() const
{
    // 获取碰撞项列表并检查是否包含植物
    QList<QGraphicsItem*> items = collidingItems(Qt::IntersectsItemShape);
    for (auto item : items) {
        // 先判断是否为植物类型
        if (item->type() != plant::Type) {
            continue;
        }
        // 排除地刺（thorn），允许其他植物被检测
        plant* targetPlant = qgraphicsitem_cast<plant*>(item);
        if (targetPlant && typeid(*targetPlant) != typeid(thorn)) {
            return true; // 检测到非地刺植物，返回碰撞
        }
    }
    return false;
}

void basiczombie::attackPlant()
{
    // 获取首个碰撞的植物并造成伤害
    QList<QGraphicsItem*> items = collidingItems();
    if (!items.isEmpty()) {
        plant* target = qgraphicsitem_cast<plant*>(items[0]);
        if (target && typeid(*target) != typeid(thorn)) {
            target->hp -= atk; // 造成伤害
            // 切换到攻击动画（如果当前不是攻击状态）
            if (state != 1) {
                state = 1;
                setMovie(":/new/prefix1/ZombieAttack.gif"); // 根据僵尸类型调整动画路径
            }
            return; // 找到第一个目标后攻击，退出循环
        }
    }
}

void basiczombie::handleDeath()
{
    // 处理僵尸死亡逻辑
    if (state < 2) {
        state = 2;  // 设置为死亡状态
        setMovie(":/new/prefix1/ZombieDie.gif");
        setHead(":/new/prefix1/ZombieHead.gif");
    }
    else if (mQMovie->currentFrameNumber() == mQMovie->frameCount() - 1) {
        delete this;        // 动画结束后安全删除
    }
    return;
}

void basiczombie::moveForward()
{
    // 更新位置
    setX(x() - speed);
}

int basiczombie::getHp() const
{
    return hp;
}

int basiczombie::getAtk() const
{
    return atk;
}
qreal basiczombie::getSPD() const
{
    return speed;
}
