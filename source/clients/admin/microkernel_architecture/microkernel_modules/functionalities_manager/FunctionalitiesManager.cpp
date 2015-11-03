#include "FunctionalitiesManager.hpp"
#include "GUIController.hpp"
#include "NetworkClientManager.hpp"

//
// Constructor : does nothing
//
FunctionalitiesManager::FunctionalitiesManager(QObject *parent)
    : AFunctionalitiesManager(parent)
{
}

//
// Destructor : does nothing
//
FunctionalitiesManager::~FunctionalitiesManager()
{
}

//
// Instanciate the various functionalities
//
void FunctionalitiesManager::_setFcts()
{
    _setMicrokernelFcts();
    _setInternalFcts();
    _setExternalFcts();
}

void FunctionalitiesManager::_setMicrokernelFcts()
{
    _microkernelFcts << new NetworkClientManager();
}

void FunctionalitiesManager::_setInternalFcts()
{
    AFunctionality *fct = NULL;

    fct = new GUIController();
    fct->setThreaded(false);
    _internalFcts << fct;
}

void FunctionalitiesManager::_setExternalFcts()
{
}
