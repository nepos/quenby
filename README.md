> Quenby (n.): A stubborn spot on a window which you spend twenty minutes trying to clean off before discovering it's on the other side of the glass.

# Simple kiosk browser based on Qt/QWebEngine

This project implements a simple kiosk browser that starts off displaying a [QWebEngineView](http://doc.qt.io/qt-5/qwebengineview.html)
widget that loads a given URL through a [QWebEnginePage](http://doc.qt.io/qt-5/qwebenginepage.html). Inside that page, the Javascript
context is provided a [QWebChannel](https://doc.qt.io/qt-5/qwebchannel.html) interface that allows it to interface with the kiosk browser,
open new widgets, make them load arbitrary URLs, receive callback if their URLs or HTML titles have changed etc.

# Usage
```
$ ./quenby --help
Usage: ./quenby [options]
Simple kiosk browser

Options:
  -h, --help               Displays this help.
  -w, --width              Main web view width [default: 1280].
  -i, --height             Main web view height [default: 800].
  -f, --fullscreen         Fullscreen display [default: off].
  -u, --url                Default view URL [default: http://localhost:3000/dist].
  -r, --remote-debug-port  WebEngine debug port [default: 3002].
```

# The Javascript interface

For a basic description of how to interface with a `QWebChannel` interface, please refer to the
[Qt WebChannel JavaScript API](https://doc.qt.io/qt-5/qtwebchannel-javascript.html).

The parameter passed to `new QWebChannel` should be `qt.webChannelTransport`, and the channel returned from that callback function
can be used for the interaction.

## Main widget control interface

In the main widget, the channel provides the following interface through the `main` object.
All other widgets do not have access to this channel for now.

### Function calls

* `createWebView()` creates a new web widget and returns its numerical identifier which can be used later for referral.
* `destroyWebView(index)` destroys a web widget that was previously created with `createWebView()`, referenced by its index.
  All memory used by the widget is freed, and the widget is removed from the screen.
* `setWebViewUrl(index, url)` sets the URL of the web widget with index `index` to `url`.
* `setWebViewGeometry(index, x, y, w, h)` sets the geometry of the web widget with index `index` to the given `x` and `y` positions
  and to height `h` and width `w`.
* `setWebViewVisible(index, visible)` sets the visibility of the web widget with index `index` to visible (`true`) or invisible (`false`),
  as given by the `visible` parameter.
* `setWebViewTransparentBackground(index, transparent)` makes the background of web widget with index `index` either transparent (`true`)
  or opaque (`false`), as given by the `transparent` parameter.

### Callbacks

* `onWebViewURLChanged(index, url)` is fired whenever the web widget with index `index` has changed its current URL. The new URL is passed in
  the paremeter `url`.
* `onWebViewTitleChanged(index, title)` is fired whenever the web widget with index `index` has changed its current HTML page title.
  The new title is passed in the paremeter `title`.
* `onWebViewLoadProgressChanged(index, value)` is fired whenever the web widget with index `index` changed its loading progress.
  The current progress is reported in the parameter `value`, in percentage.

# Debugging web pages

Web page debugging is enabled when the target is built in debug mode. Use a Chromium based web browser and point it to
`http://localhost:3002` while the application is running. You can override the default port with the `--debug` command line switch.

# License

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this software; If not, see <http://www.gnu.org/licenses/>.
