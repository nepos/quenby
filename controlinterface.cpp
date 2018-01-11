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

uint64_t ControlInterface::createWebView()
{
    return emit onCreateWebViewRequested();
}

void ControlInterface::destroyWebView(uint64_t key)
{
    emit onDestroyWebViewRequested(key);
}

void ControlInterface::setWebViewUrl(uint64_t key, const QString &url)
{
    emit onWebViewURLChangeRequested(key, url);
}

void ControlInterface::setWebViewGeometry(uint64_t key, int x, int y, int w, int h)
{
    emit onWebViewGeometryChangeRequested(key, x, y, w, h);
}

void ControlInterface::setWebViewVisible(uint64_t key, bool visible)
{
    emit onWebViewVisibleChangeRequested(key, visible);
}

void ControlInterface::setWebViewTransparentBackground(uint64_t key, bool transparent)
{
    emit onWebViewTransparentBackgroundChangeRequested(key, transparent);
}

void ControlInterface::stackUnder(uint64_t topKey, uint64_t underKey)
{
    emit onWebViewStackUnder(topKey, underKey);
}

void ControlInterface::stackOnTop(uint64_t key)
{
    emit onWebViewStackOnTop(key);
}
