/***
  Copyright (c) 2016 Nepos GmbH

  Authors: Daniel Mack <daniel@nepos.io>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or
  (at your option) any later version.

  This software is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this software; If not, see <http://www.gnu.org/licenses/>.
***/

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
