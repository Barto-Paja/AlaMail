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
    myclasswin.cpp \
    formstudents.cpp

HEADERS  += mainwindow.h \
    querybank.h \
    profile.h \
    myclasswin.h \
    formstudents.h

FORMS    += mainwindow.ui \
    profile.ui \
    myclasswin.ui \
    formstudents.ui

RESOURCES += \
    zasoby.qrc

DISTFILES +=
