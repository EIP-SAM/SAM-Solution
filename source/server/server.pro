#-------------------------------------------------
#
# Project created by QtCreator 2015-07-31T09:42:12
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

COMMON_ALL = $${PWD}/../common

INCLUDEPATH += $${COMMON_ALL}

SOURCES += main.cpp

HEADERS += \
    $${COMMON_ALL}/HelloWorld.hpp
