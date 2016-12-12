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

MainWindow::MainWindow(QUrl mainViewUrl, int mainViewWidth, int mainViewHeight, int controlPort, QWidget *parent) :
    QMainWindow(parent), socketClients(), channel(), interface(), views()
{
    window = new QWidget;
    setCentralWidget(window);

    QWebEngineView *view = new QWebEngineView(window);
    WebPage *page = new WebPage(QWebEngineProfile::defaultProfile(), view);
    view->setPage(page);
    view->setUrl(mainViewUrl);
    view->setGeometry(0, 0, mainViewWidth, mainViewHeight);
    views << view;

    socketServer = new QWebSocketServer(QStringLiteral("Control server"), QWebSocketServer::NonSecureMode, this);
    connect(socketServer, &QWebSocketServer::newConnection, [this]() {
        QWebSocket *socket = socketServer->nextPendingConnection();
        WebChannelTransport *transport = new WebChannelTransport(socket);

        connect(transport, &WebChannelTransport::disconnected, [this, transport]() {
            channel.disconnectFrom(transport);
            socketClients.removeAll(transport);
            delete transport;
        });

        channel.connectTo(transport);
        socketClients << transport;
    });

    socketServer->listen(QHostAddress::LocalHost, controlPort);

    connect(&interface, &ServerInterface::onCreateWebViewRequested, [this]() {
        QWebEngineView *view = new QWebEngineView(window);
        WebPage *page = new WebPage(QWebEngineProfile::defaultProfile(), view);
        view->setPage(page);
        int index = views.size();
        views << view;

        connect(view, &QWebEngineView::urlChanged, [this, index](const QUrl &url) {
            emit interface.onWebViewURLChanged(index, url.url());
        });

        connect(view, &QWebEngineView::titleChanged, [this, index](const QString &title) {
            emit interface.onWebViewTitleChanged(index, title);
        });

        connect(view, &QWebEngineView::loadProgress, [this, index](int progress) {
            emit interface.onWebViewLoadProgressChanged(index, progress);
        });

        return index;
    });

    connect(&interface, &ServerInterface::onDestroyWebViewRequested, [this](int index) {
        QWebEngineView *view = lookupView(index);
        if (view && index > 0) {
            view->setVisible(false);
            views[index] = Q_NULLPTR;
            delete view;
        }
    });

    connect(&interface, &ServerInterface::onWebViewURLChangeRequested, [this](int index, const QString &url) {
        QWebEngineView *view = lookupView(index);
        if (view)
            view->setUrl(QUrl(url));
    });

    connect(&interface, &ServerInterface::onWebViewGeometryChangeRequested, [this](int index, int x, int y, int w, int h) {
        QWebEngineView *view = lookupView(index);
        if (view)
            view->setGeometry(x, y, w, h);
    });

    connect(&interface, &ServerInterface::onWebViewVisibleChangeRequested, [this](int index, bool value) {
        QWebEngineView *view = lookupView(index);
        if (view)
            view->setVisible(value);
    });

    channel.registerObject(QStringLiteral("main"), &interface);
}

QWebEngineView *MainWindow::lookupView(int index) {
    if (index >= 0 && index < views.size())
        return views[index];

    return Q_NULLPTR;
}

MainWindow::~MainWindow()
{
    delete window;
}
