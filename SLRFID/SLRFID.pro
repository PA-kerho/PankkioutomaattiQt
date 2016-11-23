#-------------------------------------------------
#
# Project created by QtCreator 2016-11-15T11:42:44
#
#-------------------------------------------------

QT       -= gui

TARGET = SLRFID
TEMPLATE = lib

DEFINES += SLRFID_LIBRARY

SOURCES += slrfid.cpp

HEADERS += slrfid.h\
        slrfid_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
