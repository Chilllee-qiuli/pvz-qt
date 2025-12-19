#include "plant_card_widget.h"
#include <QPixmap>
#include <QStyle>


PlantCardWidget::PlantCardWidget(const PlantMeta& meta, QWidget* parent)
    : QFrame(parent), m_meta(meta) {

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(92, 118);


    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(8, 8, 8, 6);
    root->setSpacing(4);
    root->addWidget(m_icon, 0, Qt::AlignCenter);

    m_icon = new QLabel(this);
    m_icon->setAlignment(Qt::AlignCenter);
    m_icon->setFixedSize(70, 58);

    const QString iconPath = meta.cardIconPath.isEmpty() ? meta.portraitPath : meta.cardIconPath;
    QPixmap pix(iconPath);
    if (!pix.isNull()) {
        m_icon->setPixmap(pix.scaled(m_icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    m_cost = new QLabel(QString::number(meta.cost), this);
    m_cost->setObjectName("CardCost");
    m_cost->setAlignment(Qt::AlignCenter);

    auto *bottom = new QHBoxLayout();
bottom->setContentsMargins(0, 0, 0, 0);
bottom->setSpacing(0);
bottom->addWidget(m_cost, 0, Qt::AlignLeft | Qt::AlignBottom);
bottom->addStretch(1);

root->addLayout(bottom);

    setChecked(false);
    setLocked(!meta.unlocked);
}

void PlantCardWidget::setChecked(bool on) {
    setProperty("checked", on);
    style()->unpolish(this);
    style()->polish(this);
    update();
}

void PlantCardWidget::setLocked(bool locked) {
    setProperty("locked", locked);
    setEnabled(!locked);
    style()->unpolish(this);
    style()->polish(this);
    update();
}

void PlantCardWidget::mousePressEvent(QMouseEvent* e) {
    if (e->button() == Qt::LeftButton && isEnabled()) emit clicked(m_meta.id);
    QFrame::mousePressEvent(e);
}
