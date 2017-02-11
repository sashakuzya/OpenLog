QT += core sql testlib
QT -= gui

CONFIG += c++11

TARGET = Database
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    ../../OpenLog/database.cpp \
    test_database.cpp

HEADERS += \
    ../../OpenLog/database.h \
    ../../OpenLog/types.h
