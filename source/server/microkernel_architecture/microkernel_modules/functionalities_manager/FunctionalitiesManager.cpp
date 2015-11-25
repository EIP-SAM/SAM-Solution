#include "FunctionalitiesManager.hpp"
#include "NetworkServerManager.hpp"

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
    _microkernelFcts << new NetworkServerManager(42042);
}

//
// Instanciate the internal functionalities
//
void FunctionalitiesManager::_setInternalFcts()
{
}

//
// Instanciate the external functionalities
//
void FunctionalitiesManager::_setExternalFcts()
{
}
