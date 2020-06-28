#include "audioplayer.h"
#include <QDir>
#include <QMediaPlayer>
#include <QMediaPlaylist>

AudioPlayer::AudioPlayer(QObject *parent)
    : QObject(parent)
    , m_backgroundMusic(NULL)
{

    QUrl backgroundMusicUrl = QUrl("qrc:/new/prefix3/res/BGM.mp3");

        m_backgroundMusic = new QMediaPlayer(this);
        QMediaPlaylist *backgroundMusicList = new QMediaPlaylist();

        QMediaContent media(backgroundMusicUrl);
        backgroundMusicList->addMedia(media);
        backgroundMusicList->setCurrentIndex(0);
        backgroundMusicList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        m_backgroundMusic->setPlaylist(backgroundMusicList);

}

void AudioPlayer::startBGM()
{
    if (m_backgroundMusic)
        m_backgroundMusic->play();
}

void AudioPlayer::playSound(SoundType soundType)
{
    static const QUrl mediasUrls[] =
    {
        QUrl( "qrc:/new/prefix3/res/getTower.mp3"),//放置塔音乐
        QUrl("qrc:/new/prefix3/res/shootSound.mp3"),//打中怪兽的音乐
        QUrl( "qrc:/new/prefix3/res/EnemyDieAndGetAward.mp3"),//怪兽消失的声音
        QUrl("qrc:/new/prefix3/res/LoseLifeSound.mp3")//player失去一条生命
    };
    static QMediaPlayer player;


        player.setMedia(mediasUrls[soundType]);
        player.setVolume(50);
        player.play();

}
