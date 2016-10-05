#include "player.h"
#include "ui_player.h"

Player::Player(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Player){
    ui->setupUi(this);
    initPlayer();
}

Player::~Player(){
    delete m_pPlayer;
    delete m_pVideoWidget;
    delete ui;
}
void Player::resizeEvent(QResizeEvent *){
    /*
     * 窗口大小改变时间
     * video界面大小随之改变
    */
    m_pVideoWidget->resize(ui->player_widget->size());
}
void Player::initPlayer(){
    /*
     * 创建播放器
    */
    m_pPlayer = new QMediaPlayer(ui->player_widget);
    m_pVideoWidget = new VideoWidget(ui->player_widget);
    m_pPlayer->setVideoOutput(m_pVideoWidget);
    m_pVideoWidget->show();
    connect(ui->btn_play, &QToolButton::clicked, this, &Player::play);
    connect(ui->btn_volume, &QToolButton::clicked, this, &Player::switchMuted);
    connect(ui->btn_reload, &QToolButton::clicked, this, &Player::reload);
    connect(ui->btn_fullpage, &QToolButton::clicked, [=](){
        adjustScreen(true);
    });
    connect(m_pVideoWidget, &VideoWidget::adjustScreen, this, &Player::adjustScreen);
    connect(ui->slider_volume, &QSlider::valueChanged, this, &Player::setVolume);
    connect(m_pVideoWidget, &VideoWidget::play, this, &Player::play);
    connect(m_pPlayer, &QMediaPlayer::positionChanged, this, &Player::setProgressBar);
    connect(ui->progress_bar, &ProgressBar::changePositon, this, &Player::setCurPositon);
    m_pPlayer->setMedia(QUrl("file:///D:/%E8%BF%85%E9%9B%B7%E4%B8%8B%E8%BD%BD/%E8%A1%8C%E5%B0%B8%E8%B5%B0%E8%82%89/%E8%A1%8C%E5%B0%B8%E8%B5%B0%E8%82%89.The.Walking.Dead.S01E01.Chi_Eng.HDTVrip.720X396-YYeTs%E4%BA%BA%E4%BA%BA%E5%BD%B1%E8%A7%86.rmvb"));
}
MediaInfo Player::currentMedia(){
    /*
     * 获取media信息
    */
    return MediaInfo(m_pPlayer->currentMedia().canonicalUrl().toString(), m_pPlayer->position(), m_pPlayer->state());
}
void Player::setMedia(const QString &src) const{
    /*
     * 设置媒体资源
    */
    m_pPlayer->setMedia(QUrl(src));
}
void Player::play() const{
    /*
     * 开启播放器
     * 判断播放器是否出错
     *      出错则log
     * 判断是否正在播放
     *      正在播放则忽略
     * 判断媒体资源
     *      没有资源log
     *      正在缓冲log
     *      播放结束log
     * 播放
    */
    if (m_pPlayer->error() != QMediaPlayer::NoError){
        qDebug()<<QStringLiteral("播放器错误");
        return;
    }
    if (m_pPlayer->state() != QMediaPlayer::PlayingState) {
        switch (m_pPlayer->mediaStatus()) {
        case QMediaPlayer::NoMedia:
            qDebug()<<QStringLiteral("找不到媒体");
            return;
        case QMediaPlayer::StalledMedia:
            qDebug()<<QStringLiteral("正在缓冲");
            return;
        case QMediaPlayer::EndOfMedia:
            qDebug()<<QStringLiteral("已播放结束");
            return;
        default:
            m_pPlayer->play();
            return;
        }
    }else{
        pause();
    }
    return;
}
void Player::pause() const{
    /*
     * 暂停播放器
    */
    m_pPlayer->pause();
}
void Player::reload() const{
    /*
     * 重新连接服务器
    */
}
void Player::launchBarrage(){
    /*
     * 发射弹幕
    */
}
void Player::setVolume(const int &volume = 50){
    /*
     * 设置音量
    */
    m_pPlayer->setVolume(volume);
}
void Player::switchMuted(){
    /*
     * 静音开关
    */
    if (m_pPlayer->isMuted()){
        m_pPlayer->setMuted(false);
        ui->slider_volume->setEnabled(true);
        ui->btn_volume->setText(QStringLiteral("禁音"));
    }else{
        m_pPlayer->setMuted(true);
        ui->slider_volume->setEnabled(false);
        ui->btn_volume->setText(QStringLiteral("取消禁音"));
    }
}
void Player::setBarrageEnable(const bool enable){
    /*
     * 弹幕开关
    */
    m_bBarrageOn = enable;
}
void Player::adjustScreen(const bool adjust = true){
    /*
     * 自适应屏幕（全屏）
     *      自适应false 则显示普通窗口
     *      自适应true 则判断是否全屏
     *          全屏  则显示普通窗口
     *          非全屏 则全屏显示
    */
    if (!adjust || m_pVideoWidget->isFullScreen()){
        m_pVideoWidget->setFullScreen(false);
        m_pVideoWidget->resize(ui->player_widget->size());
    }else{
        m_pVideoWidget->setWindowFlags (Qt::FramelessWindowHint);
        m_pVideoWidget->setFullScreen(true);
    }
}
void Player::setProgressBar(qint64 position){
    /*
     * 设置进度条
    */
    ui->progress_bar->setValue(position * 1000.0 / m_pPlayer->duration());
    ui->progress_bar->setFormat(QString("%1 / %2").arg(QTime::fromString("00:00:00","hh:mm:ss").addMSecs(position).toString("hh:mm:ss"))
                                .arg(QTime::fromString("00:00:00","hh:mm:ss").addMSecs(m_pPlayer->duration()).toString("hh:mm:ss")));
}
void Player::setCurPositon(float percent){
    /*
     * 设置当前播放进度
    */
    m_pPlayer->setPosition(m_pPlayer->duration() * percent);
}
