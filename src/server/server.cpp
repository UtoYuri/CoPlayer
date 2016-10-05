#include "server.h"

Server::Server(QWidget *parent) : QWidget(parent){

}
Server::~Server(){
    delete m_pUserManager;
    delete m_pServerUserManager;
    delete m_pServerMessageRepeater;
    delete m_pServerFileReciever;
    delete m_pServerMediaController;
}

void Server::newOnlineUser(){
    /*
     * 用户上线
     * 发现新上线tcp连接
     * 等待5s获取用户信息
     *      获取不到则断开连接
     *      获取到则判断信息是否正确
     *          不正确则断开连接
     *          正确则登录成功 保持上线状态
     * 刷新在线人数
    */
    emit log(QStringLiteral("发现新连接"));
    UserSocket* t = new UserSocket(m_pServerUserManager->nextPendingConnection());
    connect(t, &UserSocket::disconnected, this, &Server::removeUserSocket);
    connect(t->getSocket(), &QTcpSocket::readyRead, [=](){
        if (t->getSocket()->bytesAvailable()){
            QString vertify = t->getSocket()->readAll();
            emit log(QStringLiteral("收到用户信息") + vertify);
            // userId=**&pass=**
            QStringList data = vertify.split("&");
            QString userId = data.at(0).split("=").at(1);
            QString pass = data.at(1).split("=").at(1);
            if (!m_pUserManager->log(userId,pass)){
                emit log(QStringLiteral("用户登录失败,连接中断") + userId);
                t->getSocket()->disconnectFromHost();
                return;
            }else{
                emit log(QStringLiteral("用户登录成功") + userId);
                t->setUserId(userId);
                connect(t->getSocket(), SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
                m_vUserSocket.append(t);
                emit onlineNumChanged(onlineNum());
            }
        }
    });
}
void Server::newMessage(){
    /*
     * 普通消息转发
    */
    m_pRepeaterSocket = m_pServerMessageRepeater->nextPendingConnection();
    connect(m_pRepeaterSocket, SIGNAL(disconnected()), m_pRepeaterSocket, SLOT(deleteLater()));
    connect(m_pRepeaterSocket, &QTcpSocket::readyRead, [=](){
        if (m_pRepeaterSocket->bytesAvailable()){
            emit log(QStringLiteral("收到消息") + m_pRepeaterSocket->readAll());
        }
    });
}
void Server::newUploadFile(){
    /*
     * 文件接收
    */
    Reciever *reciever = new Reciever(m_pServerFileReciever->nextPendingConnection());
    connect(reciever, SIGNAL(recieved()), reciever, SLOT(deleteLater()));
    connect(reciever, &Reciever::log, [=](const QString &logInfo){
        emit log(logInfo);
    });
}
void Server::newMediaControl(){
    /*
     * 控制信息转发
    */
    m_pControllerSocket = m_pServerMediaController->nextPendingConnection();
    connect(m_pControllerSocket, SIGNAL(disconnected()), m_pControllerSocket, SLOT(deleteLater()));
    connect(m_pControllerSocket, &QTcpSocket::readyRead, [=](){
        if (m_pControllerSocket->bytesAvailable()){
            emit log(QStringLiteral("收到命令") + m_pControllerSocket->readAll());
        }
    });
}
void Server::removeUserSocket(){
    /*
     * 移除下线用户socket
     * 当有usersocket断开时触发
     *      如果该socket在用户列表则移除并销毁
    */
    emit log(QStringLiteral("断开连接"));
    UserSocket *socket = static_cast<UserSocket *>(sender());
    for (int i = 0; i < m_vUserSocket.size(); i++){
        if (m_vUserSocket.at(i) == socket){
            emit log(QStringLiteral("下线通知") + m_vUserSocket.at(i)->getUserId());
            m_vUserSocket.at(i)->deleteLater();
            m_vUserSocket.removeAt(i);
            emit onlineNumChanged(onlineNum());
            return;
        }
    }
}
void Server::error(QAbstractSocket::SocketError){
    /*
     * socket报错
    */
    QTcpSocket *socket = static_cast<QTcpSocket *>(sender());
    emit log(QStringLiteral("发生错误:\t") + socket->errorString());
}


void Server::monitor(){
    /*
     * 初始化tcp服务器并开始监听
    */
    m_pUserManager = new User();

    m_pServerUserManager = new QTcpServer;     //用户在线状态监听
    m_pServerMessageRepeater = new QTcpServer;   //消息转发监听
    m_pServerMediaController = new QTcpServer;   //媒体控制监听
    m_pServerFileReciever = new QTcpServer;  //文件接收监听

    if (!m_pServerUserManager->listen(QHostAddress::Any, 60000)){
        emit log(QStringLiteral("开启监听失败, 端口") + "60000");
        m_pServerUserManager->close();
        return;
    }
    connect(m_pServerUserManager, &QTcpServer::newConnection, this, &Server::newOnlineUser);

    if (!m_pServerMessageRepeater->listen(QHostAddress::Any, 60001)){
        emit log(QStringLiteral("开启监听失败, 端口") + "60001");
        m_pServerMessageRepeater->close();
        return;
    }
    connect(m_pServerMessageRepeater, &QTcpServer::newConnection, this, &Server::newMessage);

    if (!m_pServerMediaController->listen(QHostAddress::Any, 60002)){
        emit log(QStringLiteral("开启监听失败, 端口") + "60002");
        m_pServerMediaController->close();
        return;
    }
    connect(m_pServerMediaController, &QTcpServer::newConnection, this, &Server::newMediaControl);

    if (!m_pServerFileReciever->listen(QHostAddress::Any, 60003)){
        emit log(QStringLiteral("开启监听失败, 端口") + "60003");
        m_pServerFileReciever->close();
        return;
    }
    connect(m_pServerFileReciever, &QTcpServer::newConnection, this, &Server::newUploadFile);

    emit log(QStringLiteral("开始监听"));
}
