QT += core
QT -= gui

CONFIG += c++11

TARGET = AdventureNbr_6
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

DISTFILES += \
    testdata.in \
    puzzelinput.in
