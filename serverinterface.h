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

#ifndef SERVERINTERFACE_H
#define SERVERINTERFACE_H

#include <QObject>

class ServerInterface : public QObject
{
    Q_OBJECT

public:
    explicit ServerInterface(QObject *parent = 0);

public slots:
    int createWebView() {
        return emit onCreateWebViewRequested();
    };

    void destroyWebView(int index) {
        emit onDestroyWebViewRequested(index);
    };

    void setWebViewUrl(int index, const QString &url) {
        emit onWebViewURLChangeRequested(index, url);
    };

    void setWebViewGeometry(int index, int x, int y, int w, int h) {
        emit onWebViewGeometryChangeRequested(index, x, y, w, h);
    };

    void setWebViewVisible(int index, bool visible) {
        emit onWebViewVisibleChangeRequested(index, visible);
    };

    void setWebViewTransparentBackground(int index, bool visible) {
        emit onWebViewTransparentBackgroundChangeRequested(index, visible);
    };

signals:
    // App → Server
    int onCreateWebViewRequested();
    void onDestroyWebViewRequested(int index);
    void onWebViewGeometryChangeRequested(int index, int x, int y, int w, int h);
    void onWebViewVisibleChangeRequested(int index, bool value);
    void onWebViewTransparentBackgroundChangeRequested(int index, bool value);

    // App ←/→ Server
    void onWebViewURLChanged(int index, const QString &value);
    void onWebViewURLChangeRequested(int index, const QString &value);

    // Server → App
    void onWebViewTitleChanged(int index, const QString &value);
    void onWebViewLoadProgressChanged(int index, int value);
};

#endif // SERVERINTERFACE_H
