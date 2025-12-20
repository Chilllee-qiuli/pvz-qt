#pragma once

#include <QFrame>
#include <QLabel>
#include <QMouseEvent>
#include <QVBoxLayout>
#include "zombie_registry.h"

class ZombieCardWidget : public QFrame {
    Q_OBJECT
public:
    explicit ZombieCardWidget(const ZombieMeta& meta, QWidget* parent=nullptr);

    QString zombieId() const { return m_meta.id; }
    void setChecked(bool on);
    void setLocked(bool locked);

signals:
    void clicked(const QString& zombieId);

protected:
    void mousePressEvent(QMouseEvent* e) override;

private:
    ZombieMeta m_meta;
    QLabel* m_icon = nullptr;
    QLabel* m_tag = nullptr; // 这里显示一个关键属性（默认显示 HP）
};
