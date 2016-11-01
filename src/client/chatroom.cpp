#include "chatroom.h"

ChatRoom::ChatRoom(QObject *parent) : QObject(parent){
    /*
     * 初始化类
    */

    //初始化配置
    initRoomOpt();

    //初始化聊天室
    initChatRoom();
}
void ChatRoom::initRoomOpt(){
    /*
     * 初始化配置
    */
}
void ChatRoom::initChatRoom(){
    /*
     * 初始化聊天室
    */
    m_pVideoChat = new VideoChat;
    connect(m_pVideoChat, &VideoChat::log, this, &ChatRoom::log);
    connect(m_pVideoChat, &VideoChat::newCameraFrame, this, &ChatRoom::newCameraFrame);

    m_pSocket = new QUdpSocket(this);
    //套接字监听
    connect(m_pSocket, SIGNAL(readyRead()), this, SLOT(recieveData()));

}
void ChatRoom::initUdpOpt(QHostAddress recieverIp, quint16 recieverPort, quint16 listenerPort){
    /*
     * 初始化Udp配置
    */

    //保存有关ip/port
    m_nRecieverPort = recieverPort;
    m_nListenerPort = listenerPort;
    m_RecieverHostAddress = recieverIp;

    //中断当前Udp收发器
    m_pSocket->abort();

    //Udp监听
    if (!m_pSocket->bind(QHostAddress::Any, m_nListenerPort)){
        emit log(QStringLiteral("监听失败, 端口:") + QString::number(m_nListenerPort));
        return;
    }
    emit log(QStringLiteral("正在监听, 端口:") + QString::number(m_nListenerPort));

    m_pVideoChat->initUdpOpt(recieverIp, recieverPort + 1, listenerPort + 1);
}
ChatRoom::~ChatRoom(){
    delete m_pSocket;
}
void ChatRoom::sendMessage(const QString &message){
    /*
     * 发送消息
    */
    QByteArray data = "w" + message.toLocal8Bit();
    int sizeSended = m_pSocket->writeDatagram(data, data.size(), m_RecieverHostAddress, m_nRecieverPort);
    emit log(QStringLiteral("发送消息"));
    if (sizeSended != data.size()){
        emit log(QStringLiteral("发送消息失败"));
        return;
    }
    emit newMessage(message);
}
void ChatRoom::sendOrder(const QString &orderCode){
    /*
     * 发送命令编号
    */
    QByteArray data = "o" + orderCode.toLocal8Bit();
    int sizeSended = m_pSocket->writeDatagram(data, data.size(), m_RecieverHostAddress, m_nRecieverPort);
    emit log(QStringLiteral("发送命令"));
    if (sizeSended != data.size()){
        emit log(QStringLiteral("发送命令失败"));
        return;
    }
    emit newOrder(orderCode);
}
void ChatRoom::recieveData(){
    /*
     * 接收数据
    */
    while (m_pSocket->hasPendingDatagrams()) {
        QByteArray array;
        array.resize(m_pSocket->pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        m_pSocket->readDatagram(array.data(), array.size(), &sender, &senderPort);

        emit log(QStringLiteral("接受数据, 来自") + sender.toString());

        QString data = QString::fromLocal8Bit(array);
        QString type = data.mid(0,1);
        data = data.mid(1);
        if (type == "w"){

            emit log(QStringLiteral("新消息"));
            emit newMessage(data, true);

        }else if (type == "o"){

            emit log(QStringLiteral("新命令"));
            handleOrder(data.toInt());

        }else if (type == "v"){

            emit log(QStringLiteral("新语言消息"));

        }
    }
}
void ChatRoom::handleOrder(const int &orderCode){
    /*
     * 处理命令码
    */
    emit newOrder(QString::number(orderCode), true);
    switch (orderCode) {
    case 101:
        if (QMessageBox::Yes == QMessageBox::question(NULL, QStringLiteral("视频请求"), QStringLiteral("是否同意与Ta视频?"))){
            m_pVideoChat->startVideoChat();
            this->sendOrder("102");
        }else{
            m_pVideoChat->stopVideoChat();
            this->sendOrder("104");
        }
        break;
    case 102:
        m_pVideoChat->startVideoChat();
        break;
    case 103:
    case 104:
        m_pVideoChat->stopVideoChat();
        break;
    default:
        break;
    }
}
void ChatRoom::requestVideoChat(){
    /*
     * 请求视频聊天
    */
    this->sendOrder("101");
    m_pVideoChat->requestVideoChat();
}
void ChatRoom::startVideoChat(){
    /*
     * 开始视频聊天
    */
    m_pVideoChat->startVideoChat();
}
void ChatRoom::stopVideoChat(){
    /*
     * 停止视频聊天
    */
    this->sendOrder("103");
    m_pVideoChat->stopVideoChat();
}
