#ifndef TRANSFER_H
#define TRANSFER_H

#include <QObject>
#include <QTimer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include <QFile>
#include <QtMath>

class Transfer : public QObject
{
    Q_OBJECT
public:
    explicit Transfer(QObject *parent = 0);
    ~Transfer();

    void setConnectionHost(const QString &host, const int port);

public slots:
    void send(const QString &filePathName);
    void transfer();
    void transferring(qint64);
    void error(QAbstractSocket::SocketError);
    void countSpeed();

signals:
    void progressChanged(const int percent);
    void speedChanged(const float speed);
    void log(const QString &logInfo);

protected:
    void init();

private:
    QTcpSocket *m_pSocket;
    QFile *m_fileLocalFile;
    qint64 m_nBytesTotal;
    qint64 m_nBytesWritten;
    qint64 m_nBytesToWrite;
    qint64 m_nBytesBlock;   //每次传送最大值
    QString m_sFilePathName;
    QByteArray m_TransferBlock; //数据缓存区 每次需要发送的数据

    QString m_sAddress;
    int m_nPort;

private:
    qint64 m_nPreBytesWritten; //上一秒已传输 测速用
    QTimer *m_pSpeedCounter;
};

#endif // TRANSFER_H
