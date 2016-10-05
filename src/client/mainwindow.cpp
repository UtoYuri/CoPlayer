#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->log->setEnabled(false);

    m_pPlayer = new Player(ui->player_widget);
    m_pPlayer->show();
//    m_pPlayer->setMedia("file:///D:/%E8%BF%85%E9%9B%B7%E4%B8%8B%E8%BD%BD/%E8%A1%8C%E5%B0%B8%E8%B5%B0%E8%82%89/%E8%A1%8C%E5%B0%B8%E8%B5%B0%E8%82%89.The.Walking.Dead.S01E01.Chi_Eng.HDTVrip.720X396-YYeTs%E4%BA%BA%E4%BA%BA%E5%BD%B1%E8%A7%86.rmvb");
    m_pPlayer->setMedia("http://blog.urdreamer.cn/IU.mp4");

    init();
}

MainWindow::~MainWindow(){
    delete ui;
}
void MainWindow::resizeEvent(QResizeEvent *){
    m_pPlayer->resize(ui->player_widget->size());
}
void MainWindow::init(){
    m_bIsOnline = false;
    m_pOnlineSocket = new QTcpSocket(this);
    m_pOnlineSocket->connectToHost(QHostAddress("119.28.62.13"), 60000);
    connect(m_pOnlineSocket, &QTcpSocket::connected, this, &MainWindow::logIn);
    connect(m_pOnlineSocket,SIGNAL(disconnected()),this,SLOT(logOff()));
//    connect(m_pOnlineSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(ReadError(QAbstractSocket::SocketError)));
}
void MainWindow::logIn(){
    m_bIsOnline = true;
    ui->messages->append(QStringLiteral("在线服务器已连接"));
    ui->log->setEnabled(true);
    m_pMessageSocket = new QTcpSocket(this);
    m_pMessageSocket->connectToHost(QHostAddress("119.28.62.13"), 60001);
    connect(m_pMessageSocket, &QTcpSocket::connected, [=](){
        ui->messages->append(QStringLiteral("聊天服务器已连接"));
    });
    connect(m_pMessageSocket, &QTcpSocket::readyRead, this, &MainWindow::newMessage);
    connect(m_pMessageSocket,SIGNAL(disconnected()),this,SLOT(deleteLater()));
}
void MainWindow::logOff(){
    m_bIsOnline = false;
    QTcpSocket *t = static_cast<QTcpSocket*>(sender());
    t->deleteLater();
    ui->messages->append(QStringLiteral("退出登录"));
}
void MainWindow::newMessage(){
    if (!m_pMessageSocket->bytesAvailable()){
        return;
    }
    QString data = m_pMessageSocket->readAll();
    ui->messages->append(QStringLiteral("收到消息") + data);
}

void MainWindow::on_log_clicked()
{
    QString data = "userId=" + ui->user_id->text() + "&pass=" + ui->pass->text();
    m_pOnlineSocket->write(data.toLatin1());
}

void MainWindow::on_send_clicked()
{
    if (!m_bIsOnline){
        ui->messages->append(QStringLiteral("尚未登录"));
        return;
    }
    m_pMessageSocket->write(ui->message->toPlainText().toLatin1());
}
