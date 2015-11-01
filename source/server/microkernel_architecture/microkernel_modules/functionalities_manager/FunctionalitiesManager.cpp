#include "FunctionalitiesManager.hpp"
#include "NetworkServer.hpp"
#include "NetworkClient.hpp"

//
// Constructor : does nothing
//
FunctionalitiesManager::FunctionalitiesManager()
{
}

//
// Destructor : does nothing
//
FunctionalitiesManager::~FunctionalitiesManager()
{
}

//
// instanciates the various functionalities
// in the three QLists
// don't forget to include the header of
// the functionality
//
void FunctionalitiesManager::_setFcts()
{
    _microkernelFcts << new NetworkServer();
    _microkernelFcts << new NetworkClient();
}
