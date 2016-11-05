#include "videowidget.h"

VideoWidget::VideoWidget(QWidget *parent):QVideoWidget(parent){
    setStyleSheet("background-color: rgba(0, 0, 0, 200)");
    setFocus();
    setWindowFlags (Qt::FramelessWindowHint);
    setAcceptDrops(true);
    initWidgetUi();
    initVideoWidget();
}
VideoWidget::~VideoWidget(){
    delete m_pBtnOpenFile;
    delete m_pBtnRemove;
    delete m_pListWidget;
    delete m_pVideoListWidget;
    delete m_pVLayout;
    delete m_pHLayout;
}
void VideoWidget::initWidgetUi(){
    /*
     * 构造界面
    */
    m_pBtnOpenFile = new QToolButton(this);

    m_pVideoListWidget = new QDockWidget(this);
    m_pBtnRemove = new QToolButton(m_pVideoListWidget);
    m_pListWidget = new QListWidget(m_pVideoListWidget);
    m_pVLayout = new QVBoxLayout;
    m_pHLayout = new QHBoxLayout;

    m_pHLayout->addWidget(m_pBtnRemove);

}
void VideoWidget::initVideoWidget(){
    /*
     * 初始化界面
    */
    m_bIsListShowing = false;
    //打开文件按钮
    connect(m_pBtnOpenFile, SIGNAL(clicked(bool)), this, SLOT(openFile()));
    m_pBtnOpenFile->setStyleSheet("QToolButton{"\
                                  "background-color: transparent;"\
                                  "border-image: url(:/icon/play-big.png);"
                                  "border:none;"\
                                  "width: 100px;"\
                                  "height: 100px;"
                                  "}"\
                                  "QToolButton:hover{"\
                                  "border-image: url(:/icon/play-big-hover.png);"
                                  "}");

    //播放列表界面
    m_pVideoListWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    m_pVideoListWidget->setVisible(false);
    m_pVideoListWidget->setFloating(true);
    m_pVideoListWidget->setWindowTitle(QStringLiteral("播放列表"));

    connect(m_pBtnRemove, &QToolButton::clicked, this, &VideoWidget::removeMedia);

    m_pVideoListWidget->setMaximumSize(QSize(400, 270));
    m_pVideoListWidget->setMinimumSize(QSize(400, 270));

    m_pVideoListWidget->setStyleSheet("background-color: #333;");

    m_pBtnRemove->setText(QStringLiteral("移除"));
    m_pBtnRemove->setStyleSheet("QToolButton{margin-top: 240px; background-color: #fff; min-width: 400px; min-height: 30px; border: none; font-size: 14px; border-radius: 4px;}"
                                "QToolButton:hover{background-color: #c33; color: #fff}");

    m_pListWidget->verticalScrollBar()->setVisible(false);
    m_pListWidget->horizontalScrollBar()->setVisible(false);

    m_pListWidget->setStyleSheet("QListWidget{outline: 0px; border:none; color:#fff; font-size: 14px;background-color: #383838; min-width: 400px; min-height: 240px}"
                               "QListWidget::Item{height: 35px;border-bottom: 1px solid #3f3f3f;}"
                               "QListWidget::Item:hover{padding-left:5px; background:#333; }"
                               "QListWidget::item:selected{padding-left:15px;background:#555;}"
                               );
    connect(m_pListWidget, &QListWidget::itemDoubleClicked, [=](QListWidgetItem * item){
        emit playMedia(m_pListWidget->row(item));
    });
}
void VideoWidget::adjustWidget(){
    /*
     * 布局变化
    */
    int x = (this->width() - 100) / 2;
    int y = (this->height() - 100) / 2;
    m_pBtnOpenFile->move(x, y);
}
void VideoWidget::removeMedia(){
    /*
     * 移除资源
    */
    int index = m_pListWidget->currentRow();
    delete m_pListWidget->takeItem(index);
    emit deleteMedia(index);
}
void VideoWidget::addMedia(const QString &fileName){
    /*
     * 添加资源
    */
    m_pListWidget->addItem(fileName);
}
void VideoWidget::toggleListWidget(bool show){
    /*
     * 显示/隐藏列表
    */
    int start;
    int end;
    if (show){
        start = 0;
        end = 1;
    }else{
        start = 1;
        end = 0;
    }
    m_pVideoListWidget->setVisible(show);
    QPropertyAnimation *animation = new QPropertyAnimation(m_pVideoListWidget, "windowOpacity");
    animation->setDuration(300);
    animation->setStartValue(start);
    animation->setEndValue(end);
    animation->start();
    m_bIsListShowing = show;

    QTimer::singleShot(500, [=](){
        animation->deleteLater();
    });
}
void VideoWidget::openFile(){
    /*
     * 打开文件
    */
    QStringList fileName = QFileDialog::getOpenFileNames(this, "Open Media", "/", "Movie Files (*.MP4 *.AVI *.RMVB);;Music Files(*.mp3)");
    if (!fileName.length()){
        return;
    }
    emit playNewMedias(fileName);
}
void VideoWidget::showButton(){
    /*
     * 显示打开文件按钮
    */
    m_pBtnOpenFile->setVisible(true);
}
void VideoWidget::hideButton(){
    /*
     * 隐藏打开文件按钮
    */
    m_pBtnOpenFile->setVisible(false);
}
void VideoWidget::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Escape){
        emit fullScreenToggled(false);
        event->accept();
    }else if(event->key() == Qt::Key_Space){
        emit play();
        event->accept();
    }else if(event->key() == Qt::Key_Left){
        emit rewind();
        event->accept();
    }else if(event->key() == Qt::Key_Right){
        emit fastForward();
        event->accept();
    }
    event->ignore();
}
void VideoWidget::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        emit play();
        event->accept();
    }
}
void VideoWidget::wheelEvent(QWheelEvent *event){
    if(event->delta() > 0){
        emit volumeChanged(5);
    }else{
        emit volumeChanged(-5);
    }
}
void VideoWidget::dropEvent(QDropEvent *event){
    QList<QUrl> urls = event->mimeData()->urls();
    QStringList files;
    for (int i = 0; i < urls.size(); ++i){
        files.append(urls.at(i).toString());
    }
    emit playNewMedias(files);
}
void VideoWidget::dragEnterEvent(QDragEnterEvent *event){
    //如果为文件，则支持拖放
    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}
void VideoWidget::paintEvent(QPaintEvent *){
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

