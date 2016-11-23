#-------------------------------------------------
#
# Project created by QtCreator 2016-11-23T11:12:27
#
#-------------------------------------------------
QT += widgets
QT += sql
TARGET = SLeLasku
TEMPLATE = lib

DEFINES += SLELASKU_LIBRARY

SOURCES += slelasku.cpp \
    elaskudialog.cpp

HEADERS += slelasku.h\
        slelasku_global.h \
    elaskudialog.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    elaskudialog.ui
