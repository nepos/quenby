#-------------------------------------------------
#
# Project created by QtCreator 2017-12-01T13:47:59
#
#-------------------------------------------------

QT += core gui network webenginewidgets webchannel quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = quenby
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    webpage.cpp \
    controlinterface.cpp

HEADERS  += \
    mainwindow.h \
    webpage.h \
    controlinterface.h

FORMS    +=

DISTFILES += inputpanel.qml

RESOURCES += \
    resources.qrc
