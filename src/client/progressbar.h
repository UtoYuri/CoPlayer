#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QObject>
#include <QProgressBar>
#include <QMouseEvent>
#include <QDebug>

class ProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    ProgressBar(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void changePositon(float percent);

private:
    bool m_bPressed;
};

#endif // PROGRESSBAR_H
