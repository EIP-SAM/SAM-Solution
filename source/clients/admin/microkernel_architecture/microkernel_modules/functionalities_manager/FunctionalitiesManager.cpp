#include "FunctionalitiesManager.hpp"
#include "GUIController.hpp"
#include "NetworkClientManager.hpp"

//
// Constructor : does nothing
//
FunctionalitiesManager::FunctionalitiesManager(QObject *parent) : AFunctionalitiesManager(parent)
{
}

//
// Destructor : does nothing
//
FunctionalitiesManager::~FunctionalitiesManager()
{
}

//
// instanciate the various functionalities
//
void FunctionalitiesManager::_setFcts()
{
    _microkernelFcts << new NetworkClientManager();
    _internalFcts << new GUIController();
}
