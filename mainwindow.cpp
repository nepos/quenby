#include <QWebEngineView>
#include <QWebEngineProfile>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "webpage.h"

MainWindow::MainWindow(QUrl mainViewUrl, QUrl controlChannelUrl, QWidget *parent) :
    QMainWindow(parent)
{
    layout = new QVBoxLayout;
    window = new QWidget;
    window->setLayout(layout);
    setCentralWidget(window);

    cc = new ControlChannel(controlChannelUrl);
    QObject::connect(cc, &ControlChannel::openBrowser, this, &MainWindow::onOpenBrowser);

    addWebView(mainViewUrl);
}

void MainWindow::onOpenBrowser()
{
    addWebView(QUrl(QStringLiteral("http://spiegel.de")));
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
