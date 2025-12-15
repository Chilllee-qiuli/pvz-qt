#ifndef PAUSEBUTTON_H
#define PAUSEBUTTON_H

#include "other.h"
#include <QDialog>
#include <QLabel>

class game; // 前向声明

class PauseButton : public other
{
public:
    PauseButton(game* gamePtr = nullptr);
    ~PauseButton() override = default;

    // QGraphicsItem 接口实现
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    // 事件处理
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    // 设置游戏指针
    void setGamePointer(game* gamePtr);

private:
    game* m_gamePtr;
    bool m_isHovered;
};

// 暂停对话框
class PauseDialog : public QDialog
{
    Q_OBJECT
public:
    PauseDialog(QWidget* parent = nullptr);
    void setGamePointer(game* gamePtr);

private slots:
    void onResumeClicked();
    void onQuitClicked();

private:
    game* m_gamePtr;
};

#endif // PAUSEBUTTON_H