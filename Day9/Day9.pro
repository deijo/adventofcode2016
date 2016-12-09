QT += core
QT -= gui

CONFIG += c++11

TARGET = Day9
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

DISTFILES += \
    puzzelinput.in \
    testinput \
    testinput2
