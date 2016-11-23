#-------------------------------------------------
#
# Project created by QtCreator 2016-11-21T10:59:59
#
#-------------------------------------------------

TARGET = SLELasku
TEMPLATE = lib

DEFINES += SLELASKU_LIBRARY

SOURCES += slelasku.cpp

HEADERS += slelasku.h\
        slelasku_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
