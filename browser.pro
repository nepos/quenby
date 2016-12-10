#-------------------------------------------------
#
# Project created by QtCreator 2016-12-01T13:47:59
#
#-------------------------------------------------

QT += core gui webenginewidgets network websockets webchannel

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = browser
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    webpage.cpp \
    webchanneltransport.cpp \
    serverinterface.cpp

HEADERS  += mainwindow.h \
    webpage.h \
    webchanneltransport.h \
    serverinterface.h

FORMS    += mainwindow.ui

DISTFILES +=
