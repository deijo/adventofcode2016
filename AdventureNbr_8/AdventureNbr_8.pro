QT += core
QT -= gui

CONFIG += c++11

TARGET = AdventureNbr_8
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

DISTFILES += \
    puzzelinput.in \
    testinput.in
