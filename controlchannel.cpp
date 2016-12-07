#include "controlchannel.h"

ControlChannel::ControlChannel(const QUrl &url, QObject *parent) :
    QObject(parent), url(url)
{
    connect(&webSocket, &QWebSocket::connected, this, &ControlChannel::onConnected);
    connect(&webSocket, &QWebSocket::disconnected, this, &ControlChannel::onDisconnected);
    connect(&webSocket, &QWebSocket::textMessageReceived, this, &ControlChannel::onTextMessageReceived);

    webSocket.open(QUrl(url));
}

void ControlChannel::onDisconnected()
{
    QTimer::singleShot(500, this, SLOT(onTimerTimeout()));
}

void ControlChannel::onConnected()
{
    qWarning() << "WebSocket connected";

    webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
}

void ControlChannel::onTextMessageReceived(QString message)
{
    qWarning() << "Message received:" << message;
}

void ControlChannel::onTimerTimeout()
{
    webSocket.open(QUrl(url));
}
