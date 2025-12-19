#include "plantshow.h"
#include "ui_plantshow.h"
#include <QGraphicsPixmapItem>
#include "startpage.h"
#include <QFile>

// #include "peashot.h"
// #include "sunflower.h"
// #include "wallnut.h"


// void PlantShowWidget::initPlantData() {
//     // 1. 豌豆射手（攻击类）
//     PlantInfo peaInfo;
//     peaInfo.name = "豌豆射手";
//     peaInfo.hp = peashot::DEFAULT_HP;  // 从 PeaShot 类获取默认血量（需你项目中定义）
//     peaInfo.atk = PeaShot::ATTACK;     // 从 PeaShot 类获取攻击力
//     peaInfo.cost = 100;                // 阳光消耗（可从植物类中提取）
//     peaInfo.skill = "每3秒发射1颗豌豆，攻击前方直线上的僵尸，基础攻击型植物。";
//     peaInfo.imagePath = ":/images/plants/peashot.gif";  // 图片路径（建议用 Qt 资源文件 .qrc 管理）
//     peaInfo.category = "攻击类";
//     peaInfo.isUnlocked = true;         // 假设初始解锁
//     m_allPlantInfos.append(peaInfo);

//     // 2. 向日葵（辅助类）
//     PlantInfo sunInfo;
//     sunInfo.name = "向日葵";
//     sunInfo.hp = SunFlower::DEFAULT_HP;
//     sunInfo.atk = 0;  // 无攻击
//     sunInfo.cost = 50;
//     sunInfo.skill = "每24秒产生50点阳光，是种植其他植物的能量来源，辅助型植物。";
//     sunInfo.imagePath = ":/images/plants/sunflower.gif";
//     sunInfo.category = "辅助类";
//     sunInfo.isUnlocked = true;
//     m_allPlantInfos.append(sunInfo);

//     // 3. 坚果墙（防御类）、双发射手等其他植物... 同理添加
// }

// void PlantShowWidget::initModel() {
//     m_plantModel = new QStandardItemModel(this);
//     m_plantModel->setHorizontalHeaderLabels({"植物名称"});  // 列表表头（可选）

//     // 遍历所有植物数据，添加到模型
//     for (const auto &info : m_allPlantInfos) {
//         QStandardItem *item = new QStandardItem(info.name);
//         // 将 PlantInfo 绑定到 item 的 UserRole（方便后续获取）
//         item->setData(QVariant::fromValue(info), Qt::UserRole);
//         // 未解锁的植物设为灰色（可选）
//         if (!info.isUnlocked) {
//             item->setEnabled(false);
//             item->setForeground(Qt::gray);
//         }
//         m_plantModel->appendRow(item);
//     }

//     // 绑定模型到列表
//     m_plantListView->setModel(m_plantModel);
//     m_plantListView->setEditTriggers(QAbstractItemView::NoEditTriggers);  // 禁止编辑列表
// }
// // 在构造函数中连接信号槽
// connect(m_plantListView, &QListView::clicked, this, &PlantShowWidget::updateDetail);

// // 实现更新详情区
// void PlantShowWidget::updateDetail(const QModelIndex &index) {
//     if (!index.isValid()) return;  // 无效索引直接返回

//     // 从列表项中获取 PlantInfo
//     QStandardItem *item = m_plantModel->itemFromIndex(index);
//     PlantInfo info = item->data(Qt::UserRole).value<PlantInfo>();

//     // 1. 更新图片（支持 GIF 动画）
//     if (info.imagePath.endsWith(".gif")) {
//         QMovie *movie = new QMovie(info.imagePath, QByteArray(), this);
//         m_plantImgLabel->setMovie(movie);
//         movie->start();
//         // 调整 GIF 大小（保持比例）
//         movie->setScaledSize(m_plantImgLabel->size() * 0.8);
//     } else {
//         // 静态图片（如 PNG/JPG）
//         QPixmap pix(info.imagePath);
//         if (pix.isNull()) {
//             pix.load(":/images/default_plant.png");  // 加载失败时显示默认图
//         }
//         m_plantImgLabel->setPixmap(pix.scaled(
//             m_plantImgLabel->size() * 0.8,
//             Qt::KeepAspectRatio,
//             Qt::SmoothTransformation  // 平滑缩放
//             ));
//     }

//     // 2. 更新属性面板（先清空原有内容）
//     while (m_attrLayout->rowCount() > 0) {
//         m_attrLayout->removeRow(0);
//     }
//     // 添加属性（键值对形式，QFormLayout 自动对齐）
//     m_attrLayout->addRow("植物名称：", new QLabel(info.name));
//     m_attrLayout->addRow("生命值：", new QLabel(QString::number(info.hp)));
//     m_attrLayout->addRow("攻击力：", new QLabel(info.atk > 0 ? QString::number(info.atk) : "无"));
//     m_attrLayout->addRow("阳光消耗：", new QLabel(QString::number(info.cost)));
//     m_attrLayout->addRow("植物类型：", new QLabel(info.category));
//     // 技能描述支持换行
//     QLabel *skillLabel = new QLabel(info.skill);
//     skillLabel->setWordWrap(true);  // 自动换行
//     m_attrLayout->addRow("技能描述：", skillLabel);

