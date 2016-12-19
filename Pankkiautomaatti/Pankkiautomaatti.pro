#-------------------------------------------------
#
# Project created by QtCreator 2016-11-15T11:44:30
#
#-------------------------------------------------

QT       += core gui
QT += serialport
QT += sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pankkiautomaatti
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    actiondialog.cpp

HEADERS  += mainwindow.h \
    actiondialog.h

FORMS    += mainwindow.ui \
    actiondialog.ui

unix:!macx: LIBS += -L$$PWD/../build-SLRFID-Desktop-Release/ -lSLRFID

INCLUDEPATH += $$PWD/../SLRFID
DEPENDPATH += $$PWD/../SLRFID

unix:!macx: LIBS += -L$$PWD/../build-SLNosto-Desktop-Release/ -lSLNosto

INCLUDEPATH += $$PWD/../SLNosto
DEPENDPATH += $$PWD/../SLNosto

unix:!macx: LIBS += -L$$PWD/../build-SLeLasku-Desktop-Release/ -lSLeLasku

INCLUDEPATH += $$PWD/../SLeLasku
DEPENDPATH += $$PWD/../SLeLasku

unix:!macx: LIBS += -L$$PWD/../build-SLSaldo2-Desktop-Release/ -lSLSaldo2

INCLUDEPATH += $$PWD/../SLSaldo2
DEPENDPATH += $$PWD/../SLSaldo2

unix:!macx: LIBS += -L$$PWD/../build-SLPinKoodi-Desktop-Release/ -lSLPinKoodi

INCLUDEPATH += $$PWD/../SLPinKoodi
DEPENDPATH += $$PWD/../SLPinKoodi

unix:!macx: LIBS += -L$$PWD/../build-SLSQL-Desktop-Release/ -lSLSQL

INCLUDEPATH += $$PWD/../SLSQL
DEPENDPATH += $$PWD/../SLSQL

unix:!macx: LIBS += -L$$PWD/../build-SLSiirto-Desktop-Release/ -lSLSiirto

INCLUDEPATH += $$PWD/../SLSiirto
DEPENDPATH += $$PWD/../SLSiirto
