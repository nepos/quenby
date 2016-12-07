#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "controlchannel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QUrl mainViewUrl, QUrl controlChannelUrl, QWidget *parent = 0);
    ~MainWindow();

    void addWebView(const QUrl url);

private Q_SLOTS:
    void onOpenBrowser();

private:
    QWidget *window;
    QVBoxLayout *layout;
    ControlChannel *cc;
};

#endif // MAINWINDOW_H
