######################################################################
# Automatically generated by qmake (3.0) lun. oct. 5 11:47:33 2015
######################################################################

TARGET = TestANetworkInstruction

TEMPLATE = app

CONFIG   -= app_bundle
CONFIG   += console c++11

QT       -= gui
QT       += testlib

INCLUDEPATH += \
    ../../common/microkernel_architecture/microkernel_modules/instructions

HEADERS += \
    ../../common/microkernel_architecture/microkernel_modules/instructions/AInstructionModel.hpp \
    ../../common/microkernel_architecture/microkernel_modules/instructions/ANetworkInstruction.hpp \
    TestANetworkInstruction.hpp

SOURCES += \
    ../../common/microkernel_architecture/microkernel_modules/instructions/ANetworkInstruction.cpp \
    ../../common/microkernel_architecture/microkernel_modules/instructions/AInstructionModel.cpp \
    TestANetworkInstruction.cpp
