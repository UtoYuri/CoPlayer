#ifndef MYVIDEOWIDGET_H
#define MYVIDEOWIDGET_H

#include <QVideoWidget>
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>

class VideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    VideoWidget(QWidget *parent = 0);

protected:
    void mouseDoubleClickEvent (QMouseEvent* event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void adjustScreen(const bool adjust);
    void play();
};

#endif // MYVIDEOWIDGET_H
