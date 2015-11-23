#-------------------------------------------------
#
# Project created by QtCreator 2015-11-22T15:11:00
#
#-------------------------------------------------

TARGET = TestInstructionBus

DEFINES += SRCDIR=\\\"$$PWD/\\\"

QT       -= gui
QT       += testlib

CONFIG   -= app_bundle
CONFIG   += console \
            c++11

TEMPLATE = app

COMMON_ALL = $${PWD}/../../common

INCLUDEPATH += \
    $${COMMON_ALL}/others \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions

HEADERS += \
    $${COMMON_ALL}/others/struct_packed.h \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstruction.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstructionParameter.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstructionBusClient.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/InstructionBus.hpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/eProgId.hpp \
    FooBusClient.hpp \
    BarBusClient.hpp

SOURCES += \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstruction.cpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstructionParameter.cpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstructionBusClient.cpp \
    $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/InstructionBus.cpp \
    TestInstructionBus.cpp \
    FooBusClient.cpp \
    BarBusClient.cpp
