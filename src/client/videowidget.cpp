#include "videowidget.h"

VideoWidget::VideoWidget(QWidget *parent):QVideoWidget(parent){

}

void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        emit adjustScreen(true);
        event->accept();
    }
}
void VideoWidget::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Escape){
        emit adjustScreen(false);
        event->accept();
    }
}
void VideoWidget::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        emit play();
        event->accept();
    }
}

