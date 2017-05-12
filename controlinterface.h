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

#ifndef CONTROLINTERFACE_H
#define CONTROLINTERFACE_H

#include <QObject>

class ControlInterface : public QObject
{
    Q_OBJECT

public:
    explicit ControlInterface(QObject *parent = 0);

public slots:
	int createWebView();
	void destroyWebView(int index);
	void setWebViewUrl(int index, const QString &url);
	void setWebViewGeometry(int index, int x, int y, int w, int h);
	void setWebViewVisible(int index, bool visible);
	void setWebViewTransparentBackground(int index, bool transparent);

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

#endif // CONTROLINTERFACE_H
