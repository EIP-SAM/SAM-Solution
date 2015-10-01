###############################
##                           ##
## SAM-Solution : User Admin ##
##                           ##
###############################

QT += \
    qml \
    quick \
    network \
    widgets

TEMPLATE = app

COMMON_ALL = $${PWD}/../../common

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment
include(deployment.pri)

INCLUDEPATH += \
    $${COMMON_ALL} \
    trunk/microkernel/main_controller \
    trunk/internal_fcts/gui/gui_controller

SOURCES += \
    trunk/main.cpp \
    trunk/microkernel/main_controller/MainController.cpp \
    trunk/internal_fcts/gui/gui_controller/GUIController.cpp

RESOURCES += \
    qml.qrc

HEADERS += \
    $${COMMON_ALL}/HelloWorld.hpp \
    trunk/microkernel/main_controller/MainController.hpp \
    trunk/internal_fcts/gui/gui_controller/GUIController.hpp
