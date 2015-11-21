################################
##                            ##
## SAM-Solution : User Client ##
##                            ##
################################

QT += \
    qml \
    quick \
    network \
    widgets

CONFIG += \
    c++11

TEMPLATE = app

COMMON_ALL = $${PWD}/../../common
COMMON_CLIENTS = $${PWD}/../common

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment
include(deployment.pri)

RESOURCES += \
    qml.qrc

INCLUDEPATH += \
    $${COMMON_ALL}/others \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/functionalities \
    $${COMMON_ALL}/microkernel_architecture/main_controller \
    $${COMMON_CLIENTS}/microkernel_architecture/microkernel_modules/network_manager \
    microkernel_architecture/microkernel_modules/functionalities_manager \
    microkernel_architecture/internal_fcts_modules/gui/gui_controller \
    microkernel_architecture/microkernel_modules/main_controller

HEADERS += \
    $${COMMON_ALL}/others/struct_packed.h \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/InstructionBus.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstructionBusClient.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstruction.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstructionParameter.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/InstructionBuffer.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/functionalities/AFunctionalitiesManager.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/functionalities/AFunctionality.hpp \
    $${COMMON_ALL}/microkernel_architecture/main_controller/AMainController.hpp \
    $${COMMON_CLIENTS}/microkernel_architecture/microkernel_modules/network_manager/NetworkClientManager.hpp \
    microkernel_architecture/microkernel_modules/functionalities_manager/FunctionalitiesManager.hpp \
    microkernel_architecture/internal_fcts_modules/gui/gui_controller/GUIController.hpp \
    microkernel_architecture/microkernel_modules/main_controller/MainController.hpp

SOURCES += \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/InstructionBus.cpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstructionBusClient.cpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstruction.cpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstructionParameter.cpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/InstructionBuffer.cpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/functionalities/AFunctionalitiesManager.cpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/functionalities/AFunctionality.cpp \
    $${COMMON_ALL}/microkernel_architecture/main_controller/AMainController.cpp \
    $${COMMON_CLIENTS}/microkernel_architecture/microkernel_modules/network_manager/NetworkClientManager.cpp \
    microkernel_architecture/microkernel_modules/functionalities_manager/FunctionalitiesManager.cpp \
    microkernel_architecture/internal_fcts_modules/gui/gui_controller/GUIController.cpp \
    microkernel_architecture/microkernel_modules/main_controller/MainController.cpp \
    microkernel_architecture/main.cpp
