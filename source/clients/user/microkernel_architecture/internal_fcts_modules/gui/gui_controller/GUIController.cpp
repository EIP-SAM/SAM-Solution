#include "GUIController.hpp"

//
// Constructor
//
GUIController::GUIController()
    : AFunctionality(GUI, false), _qmlEngine(this)
{
}

//
// Destructor
//
GUIController::~GUIController()
{
}

//
// Entry point of the AFunctionality
//
void GUIController::_run()
{
    init();
}

//
// Functionality initialization
//
void GUIController::init()
{
    _qmlEngine.load(QUrl(QStringLiteral("qrc:/microkernel_architecture/internal_fcts_modules/gui/qml/main.qml")));
}
