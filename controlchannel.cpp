/***
  Copyright (c) 2016 Nepos GmbH

  Authors: Daniel Mack <daniel@nepos.io>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or
  (at your option) any later version.

  This software is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this software; If not, see <http://www.gnu.org/licenses/>.
***/

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
        emit openBrowser(obj["url"].toString());

    if (command == "closeBrowser")
        emit closeBrowser();

    qWarning() << "Message received:" << command;
}

void ControlChannel::onTimerTimeout()
{
    webSocket.open(QUrl(url));
}
