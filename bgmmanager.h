#pragma once
#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class BgmManager : public QObject
{
    Q_OBJECT
public:
    static BgmManager& instance();

    void play(const QString& resPath, bool loop = true);
    void stop();

private:
    explicit BgmManager(QObject* parent = nullptr);
    QMediaPlayer* player = nullptr;
    QMediaPlaylist* playlist = nullptr;
};
