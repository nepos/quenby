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
    void setKeyboardEnabled(bool enabled);
    void setWebViewStackUnder(int topKey, int underKey);
    void setWebViewStackOnTop(int key);
    void getWebViewForwardHistory(int key);
    void getWebViewBackwardHistory(int key);

    void showKeyboard(void);
    void hideKeyboard(void);

signals:
    // App → Server
    int onCreateWebViewRequest();
    void onDestroyWebViewRequest(int key);
    void onWebViewGeometryChangeRequest(int key, int x, int y, int w, int h);
    void onWebViewVisibleChangeRequest(int key, bool value);
    void onWebViewTransparentBackgroundChangeRequest(int key, bool value);
    void onWebViewStackUnderRequest(int topKey, int underKey);
    void onWebViewStackOnTopRequest(int key);
    void onWebViewNextRequest(int key);
    void onWebViewPrevRequest(int key);
    void onWebViewForwardHistoryRequest(int key);
    void onWebViewBackwardHistoryRequest(int key);
    void onKeyboardShowRequest(void);
    void onKeyboardHideRequest(void);

    // App ←/→ Server
    void onWebViewURLChanged(int key, const QString &value);
    void onWebViewHostnameChanged(int key, const QString &value);
    void onWebViewURLChangeRequested(int key, const QString &value);

    // Server → App
    void onCertificateInvalid(int key, const QUrl &url);
    void onWebViewTitleChanged(int key, const QString &value);
    void onWebViewLoadProgressChanged(int key, int value);
    void onWebViewForwardHistoryRequested(int key, const QStringList);
    void onWebViewBackwardHistoryRequested(int key, const QStringList);
    void onKeyboardShown(int height);
    void onKeyboardHidden(void);

    // Other
    void onSetKeyboardEnabledRequested(bool enabled);
};
