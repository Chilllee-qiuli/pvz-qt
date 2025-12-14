#include "shovel.h"
#include "plant.h"

// 铲子类实现

shovel::shovel()
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

QRectF shovel::boundingRect() const
{
    return QRectF(-35, -35, 70, 70);
}

void shovel::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // 绘制铲子背景和图标
    painter->drawPixmap(boundingRect().toRect(), QPixmap(":/new/prefix1/ShovelBank.png"));
    painter->drawPixmap(boundingRect().adjusted(5, 5, -5, -5).toRect(), QPixmap(":/new/prefix1/Shovel.png"));
}

void shovel::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    isDragging = true;
    setCursor(Qt::ClosedHandCursor);
    QGraphicsItem::mousePressEvent(event);
}

void shovel::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (isDragging && (event->buttons() & Qt::LeftButton)) {
        // 创建拖放操作
        QDrag* drag = new QDrag(event->widget());
        QMimeData* mimeData = new QMimeData;
        mimeData->setText("shovel");

        drag->setMimeData(mimeData);
        drag->setPixmap(QPixmap(":/new/prefix1/Shovel.png").scaled(60, 60));
        drag->setHotSpot(QPoint(30, 30));

        drag->exec(Qt::CopyAction);
        isDragging = false;
        setCursor(Qt::ArrowCursor);
    }
}

void shovel::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    isDragging = false;
    setCursor(Qt::ArrowCursor);
    QGraphicsItem::mouseReleaseEvent(event);
}

void shovel::removePlant(const QPointF& position)
{
    // 查找并移除指定位置的植物
    const auto items = scene()->items(position);
    for (QGraphicsItem* item : items) {
        if (item->type() == plant::Type) {
            delete item;
            break;
        }
    }
}
