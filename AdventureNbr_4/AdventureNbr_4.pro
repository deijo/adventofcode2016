QT += core
QT -= gui

CONFIG += c++11

TARGET = AdventureNbr_4
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

DISTFILES += \
    testdata.in \
    puzzeldata.in \
    testdata4B.in
