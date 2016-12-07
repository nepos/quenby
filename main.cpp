#include <QApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>

#include "mainwindow.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("Simple kiosk browser");
    parser.addHelpOption();

    QCommandLineOption fullscreenOption(QStringList() << "f" << "fullscreen", "Fullscreen display [default: off].");
    parser.addOption(fullscreenOption);

    QCommandLineOption defaultViewUrlOption(QStringList() << "u" << "url", "Default view URL", NULL, QStringLiteral("http://acid3.acidtests.org"));
    parser.addOption(defaultViewUrlOption);

    QCommandLineOption commandUrlOption(QStringList() << "c" << "command", "Command channel URL", NULL, QStringLiteral("ws://localhost:3000/ws/"));
    parser.addOption(commandUrlOption);

    parser.process(a);

    MainWindow w(parser.value(defaultViewUrlOption),
                 parser.value(commandUrlOption));

    if (parser.isSet(fullscreenOption)) {
        w.setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        w.setWindowState(Qt::WindowFullScreen);
        w.showFullScreen();
    } else {
        w.setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
        w.show();
    }

    return a.exec();
}
