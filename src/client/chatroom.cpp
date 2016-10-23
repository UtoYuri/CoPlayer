#include "chatroom.h"

ChatRoom::ChatRoom(QObject *parent) : QObject(parent){
    /*
     * 初始化类
    */

    //初始化配置
    initOpt();

    //创建刷新计时器
    m_pTimer = new QTimer(this);
    m_pTimer->setInterval(1000 / m_nFPS);
    connect(m_pTimer, &QTimer::timeout, this, &ChatRoom::readFrame);

}
void ChatRoom::openCamera(){
    /*
     * 打开摄像头
    */
    m_cvCamera = cv::VideoCapture(0);
    m_pTimer->start();
    emit log(QStringLiteral("打开摄像头"));
}
void ChatRoom::readFrame(){
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
    sendFrame(frame);
}
void ChatRoom::closeCamera(){
    /*
     * 关闭摄像头
    */
    m_pTimer->stop();
    m_cvCamera.release();
    emit log(QStringLiteral("关闭摄像头"));
}
void ChatRoom::capture(){
    /*
     * 拍照
    */
    //转化帧格式
    cv::cvtColor(m_cvFrame, m_cvFrame, CV_BGR2RGB);
    //转化帧为QImage类型
    QImage capture =  QImage((const uchar*)(m_cvFrame.data), m_cvFrame.cols, m_cvFrame.rows, QImage::Format_RGB888);
    //触发刷新帧信号
    emit newCameraCapture(capture);
    emit log(QStringLiteral("拍照"));
}



void ChatRoom::monitor(int port){
    /*
     * 监听连接请求
    */
    m_pServer = new QTcpServer(this);
    if (!m_pServer->listen(QHostAddress::Any, port)){
        emit log(QStringLiteral("监听失败, 端口") + QString::number(port));
        m_pServer->close();
        return;
    }
    connect(m_pServer, &QTcpServer::newConnection, this, &ChatRoom::handleConnection);
    emit log(QStringLiteral("开始监听端口") + QString::number(port));
}
void ChatRoom::connectHost(const QString &socket){
    /*
     * 远程视频连接
    */
    QStringList list = socket.split(":");

    m_pSocket = new QTcpSocket;
    m_pSocket->connectToHost(QHostAddress(list[0]), list[1].toInt());
    connect(m_pSocket, SIGNAL(disconnected()), m_pSocket, SLOT(deleteLater()));
    connect(m_pSocket, &QTcpSocket::readyRead, this, &ChatRoom::recieve);

    closeCamera();
    openCamera();
    emit log(QStringLiteral("请求连接"));
}
void ChatRoom::disconnectHost(){
    /*
     * 断开远程视频连接
    */
    if (m_pSocket) {
        disconnect(m_pSocket, &QTcpSocket::readyRead, this, &ChatRoom::recieve);
        m_pSocket->disconnectFromHost();
    }
    emit log(QStringLiteral("断开视频连接"));
}
void ChatRoom::handleConnection(){
    /*
     * 连接处理
    */
    emit log(QStringLiteral("发现新连接"));
    m_pSocket = new QTcpSocket(m_pServer->nextPendingConnection());
    connect(m_pSocket, &QTcpSocket::disconnected, this, &QTcpSocket::deleteLater);
    if (!QMessageBox::question(NULL, QStringLiteral("视频请求"), QStringLiteral("有新的视频请求，是否接受?")) == QMessageBox::Yes){
        emit log(QStringLiteral("拒绝连接"));
        m_pSocket->disconnectFromHost();
        m_pSocket = NULL;
        return;
    }
    connect(m_pSocket, &QTcpSocket::readyRead, this, &ChatRoom::recieve);
    emit log(QStringLiteral("连接成功"));
}
void ChatRoom::sendFrame(QImage &image){
    /*
     * 发送帧
    */
    //判断是否连接
    if (!m_pSocket){
        return;
    }
    QString words = "i";
    m_pSocket->write(words.toLatin1(),words.length());
    int size;
    QByteArray bArr;
    QBuffer buffer(&bArr);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer,"jpg",-1);
    size = bArr.size();
    QDataStream out(m_pSocket);
    out.setVersion(QDataStream::Qt_5_7);
    out<<(qint64)size<<bArr;
}
void ChatRoom::sendMessage(QString &msg){
    /*
     * 发送消息
    */
    //判断是否连接
    if (!m_pSocket){
        return;
    }
    msg = "w" + msg;
    m_pSocket->write(msg.toLatin1(), msg.length());
}
void ChatRoom::recieve(){
    /*
     * 接受帧
    */
    char judge;
    qint64 size;
    m_pSocket->read(&judge,1);
    if (judge == 'w'){
        size = m_pSocket->bytesAvailable();
        char buffer[10000];
        m_pSocket->read(buffer,size);
        emit log("message");
        return;
    }else if (judge == 'i'){
        QByteArray inArr;
        QDataStream in(m_pSocket);
        in.setVersion(QDataStream::Qt_5_7);
        in >> size;
        inArr.resize(size);
        in >> inArr;
        QImage image;
        image.loadFromData(inArr);
        inArr.resize(0);
        emit newCameraFrame(image, true);
        emit log("image");
        return;
    }
    emit log("none");
}
