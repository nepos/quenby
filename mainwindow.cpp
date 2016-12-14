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

MainWindow::MainWindow(QUrl mainViewUrl, int mainViewWidth, int mainViewHeight, QWidget *parent) :
    QMainWindow(parent), controlChannel(), controlInterface(), views()
{
    window = new QWidget;
    setCentralWidget(window);

    createControlInterface();

    QWebEngineView *view = addWebView();
    view->page()->setWebChannel(&controlChannel);
    view->setUrl(mainViewUrl);
    view->setGeometry(0, 0, mainViewWidth, mainViewHeight);

    connect(view, &QWebEngineView::titleChanged, [this](const QString &title) {
        setWindowTitle(title);
    });
}

void MainWindow::createControlInterface()
{
    connect(&controlInterface, &ControlInterface::onCreateWebViewRequested, [this]() {
        int index = views.size();
        QWebEngineView *view = addWebView();

        connect(view, &QWebEngineView::urlChanged, [this, index](const QUrl &url) {
            emit controlInterface.onWebViewURLChanged(index, url.url());
        });

        connect(view, &QWebEngineView::titleChanged, [this, index](const QString &title) {
            emit controlInterface.onWebViewTitleChanged(index, title);
        });

        connect(view, &QWebEngineView::loadProgress, [this, index](int progress) {
            emit controlInterface.onWebViewLoadProgressChanged(index, progress);
        });

        return index;
    });

    connect(&controlInterface, &ControlInterface::onDestroyWebViewRequested, [this](int index) {
        QWebEngineView *view = lookupWebView(index);
        if (view && index > 0) {
            view->setVisible(false);
            views[index] = Q_NULLPTR;
            delete view;
        }
    });

    connect(&controlInterface, &ControlInterface::onWebViewURLChangeRequested, [this](int index, const QString &url) {
        QWebEngineView *view = lookupWebView(index);
        if (view)
            view->setUrl(QUrl(url));
    });

    connect(&controlInterface, &ControlInterface::onWebViewGeometryChangeRequested, [this](int index, int x, int y, int w, int h) {
        QWebEngineView *view = lookupWebView(index);
        if (view)
            view->setGeometry(x, y, w, h);
    });

    connect(&controlInterface, &ControlInterface::onWebViewVisibleChangeRequested, [this](int index, bool value) {
        QWebEngineView *view = lookupWebView(index);
        if (view)
            view->setVisible(value);
    });

    connect(&controlInterface, &ControlInterface::onWebViewTransparentBackgroundChangeRequested, [this](int index, bool value) {
        QWebEngineView *view = lookupWebView(index);
        if (view) {
            if (value) {
                view->setAutoFillBackground(false);
                view->page()->setBackgroundColor(Qt::transparent);
            } else {
                view->setAutoFillBackground(true);
                view->page()->setBackgroundColor(Qt::white);
            }
        }
    });

    controlChannel.registerObject(QStringLiteral("main"), &controlInterface);
}

QWebEngineView *MainWindow::addWebView()
{
    QWebEngineView *view = new QWebEngineView(window);
    view->setAutoFillBackground(true);

    WebPage *page = new WebPage(QWebEngineProfile::defaultProfile(), view);
    view->setPage(page);

    views << view;

    return view;
}

QWebEngineView *MainWindow::lookupWebView(int index) {
    if (index >= 0 && index < views.size())
        return views[index];

    return Q_NULLPTR;
}

MainWindow::~MainWindow()
{
    delete window;
}
