#include "audiochat.h"

AudioChat::AudioChat(QObject *parent) : QObject(parent){
    initAudioOpt();
    initAudioChat();
}
void AudioChat::initAudioOpt(){
    /*
     * 初始化配置
    */
    //设置音频采集频率
    m_nTimeClip = 500;  //ms

    //设置音频聊天状态
    m_AudioChatState = AudioChat::Off;  //state

    //设置音频格式
    m_AudioFormat.setSampleRate(8000);
    m_AudioFormat.setChannelCount(1);
    m_AudioFormat.setSampleSize(8);
    m_AudioFormat.setCodec("audio/pcm");
    m_AudioFormat.setByteOrder(QAudioFormat::LittleEndian);
    m_AudioFormat.setSampleType(QAudioFormat::UnSignedInt);

    //如果不支持则自动选取其他格式
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(m_AudioFormat)) {
        m_AudioFormat = info.nearestFormat(m_AudioFormat);
    }
}
void AudioChat::initAudioChat(){
    /*
     * 初始化语音通话
    */

    //设置语言录制计时器
    m_pTimer = new QTimer(this);
    m_pTimer->setInterval(m_nTimeClip);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(readAudioClip()));

    //设置音频采集器和播放器
    m_pAudioInputer = new QAudioInput(m_AudioFormat, this);
    m_pAudioOutputer = new QAudioOutput(m_AudioFormat, this);
    connect(m_pAudioOutputer, &QAudioOutput::stateChanged, [=](){
        emit log(QString::number(m_pAudioOutputer->state()));
        if (QAudio::IdleState == m_pAudioOutputer->state()) playAudioClip();
    });

    //设置音频发送/接受缓冲区
    m_pAudioClipSending = new QBuffer;
    m_pAudioClipSending->open(QIODevice::ReadWrite);
    m_TempBuffer.clear();
    m_pAudioClipRecieved = new QBuffer(&m_TempBuffer);
    m_pAudioClipRecieved->open(QIODevice::ReadWrite);

    //设置Udp收发类
    m_pAudioSocket = new QUdpSocket(this);
    connect(m_pAudioSocket, SIGNAL(readyRead()), this, SLOT(recieveAudioClip()));
}
void AudioChat::initUdpOpt(QHostAddress recieverIp, quint16 recieverPort, quint16 listenerPort){
    /*
     * 初始化Udp配置
    */
    //保存有关ip/port
    m_nRecieverPort = recieverPort;
    m_nListenerPort = listenerPort;
    m_RecieverHostAddress = recieverIp;

    //中断当前Udp收发器
    m_pAudioSocket->abort();

    //Udp监听
    if (!m_pAudioSocket->bind(QHostAddress::Any, m_nListenerPort)){
        emit log(QStringLiteral("监听失败, 端口:") + QString::number(m_nListenerPort));
        return;
    }
    emit log(QStringLiteral("正在监听, 端口:") + QString::number(m_nListenerPort));
}
AudioChat::AudioChatState AudioChat::audioChatState(){
    /*
     * 获取语音通话状态
    */
    return m_AudioChatState;
}
AudioChat::~AudioChat(){
    delete m_pAudioClipRecieved;
    delete m_pAudioClipSending;
    delete m_pAudioInputer;
    delete m_pAudioOutputer;
    delete m_pAudioSocket;
    delete m_pTimer;
}
void AudioChat::requestAudioChat(){
    /*
     * 请求语音聊天
    */
    m_AudioChatState = AudioChat::Pending;
    emit stateChanged(m_AudioChatState);
}
void AudioChat::startAudioChat(){
    /*
     * 开始语音聊天
    */
    emit log(QStringLiteral("开始语音聊天"));
    //设置已发送的录音字节长度
    m_nAudioDataSendedSize = 0;
    //设置聊天计时
    m_nChatTimes = 0;
    //设置聊天状态
    m_AudioChatState = AudioChat::On;
    emit stateChanged(m_AudioChatState);

    //开始录音并发送
    m_pAudioInputer->start(m_pAudioClipSending);
    m_pTimer->start();
    //开始播放收到的录音
    playAudioClip();
}
void AudioChat::stopAudioChat(){
    /*
     * 停止语音聊天
    */
    emit log(QStringLiteral("停止语音聊天"));
    //设置聊天状态
    m_AudioChatState = AudioChat::Off;
    emit stateChanged(m_AudioChatState);

    //停止录音发送和接收播放
    m_pTimer->stop();
    m_pAudioInputer->stop();
    m_pAudioOutputer->stop();

    //清空录音缓冲内容
    m_TempBuffer.clear();

    //重置收发缓冲区
    m_pAudioClipRecieved->reset();
    m_pAudioClipSending->reset();
}
void AudioChat::readAudioClip(){
    /*
     * 读取一段语音
    */
    //计时叠加
    m_nChatTimes += m_nTimeClip;
    emit chatTimesChanged(m_nChatTimes);

    // 发送已录制的音频
    QByteArray clip = m_pAudioClipSending->buffer();
    quint64 curSize = clip.size();
    clip = clip.mid(m_nAudioDataSendedSize);
    sendAudioClip(clip);
    m_nAudioDataSendedSize = curSize;
}
void AudioChat::sendAudioClip(QByteArray &audio){
    /*
     * 发送语音片段
    */
    int len = m_pAudioSocket->writeDatagram(audio, m_RecieverHostAddress, m_nRecieverPort);
//    emit log("send "+QString::number(len));
}
void AudioChat::recieveAudioClip(){
    /*
     * 接受语音片段
    */
    while (m_pAudioSocket->hasPendingDatagrams()) {
        QByteArray array;
        array.resize(m_pAudioSocket->pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        m_pAudioSocket->readDatagram(array.data(), array.size(), &sender, &senderPort);

        //过滤其他ip发送来的数据
        m_TempBuffer.append(array);
//        emit log("recieve " + QString::number(array.size()));
    }
}
void AudioChat::playAudioClip(){
    /*
     * 播放语音片段
    */
    if (m_AudioChatState == AudioChat::On)
        m_pAudioOutputer->start(m_pAudioClipRecieved);
}
