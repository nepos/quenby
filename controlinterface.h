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

public:
    int createWebView();
    void destroyWebView(uint64_t key);
    void setWebViewUrl(uint64_t key, const QString &url);
    void setWebViewGeometry(uint64_t key, int x, int y, int w, int h);
    void setWebViewVisible(uint64_t key, bool visible);
    void setWebViewTransparentBackground(uint64_t key, bool transparent);
    void stackUnder(uint64_t topKey, uint64_t underKey);
    void stackOnTop(uint64_t key);

signals:
    // App → Server
    int onCreateWebViewRequested();
    void onDestroyWebViewRequested(uint64_t key);
    void onWebViewGeometryChangeRequested(uint64_t key, int x, int y, int w, int h);
    void onWebViewVisibleChangeRequested(uint64_t key, bool value);
    void onWebViewTransparentBackgroundChangeRequested(uint64_t key, bool value);
    void onWebViewStackUnder(uint64_t topKey, uint64_t underKey);
    void onWebViewStackOnTop(uint64_t key);

    // App ←/→ Server
    void onWebViewURLChanged(uint64_t key, const QString &value);
    void onWebViewURLChangeRequested(uint64_t key, const QString &value);

    // Server → App
    void onWebViewTitleChanged(uint64_t key, const QString &value);
    void onWebViewLoadProgressChanged(uint64_t key, int value);
};
