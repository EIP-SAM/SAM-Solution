#include "FunctionalitiesManager.hpp"
#include "NetworkServerManager.hpp"

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
    AFunctionality *fct = NULL;

    fct = new NetworkServerManager();
    fct->setThreaded(false);
    _microkernelFcts << fct;
}

void FunctionalitiesManager::_setInternalFcts()
{
}

void FunctionalitiesManager::_setExternalFcts()
{
}
