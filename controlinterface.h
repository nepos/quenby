/***
  Copyright (c) 2017 Nepos GmbH

  Authors: Daniel Mack <daniel@nepos.io>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, see <http://www.gnu.org/licenses/>.
***/

#pragma once

#include <QObject>

class ControlInterface : public QObject
{
    Q_OBJECT

public:
    explicit ControlInterface(QObject *parent = 0);

public slots:
    int createWebView();
    void destroyWebView(int key);
    void setWebViewUrl(int key, const QString &url);
    void setWebViewGeometry(int key, int x, int y, int w, int h);
    void setWebViewVisible(int key, bool visible);
    void setWebViewTransparentBackground(int key, bool transparent);
    void stackUnder(int topKey, int underKey);
    void stackOnTop(int key);

signals:
    // App → Server
    int onCreateWebViewRequested();
    void onDestroyWebViewRequested(int key);
    void onWebViewGeometryChangeRequested(int key, int x, int y, int w, int h);
    void onWebViewVisibleChangeRequested(int key, bool value);
    void onWebViewTransparentBackgroundChangeRequested(int key, bool value);
    void onWebViewStackUnder(int topKey, int underKey);
    void onWebViewStackOnTop(int key);

    // App ←/→ Server
    void onWebViewURLChanged(int key, const QString &value);
    void onWebViewURLChangeRequested(int key, const QString &value);

    // Server → App
    void onWebViewTitleChanged(int key, const QString &value);
    void onWebViewLoadProgressChanged(int key, int value);
};
