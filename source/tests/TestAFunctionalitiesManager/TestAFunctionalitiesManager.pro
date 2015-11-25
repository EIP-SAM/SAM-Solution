######################################################################
# Automatically generated by qmake (2.01a) mer. nov. 25 20:44:48 2015
######################################################################

TARGET = TestAFunctionalitiesManager

DEFINES += SRCDIR=\\\"$$PWD/\\\"

QT	+= \
	testlib \
	network

TEMPLATE = app

CONFIG	-= app_bundle
CONFIG	+= \
	console \
	c++11

COMMON_ALL = $${PWD}/../../common

SERVER_ALL = $${PWD}/../../server

INCLUDEPATH += \
	$${COMMON_ALL}/others \
	$${COMMON_ALL}/qt_custom_extensions \
	$${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions \
	$${COMMON_ALL}/microkernel_architecture/microkernel_modules/functionalities

# Input
HEADERS += \
           $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstruction.hpp \
           $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstructionParameter.hpp \
           $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/eProgId.hpp \
           $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstructionBusClient.hpp \
           $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/InstructionBus.hpp \
           $${COMMON_ALL}/others/struct_packed.h \   
           $${COMMON_ALL}/microkernel_architecture/microkernel_modules/functionalities/AFunctionality.hpp \
           $${COMMON_ALL}/microkernel_architecture/microkernel_modules/functionalities/AFunctionalitiesManager.hpp \
           AMainController.hpp \
           BasicAFunctionality.hpp \
           BasicFunctionalitiesManager.hpp \
           MainController.hpp \
           TestAFunctionalitiesManager.hpp

SOURCES += \
           $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstruction.cpp \
           $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstructionParameter.cpp \
           $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/InstructionBus.cpp \
           $${COMMON_ALL}/microkernel_architecture/microkernel_modules/instructions/AInstructionBusClient.cpp \
           $${COMMON_ALL}/microkernel_architecture/microkernel_modules/functionalities/AFunctionality.cpp \
           $${COMMON_ALL}/microkernel_architecture/microkernel_modules/functionalities/AFunctionalitiesManager.cpp \
           AMainController.cpp \
           BasicAFunctionality.cpp \
           BasicFunctionalitiesManager.cpp \
           MainController.cpp \
           TestAFunctionalitiesManager.cpp
