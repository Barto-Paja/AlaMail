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
    f_dodajucznia.cpp

HEADERS  += mainwindow.h \
    querybank.h \
    f_dodajucznia.h

FORMS    += mainwindow.ui \
    f_dodajucznia.ui

RESOURCES += \
    zasoby.qrc
