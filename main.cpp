#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    w.setWindowState(Qt::WindowFullScreen);
    w.showFullScreen();

    w.foo();
    w.foo();
    w.foo();

    return a.exec();
}
