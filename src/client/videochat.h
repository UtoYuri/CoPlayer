#ifndef VIDEOCHAT_H
#define VIDEOCHAT_H

#include "audiochat.h"

#include <QStringList>
#include <QImage>
#include <QPixmap>
#include <QImageReader>

#include <opencv2/opencv.hpp>

class VideoChat : public QObject
{
    Q_OBJECT
public:
    explicit VideoChat(QObject *parent = 0);
    ~VideoChat();

    enum VideoChatState{
        On,
        Off,
        Pending
    };

    void initVideoOpt(); //初始化基本变量
    void initVideoChat();   //初始化语音通话
    void initUdpOpt(QHostAddress recieverIp, quint16 recieverPort, quint16 listenerPort);  //初始化Udp配置
    VideoChatState videoChatState();   //语音通话状态

signals:
    void log(const QString &logInfo); //日志log
    void stateChanged(VideoChat::VideoChatState state);    //状态变化
    void newCameraCapture(QImage &img);  //新视频截图
    void newCameraFrame(QImage &img, bool recieved = false);  //新视频帧
    void cameraOpened();    //摄像头已开启
    void cameraClosed();    //摄像头已关闭

public slots:
    void openCamera();  //打开摄像头
    void readFrame();   //读取当前帧
    void closeCamera(); //关闭摄像头
    void capture();     //拍照

    void sendFrame(const QImage &image);   //发送帧
    void recieveFrame(); //接受视频帧

    void requestVideoChat();    //请求视频聊天
    void startVideoChat();    //开始视频聊天
    void stopVideoChat();   //停止视频聊天

private:
    QTimer *m_pTimer;   //刷新帧计时器
    int m_nFPS;         //视频帧数
    VideoChatState m_VideoChatState;    //视频聊天状态

    cv::VideoCapture m_cvCamera;    //摄像头
    cv::Mat m_cvFrame;    //帧

    QHostAddress m_RecieverHostAddress; //接收方ip
    quint16 m_nRecieverPort;    //接受者端口
    quint16 m_nListenerPort;    //本地监听端口
    QUdpSocket *m_pVideoSocket; //udp

    AudioChat *m_pAudioChat;
};

#endif // VIDEOCHAT_H
