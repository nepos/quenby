#ifndef CONTROLCHANNEL_H
#define CONTROLCHANNEL_H

#include <QObject>
#include <QTimer>
#include <QtWebSockets/QWebSocket>

class ControlChannel : public QObject
{
    Q_OBJECT
public:
    explicit ControlChannel(const QUrl &url, QObject *parent = Q_NULLPTR);

signals:
    void openBrowser(const QString &url);
    void closeBrowser();

private Q_SLOTS:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(QString message);
    void onTimerTimeout();

private:
    QWebSocket webSocket;
    QUrl url;
};

#endif // CONTROLCHANNEL_H
