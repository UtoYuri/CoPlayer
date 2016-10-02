#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    resize(QSize(960,600));

    p = new Player(this);
    p->show();

}

MainWindow::~MainWindow(){
    delete ui;
}
void MainWindow::resizeEvent(QResizeEvent *){
    p->resize(size());
}
