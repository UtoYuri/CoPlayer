#ifndef VIDEOCONTROLLER_H
#define VIDEOCONTROLLER_H

#include "progressbar.h"

#include <QWidget>
#include <QToolButton>
#include <QSlider>
#include <QLayout>
#include <QLabel>
#include <QFile>

class VideoController : public QWidget
{
    Q_OBJECT
public:
    explicit VideoController(QWidget *parent = 0);
    ~VideoController();

    void initControllerOpt();   //初始化控制器基本变量
    void initControllerUi();    //构造控制器
    void initVideoController(); //初始化控制器

    void initMediaInfo(qint64 duration);   //初始化资源信息
    void setProgress(qint64 duration);  //刷新进度
    void setVolume(int value);  //刷新音量

private:
    QString int2TimeString(qint64 duration); //毫秒转化mm:ss

signals:
    void play(bool play);    //开始/暂停播放
    void muteChanged(bool muted);  //禁音开关
    void volumeChanged(int volume);   //设置音量
    void fullScreenToggled(bool fullScreen);    //切换全屏/半屏
    void positionChanged(float percent);    //播放进度变化
    void listWidgetToggled(bool show);  //显示/隐藏播放列表

public slots:
    void setIsFullScreen(bool isFullScreen); //设置变量 是否全屏
    void setIsPlaying(bool isPlaying);   //设置变量 是否正在播放
    void setIsMuted(bool isMuted);   //设置变量 是否禁音

private:
    bool m_bIsFullScreen;   //是否全屏
    bool m_bIsPlaying;  //是否正在播放
    bool m_bIsMuted;    //是否禁音
    bool m_bIsListShowing;    //播放列表是否显示
    QString m_MediaDuration;    //视频总时长 mm:ss
    qint64 m_nMediaDuration;    //视频总时长
    QString m_PositionShowFormat;   //播放进度显示格式

    ProgressBar *m_pProgressBar;    //视频进度条
    QWidget *m_pPanel;  //控制面板

    QToolButton *m_pBtnPlay;    //播放/暂停开关
    QLabel *m_pPositionShow;    //显示播放进度控件

    QToolButton *m_pBtnMute;    //禁音开关
    QSlider *m_pVolumeSlider;   //音量控制
    QToolButton *m_pBtnList;    //播放清单显示/隐藏
    QToolButton *m_pBtnFullScreen;  //全屏开关

    QHBoxLayout *m_pHLayout;    //水平布局
    QVBoxLayout *m_pVLayout;    //垂直布局
};

#endif // VIDEOCONTROLLER_H
