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

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("Simple kiosk browser");
    parser.addHelpOption();

    QCommandLineOption widthOption(QStringList() << "w" << "width", "Main web view width", NULL, QStringLiteral("1280"));
    parser.addOption(widthOption);

    QCommandLineOption heightOption(QStringList() << "i" << "height", "Main web view height", NULL, QStringLiteral("800"));
    parser.addOption(heightOption);

    QCommandLineOption fullscreenOption(QStringList() << "f" << "fullscreen", "Fullscreen display [default: off].");
    parser.addOption(fullscreenOption);

    QCommandLineOption defaultViewUrlOption(QStringList() << "u" << "url", "Default view URL", NULL, QStringLiteral("http://localhost:3000/"));
    parser.addOption(defaultViewUrlOption);

#ifdef QT_DEBUG
    QCommandLineOption debugPortOption(QStringList() << "d" << "debug", "WebEngine debug port", NULL, QStringLiteral("3002"));
    parser.addOption(debugPortOption);
#endif

    parser.process(app);

#ifdef QT_DEBUG
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", parser.value(debugPortOption).toUtf8());
#endif

    MainWindow w(parser.value(defaultViewUrlOption),
                 parser.value(widthOption).toInt(),
                 parser.value(heightOption).toInt());

    if (parser.isSet(fullscreenOption)) {
        w.setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        w.setWindowState(Qt::WindowFullScreen);
        w.showFullScreen();
    } else {
        w.setFixedSize(parser.value(widthOption).toInt(),
                       parser.value(heightOption).toInt());
        w.show();
    }

    return app.exec();
}
