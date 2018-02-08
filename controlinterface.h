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

class QWebEngineHistory;

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
    void setWebViewNext(int key);
    void setWebViewPrev(int key);
    void setWebViewStackUnder(int topKey, int underKey);
    void setWebViewStackOnTop(int key);
    void getWebViewForwardHistory(int key);
    void getWebViewBackwardHistory(int key);

    void showKeyboard(void);
    void hideKeyboard(void);


signals:
    // App → Server
    int onCreateWebViewRequested();
    void onDestroyWebViewRequested(int key);
    void onWebViewGeometryChangeRequested(int key, int x, int y, int w, int h);
    void onWebViewVisibleChangeRequested(int key, bool value);
    void onWebViewTransparentBackgroundChangeRequested(int key, bool value);
    void onWebViewStackUnderRequested(int topKey, int underKey);
    void onWebViewStackOnTopRequested(int key);
    void onWebViewNextRequested(int key);
    void onWebViewPrevRequested(int key);
    void onWebViewForwardHistoryRequestedL(int key);
    void onWebViewBackwardHistoryRequestedL(int key);
    void onWebViewForwardHistoryRequested(int key, const QStringList);
    void onWebViewBackwardHistoryRequested(int key, const QStringList);

    void onKeyboardShowRequested(void);
    void onKeyboardHideRequested(void);

    // App ←/→ Server
    void onWebViewURLChanged(int key, const QString &value);
    void onWebViewHostnameChanged(int key, const QString &value);
    void onWebViewURLChangeRequested(int key, const QString &value);

    // Server → App
    void onWebViewTitleChanged(int key, const QString &value);
    void onWebViewLoadProgressChanged(int key, int value);





};
