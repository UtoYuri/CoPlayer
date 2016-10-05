#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    m_pServer = new Server;

    connect(m_pServer, &Server::log, [=](const QString &logInfo){
        ui->log->append(logInfo);
    });
}

MainWindow::~MainWindow(){
    delete ui;
    delete m_pServer;
}

void MainWindow::on_connect_clicked()
{
    m_pServer->monitor();
}
