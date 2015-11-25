###########################
##                       ##
## SAM-Solution : Server ##
##                       ##
###########################

QT -= \
    gui

QT += \
    core \
    network \
    widgets

TARGET = server

CONFIG -= \
    app_bundle

CONFIG += \
    console \
    c++11

TEMPLATE = app

COMMON_ALL = $${PWD}/../common

INCLUDEPATH += \
    $${COMMON_ALL}/others \
    $${COMMON_ALL}/qt_custom_extensions \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/functionalities \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/network_manager \
    $${COMMON_ALL}/microkernel_architecture/main_controller \
    microkernel_architecture/microkernel_modules/functionalities_manager \
    microkernel_architecture/microkernel_modules/network_manager \
    microkernel_architecture/microkernel_modules/main_controller

HEADERS += \
    $${COMMON_ALL}/others/struct_packed.h \
    $${COMMON_ALL}/qt_custom_extensions/_QFile.hpp \
    $${COMMON_ALL}/qt_custom_extensions/_QTcpServer.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/InstructionBus.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstructionBusClient.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstruction.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstructionParameter.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/InstructionBuffer.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/eProgId.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/functionalities/AFunctionalitiesManager.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/functionalities/AFunctionality.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/network_manager/ANetworkManager.hpp \
    $${COMMON_ALL}/microkernel_architecture/main_controller/AMainController.hpp \
    microkernel_architecture/microkernel_modules/functionalities_manager/FunctionalitiesManager.hpp \
    microkernel_architecture/microkernel_modules/network_manager/NetworkServerManager.hpp \
    microkernel_architecture/microkernel_modules/network_manager/NetworkClient.hpp \
    microkernel_architecture/microkernel_modules/main_controller/MainController.hpp

SOURCES += \
    $${COMMON_ALL}/qt_custom_extensions/_QFile.cpp \
    $${COMMON_ALL}/qt_custom_extensions/_QTcpServer.cpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/InstructionBus.cpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstructionBusClient.cpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstruction.cpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstructionParameter.cpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/InstructionBuffer.cpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/functionalities/AFunctionalitiesManager.cpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/functionalities/AFunctionality.cpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/network_manager/ANetworkManager.cpp \
    $${COMMON_ALL}/microkernel_architecture/main_controller/AMainController.cpp \
    microkernel_architecture/microkernel_modules/functionalities_manager/FunctionalitiesManager.cpp \
    microkernel_architecture/microkernel_modules/network_manager/NetworkServerManager.cpp \
    microkernel_architecture/microkernel_modules/network_manager/NetworkClient.cpp \
    microkernel_architecture/microkernel_modules/main_controller/MainController.cpp \
    microkernel_architecture/main.cpp
