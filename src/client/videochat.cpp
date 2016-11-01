#include "videochat.h"

VideoChat::VideoChat(QObject *parent) : QObject(parent){
    initVideoOpt();
    initVideoChat();
}
VideoChat::~VideoChat(){
    delete m_pVideoSocket;
    delete m_pTimer;
}
void VideoChat::initVideoOpt(){
    /*
     * 初始化配置
    */
    //设置视频帧数
    m_nFPS = 30;

    //设置视频状态
    m_VideoChatState = VideoChat::Off;

}
void VideoChat::initVideoChat(){
    /*
     * 初始化聊天室
    */

    //设置刷新帧计时器
    m_pTimer = new QTimer(this);
    m_pTimer->setInterval(1000 / m_nFPS);
    connect(m_pTimer, &QTimer::timeout, this, &VideoChat::readFrame);

    //设置Udp收发类
    m_pVideoSocket = new QUdpSocket(this);

    //套接字监听
    connect(m_pVideoSocket, SIGNAL(readyRead()), this, SLOT(recieveFrame()));

    //设置语言聊天类
    m_pAudioChat = new AudioChat;
    connect(m_pAudioChat, &AudioChat::log, this, &VideoChat::log);

}
void VideoChat::initUdpOpt(QHostAddress recieverIp, quint16 recieverPort, quint16 listenerPort){
    /*
     * 初始化Udp配置
    */

    //保存有关ip/port
    m_nRecieverPort = recieverPort;
    m_nListenerPort = listenerPort;
    m_RecieverHostAddress = recieverIp;

    //中断当前Udp收发器
    m_pVideoSocket->abort();

    //Udp监听
    if (!m_pVideoSocket->bind(QHostAddress::Any, m_nListenerPort)){
        emit log(QStringLiteral("监听失败, 端口:") + QString::number(m_nListenerPort));
        return;
    }
    emit log(QStringLiteral("正在监听, 端口:") + QString::number(m_nListenerPort));

    //配置语音聊天Udp
    m_pAudioChat->initUdpOpt(recieverIp, recieverPort + 1, listenerPort + 1);
}

void VideoChat::openCamera(){
    /*
     * 打开摄像头
    */
    m_cvCamera.release();
    m_cvCamera = cv::VideoCapture(0);
    emit log(QStringLiteral("打开摄像头"));
    emit cameraOpened();
    m_pTimer->start();
}
void VideoChat::readFrame(){
    /*
     * 读取当前帧
    */
    //读取当前帧
    m_cvCamera >> m_cvFrame;

    //转化帧格式
    cv::cvtColor(m_cvFrame, m_cvFrame, CV_BGR2RGB);

    //转化帧为QImage类型
    QImage frame =  QImage((const uchar*)(m_cvFrame.data), m_cvFrame.cols, m_cvFrame.rows, QImage::Format_RGB888);

    //触发刷新帧信号
    emit newCameraFrame(frame);

    //如果远程视频已连接则发送帧
    if (VideoChat::On == m_VideoChatState){
        sendFrame(frame);
    }
}
void VideoChat::closeCamera(){
    /*
     * 关闭摄像头
    */
    m_cvCamera.release();
    emit log(QStringLiteral("关闭摄像头"));
    emit cameraClosed();
    m_pTimer->stop();
}
void VideoChat::capture(){
    /*
     * 拍照
    */
    //转化帧格式
    cv::cvtColor(m_cvFrame, m_cvFrame, CV_BGR2RGB);

    //转化帧为QImage类型
    QImage capture =  QImage((const uchar*)(m_cvFrame.data), m_cvFrame.cols, m_cvFrame.rows, QImage::Format_RGB888);

    //触发刷新帧信号
    emit log(QStringLiteral("视频截图"));
    emit newCameraCapture(capture);
}
void VideoChat::sendFrame(const QImage &image){
    /*
     * 发送帧
    */
    //转化QImage为QByteArray
    QPixmap pix = QPixmap::fromImage(image);
    QBuffer buffer;
    buffer.open(QIODevice::ReadWrite);
    pix.save(&buffer, "JPG");
    QByteArray data;
    data.append(buffer.data());

    //发送
    m_pVideoSocket->writeDatagram(data, m_RecieverHostAddress, m_nRecieverPort);
}
void VideoChat::recieveFrame(){
    /*
     * 接收视频帧
    */
    while (m_pVideoSocket->hasPendingDatagrams()) {
        QByteArray data;
        data.resize(m_pVideoSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        m_pVideoSocket->readDatagram(data.data(), data.size(), &sender, &senderPort);

        //转化数据为QImage类型
        QBuffer buffer(&data);
        buffer.open(QIODevice::ReadOnly);

        QImageReader reader(&buffer, "JPG");
        QImage image = reader.read();
        emit newCameraFrame(image, true);
    }
}
void VideoChat::requestVideoChat(){
    /*
     * 请求视频聊天
    */
    openCamera();
    m_VideoChatState = VideoChat::Pending;
    emit stateChanged(m_VideoChatState);
    m_pAudioChat->requestAudioChat();
}
void VideoChat::startVideoChat(){
    /*
     * 开始视频聊天
    */
    if (!m_cvCamera.isOpened()){
        openCamera();
    }
    emit log(QStringLiteral("开始视频聊天"));
    m_VideoChatState = VideoChat::On;
    emit stateChanged(m_VideoChatState);
    if (m_pAudioChat) {
        m_pAudioChat->startAudioChat();
    }
}
void VideoChat::stopVideoChat(){
    /*
     * 停止视频聊天
    */
    emit log(QStringLiteral("停止视频聊天"));
    m_VideoChatState = VideoChat::Off;
    emit stateChanged(m_VideoChatState);
    closeCamera();
    m_pAudioChat->stopAudioChat();
}
