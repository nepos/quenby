#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QVBoxLayout>
#include <QWebEngineView>
#include <QWebChannel>
#include <QtWebSockets/QWebSocketServer>

#include "serverinterface.h"
#include "webchanneltransport.h"
#include "webpage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QUrl mainViewUrl, int controlPort, QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void onNewServerConnection();
    void onTransportDisconnected();

private:
    QWidget *window;
    QVBoxLayout *layout;

    QWebEngineView *mainView;
    QWebEngineView *browserView;

    WebPage *mainWebPage;
    WebPage *browserWebPage;

    QWebSocketServer *socketServer;
    QList<WebChannelTransport *> socketClients;
    QWebChannel channel;

    ServerInterface interface;
};

#endif // MAINWINDOW_H
