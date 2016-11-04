#include "videoplayer.h"

VideoPlayer::VideoPlayer(QWidget *parent) : QWidget(parent){
    initPlayerOpt();
    initPlayerUi();
    initVideoPlayer();
}
VideoPlayer::~VideoPlayer(){
    delete m_pVideoController;
    delete m_pVideoList;
    delete m_pVideoPlayer;
    delete m_pVideoWidget;
    delete m_pVLayout;
}
void VideoPlayer::initPlayerOpt(){
    /*
     * 初始化播放器基本变量
    */
    //新建播放列表
    m_pVideoList = new QMediaPlaylist;
    m_pVideoList->clear();
}
void VideoPlayer::initPlayerUi(){
    /*
     * 构造播放器
    */
    m_pVideoController = new VideoController(this);
    m_pVideoPlayer = new QMediaPlayer;
    m_pVideoWidget = new VideoWidget(this);

    m_pVLayout = new QVBoxLayout(this);
    m_pVLayout->addWidget(m_pVideoWidget);
    m_pVLayout->addWidget(m_pVideoController);

    m_pVLayout->setSpacing(0);
    m_pVLayout->setMargin(0);

    this->setLayout(m_pVLayout);
}
void VideoPlayer::initVideoPlayer(){
    /*
     * 初始化播放器
    */
    m_pVideoPlayer->setVolume(60);
    m_pVideoPlayer->setPlaylist(m_pVideoList);
    m_pVideoPlayer->setVideoOutput(m_pVideoWidget);
    m_pVideoWidget->setWindowFlags (Qt::FramelessWindowHint);

    //连接信号槽
    //播放新媒体
    connect(m_pVideoWidget, SIGNAL(playNewMedia(QStringList)), this, SLOT(playMedia(QStringList)));
    //全屏/半屏切换
    connect(m_pVideoWidget, &VideoWidget::fullScreenToggled, this, &VideoPlayer::fullScreenToggled);
    //进度变更
    connect(m_pVideoWidget, &VideoWidget::positionChanged, [=](qint64 pos){
        m_pVideoPlayer->setPosition(pos);
    });
    //播放/暂停
    connect(m_pVideoWidget, &VideoWidget::play, [=](){
        if (m_pVideoPlayer->mediaStatus() == QMediaPlayer::UnknownMediaStatus ||
                m_pVideoPlayer->mediaStatus() == QMediaPlayer::NoMedia ||
                m_pVideoPlayer->mediaStatus() == QMediaPlayer::InvalidMedia){
            return;
        }
        QMediaPlayer::PlayingState == m_pVideoPlayer->state() ? m_pVideoPlayer->pause() : m_pVideoPlayer->play();
    });
    //快进
    connect(m_pVideoWidget, &VideoWidget::fastForward, [=](){
        m_pVideoPlayer->setPosition(m_pVideoPlayer->position() + 5000);
    });
    //快退
    connect(m_pVideoWidget, &VideoWidget::rewind, [=](){
        m_pVideoPlayer->setPosition(m_pVideoPlayer->position() - 5000);
    });
    //音量变更
    connect(m_pVideoWidget, &VideoWidget::volumeChanged, [=](int increment){
        m_pVideoPlayer->setVolume(increment + m_pVideoPlayer->volume());
    });

    //播放/暂停
    connect(m_pVideoController, &VideoController::play, [=](bool play){
        if (play && m_pVideoPlayer->mediaStatus() == QMediaPlayer::UnknownMediaStatus ||
                m_pVideoPlayer->mediaStatus() == QMediaPlayer::NoMedia ||
                m_pVideoPlayer->mediaStatus() == QMediaPlayer::InvalidMedia){
            m_pVideoController->setIsPlaying(true);
            return;
        }
        if (play){
            m_pVideoPlayer->play();
        }else{
            m_pVideoPlayer->pause();
        }
    });
    //全屏/半屏
    connect(m_pVideoController, &VideoController::fullScreenToggled, this, &VideoPlayer::fullScreenToggled);
    //禁音开关
    connect(m_pVideoController, &VideoController::muteChanged, m_pVideoPlayer, &QMediaPlayer::setMuted);
    //音量调节开关
    connect(m_pVideoController, &VideoController::volumeChanged, m_pVideoPlayer, &QMediaPlayer::setVolume);
    //主动进度变更
    connect(m_pVideoController, &VideoController::positionChanged, [=](float percent){
        m_pVideoPlayer->setPosition(m_pVideoPlayer->duration() * percent);
    });
    //显示/隐藏列表
    connect(m_pVideoController, &VideoController::listWidgetToggled, [=](bool show){
        m_pVideoWidget->toggleListWidget(show);
    });

    //被动进度变更
    connect(m_pVideoPlayer, &QMediaPlayer::positionChanged, [=](qint64 pos){
        m_pVideoController->setProgress(pos);
    });
    //被动媒体时长变化
    connect(m_pVideoPlayer, &QMediaPlayer::durationChanged, [=](qint64 duration){
        m_pVideoController->initMediaInfo(duration);
    });
    //被动媒体播放状态变化
    connect(m_pVideoPlayer, &QMediaPlayer::stateChanged, [=](QMediaPlayer::State state){
        if (QMediaPlayer::PlayingState == state){
            m_pVideoController->setIsPlaying(false);
        }else{
            m_pVideoController->setIsPlaying(true);
        }
    });
    //被动媒体状态变化
    connect(m_pVideoPlayer, &QMediaPlayer::mediaStatusChanged, [=](QMediaPlayer::MediaStatus state){
        if (QMediaPlayer::NoMedia == state ||
                QMediaPlayer::UnknownMediaStatus == state ||
                QMediaPlayer::EndOfMedia == state ||
                QMediaPlayer::InvalidMedia == state){
            m_pVideoWidget->showButton();
        }else{
            m_pVideoWidget->hideButton();
        }
    });
    //音量变更
    connect(m_pVideoPlayer, &QMediaPlayer::volumeChanged, [=](int value){
        m_pVideoController->setVolume(value);
    });
}
void VideoPlayer::resizeEvent(QResizeEvent *){
    m_pVideoWidget->adjustWidget();
}
void VideoPlayer::playMedia(QStringList files){
    /*
     * 播放媒体
    */
    m_pVideoWidget->hideButton();
    for (int i = 0; i < files.size(); ++i){
        m_pVideoWidget->addMedia(files.at(i));
        m_pVideoList->addMedia(QUrl(files.at(i)));
    }
    m_pVideoPlayer->play();
}
void VideoPlayer::fullScreenToggled(bool fullScreen){
    /*
     * 全屏/半屏
    */
    if (QMediaPlayer::NoMedia == m_pVideoPlayer->mediaStatus()){
        m_pVideoController->setIsFullScreen(true);
        return;
    }
    m_pVideoWidget->setFullScreen(fullScreen);
    m_pVideoController->setIsFullScreen(!fullScreen);
}
