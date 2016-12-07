#include <QWebEngineProfile>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "webpage.h"

MainWindow::MainWindow(QUrl mainViewUrl, QUrl controlChannelUrl, QWidget *parent) :
    QMainWindow(parent)
{
    layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);

    window = new QWidget;
    window->setLayout(layout);
    setCentralWidget(window);

    cc = new ControlChannel(controlChannelUrl);
    QObject::connect(cc, &ControlChannel::openBrowser, this, &MainWindow::onOpenBrowser);
    QObject::connect(cc, &ControlChannel::closeBrowser, this, &MainWindow::onCloseBrowser);

    mainView = new QWebEngineView;
    mainWebPage = new WebPage(QWebEngineProfile::defaultProfile(), mainView);
    mainView->setPage(mainWebPage);
    mainView->setUrl(mainViewUrl);
    layout->addWidget(mainView);

    browserView = new QWebEngineView;
    browserWebPage = new WebPage(QWebEngineProfile::defaultProfile(), browserView);
    browserView->setPage(browserWebPage);
}

void MainWindow::onOpenBrowser(const QString &url)
{
    browserView->setUrl(QUrl(url));
    browserView->setHidden(false);
    layout->addWidget(browserView);
}

void MainWindow::onCloseBrowser()
{
    browserView->setHidden(true);
    layout->removeWidget(browserView);
}

void MainWindow::addWebView(const QUrl url)
{
    QWebEngineView *webView = new QWebEngineView;
    WebPage *webPage = new WebPage(QWebEngineProfile::defaultProfile(), webView);
    webView->setPage(webPage);
    webView->setUrl(url);

    layout->addWidget(webView);
}

MainWindow::~MainWindow()
{
    delete window;
}
