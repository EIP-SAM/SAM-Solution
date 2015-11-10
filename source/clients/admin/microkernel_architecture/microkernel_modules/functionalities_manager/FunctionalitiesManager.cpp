#include "FunctionalitiesManager.hpp"
#include "GUIController.hpp"
#include "NetworkClientManager.hpp"

#include "HelloWorldFunctionality.hpp"

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
    _internalFcts << new GUIController();
}

void FunctionalitiesManager::_setExternalFcts()
{
    _externalFcts << new HelloWorldFunctionality(); // temporary
}
