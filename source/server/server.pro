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

CONFIG   -= app_bundle
CONFIG   += console \
            c++11

TEMPLATE = app

COMMON_ALL = $${PWD}/../common

INCLUDEPATH += \
    $${COMMON_ALL}/qt_custom_extensions \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/functionalities \
    microkernel_architecture/microkernel_modules/main_controller \
    microkernel_architecture/microkernel_modules/functionalities_manager \
    microkernel_architecture/microkernel_modules/network_manager

HEADERS += \
    $${COMMON_ALL}/qt_custom_extensions/_QFile.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstructionModel.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/ANetworkInstruction.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/functionalities/AFunctionalitiesManager.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/functionalities/AFunctionality.hpp \
    microkernel_architecture/microkernel_modules/functionalities_manager/FunctionalitiesManager.hpp \
    microkernel_architecture/microkernel_modules/network_manager/NetworkServer.hpp \
    microkernel_architecture/microkernel_modules/main_controller/MainController.hpp \
    microkernel_architecture/microkernel_modules/network_manager/NetworkClient.hpp

SOURCES += \
    $${COMMON_ALL}/qt_custom_extensions/_QFile.cpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstructionModel.cpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/ANetworkInstruction.cpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/functionalities/AFunctionalitiesManager.cpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/functionalities/AFunctionality.cpp \
    microkernel_architecture/main.cpp \
    microkernel_architecture/microkernel_modules/network_manager/NetworkServer.cpp \
    microkernel_architecture/microkernel_modules/functionalities_manager/FunctionalitiesManager.cpp \
    microkernel_architecture/microkernel_modules/main_controller/MainController.cpp \
    microkernel_architecture/microkernel_modules/network_manager/NetworkClient.cpp
