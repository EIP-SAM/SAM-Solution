#include "GUIController.hpp"

GUIController::GUIController(QObject *parent)
    : QObject(parent), _qmlEngine(parent)
{
}

GUIController::~GUIController()
{
}

void GUIController::init()
{
    _qmlEngine.load(QUrl(QStringLiteral("qrc:/trunk/internal_fcts/gui/qml/main.qml")));
}
