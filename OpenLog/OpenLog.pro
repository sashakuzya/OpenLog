#-------------------------------------------------
#
# Project created by QtCreator 2017-02-10T22:19:52
#
#-------------------------------------------------

QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenLog
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calltolocation.cpp \
    qthlocator.cpp

HEADERS  += mainwindow.h \
    calltolocation.h \
    qthlocator.h

FORMS    += mainwindow.ui

DISTFILES += \
    prefix.list
