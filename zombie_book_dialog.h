#pragma once

#include <QDialog>
#include <QHash>
#include <QLabel>
#include <QMovie>
#include <QPushButton>
#include <QScrollArea>
#include <QTabWidget>
#include <QTextBrowser>

#include "flow_layout.h"
#include "zombie_card_widget.h"
#include "zombie_registry.h"

class ZombieBookDialog : public QDialog {
    Q_OBJECT
public:
    explicit ZombieBookDialog(QWidget* parent=nullptr);

    void reloadFromRegistry();

private:
    void buildUi();
    void applyQss();
    void rebuildCards(const QVector<ZombieMeta>& zombies);
    void showDetail(const ZombieMeta& meta);

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
    QHash<QString, ZombieCardWidget*> m_cardById;
    QMovie* m_movie = nullptr;

signals:
    void requestBackToStart();
};
