#include "flagzombie.h"
#include "thorn.h"
#include "zombieshow.h"
#include <typeinfo>

FlagZombie::FlagZombie()
{
    // 设置旗帜僵尸属性（可根据需求调整）
    hp = 270;  // 和普通僵尸相同血量
    atk = 100 * 33 / 1000;  // 攻击频率同普通僵尸
    speed = 30.0 * 33 / 1000;  // 移动速度同普通僵尸
    setMovie(":/new/prefix1/FlagZombieWalk.gif");  // 旗帜僵尸行走动画
}

void FlagZombie::advance(int phase)
{
    if (!phase)
        return;
    update();

    // 死亡处理逻辑
    if (hp <= 0)
    {
        if (state < 2)
        {
            state = 2;
            // 使用zombieshow统一处理死亡动画
            ZombieShow::playDeathAnimation(this);
        }
        else if (mQMovie->currentFrameNumber() == mQMovie->frameCount() - 1)
            delete this;
        return;
    }

    // 碰撞检测与攻击逻辑
    if (checkCollisionWithPlant()) {
        attackPlant();
        return;
    }

    // 移动状态处理
    if (state != 0) {
        state = 0;
        setMovie(":/new/prefix1/FlagZombieWalk.gif");
    }

    moveForward();
}

bool FlagZombie::checkCollisionWithPlant() const
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

void FlagZombie::attackPlant()
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
                // 使用zombieshow统一处理攻击动画
                ZombieShow::playAttackAnimation(this);
            }
            return; // 找到第一个目标后攻击，退出循环
        }
    }
}

void FlagZombie::handleDeath()
{
    // 处理僵尸死亡逻辑
    if (state < 2) {
        state = 2;  // 设置为死亡状态
        // 使用zombieshow统一处理死亡动画
        ZombieShow::playDeathAnimation(this);
    }
    else if (mQMovie->currentFrameNumber() == mQMovie->frameCount() - 1) {
        delete this;        // 动画结束后安全删除
    }
    return;
}

void FlagZombie::moveForward()
{
    // 更新位置
    setX(x() - speed);
}

int FlagZombie::getHp() const
{
    return hp;
}

int FlagZombie::getAtk() const
{
    return atk;
}

qreal FlagZombie::getSPD() const
{
    return speed;
}