//     // 可选：添加点击音效（复用你项目的 sound 文件夹）
//     QMediaPlayer *player = new QMediaPlayer(this);
//     player->setMedia(QUrl::fromLocalFile("sound/click.wav"));
//     player->play();
// }


PlantShow::PlantShow(QWidget *parent): QDialog(parent), ui(new Ui::PlantShow){
    QFile f(":/plant_book.qss");
    if (f.open(QIODevice::ReadOnly)) {
        this->setStyleSheet(QString::fromUtf8(f.readAll()));
    }
    ui->setupUi(this);
    setStyleSheet(R"(
        PlantShow {
            background-image: url(:/new/prefix1/plant_bg.png); /* 替换为你的背景图路径 */
            background-repeat: no-repeat;
            background-position: center;
            background-size: cover;
        }
    )");
    setFixedSize(800, 600); // 固定窗口大小
    // 设置全局字体（避免系统字体混乱）
    this->setStyleSheet(R"(
    /* 1. 主窗口背景（用 PVZ 风格的淡绿色） */
    PlantShowWidget {
        background-color: #f0f8e8;
        font-family: "Microsoft YaHei", Arial;
    }

    /* 2. 左侧列表容器（圆角+轻微阴影） */
    #leftWidget {
        background-color: white;
        border-radius: 8px;
        box-shadow: 0 2px 6px rgba(0, 0, 0, 0.1);
        margin: 10px;
        padding: 10px;
    }

    /* 3. 分类筛选框和搜索框（统一风格） */
    QComboBox, QLineEdit {
        border: 1px solid #d0d8c8;
        border-radius: 4px;
        padding: 6px 10px;
        margin-bottom: 8px;
        font-size: 12px;
    }
    QComboBox:focus, QLineEdit:focus {
        border-color: #8db654;  /* PVZ 绿色高亮 */
        outline: none;
    }

    /* 4. 列表项样式（选中时高亮） */
    QListView {
        border: none;
        font-size: 13px;
    }
    QListView::item {
        height: 30px;
        border-radius: 4px;
        padding-left: 10px;
    }
    QListView::item:selected {
        background-color: #8db654;  /* 选中色：PVZ 绿色 */
        color: white;
    }
    QListView::item:disabled {
        color: #b8b8b8;  /* 未解锁项：灰色 */
    }

    /* 5. 右侧详情容器（圆角+阴影，白色背景突出内容） */
    #rightWidget {
        background-color: white;
        border-radius: 8px;
        box-shadow: 0 2px 8px rgba(0, 0, 0, 0.15);
        margin: 10px;
        padding: 20px;
    }

    /* 6. 属性面板样式（键值对对齐，标签加粗） */
    QFormLayout QLabel:first-child {
        color: #333333;
        font-weight: bold;
        font-size: 13px;
        min-width: 80px;
    }
    QFormLayout QLabel:last-child {
        color: #666666;
        font-size: 12px;
    }

    /* 7. 图片标签（加轻微边框） */
    #plantImgLabel {
        border: 1px solid #f0f0f0;
        border-radius: 6px;
        margin-bottom: 15px;
        background-color: #fafafa;
    }
)");

    // 注意：需给左侧容器（leftWidget）和右侧容器（rightWidget）在 UI 文件中设置“objectName”为“leftWidget”和“rightWidget”，否则 QSS 无法生效！
}

PlantShow::~PlantShow()
{
    delete ui;
}

void PlantShow::showPlantInfo(plant* plant, const QString& plantName)
{
    if (plant) {
        QString info = QString("这是%1，%2").arg(plantName).arg(plant->getInfo());
        ui->textBrowser->setText(info);
    }
}

void setupScaledBackground(QGraphicsView* view, const QString& imagePath, Qt::AspectRatioMode aspectRatioMode = Qt::KeepAspectRatio){
    if(!view) return;

    QGraphicsScene* scene = new QGraphicsScene(view);
    view->setScene(scene);

    // 加载背景图片
    QPixmap background(imagePath);
    if (!background.isNull()) {
        // 配置视图
        view->setRenderHint(QPainter::SmoothPixmapTransform);
        view->setAlignment(Qt::AlignCenter);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        // 设置场景大小为视图大小
        scene->setSceneRect(view->rect());

        // 伸展图片以适应场景
        QGraphicsPixmapItem* backgroundItem = scene->addPixmap(background.scaled(
            view->size(),
            aspectRatioMode,
            Qt::SmoothTransformation
            ));
        backgroundItem->setPos(0, 0);
    } else {
        // 图片加载失败时设置纯色背景
        scene->setBackgroundBrush(Qt::lightGray);
    }
}








