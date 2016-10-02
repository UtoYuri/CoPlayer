#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

//#include "mainwindow.h"
//#include <QApplication>
//#include <QtWebEngineWidgets/QWebEngineView>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    QWebEngineView *view = new QWebEngineView;
//    view->load(QUrl(QStringLiteral("http://hunter.urdreamer.cn/")));
//    view->show();

//    return a.exec();
//}
