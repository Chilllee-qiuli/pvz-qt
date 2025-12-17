#include "pausebutton.h"
#include "game.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "startpage.h"

PauseButton::PauseButton(game* gamePtr)
    : m_gamePtr(gamePtr), m_isHovered(false)
{
    setAcceptHoverEvents(true);
}

QRectF PauseButton::boundingRect() const
{
    return QRectF(0, 0, 60, 60);
}

void PauseButton::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (m_isHovered) {
        painter->fillRect(boundingRect(), QColor(100, 150, 200, 200));
    } else {
        painter->fillRect(boundingRect(), QColor(70, 120, 170, 180));
    }

    painter->setPen(QPen(Qt::white, 2));
    painter->drawRect(boundingRect());

    painter->setPen(Qt::white);
    QFont font;
    font.setPointSize(10);
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(boundingRect(), Qt::AlignCenter, "Pause");
}

void PauseButton::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);

    if (!m_gamePtr) {
        return;
    }

    if (m_gamePtr->mQTimer) {
        m_gamePtr->mQTimer->stop();
    }

    PauseDialog pauseDialog;
    pauseDialog.setGamePointer(m_gamePtr);
    pauseDialog.exec();

    if (m_gamePtr->mQTimer) {
        m_gamePtr->mQTimer->start(33);
    }
}

void PauseButton::setGamePointer(game* gamePtr)
{
    m_gamePtr = gamePtr;
}

PauseDialog::PauseDialog(QWidget* parent)
    : QDialog(parent), m_gamePtr(nullptr)
{
    setWindowTitle("游戏暂停");
    setWindowModality(Qt::ApplicationModal);
    setFixedSize(300, 150);
    setStyleSheet("background-color: #f0f0f0;");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* tipLabel = new QLabel("游戏已暂停");
    tipLabel->setAlignment(Qt::AlignCenter);
    QFont tipFont;
    tipFont.setPointSize(14);
    tipFont.setBold(true);
    tipLabel->setFont(tipFont);
    mainLayout->addWidget(tipLabel);

    QHBoxLayout* btnLayout = new QHBoxLayout();

    QPushButton* resumeBtn = new QPushButton("继续游戏");
    resumeBtn->setFixedSize(100, 40);
    resumeBtn->setStyleSheet(
        "QPushButton { background-color: #4CAF50; color: white; border: none; border-radius: 5px; font-weight: bold; }"
        "QPushButton:hover { background-color: #45a049; }"
    );
    connect(resumeBtn, &QPushButton::clicked, this, &PauseDialog::onResumeClicked);
    btnLayout->addWidget(resumeBtn);

    QPushButton* quitBtn = new QPushButton("退出游戏");
    quitBtn->setFixedSize(100, 40);
    quitBtn->setStyleSheet(
        "QPushButton { background-color: #f44336; color: white; border: none; border-radius: 5px; font-weight: bold; }"
        "QPushButton:hover { background-color: #da190b; }"
    );
    connect(quitBtn, &QPushButton::clicked, this, &PauseDialog::onQuitClicked);
    btnLayout->addWidget(quitBtn);

    mainLayout->addLayout(btnLayout);
}

void PauseDialog::setGamePointer(game* gamePtr)
{
    m_gamePtr = gamePtr;
}

void PauseDialog::onResumeClicked()
{
    accept();
}

void PauseDialog::onQuitClicked()
{
    if (m_gamePtr && m_gamePtr->mQTimer) {
        m_gamePtr->mQTimer->stop();
    }
    if (m_gamePtr) {
        m_gamePtr->close(); // 关闭game窗口（会触发析构，释放资源）
    }
    // 打开大厅页面
    startpage* mstartpage = new startpage;
    mstartpage->show();
    reject();
}
