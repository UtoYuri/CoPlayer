#include "transfer.h"

Transfer::Transfer(QObject *parent) : QObject(parent){
    init();
}
Transfer::~Transfer(){
    delete m_pSocket;
    delete m_pSpeedCounter;
}

void Transfer::setConnectionHost(const QString &host, const int port){
    /*
     * 设置socket连接参数
    */
    m_sAddress = host;
    m_nPort = port;
}
void Transfer::send(const QString &filePathName){
    /*
     * filePathName: (C:/...)
     * 重置传送参数
     * 创建tcp连接
     *      成功创建则触发发送槽
    */
    m_nBytesWritten = 0;
    m_sFilePathName = filePathName;
    m_pSocket->connectToHost(QHostAddress(m_sAddress), m_nPort);
    emit log(QStringLiteral("连接服务器"));
}
void Transfer::transfer(){
    /*
     * 开始上传（上传文件头信息）
     * 打开文件
     *      打开失败则报错并断开TCP连接
     * 测速计时器开始
     * 获取文件大小信息
     * 初始化数据流
     * 添加传送文件头信息
     * 上传头信息
    */
    emit log(QStringLiteral("连接成功,准备上传文件"));
    m_fileLocalFile = new QFile(m_sFilePathName);
    if (!m_fileLocalFile->open(QFile::ReadOnly)){
        emit log(QStringLiteral("文件打开失败"));
        m_pSocket->disconnect();
        return;
    }
    emit log(QStringLiteral("开始上传"));
    m_pSpeedCounter->start();
    m_nBytesTotal = m_fileLocalFile->size();
    QDataStream uploader(&m_TransferBlock, QIODevice::WriteOnly);
    uploader.setVersion(QDataStream::Qt_5_7);
    QString fileName = m_sFilePathName.right(m_sFilePathName.size() - m_sFilePathName.lastIndexOf('/') - 1);
    uploader << qint64(0) << qint64(0) <<fileName;
    m_nBytesTotal += m_TransferBlock.size();
    uploader.device()->seek(0);
    uploader << m_nBytesTotal << qint64(m_TransferBlock.size() - sizeof(qint64) * 2);
    m_nBytesToWrite = m_nBytesTotal - m_pSocket->write(m_TransferBlock);
    m_TransferBlock.resize(0);
}
void Transfer::transferring(qint64 byteNum){
    /*
     * 继续上传（上传文件内容）
     * 刷新进度
     * 判断是否上传结束
     *      如果结束则log并停止测速器 关闭TCP连接
     *      否则更新缓冲区继续上传
    */
    emit progressChanged(m_nBytesWritten * 100.0 / m_nBytesTotal);
    m_nBytesWritten += byteNum;
    if (m_nBytesToWrite > 0){
        m_TransferBlock = m_fileLocalFile->read(qMin(m_nBytesToWrite, m_nBytesBlock));
        m_nBytesToWrite -= (int)m_pSocket->write(m_TransferBlock);
        m_TransferBlock.resize(0);
    }else{
        m_fileLocalFile->close();
        m_pSocket->close();
        m_pSpeedCounter->stop();
        emit log(QStringLiteral("上传成功"));
        emit progressChanged(m_nBytesWritten * 100.0 / m_nBytesTotal);
    }
//    if (m_nBytesTotal == m_nBytesWritten){
//        m_fileLocalFile->close();
//        m_pSocket->close();
//        emit log(QStringLiteral("上传成功"));
//        m_pSpeedCounter->stop();
//        emit progressChanged(m_nBytesWritten * 100.0 / m_nBytesTotal);
//    }
}
void Transfer::error(QAbstractSocket::SocketError){
    /*
     * 出现错误则log
    */
    emit log(QStringLiteral("发生错误:\t") + m_pSocket->errorString());
}
void Transfer::countSpeed(){
    /*
     * 测速
     * 根据 上一秒已上传信息和当前已上传信息 计算出上传速度
     * 刷新上一秒已传信息变量
    */
    emit speedChanged((m_nBytesWritten - m_nPreBytesWritten) / 10240.0);
    m_nPreBytesWritten = m_nBytesWritten;
}
void Transfer::init(){
    /*
     * 初始化所有参数
     * 创建TCPSocket
     * 连接socket信号槽
     * 监控连接信号 触发上传文件槽
     * 监控错误信号 触发报错槽
     * 监控数据传送信号 触发持续传送槽
     * 创建测速器
    */
    m_nBytesBlock = 10240 * 16;
    m_nBytesTotal = 0;
    m_nBytesWritten = 0;
    m_nBytesToWrite = 0;
    m_nPreBytesWritten = 0;
    m_pSocket = new QTcpSocket(this);
    connect(m_pSocket, &QTcpSocket::connected, this, &Transfer::transfer);
    connect(m_pSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
    connect(m_pSocket, &QTcpSocket::bytesWritten, this, &Transfer::transferring);
    m_pSpeedCounter = new QTimer(this);
    m_pSpeedCounter->setInterval(1000);
    connect(m_pSpeedCounter, &QTimer::timeout, this, &Transfer::countSpeed);
}
