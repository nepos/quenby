#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QWebEngineView>

#include "controlchannel.h"
#include "webpage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QUrl mainViewUrl, QUrl controlChannelUrl, QWidget *parent = 0);
    ~MainWindow();

    void addWebView(const QUrl url);

private Q_SLOTS:
    void onOpenBrowser(const QString &url);
    void onCloseBrowser();

private:
    QWidget *window;
    QVBoxLayout *layout;
    ControlChannel *cc;

    QWebEngineView *mainView;
    QWebEngineView *browserView;

    WebPage *mainWebPage;
    WebPage *browserWebPage;
};

#endif // MAINWINDOW_H
