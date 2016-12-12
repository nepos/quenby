#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
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
    explicit MainWindow(QUrl mainViewUrl, int mainViewWidth, int mainViewHeight, int controlPort, QWidget *parent = Q_NULLPTR);
    ~MainWindow();

    void init(QUrl mainViewUrl, int controlPort);

private:
    QWidget *window;

    QWebSocketServer *socketServer;
    QList<WebChannelTransport *> socketClients;

    QWebChannel channel;
    ServerInterface interface;

    QList<QWebEngineView*> views;

    QWebEngineView *lookupView(int index);
};

#endif // MAINWINDOW_H
