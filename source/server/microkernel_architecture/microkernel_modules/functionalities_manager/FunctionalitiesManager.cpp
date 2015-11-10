#include "FunctionalitiesManager.hpp"
#include "NetworkServerManager.hpp"

#include "HelloWorldFunctionality.hpp"

FunctionalitiesManager::FunctionalitiesManager(QObject *parent)
    : AFunctionalitiesManager(parent)
{
}

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
    _microkernelFcts << new NetworkServerManager(false);
}

void FunctionalitiesManager::_setInternalFcts()
{
}

void FunctionalitiesManager::_setExternalFcts()
{
    _externalFcts << new HelloWorldFunctionality(); // temporary
}
