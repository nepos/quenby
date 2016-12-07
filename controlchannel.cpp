#include <QJsonDocument>
#include <QJsonObject>
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
}

void ControlChannel::onTextMessageReceived(QString message)
{
    QJsonDocument json = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject obj = json.object();
    QString command = obj["command"].toString();

    if (command == "openBrowser")
        emit openBrowser();

    qWarning() << "Message received:" << command;
}

void ControlChannel::onTimerTimeout()
{
    webSocket.open(QUrl(url));
}
