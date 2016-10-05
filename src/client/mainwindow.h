#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "player.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QFile>
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

public slots:
    void logIn();
    void logOff();
    void newMessage();

protected:
    void init();
    void resizeEvent(QResizeEvent* size);

private slots:
    void on_log_clicked();

    void on_send_clicked();

private:
    Ui::MainWindow *ui;

    Player *m_pPlayer;

    QTcpSocket *m_pOnlineSocket;
    QTcpSocket *m_pMessageSocket;

    bool m_bIsOnline;
};

#endif // MAINWINDOW_H
