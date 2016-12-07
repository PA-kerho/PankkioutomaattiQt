#-------------------------------------------------
#
# Project created by QtCreator 2016-11-15T12:42:32
#
#-------------------------------------------------
QT += widgets
TARGET = SLPinKoodi
TEMPLATE = lib

DEFINES += SLPINKOODI_LIBRARY

SOURCES += slpinkoodi.cpp \
    pinkoodidialogi.cpp

HEADERS += slpinkoodi.h\
        slpinkoodi_global.h \
    pinkoodidialogi.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    pinkoodidialogi.ui
