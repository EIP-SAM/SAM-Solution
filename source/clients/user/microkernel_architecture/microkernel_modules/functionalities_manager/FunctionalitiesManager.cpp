#include "FunctionalitiesManager.hpp"
#include "NetworkClientManager.hpp"
#include "GUIController.hpp"

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

inline void FunctionalitiesManager::_setMicrokernelFcts()
{
    _microkernelFcts << new NetworkClientManager();
}

inline void FunctionalitiesManager::_setInternalFcts()
{
    AFunctionality *fct = NULL;

    fct = new GUIController();
    fct->setThreaded(false);
    _internalFcts << fct;
}

inline void FunctionalitiesManager::_setExternalFcts()
{
}
