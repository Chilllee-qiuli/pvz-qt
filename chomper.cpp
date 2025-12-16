#include "chomper.h"
#include "zombie.h"

chomper::chomper()
{
    hp = 400;
    atk = 1800;
    currentState = STATE_INITIAL;
    chewCounter = 0;
    setMovie(":/new/prefix1/Chomper_init.gif");  // 初始状态的动画
}


QRectF chomper::boundingRect() const
{
    return plant::boundingRect();
}

void chomper::advance(int phase)
{
    if (!phase)
        return;
    update();

    if (hp <= 0)
    {
        delete this;
        return;
    }

    switch (currentState)
    {
    case STATE_INITIAL:
    {
        QList<QGraphicsItem *> items = collidingItems();
        foreach (QGraphicsItem *item, items)
        {
            zombie *zom = qgraphicsitem_cast<zombie*>(item);
            if (zom)
            {
                currentState = STATE_ATTACKING;
                setMovie(":/new/prefix1/ChomperAttack.gif");  // 攻击状态的动画
                zom->hp -= atk;
                if (zom->hp <= 0)
                {
                    //delete zom;
                    // 这里简单粗暴直接把delete语句删了，现在还不明确qt会不会自然释放内存
                    // 但是如果目前不删除，会有非常莫名其妙的bug
                     zom->setMovie(":/new/prefix1/Burn.gif");
                    currentState = STATE_CHEWING;
                    setMovie(":/new/prefix1/ChomperDigest.gif");  // 嚼僵尸状态的动画
                    chewCounter = 0;
                }
                return;
            }
        }
        break;
    }
    case STATE_CHEWING:
    {
        if (++chewCounter >= CHEW_TIME)
        {
            currentState = STATE_INITIAL;
            setMovie(":/new/prefix1/Chomper_init.gif");  // 回到初始状态
        }
        break;
    }
    case STATE_ATTACKING:
    {
        QList<QGraphicsItem *> items = collidingItems();
        foreach (QGraphicsItem *item, items)
        {
            zombie *zom = qgraphicsitem_cast<zombie*>(item);
            if (zom && zom->hp <= 0)
            {
                currentState = STATE_CHEWING;
                setMovie(":/new/prefix1/ChomperDigest.gif");  // 嚼僵尸状态的动画
                chewCounter = 0;
            }
        }
        break;
    }
    }
}

bool chomper::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);
    return other->type() == zombie::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 30;
}


QString chomper::getInfo() const
{
    // QString s = QString("血量值：%d ,攻击值: %d ").arg(atk) .arg(hp);
        QString s = QString("血量值：%1 ,攻击值: %2 ").arg(hp) .arg(atk);
    return s;
}
