###########################
##                       ##
## SAM-Solution : Server ##
##                       ##
###########################

QT       -= gui
QT       += core \
            network \
            widgets

TARGET   = server

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

COMMON_ALL = $${PWD}/../common

INCLUDEPATH += \
    $${COMMON_ALL} \
    $${COMMON_ALL}/qt_extensions \
    trunk/microkernel/main_controller \
    trunk/microkernel/network

SOURCES += \
    trunk/main.cpp \
    trunk/microkernel/network/NetworkServer.cpp \
    trunk/microkernel/main_controller/MainController.cpp

HEADERS += \
    $${COMMON_ALL}/HelloWorld.hpp \
    trunk/microkernel/network/NetworkServer.hpp \
    trunk/microkernel/main_controller/MainController.hpp
