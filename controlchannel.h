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
