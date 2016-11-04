#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include "videocontroller.h"
#include "videowidget.h"

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaPlaylist>

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();

    void initPlayerOpt();   //初始化播放器基本变量
    void initPlayerUi();    //构造播放器
    void initVideoPlayer(); //初始化播放器

signals:

protected:
    void resizeEvent(QResizeEvent *);

public slots:
    void playMedia(QStringList);   //播放媒体
    void fullScreenToggled(bool fullScreen);    //全屏/半屏

private:
    QMediaPlaylist *m_pVideoList;   //播放列表

    VideoController *m_pVideoController;    //播放器控制器
    QMediaPlayer *m_pVideoPlayer;   //播放器
    VideoWidget *m_pVideoWidget;    //视频渲染控件

    QVBoxLayout *m_pVLayout;    //布局
};

#endif // VIDEOPLAYER_H
