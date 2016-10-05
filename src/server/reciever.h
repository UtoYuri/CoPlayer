#ifndef RECIEVER_H
#define RECIEVER_H

#include <QObject>
#include <QTcpSocket>
#include <QFile>
#include <QDataStream>
#include <QHostAddress>

class Reciever : public QObject
{
    Q_OBJECT
public:
    explicit Reciever(QTcpSocket *socket, QObject *parent = 0);
    ~Reciever();

    void download();

protected:
    void init();

public slots:
    void recieving();
    void error(QAbstractSocket::SocketError);

signals:
    void progressChanged(const int percent);
    void log(const QString &logInfo);
    void recieved();

private:
    QTcpSocket *m_pSocket;
    qint64 m_nBytesTotal;
    qint64 m_nBytesRecieved;
    qint64 m_nFileNameSize;
    QString m_sFileName;
    QFile *m_fileLocalFile;
    QByteArray m_RecieveBlock;  //数据收集缓冲区
};

#endif // RECIEVER_H
