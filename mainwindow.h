/***
  Copyright (c) 2016 Nepos GmbH

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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QWebEngineView>
#include <QWebChannel>
#include <QtWebSockets/QWebSocketServer>

#include "controlinterface.h"
#include "webpage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QUrl mainViewUrl, int mainViewWidth, int mainViewHeight, QWidget *parent = Q_NULLPTR);
    ~MainWindow();

private:
    QWidget *window;

    void createControlInterface();
    QWebChannel controlChannel;
    ControlInterface controlInterface;

    QList<QWebEngineView*> views;

    QWebEngineView *addWebView();
    QWebEngineView *lookupWebView(int index);
};

#endif // MAINWINDOW_H
