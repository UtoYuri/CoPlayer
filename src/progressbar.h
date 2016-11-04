#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QObject>
#include <QProgressBar>
#include <QMouseEvent>

class ProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    ProgressBar(QWidget *parent = 0);
    ~ProgressBar();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void positionChanged(float percent);

private:
    bool m_bPressed;
};

#endif // PROGRESSBAR_H
