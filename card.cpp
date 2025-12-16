#include "card.h"
#include "shop.h"

// 定义静态常量映射，存储植物名称和对应的索引
const QMap<QString, int> card::map = {
    {"SunFlower", 0},
    {"Peashooter", 1},
    {"CherryBomb", 2},
    {"Chomper", 3},
    {"SnowPea", 4},
    {"PotatoMine", 5},
    {"Repeater", 6},
    {"WallNut", 7},
    {"chilipepper", 8},
    {"Thorn", 9} // 地刺的索引
};

// 定义静态常量向量，存储所有植物的名称
const QVector<QString> card::name = {
    "SunFlower",
    "Peashooter",
    "CherryBomb",
    "Chomper",
    "SnowPea",
    "PotatoMine",
    "Repeater",
    "WallNut",
    "chilipepper",
    "Thorn"
};

// 定义静态常量向量，存储每种植物的成本
const QVector<int> card::cost = {50, 100, 150, 50, 175, 25, 200, 75, 50, 100};

// 定义静态常量向量，存储每种植物卡片的冷却时间
const QVector<int> card::cool = {227, 227, 606, 100, 227, 606, 227, 227, 100, 227};

// 卡片类的构造函数，初始化卡片文本和计数器
card::card(QString cardText) {
    text = cardText;
    counter = 0;
}

// 重写 boundingRect 函数，返回卡片的边界矩形
QRectF card::boundingRect() const {
    return QRectF(-50, -30, 100, 60);
}

// 重写 paint 函数，绘制卡片的外观
void card::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // 缩放绘制比例
    painter->scale(0.6, 0.58);

    // 绘制卡片背景
    painter->drawPixmap(QRect(-50, -70, 100, 140), QPixmap(":/new/prefix1/Card.png"));

    // 绘制卡片上的植物图标
    painter->drawPixmap(QRect(-35, -42, 70, 70), QPixmap(":/new/prefix1/" + text + ".png"));

    // 设置字体并绘制植物成本
    QFont cardFont;
    cardFont.setPointSizeF(15);
    painter->setFont(cardFont);
    painter->drawText(-30, 60, QString().sprintf("%3d", cost[map[text]]));

    // 如果卡片处于冷却状态，绘制半透明遮罩
    if (counter < cool[map[text]]) {
        QBrush maskBrush(QColor(0, 0, 0, 200));
        painter->setBrush(maskBrush);
        painter->drawRect(QRectF(-48, -68, 98, 132 * (1 - qreal(counter) / cool[map[text]])));
    }
    else {
        shop *sh = qgraphicsitem_cast<shop *>(scene()->items(QPointF(300, 15))[0]);
        if(sh->sunnum < cost[map[text]]){
            QBrush maskBrush(QColor(0, 0, 0, 200));
            painter->setBrush(maskBrush);
            painter->drawRect(QRectF(-48, -68, 98, 132));
        }

    }
}

// 重写 advance 函数，处理卡片的更新逻辑
void card::advance(int phase) {
    if (!phase) {
        return;
    }
    update();
    if (counter < cool[map[text]]) {
        counter++;
    }
}

// 重写鼠标按下事件处理函数
void card::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    // 如果卡片处于冷却状态或者阳光不足，拒绝事件
    if (counter < cool[map[text]] || cost[map[text]] > qgraphicsitem_cast<shop*>(parentItem())->sunnum) {
        event->setAccepted(false);
    }
    setCursor(Qt::ArrowCursor);
}

// 重写鼠标移动事件处理函数，处理卡片的拖拽操作
void card::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    // 检查鼠标移动距离是否超过系统设定的拖拽阈值
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length() < QApplication::startDragDistance()) {
        return;
    }

    // 创建拖拽对象和数据对象
    QDrag* dragAction = new QDrag(event->widget());
    QMimeData* dragData = new QMimeData;

    // 加载植物图标并设置拖拽数据
    QImage plantImage(":/new/prefix1/" + text + ".png");
    dragData->setText(text);
    dragData->setImageData(plantImage);
    dragAction->setMimeData(dragData);
    dragAction->setPixmap(QPixmap::fromImage(plantImage));
    dragAction->setHotSpot(QPoint(35, 35));

    // 执行拖拽操作
    dragAction->exec();
    setCursor(Qt::ArrowCursor);
}

// 重写鼠标释放事件处理函数
void card::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    Q_UNUSED(event);
    setCursor(Qt::ArrowCursor);
}
