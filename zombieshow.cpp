#include "zombieshow.h"
#include "ui_zombieshow.h"
#include "startpage.h"
#include <QGraphicsItem>

ZombieShow::ZombieShow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ZombieShow)
{
    ui->setupUi(this);
}

ZombieShow::~ZombieShow()
{
    delete ui;
}

void ZombieShow::showZombieInfo(zombie* zombie, const QString& zombieName)
{
    if (zombie) {
        QString info = QString("这是%1，血量：%2，攻击值：%3，速度：%4").arg(zombieName).arg(zombie->getHp()).arg(zombie->getAtk()).arg(zombie->getSPD());
        ui->textBrowser->setText(info);
    }
}

void setupScaledBackground1(QGraphicsView* view, const QString& imagePath, Qt::AspectRatioMode aspectRatioMode = Qt::KeepAspectRatio) {
    if (!view) return;

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

void ZombieShow::on_pushButton_sunflower_clicked()
{

    setupScaledBackground1(ui->graphicsView, ":/new/prefix1/zombieshow.png", Qt::IgnoreAspectRatio);
    basiczombie* zombie = new basiczombie();
    showZombieInfo(zombie, "普通僵尸");
    delete zombie;
}


void ZombieShow::on_pushButton_nullwall_clicked()
{

    setupScaledBackground1(ui->graphicsView, ":/new/prefix1/ConeheadZombieshow.png", Qt::IgnoreAspectRatio);
    ConeZombie* zombie = new ConeZombie();
    showZombieInfo(zombie, "路障僵尸");
    delete zombie;
}


void ZombieShow::on_pushButton_peashooter_clicked()
{

    setupScaledBackground1(ui->graphicsView, ":/new/prefix1/footballshow.png", Qt::IgnoreAspectRatio);
    FootballZombie* zombie = new FootballZombie();
    showZombieInfo(zombie, "足球僵尸");
    delete zombie;
}


void ZombieShow::on_pushButton_potato_clicked()
{

    setupScaledBackground1(ui->graphicsView, ":/new/prefix1/BucketheadZombie.png", Qt::IgnoreAspectRatio);
    BucketZombie* zombie = new BucketZombie();
    showZombieInfo(zombie, "铁桶僵尸");
    delete zombie;
}


void ZombieShow::on_pushButton_4_clicked()
{

    setupScaledBackground1(ui->graphicsView, ":/new/prefix1/screenzshow.png", Qt::IgnoreAspectRatio);
    ScreenZombie* zombie = new ScreenZombie();
    showZombieInfo(zombie, "铁丝网僵尸");
    delete zombie;
}


void ZombieShow::on_pushButton_clicked()
{
    startpage *mstartpage = new startpage; // 创建开始页面对象
    mstartpage->show(); // 显示开始页面
    this->hide(); // 隐藏当前窗口
}


