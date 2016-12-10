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

#ifndef WEBCHANNELTRANSPORT_H
#define WEBCHANNELTRANSPORT_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtWebSockets/QWebSocket>
#include <QtWebChannel/QWebChannelAbstractTransport>

class WebChannelTransport : public QWebChannelAbstractTransport
{
    Q_OBJECT

public:
    explicit WebChannelTransport(QWebSocket *socket);
    ~WebChannelTransport();

    void sendMessage(const QJsonObject &json) Q_DECL_OVERRIDE;

signals:
    void disconnected();

private slots:
    void onTextMessageReceived(const QString &message);

private:
    QWebSocket *socket;
};

#endif // WEBCHANNELTRANSPORT_H
