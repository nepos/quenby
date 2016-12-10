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

#include "webchanneltransport.h"

WebChannelTransport::WebChannelTransport(QWebSocket *socket) :
    QWebChannelAbstractTransport(socket),
    socket(socket)
{
    connect(socket, &QWebSocket::textMessageReceived, this, &WebChannelTransport::onTextMessageReceived);
    connect(socket, &QWebSocket::disconnected, this, &WebChannelTransport::disconnected);
}

WebChannelTransport::~WebChannelTransport() {
    socket->deleteLater();
}

void WebChannelTransport::onTextMessageReceived(const QString &message) {
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(message.toUtf8(), &error);

    qWarning() << "<<" << document.object();

    if (error.error)
        qWarning() << "QJsonDocument::fromJson() failed: " << error.errorString();
    else if (!document.isObject())
        qWarning() << "QJsonDocument::fromJson() did not return a JSON object: " << message;
    else
        emit messageReceived(document.object(), this);
}

void WebChannelTransport::sendMessage(const QJsonObject &json)
{
    QJsonDocument document(json);
    qWarning() << ">>" << document.toJson(QJsonDocument::Compact);
    socket->sendTextMessage(document.toJson(QJsonDocument::Compact));
}
