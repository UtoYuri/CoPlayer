#ifndef PLAYER_H
#define PLAYER_H

#include "videowidget.h"
#include "progressbar.h"

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPainter>
#include <QLayout>
#include <QResizeEvent>
#include <QDateTime>
#include <QDebug>

struct MediaInfo{
    QString src;
    qint64 position;
    QMediaPlayer::State state;
    MediaInfo(const QString &src, const qint64 position, const QMediaPlayer::State state):src(src),position(position),state(state){}
};

namespace Ui {
class Player;
}

class Player : public QWidget
{
    Q_OBJECT

public:
    explicit Player(QWidget *parent = 0);
    ~Player();

public:
    void initPlayer();
    MediaInfo currentMedia();

public slots:
    void setMedia(const QString &src) const;
    void play() const;
    void pause() const;
    void reload() const;
    void launchBarrage();
    void setBarrageEnable(const bool enable);
    void setVolume(const int &volume);
    void switchMuted();
    void adjustScreen(const bool adjust);
    void setProgressBar(qint64 position);
    void setCurPositon(float percent);

protected:
    void resizeEvent(QResizeEvent *);

private:
    bool m_bBarrageOn;

private:
    QMediaPlayer *m_pPlayer;
    VideoWidget *m_pVideoWidget;

private:
    Ui::Player *ui;
};

#endif // PLAYER_H
