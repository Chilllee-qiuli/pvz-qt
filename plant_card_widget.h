#pragma once
#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include "plant_registry.h"

class PlantCardWidget : public QFrame {
    Q_OBJECT
public:
    explicit PlantCardWidget(const PlantMeta& meta, QWidget* parent=nullptr);

    QString plantId() const { return m_meta.id; }
    void setChecked(bool on);
    void setLocked(bool locked);

signals:
    void clicked(const QString& plantId);

protected:
    void mousePressEvent(QMouseEvent* e) override;

private:
    PlantMeta m_meta;
    QLabel* m_icon = nullptr;
    QLabel* m_cost = nullptr;
};
