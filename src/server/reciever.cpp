#include "reciever.h"

#include <QMessageBox>
Reciever::Reciever(QTcpSocket *socket, QObject *parent) : QObject(parent){
    init();
    m_pSocket = socket;
    download();
}
Reciever::~Reciever(){

}
void Reciever::download(){
    if (!m_pSocket){
        emit log(QStringLiteral("文件下载socket初始化失败"));
        return;
    }
    connect(m_pSocket,SIGNAL(readyRead()),this,SLOT(recieving()));
    connect(m_pSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(error(QAbstractSocket::SocketError)));
    connect(m_pSocket, SIGNAL(disconnected()), m_pSocket, SLOT(deleteLater()));
}
void Reciever::init(){
    m_nBytesTotal = 0;
    m_nBytesRecieved = 0;
    m_nFileNameSize = 0;
}
void Reciever::recieving(){
    emit progressChanged(m_nBytesRecieved * 100.0 / m_nBytesTotal);
    QDataStream in(m_pSocket);
    in.setVersion(QDataStream::Qt_5_7);
    if (m_nBytesRecieved <= sizeof(qint64) * 2){
        if ((m_pSocket->bytesAvailable() >= sizeof(qint64) * 2) && !m_nFileNameSize){
            in >> m_nBytesTotal >> m_nFileNameSize;
            m_nBytesRecieved += sizeof(qint64) * 2;
        }
        if ((m_pSocket->bytesAvailable() >= m_nFileNameSize && m_nFileNameSize)){
            in >> m_sFileName;
            m_nBytesRecieved += m_nFileNameSize;
            m_fileLocalFile = new QFile(m_sFileName);
            if (!m_fileLocalFile->open(QFile::WriteOnly)){
                emit log(QStringLiteral("文件打开失败") + m_sFileName);
                m_pSocket->disconnectFromHost();
                return;
            }
            emit log(QStringLiteral("开始接收文件") + m_sFileName);
        }else{
            return;
        }
    }
    if(m_nBytesRecieved < m_nBytesTotal) {
        m_nBytesRecieved += m_pSocket->bytesAvailable();
        m_RecieveBlock = m_pSocket->readAll();
        m_fileLocalFile->write(m_RecieveBlock);
        m_RecieveBlock.resize(0);
    }
    if(m_nBytesRecieved == m_nBytesTotal){
        m_pSocket->close();
        m_fileLocalFile->close();
        emit log(QStringLiteral("接收完成"));
        emit progressChanged(0);
        emit recieved();
    }
}
void Reciever::error(QAbstractSocket::SocketError){
    emit log(QStringLiteral("发生错误:\t") + m_pSocket->errorString());
    emit progressChanged(0);
}
