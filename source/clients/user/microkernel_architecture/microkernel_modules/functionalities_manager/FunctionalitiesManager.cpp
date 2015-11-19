#include "FunctionalitiesManager.hpp"
#include "GUIController.hpp"
#include "NetworkClientManager.hpp"

//
// Constructor
//
FunctionalitiesManager::FunctionalitiesManager(QObject *parent)
    : AFunctionalitiesManager(parent)
{
}

//
// Destructor
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

//
// Instanciate the microkernel functionalities
//
void FunctionalitiesManager::_setMicrokernelFcts()
{
    _microkernelFcts << new NetworkClientManager();
}

//
// Instanciate the internal functionalities
//
void FunctionalitiesManager::_setInternalFcts()
{
    _internalFcts << new GUIController();
}

//
// Instanciate the external functionalities
//
void FunctionalitiesManager::_setExternalFcts()
{
}
