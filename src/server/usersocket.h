#ifndef USERSOCKET_H
#define USERSOCKET_H

#include <QTcpSocket>

class UserSocket : public QObject
{
    Q_OBJECT
public:
    UserSocket(QTcpSocket *socket, QObject *parent = 0);

    inline QString getUserId() const{
        return userId;
    }

    inline QString getRoomId() const{
        return roomId;
    }

    inline void setUserId(const QString &id){
        userId = id;
    }

    inline void setRoomId(const QString &id){
        roomId = id;
    }

    inline QTcpSocket* getSocket()const{
        return m_pSocket;
    }

signals:
    void disconnected();

private:
    QString userId;
    QString roomId;
    QTcpSocket *m_pSocket;
};

#endif // USERSOCKET_H
