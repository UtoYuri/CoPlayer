#include "usersocket.h"

UserSocket::UserSocket(QTcpSocket *socket, QObject *parent):QObject(parent){
    m_pSocket = socket;
    connect(m_pSocket, &QTcpSocket::disconnected, [=](){
        emit disconnected();
    });
}
