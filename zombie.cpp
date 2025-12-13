#include "zombie.h"
#include "plant.h"

zombie::zombie()
{
    hp=state=atk=0;
    speed=0.0;
    mQMovie=mhead=nullptr;
}
zombie::~zombie()
{
    delete mQMovie;
    delete mhead;
}
QRectF zombie::boundingRect() const
{
    // 设置僵尸的边界矩形
    return QRectF(-80, -100, 200, 140); // 矩形的左上角坐标为(-80, -100)，宽度为200，高度为140
}

void zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QImage image = mQMovie->currentImage(); // 获取当前帧的图片

    // 如果僵尸的速度小于5.0 * 33 / 1000 且状态不为3（表示僵尸被减速）
    if (speed < 5.0 * 33 / 1000 && state != 3)
    {
        // 设置帧图片的部分像素的颜色为灰色，用于表示僵尸被减速状态
        if (state != 2) // 如果状态不为2（僵尸普通状态），设置帧播放速度为50
            mQMovie->setSpeed(50);
        int w = image.width();
        int h = image.height();
        for (int i = 0; i < h; ++i)
        {
            uchar *line = image.scanLine(i);
            for (int j = 5; j < w - 5; ++j)
                line[j << 2] = 200; // 将帧图片的像素的红色通道设置为200，即变为灰色
        }
    }

    // 在画布上绘制僵尸的帧图片
    painter->drawImage(QRectF(-70, -100, 140, 140), image); // 绘制位置为(-70, -100)，宽度为140，高度为140
    // 如果存在僵尸的头部动画
    if (mhead)
    {
        image = mhead->currentImage(); // 获取头部动画的当前帧图片
        // 如果僵尸的速度小于5.0 * 33 / 1000，表示僵尸被减速
        if (speed < 5.0 * 33 / 1000)
        {
            int w = image.width();
            int h = image.height();

            for (int i = 0; i < h; ++i)
            {
                uchar *line = image.scanLine(i);
                for (int j = 5; j < w - 5; ++j)
                    line[j << 2] = 200; // 设置帧图片的像素的红色通道为200，即变为灰色
            }
        }
        // 在画布上绘制僵尸的头部帧图片
        painter->drawImage(QRectF(0, -100, 140, 140), image); // 绘制位置为(0, -100)，宽度为140，高度为140
    }
}

bool zombie::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode)

    // 当僵尸和植物碰撞时，返回true
    return other->type() == plant::Type && qFuzzyCompare(other->y(), y()) && qAbs(other->x() - x()) < 30;
}

void zombie::setMovie(QString path)
{
    if (mQMovie)
        delete mQMovie; // 删除原有的动画对象

    mQMovie = new QMovie(path); // 创建新的动画对象
    mQMovie->start(); // 启动动画
}

void zombie::setHead(QString path)
{
    if (mhead)
        delete mhead; // 删除原有的头部动画对象

    mhead = new QMovie(path); // 创建新的头部动画对象
    mhead->start(); // 启动头部动画
}

int zombie::type() const
{
    return Type; // 返回僵尸的类型
}





bool zombie::checkCollisionWithPlant() const
{
    // 获取碰撞项列表并检查是否包含植物
    QList<QGraphicsItem*> items = collidingItems(Qt::IntersectsItemShape);
    for (auto item : items) {
        if (item->type() == plant::Type) {
            return true;
        }
    }
    return false;
}

void zombie::attackPlant()
{
    // 获取首个碰撞的植物并造成伤害
    QList<QGraphicsItem*> items = collidingItems();
    if (!items.isEmpty()) {
        plant* target = qgraphicsitem_cast<plant*>(items[0]);
        if (target) {
            target->hp -= atk;

            // 切换到攻击动画
            if (state != 1) {
                state = 1;
                setMovie(":/new/prefix1/ZombieAttack.gif");
            }
        }
    }
}

void zombie::handleDeath()
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



void zombie::moveForward()
{
    // 更新位置
    setX(x() - speed);
}

