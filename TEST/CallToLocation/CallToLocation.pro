QT += core testlib
QT -= gui

CONFIG += c++11

TARGET = CallToLocation
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    ../../OpenLog/calltolocation.cpp \
    test_calltolocation.cpp

HEADERS += \
    ../../OpenLog/calltolocation.h

DISTFILES += \
    ../../OpenLog/prefix.list
