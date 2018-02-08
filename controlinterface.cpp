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

void ControlInterface::destroyWebView(int key)
{
    emit onDestroyWebViewRequested(key);
}

void ControlInterface::setWebViewUrl(int key, const QString &url)
{
    emit onWebViewURLChangeRequested(key, url);
}

void ControlInterface::setWebViewGeometry(int key, int x, int y, int w, int h)
{
    emit onWebViewGeometryChangeRequested(key, x, y, w, h);
}

void ControlInterface::setWebViewVisible(int key, bool visible)
{
    emit onWebViewVisibleChangeRequested(key, visible);
}

void ControlInterface::setWebViewTransparentBackground(int key, bool transparent)
{
    emit onWebViewTransparentBackgroundChangeRequested(key, transparent);
}

void ControlInterface::setWebViewNext(int key)
{
    emit onWebViewNextRequested(key);
}

void ControlInterface::setWebViewPrev(int key)
{
    emit onWebViewPrevRequested(key);
}

void ControlInterface::getWebViewForwardHistory(int key)
{
    emit onWebViewForwardHistoryRequestedL(key);
}

void ControlInterface::getWebViewBackwardHistory(int key)
{
    emit onWebViewBackwardHistoryRequestedL(key);
}

void ControlInterface::setWebViewStackUnder(int topKey, int underKey)
{
    emit onWebViewStackUnderRequested(topKey, underKey);
}

void ControlInterface::setWebViewStackOnTop(int key)
{
    emit onWebViewStackOnTopRequested(key);
}

void ControlInterface::showKeyboard(void)
{
    emit onKeyboardShowRequested();
}

void ControlInterface::hideKeyboard(void)
{
    emit onKeyboardHideRequested();
}
