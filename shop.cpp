#include "shop.h"
#include "plantselectionwidget.h"

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

// 返回商店的边界矩形
QRectF shop::boundingRect() const {
    return QRectF(-270, -45, 540, 90);
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

// 添加植物到游戏场景
void shop::addPlant(QString plantType, QPointF position) {
    // 检查目标位置是否已有植物
    QList<QGraphicsItem*> itemsAtPos = scene()->items(position);
    foreach (QGraphicsItem* item, itemsAtPos) {
        if (item->type() == plant::Type) {
            return; // 已有植物，不添加
        }
    }

    // 扣除阳光成本
    sunnum -= card::cost[card::map[plantType]];

    // 创建并添加选中的植物
    plant* newPlant = nullptr;
    switch (card::map[plantType]) {
    case 0: newPlant = new sunflower; break;
    case 1: newPlant = new pea; break;
    case 2: newPlant = new cherry; break;
    case 3: newPlant = new chomper; break;
    case 4: newPlant = new snowpea; break;
    case 5: newPlant = new potato; break;
    case 6: newPlant = new repeater; break;
    case 7: newPlant = new wallnut; break;
    case 8: newPlant = new chilipepper; break;
    }

    if (newPlant) {
        newPlant->setPos(position);
        scene()->addItem(newPlant);

        // 重置对应卡片的冷却时间
        QList<QGraphicsItem*> childItemsList = childItems();
        foreach (QGraphicsItem* childItem, childItemsList) {
            card* plantCard = qgraphicsitem_cast<card*>(childItem);
            if (plantCard && plantCard->text == plantType) {
                plantCard->counter = 0;
            }
        }

        // 重置阳光生成计时器
        // 逻辑：消费后下一颗阳光在 0~5 秒内随机出现
        const int fiveSecondsFrames = int(5.0 * 1000 / 33.0);   // 5 秒对应的帧数
        int remainFrames = QRandomGenerator::global()->bounded(fiveSecondsFrames + 1);
        // remainFrames ∈ [0, fiveSecondsFrames]

        // 让 counter 靠近 time，这样下一次触发 = remainFrames 帧后
        counter = time - remainFrames;
        if (counter < 0) counter = 0;   // 理论上 5 < 7，不会小于 0，保险起见

        // 如果你还想“消费后立刻也刷新一下界面”，可以加一句：
        // update();
    }
}
