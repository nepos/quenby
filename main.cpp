#include <QApplication>
#include "controlchannel.h"
#include "mainwindow.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800

#define CONTROL_CHANNEL_URL "ws://localhost:3000/ws/"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    ControlChannel cc(QUrl(QStringLiteral(CONTROL_CHANNEL_URL)));

    //QObject::connect(&cc, &ControlChannel::disconnected, &a, &QCoreApplication::quit);

    if (0) {
        w.setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        w.setWindowState(Qt::WindowFullScreen);
        w.showFullScreen();
    } else {
        w.setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
        w.show();
    }

    w.foo();
    w.foo();
    w.foo();

    return a.exec();
}
