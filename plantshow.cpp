#include "plantshow.h"
#include "ui_plantshow.h"
#include <QGraphicsPixmapItem>
#include "startpage.h"


PlantShow::PlantShow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PlantShow)
{
    ui->setupUi(this);
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

