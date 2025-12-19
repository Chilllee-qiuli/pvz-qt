#include "bgmmanager.h"
#include <QUrl>
#include <QDebug>

BgmManager::BgmManager(QObject* parent) : QObject(parent) {}

BgmManager& BgmManager::instance()
{
    static BgmManager ins;
    return ins;
}

void BgmManager::play(const QString& resPath, bool loop)
{
    if (!player) {
        player = new QMediaPlayer(this);
        playlist = new QMediaPlaylist(this);
        player->setPlaylist(playlist);
    }

    player->stop();
    playlist->clear();
    playlist->setPlaybackMode(loop ? QMediaPlaylist::Loop : QMediaPlaylist::CurrentItemOnce);

    QUrl url(resPath); // 你现在传的是 "qrc:/new/prefix2/xxx.wav" 这种，OK
    if (!url.isValid()) {
        qWarning() << "无效的音乐资源路径:" << resPath;
        return;
    }

    playlist->addMedia(url);
    player->play();
}

void BgmManager::stop()
{
    if (player) player->stop();
}
