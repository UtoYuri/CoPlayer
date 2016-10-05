#include "progressbar.h"

ProgressBar::ProgressBar(QWidget *parent):QProgressBar(parent){
    m_bPressed = false;
    setMouseTracking(true);
}

void ProgressBar::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        m_bPressed = true;
        event->accept();
    }
}
void ProgressBar::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        if (m_bPressed) {
            emit changePositon(event->pos().x() * 1.0 / size().width());
            event->accept();
            m_bPressed = false;
            return;
        }
        event->ignore();
    }
}
void ProgressBar::mouseMoveEvent(QMouseEvent *event){
    if (m_bPressed) {
        emit changePositon(event->pos().x() * 1.0 / size().width());
        event->accept();
    }
    event->ignore();
}
