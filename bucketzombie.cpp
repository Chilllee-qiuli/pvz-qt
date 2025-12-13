#include "bucketzombie.h"

BucketZombie::BucketZombie()
{
    hp = 1370;
    atk = 100 * 33 / 1000;
    speed = 120.0 * 33 / 1000 / 4.7;
    setMovie(":/new/prefix1/BucketZombieWalk.gif");
}


void BucketZombie::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (hp <= 0)
    {
        if (state < 2)
        {
            state = 2;
            setMovie(":/new/prefix1/ZombieDie.gif");
            setHead(":/new/prefix1/ZombieHead.gif");
        }
        else if (mQMovie->currentFrameNumber() == mQMovie->frameCount() - 1)
            delete this;
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

int BucketZombie::getHp() const
{
    return hp;
}

int BucketZombie::getAtk() const
{
    return atk;
}
qreal BucketZombie::getSPD() const
{
    return speed;
}
