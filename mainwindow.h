#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QWebEngineView>
#include <QWebChannel>
#include <QtWebSockets/QWebSocketServer>

#include "controlinterface.h"
#include "webpage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QUrl mainViewUrl, int mainViewWidth, int mainViewHeight, QWidget *parent = Q_NULLPTR);
    ~MainWindow();

private:
    QWidget *window;

    void createControlInterface();
    QWebChannel controlChannel;
    ControlInterface controlInterface;

    QList<QWebEngineView*> views;

    QWebEngineView *addWebView();
    QWebEngineView *lookupWebView(int index);
};

#endif // MAINWINDOW_H
