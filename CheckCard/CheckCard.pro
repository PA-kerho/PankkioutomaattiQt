#-------------------------------------------------
#
# Project created by QtCreator 2016-11-16T12:09:10
#
#-------------------------------------------------

QT       -= gui
QT += sql

TARGET = CheckCard
TEMPLATE = lib

DEFINES += CHECKCARD_LIBRARY

SOURCES += checkcard.cpp

HEADERS += checkcard.h\
        checkcard_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
