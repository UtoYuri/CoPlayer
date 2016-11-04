#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pHLayout = new QHBoxLayout(ui->centralWidget);
    m_pVideoPlayer = new VideoPlayer(ui->centralWidget);
    m_pHLayout->addWidget(m_pVideoPlayer);
    m_pHLayout->setSpacing(0);
    m_pHLayout->setMargin(0);
    ui->centralWidget->setLayout(m_pHLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
