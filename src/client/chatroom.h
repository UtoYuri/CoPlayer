#ifndef CHATROOM_H
#define CHATROOM_H

//  10.18.204.160
#include "videochat.h"

#include <QMessageBox>

class ChatRoom : public QObject{
    Q_OBJECT
public:
    explicit ChatRoom(QObject *parent = 0);
    ~ChatRoom();
    void initRoomOpt(); //初始化基本变量
    void initChatRoom();    //初始化聊天室
    void initUdpOpt(QHostAddress recieverIp, quint16 recieverPort, quint16 listenerPort);   //初始化Udp配置

signals:
    void log(const QString &logInfo); //日志log
    void newOrder(const QString &orderCode, bool recieved = false); //新命令
    void newMessage(const QString &msg, bool recieved = false); //新文字消息

    void newCameraFrame(QImage &img, bool recieved = false);  //新视频帧

public slots:

    void sendMessage(const QString &message);   //发送消息
    void sendOrder(const QString &orderCode);   //发送命令编号
    void recieveData(); //接收数据
    void handleOrder(const int &orderCode); //处理命令码

    void requestVideoChat();    //请求视频通话
    void startVideoChat();    //开始视频通话
    void stopVideoChat();    //停止视频通话

private:

    QUdpSocket *m_pSocket;  //套接字(文字信息 命令信息)

    quint16 m_nRecieverPort;    //接受者端口
    quint16 m_nListenerPort;    //本地监听端口
    QHostAddress m_RecieverHostAddress; //接收方ip

    VideoChat *m_pVideoChat;

};

#endif // CHATROOM_H
