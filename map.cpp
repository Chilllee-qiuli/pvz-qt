#include "map.h"
#include "shop.h"
#include "shovel.h"
#include <QGraphicsScene>
#include <QMimeData>

Map::Map()
{
    dragover=false;
    setAcceptDrops(true);
}

QRectF Map::boundingRect() const
{
    return QRectF(-369, -235, 738, 470);
}
void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)

}

void Map::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if(event->mimeData()->hasText())
    {
        dragover=false;
        setAcceptDrops(true);
    }
    else
    {
        setAcceptDrops(false);
    }

}
void Map::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    dragover=false;
}
void Map::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    dragover=true;
    if(event->mimeData()->hasText())
    {
        QString s=event->mimeData()->text().toUtf8();
        QPointF scenePos = mapToScene(event->pos());

        QPointF snapped;
        if (!snapToGridFromScenePos(scenePos, snapped)) {
            update();
            return;
        }

        if(s=="shovel")
        {
            if (shovel* sho = findShovel()) {
                sho->removePlant(snapped);
            }
        }
        else
        {
            if (shop* sh = findShop()) {
                // 拖拽继续用旧接口，不影响你原来的行为
                sh->addPlant(s, snapped);
            }
        }
    }
    update();
}

void Map::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        event->ignore();
        return;
    }

    shop* sh = findShop();
    if (!sh) {
        event->ignore();
        return;
    }

    // 这里要求你 shop 里有“选中卡片”的状态（你之前已经做过 selectedPlant/hasSelection）
    if (!sh->hasSelection()) {
        event->ignore();
        return;
    }

    QPointF scenePos = mapToScene(event->pos());

    QPointF snapped;
    if (!snapToGridFromScenePos(scenePos, snapped)) {
        event->ignore();
        return;
    }

    // 种植
    sh->addPlant(sh->selectedPlant(), snapped);

    // 放下后取消选中（像原版）
    sh->clearSelection();

    event->accept();
}

shop* Map::findShop() const
{
    if (!scene()) return nullptr;
    for (QGraphicsItem* it : scene()->items()) {
        if (auto* sh = qgraphicsitem_cast<shop*>(it)) return sh;
    }
    return nullptr;
}

shovel* Map::findShovel() const
{
    if (!scene()) return nullptr;
    for (QGraphicsItem* it : scene()->items()) {
        if (auto* sv = qgraphicsitem_cast<shovel*>(it)) return sv;
    }
    return nullptr;
}

bool Map::snapToGridFromScenePos(const QPointF& scenePos, QPointF& snappedScenePos) const
{
    QPointF pos = scenePos;

    // 先算出 row/col，做边界过滤（否则点到草坪外也会被吸到第0行/第0列）
    int col = (int(pos.x()) - 245) / 85;
    int row = (int(pos.y()) - 80)  / 95;

    if (col < 0 || col >= 9 || row < 0 || row >= 5) return false;

    // 完全复用原来的判定/吸附方式
    pos.setX(col * 85 + 290);
    pos.setY(row * 95 + 120);

    snappedScenePos = pos;
    return true;
}


