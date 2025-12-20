#include "sun.h"
#include "shop.h"
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsScene>
#include <QTimer>


sun::sun()
{
    setAcceptHoverEvents(true);
    dest=QPoint(200+qrand()%200,200+qrand()%200);
    setPos(QPointF(dest.x(), 70));
    speed = 60.0 * 50 / 1000;
    counter = 0;
    time = int(10.0 * 1000 / 33);
    movie = new QMovie(":/new/prefix1/Sun.gif");
    movie->start();
    setAcceptedMouseButtons(Qt::LeftButton);
}
sun::sun(QPointF pos)
{
    setAcceptHoverEvents(true);
    dest = QPointF(pos.x() + qrand() % 30, pos.y() + qrand() % 30);
    setPos(QPointF(dest.x(), pos.y()));
    speed = 60 * 50 / 1000;
    counter = 0;
    time = int(10.0 * 1000 / 33);
    movie = new QMovie(":/new/prefix1/Sun.gif");
    movie->start();
    setAcceptedMouseButtons(Qt::LeftButton);
}

sun::~sun()
{
    if (movie)
        delete movie;
}
QRectF sun::boundingRect() const
{
    return QRectF(-35,-35,70,70);
}
void sun::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawImage(boundingRect(),movie->currentImage());
}
static shop* findShopInScene(QGraphicsScene* scene)
{
    for (QGraphicsItem* it : scene->items()) {
        if (shop* sh = qgraphicsitem_cast<shop*>(it)) return sh;
    }
    return nullptr;
}

void sun::collectOnce()
{
    if (collected) return;
    collected = true;

    if (shop* sh = findShopInScene(scene())) {
        sh->sunnum += 25;
    }

    scheduleDestroy();   // 收集后走统一销毁流程
}


void sun::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    collectOnce(); // ✅点击也能收（可保留）
    event->setAccepted(true);
}

void sun::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event)
    collectOnce(); // ✅鼠标碰到就收
}
void sun::advance(int phase)
{
    if (!phase) return;
    if (pendingDelete) return; // ✅已经安排销毁就别再动了

    update();

    if (++counter >= time) {
        collected = true;  // 可选：语义上标记过期
        scheduleDestroy();
        return;
    } else if (y() < dest.y()) {
        setY(y() + speed);
    }
}
void sun::scheduleDestroy()
{
    if (pendingDelete) return;
    pendingDelete = true;

    setAcceptHoverEvents(false);
    setAcceptedMouseButtons(Qt::NoButton);
    setVisible(false);

    if (scene()) scene()->removeItem(this);

    QTimer::singleShot(0, [this]() {
        delete this;
    });
}

