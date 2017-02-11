QT += core testlib
QT -= gui

CONFIG += c++11

TARGET = QthLocator
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    ../../OpenLog/qthlocator.cpp \
    test_qthlocator.cpp

HEADERS += \
    ../../OpenLog/qthlocator.h
