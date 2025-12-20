#include "shop.h"
#include "plantselectionwidget.h"
// 注意：shop.h 里不再 include card.h（为了解决循环包含），所以这里显式 include
#include "card.h"
#include <QRandomGenerator>

// 商店类实现文件

// 商店类构造函数
shop::shop() {
    // 初始化阳光数量
    sunnum = 200;
    // 初始化计数器和阳光生成时间间隔
    counter = 0;
    time = int(7.0 * 1000 / 33);

    // 显示植物选择对话框
    PlantSelectionWidget selectionWidget(card::name);
    if (selectionWidget.exec() == QDialog::Accepted) {
        // 获取用户选择的植物列表
        QVector<QString> selectedPlants = selectionWidget.getSelectedPlants();

        // 创建并添加选中的植物卡片
        for (int i = 0; i < selectedPlants.size(); ++i) {
            card* plantCard = new card(selectedPlants[i]);
            plantCard->setParentItem(this);
            plantCard->setPos(-157 + 65 * i, -2);
        }
    }
}


// 绘制商店界面
void shop::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // 绘制商店背景
    painter->drawPixmap(QRect(-270, -45, 540, 90), QPixmap(":/new/prefix1/Shop.png"));

    // 设置字体并绘制阳光数量
    QFont displayFont;
    displayFont.setPointSizeF(15);
    painter->setFont(displayFont);
    painter->drawText(QRectF(-255, 18, 65, 22), Qt::AlignCenter, QString::number(sunnum));
}

// 商店更新逻辑
void shop::advance(int phase) {
    if (!phase) {
        return;
    }

    // 更新显示
    update();

    // 阳光生成计时器
    if (++counter >= time) {
        counter = 0;
        // 生成新的阳光
        scene()->addItem(new sun);
    }
}
// ✅新增：选中态接口
void shop::selectPlant(const QString& name) { mSelectedPlant = name; update(); }
void shop::clearSelection() { mSelectedPlant.clear(); update(); }
bool shop::hasSelection() const { return !mSelectedPlant.isEmpty(); }
QString shop::selectedPlant() const { return mSelectedPlant; }

QRectF shop::boundingRect() const { return QRectF(-270, -45, 540, 90); }


// 添加植物到游戏场景
// ✅加固后的 addPlant（防御检查 + 原逻辑）
void shop::addPlant(const QString& plantType, const QPointF& position) {
    if (!card::map.contains(plantType)) return;

    const int idx = card::map[plantType];
    const int needSun = card::cost[idx];
    if (sunnum < needSun) return;

    // 冷却检查：从自己的子卡片里找对应 card
    for (QGraphicsItem* childItem : childItems()) {
        if (card* c = qgraphicsitem_cast<card*>(childItem)) {
            if (c->text == plantType) {
                if (c->counter < card::cool[idx]) return;
                break;
            }
        }
    }

    // 占位检查
    for (QGraphicsItem* item : scene()->items(position)) {
        if (item->type() == plant::Type) return;
    }

    // 扣除阳光成本
    sunnum -= needSun;

    plant* newPlant = nullptr;
    switch (idx) {
    case 0: newPlant = new sunflower; break;
    case 1: newPlant = new pea; break;
    case 2: newPlant = new cherry; break;
    case 3: newPlant = new chomper; break;
    case 4: newPlant = new snowpea; break;
    case 5: newPlant = new potato; break;
    case 6: newPlant = new repeater; break;
    case 7: newPlant = new wallnut; break;
    case 8: newPlant = new chilipepper; break;
    case 9: newPlant = new thorn; break;
    }

    if (!newPlant) return;

    newPlant->setPos(position);
    scene()->addItem(newPlant);

    // 重置对应卡片冷却
    for (QGraphicsItem* childItem : childItems()) {
        if (card* plantCard = qgraphicsitem_cast<card*>(childItem)) {
            if (plantCard->text == plantType) {
                plantCard->counter = 0;
            }
        }
    }

    // 你原来的“消费后下一颗阳光更快出现”的逻辑保留
    const int fiveSecondsFrames = int(4.0 * 1000 / 33.0);
    int remainFrames = QRandomGenerator::global()->bounded(fiveSecondsFrames + 1);
    counter = time - remainFrames;
    if (counter < 0) counter = 0;
}

// ✅给 game.cpp 的 eventFilter 用：成功才返回 true
bool shop::tryAddPlant(const QString& plantType, const QPointF& position)
{
    if (!card::map.contains(plantType)) return false;

    const int idx = card::map[plantType];
    if (sunnum < card::cost[idx]) return false;

    card* foundCard = nullptr;
    for (QGraphicsItem* childItem : childItems()) {
        if (card* c = qgraphicsitem_cast<card*>(childItem)) {
            if (c->text == plantType) { foundCard = c; break; }
        }
    }
    if (!foundCard) return false;
    if (foundCard->counter < card::cool[idx]) return false;

    for (QGraphicsItem* item : scene()->items(position)) {
        if (item->type() == plant::Type) return false;
    }

    addPlant(plantType, position);
    return true;
}
