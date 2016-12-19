#-------------------------------------------------
#
# Project created by QtCreator 2016-12-15T11:21:56
#
#-------------------------------------------------

QT += widgets
QT += sql

TARGET = SLSaldo2
TEMPLATE = lib

DEFINES += SLSALDO2_LIBRARY

SOURCES += slsaldo2.cpp \
    saldodialog.cpp

HEADERS += slsaldo2.h\
        slsaldo2_global.h \
    saldodialog.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    saldodialog.ui
