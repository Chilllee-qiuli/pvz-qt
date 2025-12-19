#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include "bgmmanager.h"
#include "loading.h"
#include <QGuiApplication>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 进入主界面就播放菜单BGM（Grazy）
    BgmManager::instance().play("qrc:/new/prefix2/Grazy.wav");

    
    // 计算缩放因子：基于屏幕分辨率与1080p的比例
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenHeight = screenGeometry.height();
    
    // 基准分辨率为1080p高度，当前窗口高度为600
    // 缩放因子 = 实际屏幕高度 / 1080
    double scaleFactor = screenHeight / 1080.0;
    // 限制缩放因子在 0.8 到 2.5 之间，避免过小或过大
    if (scaleFactor < 0.8) scaleFactor = 0.8;
    if (scaleFactor > 2.5) scaleFactor = 2.5;
    
    // 根据缩放因子调整窗口大小
    int scaledWidth = static_cast<int>(900 * scaleFactor);
    int scaledHeight = static_cast<int>(600 * scaleFactor);
    
    this->resize(scaledWidth, scaledHeight);
    this->setWindowTitle("PlantsVsZombies");
    this->setWindowIcon(QIcon(":/new/prefix1/WallNut.png")); // 设置窗口图标
    mpainter_1 = new QPainter(this); // 创建 QPainter 对象
    mqtimer = new QTimer(this); // 创建 QTimer 对象
    mqtimer->setInterval(4000); // 设置定时器时间间隔为 4000 毫秒
    mqtimer->start(); // 启动定时器
    connect(mqtimer, &QTimer::timeout, [this]() {
        mqtimer->stop(); // 定时器触发后停止
        loading* load = new loading; // 创建 loading 对象
        load->show(); // 显示 loading 窗口
        this->hide(); // 隐藏当前主窗口
    });
}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *event)
{
    mpainter_1->begin(this); // 开始绘制
    QImage img(":/new/prefix1/init.png"); // 加载图片资源
    mpainter_1->drawImage(QRect(0, 0, this->width(), this->height()), img); // 在主窗口绘制图片
    mpainter_1->end(); // 结束绘制
}


