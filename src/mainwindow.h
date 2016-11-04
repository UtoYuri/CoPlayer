#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "videoplayer.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    VideoPlayer *m_pVideoPlayer;

    QHBoxLayout *m_pHLayout;
};

#endif // MAINWINDOW_H
