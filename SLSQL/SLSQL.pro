#-------------------------------------------------
#
# Project created by QtCreator 2016-11-15T12:32:21
#
#-------------------------------------------------

QT       -= gui
QT       += core
QT       += sql





TARGET = SLSQL
TEMPLATE = lib

DEFINES += SLSQL_LIBRARY

SOURCES += slsql.cpp

HEADERS += slsql.h\
        slsql_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
