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

#include <QWebEngineProfile>

#include "mainwindow.h"
#include "webpage.h"

MainWindow::MainWindow(QUrl mainViewUrl, int controlPort, QWidget *parent) :
    QMainWindow(parent), socketClients(), channel(), interface()
{
    layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);

    window = new QWidget;
    window->setLayout(layout);
    setCentralWidget(window);

    mainView = new QWebEngineView;
    mainWebPage = new WebPage(QWebEngineProfile::defaultProfile(), mainView);
    mainView->setPage(mainWebPage);
    mainView->setUrl(mainViewUrl);
    layout->addWidget(mainView);

    browserView = new QWebEngineView;
    browserWebPage = new WebPage(QWebEngineProfile::defaultProfile(), browserView);
    browserView->setPage(browserWebPage);
    browserView->setFixedHeight(600);

    socketServer = new QWebSocketServer(QStringLiteral("Control server"), QWebSocketServer::NonSecureMode, this);
    connect(socketServer, &QWebSocketServer::newConnection, this, &MainWindow::onNewServerConnection);

    channel.registerObject(QStringLiteral("main"), &interface);
    socketServer->listen(QHostAddress::LocalHost, controlPort);

    connect(&interface, &ServerInterface::onBrowserURLChanged, [this](const QString &value) {
        browserView->setUrl(QUrl(value));
    });

    connect(&interface, &ServerInterface::onBrowserVisibleChanged, [this](bool value) {
        if (value) {
            browserView->setHidden(false);
            layout->addWidget(browserView);
        } else {
            browserView->setHidden(true);
            layout->removeWidget(browserView);
        }
    });

    connect(browserView, &QWebEngineView::urlChanged, [this](const QUrl &url) {
        interface.setProperty("browserURL", url.url());
    });

    connect(browserView, &QWebEngineView::titleChanged, [this](const QString &title) {
        interface.setProperty("browserTitle", title);
    });
}

void MainWindow::onNewServerConnection() {
    QWebSocket *socket = socketServer->nextPendingConnection();
    WebChannelTransport *transport = new WebChannelTransport(socket);

    connect(transport, &WebChannelTransport::disconnected, this, &MainWindow::onTransportDisconnected);
    channel.connectTo(transport);
    socketClients << transport;
}

void MainWindow::onTransportDisconnected() {
    WebChannelTransport *transport = qobject_cast<WebChannelTransport *>(sender());
    if (transport) {
        channel.disconnectFrom(transport);
        socketClients.removeAll(transport);
        delete transport;
    }
}

MainWindow::~MainWindow()
{
    delete window;
}
