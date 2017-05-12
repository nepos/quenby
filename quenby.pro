#-------------------------------------------------
#
# Project created by QtCreator 2017-12-01T13:47:59
#
#-------------------------------------------------

QT += core gui network webenginewidgets webchannel quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = quenby
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    controlinterface.cpp \
    webenginepage.cpp

HEADERS  += \
    mainwindow.h \
    controlinterface.h \
    webenginepage.h

FORMS    +=

DISTFILES += inputpanel.qml

RESOURCES += \
    resources.qrc
