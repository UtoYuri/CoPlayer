#ifndef SERVER_H
#define SERVER_H

#include "user.h"
#include "usersocket.h"
#include "reciever.h"

#include <QWidget>
#include <QTcpServer>
#include <QStringList>

class Server : public QWidget{
    Q_OBJECT
public:
    explicit Server(QWidget *parent = 0);
    ~Server();

    inline int onlineNum()const{
        return m_vUserSocket.size();
    }

public slots:
    void newOnlineUser();
    void newMessage();
    void newUploadFile();
    void newMediaControl();
    void error(QAbstractSocket::SocketError);
    void removeUserSocket();


//protected:
    void monitor();

signals:
    void log(const QString &logInfo);
    void onlineNumChanged(const int num);

private:
    User *m_pUserManager;

    QTcpServer *m_pServerUserManager;     //用户在线状态监听
    QTcpServer *m_pServerMessageRepeater;   //消息转发监听
    QTcpServer *m_pServerFileReciever;  //文件接收监听
    QTcpServer *m_pServerMediaController;   //媒体控制监听

    QVector<UserSocket*> m_vUserSocket;    //持续连接
    QTcpSocket *m_pRepeaterSocket;   //持续连接
    QTcpSocket *m_pControllerSocket;   //持续连接
};

#endif // SERVER_H
