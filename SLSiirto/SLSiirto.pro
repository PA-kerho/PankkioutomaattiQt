#-------------------------------------------------
#
# Project created by QtCreator 2016-12-13T09:46:17
#
#-------------------------------------------------
QT += widgets
QT += sql
TARGET = SLSiirto
TEMPLATE = lib

DEFINES += SLSIIRTO_LIBRARY

SOURCES += slsiirto.cpp \
    siirtodialog.cpp

HEADERS += slsiirto.h\
        slsiirto_global.h \
    siirtodialog.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    siirtodialog.ui
