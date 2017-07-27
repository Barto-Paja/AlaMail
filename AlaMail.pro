#-------------------------------------------------
#
# Project created by QtCreator 2017-04-03T19:49:15
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AlaMail
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    querybank.cpp \
    profile.cpp \
    myclasswin.cpp

HEADERS  += mainwindow.h \
    querybank.h \
    profile.h \
    myclasswin.h

FORMS    += mainwindow.ui \
    profile.ui \
    myclasswin.ui

RESOURCES += \
    zasoby.qrc

DISTFILES +=
