#-------------------------------------------------
#
# Project created by QtCreator 2017-02-10T22:19:52
#
#-------------------------------------------------

QT       += core gui sql testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenLog
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calltolocation.cpp \
    qthlocator.cpp \
    database.cpp \
    test_database.cpp

HEADERS  += mainwindow.h \
    calltolocation.h \
    qthlocator.h \
    database.h \
    types.h

FORMS    += mainwindow.ui

DISTFILES += \
    prefix.list
