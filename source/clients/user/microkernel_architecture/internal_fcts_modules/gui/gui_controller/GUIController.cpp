#include "GUIController.hpp"

GUIController::GUIController(QObject *parent)
    : AFunctionality(parent), _qmlEngine(this)
{
}

GUIController::~GUIController()
{
}

void GUIController::run()
{
    init();
}

void GUIController::init()
{
    _qmlEngine.load(QUrl(QStringLiteral("qrc:/microkernel_architecture/internal_fcts_modules/gui/qml/main.qml")));
}
