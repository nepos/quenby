/***
  Copyright (c) 2017 Nepos GmbH

  Authors: Daniel Mack <daniel@nepos.io>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, see <http://www.gnu.org/licenses/>.
***/

#include <QApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    qputenv("QT_VIRTUALKEYBOARD_STYLE", QByteArray("nepos"));

    QApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("Simple kiosk browser");
    parser.addHelpOption();

    QCommandLineOption widthOption(QStringList() <<
                                   "w" << "width",
                                   "Main web view width [default: 1280].",
                                   "width", "1280");
    parser.addOption(widthOption);

    QCommandLineOption heightOption(QStringList() <<
                                    "i" << "height",
                                    "Main web view height [default: 800].",
                                    "height", "800");
    parser.addOption(heightOption);

    QCommandLineOption fullscreenOption(QStringList() <<
                                        "f" << "fullscreen",
                                        "Fullscreen display [default: off].");
    parser.addOption(fullscreenOption);

    QCommandLineOption defaultViewUrlOption(QStringList() <<
                                            "u" << "url",
                                            "Default view URL [default: http://localhost:3000/dist].",
                                            "url", "http://localhost:3000/dist");
    parser.addOption(defaultViewUrlOption);

    // These options are read by the Qt/Chromium glue layer by parsing the command line of the current process.
    // quenby silently accepts them if passed, but doesn't actually do anything with it.
    QCommandLineOption chromeLoggingOption("enable-logging", "", "enable-logging", "");
    parser.addOption(chromeLoggingOption);

    QCommandLineOption chromeLogLevelOption("log-level", "", "log-level", "0");
    parser.addOption(chromeLogLevelOption);

    QCommandLineOption chromeGPURasterizationOption("enable-gpu-rasterization");
    parser.addOption(chromeGPURasterizationOption);

    QCommandLineOption chromeGPUBuffersOption("enable-native-gpu-memory-buffers");
    parser.addOption(chromeGPUBuffersOption);

    QCommandLineOption numRasterThreadsOption("num-raster-threads", "", "num-raster-threads", "1");
    parser.addOption(numRasterThreadsOption);

    QCommandLineOption debugPortOption(QStringList() <<
                                       "p" << "remote-debug-port",
                                       "WebEngine debug port [default: 3002].",
                                       "remote-debug-port", "3002");
    parser.addOption(debugPortOption);

    parser.process(app);

    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", parser.value(debugPortOption).toUtf8());

    MainWindow w(QUrl(parser.value(defaultViewUrlOption)),
                 parser.value(widthOption).toInt(),
                 parser.value(heightOption).toInt());

    w.setFixedSize(parser.value(widthOption).toInt(),
                   parser.value(heightOption).toInt());

    if (parser.isSet(fullscreenOption)) {
        w.setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        w.setWindowState(Qt::WindowFullScreen);
        w.move(0, 0);
        w.showFullScreen();
    } else {
        w.show();
    }

    return app.exec();
}
