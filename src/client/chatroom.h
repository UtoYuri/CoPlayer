#ifndef CHATROOM_H
#define CHATROOM_H

#include <QObject>
#include <QHostAddress>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QImage>
#include <QMessageBox>
#include <QBuffer>
#include <QStringList>

#include <opencv2/opencv.hpp>

class ChatRoom : public QObject{
    Q_OBJECT
public:
    explicit ChatRoom(QObject *parent = 0);
    void initOpt(){
        m_nFPS = 30;
        m_pSocket = NULL;
    }

signals:
    void log(const QString &logInfo); //日志log

    void newCameraCapture(QImage &img, bool recieved = false);  //新照片
    void newCameraFrame(QImage &img, bool recieved = false);  //新帧
    void newMessage(const QString &msg, bool recieved = false);

    void cameraClosed();    //摄像头已关闭
    void socketConnected(); //视频通讯已连接
    void socketDisconnected();  //视频通讯断开

public slots:
    void openCamera();  //打开摄像头
    void readFrame();   //读取当前帧
    void closeCamera(); //关闭摄像头
    void capture();     //拍照

    void monitor(int port);     //监听连接请求
    void connectHost(const QString &socket);     //远程视频连接
    void disconnectHost();  //断开远程视频连接
    void handleConnection();   //连接处理
    void sendFrame(QImage &img);   //发送帧
    void sendMessage(QString &msg);   //发送消息
    void recieve();//接受帧+消息

private:
    QTimer *m_pTimer;   //刷新帧计时器
    int m_nFPS;         //视频帧数

    cv::VideoCapture m_cvCamera;    //摄像头
    cv::Mat m_cvFrame;    //帧
    cv::Mat m_cvFrameRecieved;    //接收到的帧

    QTcpSocket *m_pSocket;  //主动连接socket
    QTcpServer *m_pServer;  //被动连接socket
};

#endif // CHATROOM_H
