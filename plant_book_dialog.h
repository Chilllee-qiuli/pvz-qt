#pragma once
#include <QDialog>
#include <QLabel>
#include <QScrollArea>
#include <QTabWidget>
#include <QPushButton>
#include <QTextBrowser>
#include <QMovie>
#include "flow_layout.h"
#include "plant_card_widget.h"
#include "plant_registry.h"

class PlantBookDialog : public QDialog {
    Q_OBJECT
public:
    explicit PlantBookDialog(QWidget* parent=nullptr);

    void reloadFromRegistry(); // 需要时刷新（比如解锁/新增）

private:
    void buildUi();
    void applyQss();
    void rebuildCards(const QVector<PlantMeta>& plants);
    void showDetail(const PlantMeta& meta);

private slots:
    void onCardClicked(const QString& id);

private:
    QFrame* m_headerBar = nullptr;
    QLabel* m_headerTitle = nullptr;

    QScrollArea* m_cardScroll = nullptr;
    QWidget* m_cardPane = nullptr;
    FlowLayout* m_flow = nullptr;

    QFrame* m_detailOuter = nullptr;
    QFrame* m_detailInner = nullptr;
    QFrame* m_portraitFrame = nullptr;
    QLabel* m_portrait = nullptr;
    QLabel* m_name = nullptr;

    QTabWidget* m_tabs = nullptr;
    QTextBrowser* m_introText = nullptr;

    QPushButton* m_close = nullptr;

    QString m_selectedId;
    QHash<QString, PlantCardWidget*> m_cardById;
    QMovie* m_movie = nullptr;
signals:
    void requestBackToStart();
};
