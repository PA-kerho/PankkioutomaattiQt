#-------------------------------------------------
#
# Project created by QtCreator 2016-11-21T11:05:18
#
#-------------------------------------------------
QT += widgets
QT += sql
TARGET = SLNosto
TEMPLATE = lib


DEFINES += SLNOSTO_LIBRARY

SOURCES += slnosto.cpp \
    nostodialog.cpp \
    infodialog.cpp

HEADERS += slnosto.h\
        slnosto_global.h \
    nostodialog.h \
    infodialog.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    nostodialog.ui \
    infodialog.ui