void PlantShow::on_pushButton_clicked()
{
    setupScaledBackground(ui->graphicsView, ":/new/prefix1/SunFlower.png", Qt::IgnoreAspectRatio);
    sunflower* plant = new sunflower();
    showPlantInfo(plant, "向日葵");
    delete plant;
}


void PlantShow::on_pushButton_4_clicked()
{
    setupScaledBackground(ui->graphicsView, ":/new/prefix1/WallNut.png", Qt::IgnoreAspectRatio);

    wallnut* plant = new wallnut();
    showPlantInfo(plant, "坚果墙");
    delete plant;
}


void PlantShow::on_pushButton_9_clicked()
{
    setupScaledBackground(ui->graphicsView, ":/new/prefix1/Chomper.png", Qt::IgnoreAspectRatio);
    chomper* plant = new chomper();
    showPlantInfo(plant, "大嘴花");
    delete plant;
}


void PlantShow::on_pushButton_2_clicked()
{
    setupScaledBackground(ui->graphicsView, ":/new/prefix1/chilipepper.png", Qt::IgnoreAspectRatio);
    chilipepper* plant = new chilipepper();
    showPlantInfo(plant, "辣椒炸弹");
    delete plant;
}


void PlantShow::on_pushButton_5_clicked()
{
    setupScaledBackground(ui->graphicsView, ":/new/prefix1/Peashooter.png", Qt::IgnoreAspectRatio);
    pea* plant = new pea();
    showPlantInfo(plant, "豌豆射手");
    delete plant;
}


void PlantShow::on_pushButton_10_clicked()
{
    setupScaledBackground(ui->graphicsView, ":/new/prefix1/PotatoMine.png", Qt::IgnoreAspectRatio);
    potato* plant = new potato();
    showPlantInfo(plant, "土豆地雷");
    delete plant;
}


void PlantShow::on_pushButton_3_clicked()
{
    setupScaledBackground(ui->graphicsView, ":/new/prefix1/SnowPea.png", Qt::IgnoreAspectRatio);
    snowpea* plant = new snowpea();
    showPlantInfo(plant, "寒冰射手");
    delete plant;
}


void PlantShow::on_pushButton_6_clicked()
{
    setupScaledBackground(ui->graphicsView, ":/new/prefix1/Repeater.png", Qt::IgnoreAspectRatio);
    // ui->textBrowser->setText("这是连发豌豆射手");
    repeater* plant = new repeater();
    showPlantInfo(plant, "连发豌豆射手");
    delete plant;
}


void PlantShow::on_pushButton_11_clicked()
{
    setupScaledBackground(ui->graphicsView, ":/new/prefix1/CherryBomb.png", Qt::IgnoreAspectRatio);
    ui->textBrowser->setText("这是樱桃炸弹");
    cherry* plant = new cherry();
    showPlantInfo(plant, "樱桃炸弹");
    delete plant;
}

void PlantShow::on_pushButton_thorn_clicked() {
    setupScaledBackground(ui->graphicsView, ":/new/prefix1/Thorn.png", Qt::IgnoreAspectRatio);
    thorn* plant = new thorn();
    showPlantInfo(plant, "地刺");
    delete plant;
}

void PlantShow::on_pushButton_7_clicked()
{
    startpage *mstartpage = new startpage; // 创建开始页面对象
    mstartpage->show(); // 显示开始页面
    this->hide(); // 隐藏当前窗口
}

void PlantShow::showPlant(const QString& plantClassName, const QString& imagePath, const QString& plantName) {
    // 1. 设置植物图片背景
    setupScaledBackground(ui->graphicsView, imagePath, Qt::IgnoreAspectRatio);

    // 2. 创建对应植物实例并获取信息
    plant* p = nullptr;
    if (plantClassName == "sunflower") p = new sunflower();
    else if (plantClassName == "wallnut") p = new wallnut();
    else if (plantClassName == "chomper") p = new chomper();
    else if (plantClassName == "chilipepper") p = new chilipepper();
    else if (plantClassName == "pea") p = new pea();
    else if (plantClassName == "potato") p = new potato();
    else if (plantClassName == "snowpea") p = new snowpea();
    else if (plantClassName == "repeater") p = new repeater();
    else if (plantClassName == "cherry") p = new cherry();
    else if (plantClassName == "thorn") p = new thorn();

    // 3. 显示信息
    if (p) {
        showPlantInfo(p, plantName);
        delete p; // 用完即删，避免内存泄漏
    }
}

