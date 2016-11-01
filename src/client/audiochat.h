#ifndef AUDIOCHAT_H
#define AUDIOCHAT_H

#include <QObject>
#include <QUdpSocket>
#include <QAudioInput>
#include <QAudioOutput>
#include <QBuffer>
#include <QTimer>

class AudioChat : public QObject
{
    Q_OBJECT
public:
    explicit AudioChat(QObject *parent = 0);
    ~AudioChat();

    enum AudioChatState{
        On,
        Off,
        Pending
    };

    void initAudioOpt(); //初始化基本变量
    void initAudioChat();   //初始化语音通话
    void initUdpOpt(QHostAddress recieverIp, quint16 recieverPort, quint16 listenerPort);  //初始化Udp配置
    AudioChatState audioChatState();   //语音通话状态

signals:
    void log(const QString &logInfo); //日志log
    void stateChanged(AudioChat::AudioChatState state);    //状态变化
    void chatTimesChanged(quint64 times);   //通话时长变化

public slots:
    void requestAudioChat();    //请求语音聊天
    void startAudioChat();  //开始语音聊天
    void stopAudioChat();   //停止语音聊天

    void readAudioClip();   //读取一段语音
    void sendAudioClip(QByteArray &audio);   //发送语音片段
    void recieveAudioClip(); //接受语音片段
    void playAudioClip();   //播放语音片段

private:
    QTimer *m_pTimer;   //计时器
    int m_nTimeClip;         //录音时间片长度
    quint64 m_nChatTimes;   //通话时长
    AudioChatState m_AudioChatState;    //视频聊天状态
    quint64 m_nAudioDataSendedSize; //已发送的数据大小

    quint16 m_nRecieverPort;    //接受者端口
    quint16 m_nListenerPort;    //本地监听端口
    QHostAddress m_RecieverHostAddress; //接收方ip
    QUdpSocket *m_pAudioSocket; //udp

    QBuffer *m_pAudioClipSending;  //待发送的语音片段
    QBuffer *m_pAudioClipRecieved;  //接受的语音片段
    QAudioInput *m_pAudioInputer;   //音频采集器
    QAudioOutput *m_pAudioOutputer; //音频播放器
    QAudioFormat m_AudioFormat;   //音频格式

    QByteArray m_TempBuffer;    //m_pAudioClipRecieved数据流

};

#endif // AUDIOCHAT_H
