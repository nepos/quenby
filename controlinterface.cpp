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

#include "controlinterface.h"

ControlInterface::ControlInterface(QObject *parent) : QObject(parent)
{
}

int ControlInterface::createWebView()
{
	return emit onCreateWebViewRequested();
}

void ControlInterface::destroyWebView(int index)
{
	emit onDestroyWebViewRequested(index);
}

void ControlInterface::setWebViewUrl(int index, const QString &url)
{
	emit onWebViewURLChangeRequested(index, url);
}

void ControlInterface::setWebViewGeometry(int index, int x, int y, int w, int h)
{
	emit onWebViewGeometryChangeRequested(index, x, y, w, h);
}

void ControlInterface::setWebViewVisible(int index, bool visible)
{
	emit onWebViewVisibleChangeRequested(index, visible);
}

void ControlInterface::setWebViewTransparentBackground(int index, bool transparent) {
	emit onWebViewTransparentBackgroundChangeRequested(index, transparent);
}
