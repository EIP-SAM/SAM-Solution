#include "GUIController.hpp"

GUIController::GUIController()
    : AFunctionality(GUI), _qmlEngine(this)
{
}

GUIController::~GUIController()
{
}

void GUIController::_run()
{
    init();
}

inline void GUIController::init()
{
    _qmlEngine.load(QUrl(QStringLiteral("qrc:/microkernel_architecture/internal_fcts_modules/gui/qml/main.qml")));
}
