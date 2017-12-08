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

#include <QWebEngineProfile>
#include <QWebEngineView>
#include <QQuickItem>
#include <QQuickWidget>
#include <QVBoxLayout>
#include <QApplication>
#include <QTemporaryFile>
#include <QTimer>

#include "mainwindow.h"
#include "webenginepage.h"

MainWindow::MainWindow(QUrl mainViewUrl, int mainViewWidth, int mainViewHeight, QWidget *parent) :
    QMainWindow(parent),
    frame(new QWidget(this)),
    browserWidget(new QWidget(this)),
    layout(new QVBoxLayout(this)),
    quickWidget(new QQuickWidget(this)),
    inputPanel(nullptr),
    controlChannel(),
    controlInterface(),
    views()
{
    setCentralWidget(frame);
    frame->setLayout(layout);

    setAttribute(Qt::WA_TranslucentBackground);

    quickWidget->setFocusPolicy(Qt::NoFocus);
    quickWidget->setSource(QUrl("qrc:/inputpanel.qml"));
    quickWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    quickWidget->setVisible(false);

    layout->addWidget(browserWidget);
    layout->addWidget(quickWidget);
    layout->setSpacing(0);
    layout->setMargin(0);

    inputPanel = quickWidget->rootObject();
    if (inputPanel)
        inputPanel->setProperty("width", size().width());

    connect(inputPanel, SIGNAL(activated(bool)), this, SLOT(onActiveChanged(bool)));
    connect(inputPanel, SIGNAL(heightChanged(int)), this, SLOT(onHeightChanged(int)));

    createControlInterface();

    auto *view = addWebView();
    auto *page = view->page();
    view->page()->setWebChannel(&controlChannel);
    view->setUrl(mainViewUrl);
    view->setGeometry(0, 0, mainViewWidth, mainViewHeight);
    view->setAutoFillBackground(false);

    page->setBackgroundColor(Qt::transparent);

    QObject::connect(page, &WebEnginePage::featurePermissionRequested, [this, page](const QUrl &securityOrigin, WebEnginePage::Feature feature) {
        enum WebEnginePage::PermissionPolicy verdict =
                (securityOrigin.host() == "localhost") ?
                            WebEnginePage::PermissionGrantedByUser :
                            WebEnginePage::PermissionDeniedByUser;

         qInfo() << "WebEnginePage::featurePermissionRequested: " << feature << "verdict" << verdict;
         page->setFeaturePermission(securityOrigin, feature, verdict);
    });

    QObject::connect(view, &QWebEngineView::titleChanged, [this](const QString &title) {
        setWindowTitle(title);
    });

}

MainWindow::~MainWindow()
{
    if (quickWidget)
        delete quickWidget;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    if (inputPanel)
        inputPanel->setProperty("width", event->size().width());
}

void MainWindow::onActiveChanged(bool a)
{
    quickWidget->setVisible(a);
}

void MainWindow::onWidthChanged(int w)
{
    qDebug() << __PRETTY_FUNCTION__ << " :" << w;
}

void MainWindow::onHeightChanged(int h)
{
    auto newSize = quickWidget->size();
    newSize.setHeight(h);
    quickWidget->resize(newSize);
}

void MainWindow::createControlInterface()
{
    QObject::connect(&controlInterface, &ControlInterface::onCreateWebViewRequested, [this]() {
        int index = views.size();
        QWebEngineView *view = addWebView();

        QObject::connect(view, &QWebEngineView::urlChanged, [this, index](const QUrl &url) {
            emit controlInterface.onWebViewURLChanged(index, url.url());
        });

        QObject::connect(view, &QWebEngineView::titleChanged, [this, index](const QString &title) {
            emit controlInterface.onWebViewTitleChanged(index, title);
        });

        QObject::connect(view, &QWebEngineView::loadProgress, [this, index](int progress) {
            emit controlInterface.onWebViewLoadProgressChanged(index, progress);
        });

        return index;
    });

    QObject::connect(&controlInterface, &ControlInterface::onDestroyWebViewRequested, [this](int index) {
        QWebEngineView *view = lookupWebView(index);
        if (view && index > 0) {
            view->setVisible(false);
            views[index] = Q_NULLPTR;
            delete view;
        }
    });

    QObject::connect(&controlInterface, &ControlInterface::onWebViewURLChangeRequested, [this](int index, const QString &url) {
        QWebEngineView *view = lookupWebView(index);
        if (view)
            view->setUrl(QUrl(url));
    });

    QObject::connect(&controlInterface, &ControlInterface::onWebViewGeometryChangeRequested, [this](int index, int x, int y, int w, int h) {
        QWebEngineView *view = lookupWebView(index);
        if (view)
            view->setGeometry(x, y, w, h);
    });

    QObject::connect(&controlInterface, &ControlInterface::onWebViewVisibleChangeRequested, [this](int index, bool value) {
        QWebEngineView *view = lookupWebView(index);
        if (view)
            view->setVisible(value);
    });

    QObject::connect(&controlInterface, &ControlInterface::onWebViewTransparentBackgroundChangeRequested, [this](int index, bool value) {
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
    QWebEngineView *view = new QWebEngineView(browserWidget);
    view->setAutoFillBackground(true);

    WebEnginePage *page = new WebEnginePage(QWebEngineProfile::defaultProfile(), view);
    view->setPage(page);

    views << view;

    return view;
}

QWebEngineView *MainWindow::lookupWebView(int index)
{
    if (index >= 0 && index < views.size())
        return views[index];

    return Q_NULLPTR;
}

QWebEngineView *MainWindow::lookupVisibleWebView()
{
    for (int i=0; i<views.size(); i++)
        if (views[i]->isVisible())
            return views[i];

    return Q_NULLPTR;
}
