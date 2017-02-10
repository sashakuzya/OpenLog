QT += core
QT -= gui

CONFIG += c++11

TARGET = CallToLocation
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ../../OpenLog/calltolocation.cpp

HEADERS += \
    ../../OpenLog/calltolocation.h

DISTFILES += \
    ../../OpenLog/prefix.list
