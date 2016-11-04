#include "videocontroller.h"

VideoController::VideoController(QWidget *parent) : QWidget(parent){
    initControllerOpt();
    initControllerUi();
    initVideoController();
}
VideoController::~VideoController(){
    delete m_pBtnFullScreen;
    delete m_pBtnList;
    delete m_pBtnMute;
    delete m_pBtnPlay;
    delete m_pPositionShow;
    delete m_pVolumeSlider;
    delete m_pProgressBar;
    delete m_pVLayout;
    delete m_pHLayout;
    delete m_pPanel;
}
void VideoController::initControllerOpt(){
    /*
     * 初始化控制器基本变量
    */
    m_bIsFullScreen = false;
    m_bIsPlaying = false;
    m_bIsMuted = false;
    m_bIsListShowing = false;
    m_PositionShowFormat = QString("%1 / %2");
    m_MediaDuration = "00:00";
}
void VideoController::initControllerUi(){
    /*
     * 构造控制器
    */
    //构造
    m_pProgressBar = new ProgressBar(this);
    m_pPanel = new QWidget(this);
    m_pBtnPlay = new QToolButton(this);
    m_pPositionShow = new QLabel(this);
    m_pBtnMute = new QToolButton(this);
    m_pVolumeSlider = new QSlider(this);
    m_pBtnList = new QToolButton(this);
    m_pBtnFullScreen = new QToolButton(this);
    m_pHLayout = new QHBoxLayout;
    m_pVLayout = new QVBoxLayout;

    //布局
    m_pHLayout->addSpacing(15);
    m_pHLayout->addWidget(m_pBtnPlay);
    m_pHLayout->addSpacing(15);
    m_pHLayout->addWidget(m_pPositionShow);
    m_pHLayout->addStretch();
    m_pHLayout->addWidget(m_pBtnMute);
    m_pHLayout->addWidget(m_pVolumeSlider);
    m_pHLayout->addSpacing(20);
    m_pHLayout->addWidget(m_pBtnList);
    m_pHLayout->addSpacing(15);
    m_pHLayout->addWidget(m_pBtnFullScreen);
    m_pHLayout->addSpacing(15);
    m_pHLayout->setMargin(0);
    m_pPanel->setLayout(m_pHLayout);

    m_pVLayout->addWidget(m_pProgressBar);
    m_pVLayout->addWidget(m_pPanel);
    m_pVLayout->setSpacing(0);
    m_pVLayout->setMargin(0);
    this->setLayout(m_pVLayout);
}
void VideoController::initVideoController(){
    /*
     * 初始化控制器
    */
    //初始化进度条和控制器
    this->setMaximumHeight(50);
    this->setMinimumHeight(50);
    m_pProgressBar->setMaximumHeight(5);
    m_pPanel->setMaximumHeight(45);
    m_pPanel->setObjectName("Panel");

    //初始化控制器所有控件
    m_pVolumeSlider->setValue(60);
    m_pVolumeSlider->setOrientation(Qt::Horizontal);
    m_pBtnPlay->setIcon(QIcon(":/icon/play.png"));
    m_pBtnMute->setIcon(QIcon(":/icon/mute.png"));
    m_pBtnList->setIcon(QIcon(":/icon/list.png"));
    m_pBtnFullScreen->setIcon(QIcon(":/icon/full_screen.png"));
    m_pBtnPlay->setIconSize(QSize(28, 28));
    m_pPositionShow->setText(m_PositionShowFormat.arg("00:00").arg(m_MediaDuration));

    //加载界面效果
    QFile styleSheet(":/media_player/video_controller.qss");
    if (!styleSheet.open(QIODevice::ReadOnly)){
    }else{
        this->setStyleSheet(styleSheet.readAll());
    }

    //转发信号
    //进度调整
    connect(m_pProgressBar, &ProgressBar::positionChanged, [=](float percent){
        emit positionChanged(percent);
    });
    //音量调整
    connect(m_pVolumeSlider, &QSlider::valueChanged, [=](int value){
        emit volumeChanged(value);
    });
    //播放暂停
    connect(m_pBtnPlay, &QToolButton::clicked, [=](){
        setIsPlaying(m_bIsPlaying);
        emit play(m_bIsPlaying);
    });
    //禁音/正常
    connect(m_pBtnMute, &QToolButton::clicked, [=](){
        setIsMuted(m_bIsMuted);
        emit muteChanged(m_bIsMuted);
    });
    //全屏/半屏
    connect(m_pBtnFullScreen, &QToolButton::clicked, [=](){
        setIsFullScreen(m_bIsFullScreen);
        emit fullScreenToggled(m_bIsFullScreen);
    });
    //显示/隐藏播放列表
    connect(m_pBtnList, &QToolButton::clicked, [=](){
        m_bIsListShowing = !m_bIsListShowing;
        emit listWidgetToggled(m_bIsListShowing);
    });
}
void VideoController::initMediaInfo(qint64 duration){
    /*
     * 初始化资源信息
    */
    m_nMediaDuration = duration;
    m_MediaDuration = int2TimeString(duration);
}
void VideoController::setVolume(int value){
    /*
     * 刷新音量
    */
    m_pVolumeSlider->setValue(value);
}
void VideoController::setProgress(qint64 pos){
    /*
     * 刷新进度
    */
    m_pProgressBar->setMaximum(1000);
    m_pProgressBar->setValue(pos * 1000.0 / m_nMediaDuration);
    m_pPositionShow->setText(m_PositionShowFormat.arg(int2TimeString(pos)).arg(m_MediaDuration));
}
QString VideoController::int2TimeString(qint64 duration){
    /*
     * 毫秒转化mm:ss
    */
    qint16 seconds = duration / 1000;
    return QString("%1:%2").arg(QString::number(seconds / 60), 2, '0').arg(QString::number(seconds % 60), 2, '0');
}
void VideoController::setIsFullScreen(bool isFullScreen){
    /*
     * 设置变量 是否全屏
    */
    if (isFullScreen){
        m_bIsFullScreen = false;
        m_pBtnFullScreen->setIcon(QIcon(":/icon/full_screen.png"));
    }else{
        m_bIsFullScreen = true;
        m_pBtnFullScreen->setIcon(QIcon(":/icon/normal_screen.png"));
    }
}
void VideoController::setIsPlaying(bool isPlaying){
    /*
     * 设置变量 是否正在播放
    */
    if (isPlaying){
        m_bIsPlaying = false;
        m_pBtnPlay->setIcon(QIcon(":/icon/play.png"));
    }else{
        m_bIsPlaying = true;
        m_pBtnPlay->setIcon(QIcon(":/icon/pause.png"));
    }
}
void VideoController::setIsMuted(bool isMuted){
    /*
     * 设置变量 是否禁音
    */
    if (isMuted){
        m_bIsMuted = false;
        m_pBtnMute->setIcon(QIcon(":/icon/mute.png"));
    }else{
        m_bIsMuted = true;
        m_pBtnMute->setIcon(QIcon(":/icon/muted.png"));
    }
}
