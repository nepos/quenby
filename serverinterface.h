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

    Q_PROPERTY(QString  browserURL          MEMBER browserURL           NOTIFY onBrowserURLChanged)
    Q_PROPERTY(QString  browserTitle        MEMBER browserTitle         NOTIFY onBrowserTitleChanged)
    Q_PROPERTY(bool     browserVisible      MEMBER browserVisible       NOTIFY onBrowserVisibleChanged)
    Q_PROPERTY(int      browserLoadProgress MEMBER browserLoadProgress  NOTIFY onbrowserLoadProgressChanged)

signals:
    void onBrowserURLChanged(const QString &value);
    void onBrowserTitleChanged(const QString &value);
    void onBrowserVisibleChanged(bool value);
    void onbrowserLoadProgressChanged(int value);

private:
    QString browserURL;
    QString browserTitle;
    bool    browserVisible;
    int     browserLoadProgress;
};

#endif // SERVERINTERFACE_H
