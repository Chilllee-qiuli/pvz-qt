#include "flagzombie.h"

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
            setMovie(":/new/prefix1/ZombieDie.gif");  // 可共用死亡动画
            setHead(":/new/prefix1/ZombieHead.gif");
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
