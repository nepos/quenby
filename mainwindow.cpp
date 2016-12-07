#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "webpage.h"

#include <QWebEngineView>
#include <QWebEngineProfile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    layout = new QVBoxLayout;
    window = new QWidget;
    window->setLayout(layout);
    setCentralWidget(window);
}

void MainWindow::foo()
{
    QWebEngineView *webView = new QWebEngineView;
    WebPage *webPage = new WebPage(QWebEngineProfile::defaultProfile(), webView);
    webView->setPage(webPage);

    QUrl url("http://acid3.acidtests.org/");
    webView->setUrl(url);

    layout->addWidget(webView);
}

MainWindow::~MainWindow()
{
    delete window;
}
